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
#ifndef COORDINATOR_H_
#define COORDINATOR_H_

#include <QObject>
#include <QString>
#include <QUrl>

/// Coordinates the UI.
/// Receives messages from all components such as lookup edit text and web view,
/// and ensures all the components are synchronized.
class Coordinator : public QObject
{
  Q_OBJECT
public:
  /// Standard constructor.
  /// @param parent
  ///   Parent window is used to access other components to rule them.
  Coordinator(QObject *parent);

  /// State of the application.
  typedef enum {
    Initial,
    TextEnteredToLookup,
    LocalLinkClickedInView,
    LocalLinkClickedInRelatedPagesPanel,
    LocalLinkClickedInInterestingPagesPanel,
    CategoryClickedInCategoriesPanel,
    HomeActivated
  } State;

  State state() const { return _state; }
  const QString &text() const { return _text; }

public slots:
  /// Called when user enters some text to the search text box.
  /// It does not have to be an existing entry, it can be
  /// multiple entries or bad caps or whatever.
  void textEnteredToLookup(const QString &text);
  /// We assume the headingId is valid.
  void tableOfContentsClicked(const QString &headingId);
  /// We assume the entry exist.
  void localLinkClickedInView(const QUrl &url);
  /// A local link has been activated in the interesting pages panel.
  void interestingPagesPanelClicked(const QString &entry);
  /// We assume the entry exist.
  void localLinkClickedInRelatedPagesPanel(const QString &entry);
  /// We assume the category exist.
  void categoryClickedInCategoriesPanel(const QString &entry);
  /// Request to go to the title page.
  void homeActivated();
  /// Previous or next item in the history.
  void historyActivated(const QUrl &url);
  /// User changed some setting that possibly affects the view.
  void userSettingChanged_SectionVisibility();
  /// User changed some setting that possibly affects the view.
  void userSettingChanged_Translations();

private:
  void displayTitlePage();

  State _state;
  QString _text;
};

#endif /* COORDINATOR_H_ */
