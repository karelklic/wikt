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
#include <libwikt/language.h>
#include <libwikt/debug.h>
#include <QSettings>

//===========================================================================
OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent)
{
  ui.setupUi(this);
  connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect(this, SIGNAL(accepted()), this, SLOT(saveSettings()));

  QSettings settings;
  bool translationsFolded = settings.value("translationsFolded", true).toBool();
  ui.translationsFoldedCheckBox->setCheckState(translationsFolded ? Qt::Checked : Qt::Unchecked);

  QList<QTreeWidgetItem*> alphabet;
  for (char c = 'A'; c <= 'Z'; ++c)
  {
    QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(QChar(c))));
    alphabet.append(item);
  }
  ui.translationsTree->insertTopLevelItems(0, alphabet);

  for (int i = 0; i < Language::Unknown; ++i)
  {
    Language::Type language = (Language::Type)i;
    QStringList names = Language::instance().toNames(language);
    if (names.length() == 0) continue;
    QString name = names.first();

    // Find the first A-Z character in the language name.
    // Some language names do not start with A-Z, but with '\'' or another
    // character.
    char firstChar = ' ';
    int firstCharIndex = 0;
    while (firstChar < 'A' || firstChar > 'Z')
      firstChar = name[firstCharIndex++].toUpper().toAscii();

    QTreeWidgetItem *parent = alphabet[firstChar - 'A'];
    QTreeWidgetItem *item = new QTreeWidgetItem(parent, QStringList(name));
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(0, Qt::UserRole, i);
    bool visible = Language::instance().isTranslationVisible(language);
    item->setCheckState(0, visible ? Qt::Checked : Qt::Unchecked);
  }

  foreach (QTreeWidgetItem *character, alphabet)
  {
    character->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsTristate | Qt::ItemIsEnabled);
    updateCharacterCheckState(character);
  }

  connect(ui.translationsTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(itemChanged(QTreeWidgetItem*, int)));
}

//===========================================================================
OptionsDialog::~OptionsDialog()
{
}

//===========================================================================
void OptionsDialog::saveSettings()
{
  QSettings settings;
  settings.setValue("translationsFolded", ui.translationsFoldedCheckBox->checkState() == Qt::Checked);

  for (int i = 0; i < ui.translationsTree->topLevelItemCount(); ++i)
  {
    QTreeWidgetItem *character = ui.translationsTree->topLevelItem(i);
    for (int j = 0; j < character->childCount(); ++j)
    {
      QTreeWidgetItem *item = character->child(j);
      Language::Type language = (Language::Type)item->data(0, Qt::UserRole).toInt();
      Language::instance().setTranslationVisible(language, item->checkState(0) == Qt::Checked);
    }
  }

  MainWindow::instance()->coordinator()->userSettingChanged_Translations();
}

//===========================================================================
void OptionsDialog::itemChanged(QTreeWidgetItem *item, int /*column*/)
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
void OptionsDialog::updateCharacterCheckState(QTreeWidgetItem *character)
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

