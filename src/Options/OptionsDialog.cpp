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
#include "OptionsDialog.h"
#include "../Wiki/Language.h"
#include "../MainWindow/MainWindow.h"
#include "../MainWindow/Coordinator.h"
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
  ui.translationsFoldedCheckBox->setCheckState(
      translationsFolded ? Qt::Checked : Qt::Unchecked);

  for (int i = 0; i < Language::Unknown; ++i)
  {
    Language::Type language = (Language::Type)i;
    QString name = Language::instance().toTranslationSectionName(language);
    if (name.length() == 0) continue;

    QListWidgetItem *item = new QListWidgetItem(name, ui.translationList);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(Qt::UserRole, i);
    bool visible = Language::instance().isTranslationVisible(language);
    item->setCheckState(visible ? Qt::Checked : Qt::Unchecked);
  }
}

//===========================================================================
OptionsDialog::~OptionsDialog()
{
}

//===========================================================================
void OptionsDialog::saveSettings()
{
  QSettings settings;
  settings.setValue("translationsFolded",
      ui.translationsFoldedCheckBox->checkState() == Qt::Checked);

  for (int i = 0; i < ui.translationList->count(); ++i)
  {
    QListWidgetItem *item = ui.translationList->item(i);
    Language::Type language = (Language::Type)item->data(Qt::UserRole).toInt();
    Language::instance().setTranslationVisible(language,
        item->checkState() == Qt::Checked);
  }

  MainWindow::instance()->coordinator()->userSettingChanged_Translations();
}
