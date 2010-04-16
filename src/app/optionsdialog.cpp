/* This file is part of Wikt.
 *
 * Wikt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Wikt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wikt. If not, see <http://www.gnu.org/licenses/>.
 */
#include "optionsdialog.h"
#include "mainwindow.h"
#include "coordinator.h"
#include <libwikt/languages.h>
#include <libwikt/debug.h>
#include <QSettings>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QPushButton>
#include <QHeaderView>

//===========================================================================
OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent)
{
  resize(332, 376);
  setWindowTitle(tr("Options"));
  connect(this, SIGNAL(accepted()), this, SLOT(saveSettings()));

  _save = new QPushButton(this);
  _save->setGeometry(QRect(230, 340, 92, 28));
  _save->setText(tr("Save"));
  connect(_save, SIGNAL(clicked()), this, SLOT(accept()));

  _cancel = new QPushButton(this);
  _cancel->setGeometry(QRect(120, 340, 92, 28));
  _cancel->setText(tr("Cancel"));
  connect(_cancel, SIGNAL(clicked()), this, SLOT(reject()));

  _transVisible = new QCheckBox(this);
  _transVisible->setGeometry(QRect(10, 20, 311, 23));
  _transVisible->setText(tr("Translation lists visible (unfolded)"));
  QSettings settings;
  bool tvisible = settings.value("translationsVisible", false).toBool();
  _transVisible->setCheckState(tvisible ? Qt::Checked : Qt::Unchecked);

  _transTree = new QTreeWidget(this);
  QTreeWidgetItem *item = new QTreeWidgetItem();
  item->setText(0, QString::fromUtf8("1"));
  _transTree->setHeaderItem(item);
  _transTree->setGeometry(QRect(10, 50, 311, 281));
  _transTree->header()->setVisible(false);

  /* Insert the alphabet A-Z. */
  QMap<QChar, QTreeWidgetItem*> alphabet;

  /* Insert the languages. */
  struct language *language = languages;
  while (language)
    {
      /* Skip languages without localized name. */
      if (!language->name)
        {
          language = language->next;
          continue;
        }

      QString name = QString::fromUtf8(language->name);
      QChar firstChar = name[0];
      QTreeWidgetItem *parent = NULL;
      if (!alphabet.contains(firstChar))
        {
          parent = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(firstChar)));
          alphabet.insert(firstChar, parent);
        }
      else
        parent = alphabet[firstChar];

      QTreeWidgetItem *item = new QTreeWidgetItem(parent, QStringList(name));
      item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
      /* Use the ISO639-3 code as the unique identifier. */
      item->setData(0, Qt::UserRole, language->iso639_3_code);
      // TODO:bool visible = Language::instance().isTranslationVisible(language);
      bool visible = true;
      item->setCheckState(0, visible ? Qt::Checked : Qt::Unchecked);
      language = language->next;
    }

  _transTree->insertTopLevelItems(0, alphabet.values());
  foreach (QTreeWidgetItem *character, alphabet)
    {
      character->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsTristate | Qt::ItemIsEnabled);
      updateCharacterCheckState(character);
    }

  connect(_transTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)),
	  this, SLOT(itemChanged(QTreeWidgetItem*, int)));
}

//===========================================================================
OptionsDialog::~OptionsDialog()
{
}

//===========================================================================
void
OptionsDialog::saveSettings()
{
  QSettings settings;
  settings.setValue("translationsVisible", _transVisible->checkState() == Qt::Checked);

  for (int i = 0; i < _transTree->topLevelItemCount(); ++i)
    {
      QTreeWidgetItem *character = _transTree->topLevelItem(i);
      for (int j = 0; j < character->childCount(); ++j)
        {
          QTreeWidgetItem *item = character->child(j);
          /* TO BE FIXED
             Language::Type language = (Language::Type)item->data(0, Qt::UserRole).toInt();
             Language::instance().setTranslationVisible(language, item->checkState(0) == Qt::Checked);
          */
        }
    }

  MainWindow::instance()->coordinator()->userSettingChanged_Translations();
}

//===========================================================================
void
OptionsDialog::itemChanged(QTreeWidgetItem *item, int /*column*/)
{
  // If it is a language node.
  if (item->childCount() == 0)
    {
      // Update the parent character node check status.
      updateCharacterCheckState(item->parent());
      return;
    }

  // Now we know it is a character node.
  if (item->checkState(0) == Qt::PartiallyChecked) return;
  for (int i = 0; i < item->childCount(); ++i)
    item->child(i)->setCheckState(0, item->checkState(0));
}

//===========================================================================
void
OptionsDialog::updateCharacterCheckState(QTreeWidgetItem *character)
{
  Qt::CheckState state = Qt::Checked;
  bool hasChecked = false;
  for (int i = 0; i < character->childCount(); ++i)
    {
      Qt::CheckState child = character->child(i)->checkState(0);
      if (child == Qt::Unchecked)
        state = Qt::PartiallyChecked;
      else
        hasChecked = true;
    }
  if (!hasChecked)
    state = Qt::Unchecked;

  if (character->checkState(0) != state)
    character->setCheckState(0, state);
}
