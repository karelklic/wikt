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
#include "MenuBar.h"
#include "MainWindow.h"
#include "Coordinator.h"
#include "FindPanel.h"
#include "WebView/WebView.h"
#include "../Debug/HtmlSourceView.h"
#include "../Debug/WikiProcessingView.h"
#include "../Debug/WikiSourceView.h"
#include "../Debug/XmlSourceView.h"
#include "../Debug/UnitTest/UnitTestDialog.h"
#include "../Version.h"
#include "../DictionaryFile/Format1ToFormat2/Format1ToFormat2Dialog.h"
#include "../DictionaryFile/Format2ToFormat3/Format2ToFormat3Dialog.h"
#include "../DictionaryFile/Format3ToFormat4/Format3ToFormat4Dialog.h"
#include "../Media/MediaDownloaderDialog.h"
#include "../Media/ImageResizerDialog.h"
#include "../Media/MediaPackerDialog.h"
#include "../Wiki/Tree/Heading/Heading.h"
#include "../Options/OptionsDialog.h"
#include <QMessageBox>

//===========================================================================
MenuBar::MenuBar(MainWindow *parent) : QMenuBar(parent)
{
  this->_parent = parent;

  //
  // File
  //
  _quitAct = new QAction(tr("&Quit"), this);
  _quitAct->setShortcut(tr("Ctrl+Q"));
  _quitAct->setStatusTip(tr("Quit the application"));
  connect(_quitAct, SIGNAL(triggered()), parent, SLOT(close()));

  //
  // Edit
  //
  _cut = parent->webView()->pageAction(QWebPage::Cut);
  _cut->setShortcut(tr("Ctrl+X"));
  _copy = parent->webView()->pageAction(QWebPage::Copy);
  _copy->setShortcut(tr("Ctrl+C"));
  _paste = parent->webView()->pageAction(QWebPage::Paste);
  _paste->setShortcut(tr("Ctrl+V"));
  _selectAll = parent->webView()->pageAction(QWebPage::SelectAll);
  if (_selectAll) // it is null in Qt 4.5 on Ubuntu 9.04
    _selectAll->setShortcut(tr("Ctrl+A"));

  _find = new QAction(tr("&Find"), this);
  _find->setShortcut(tr("Ctrl+F"));
  connect(_find, SIGNAL(triggered()), this, SLOT(find()));

  _findNext = new QAction(tr("Find &next"), this);
  _findNext->setShortcut(tr("Ctrl+G"));
  connect(_findNext, SIGNAL(triggered()), this, SLOT(findNext()));

  _options = new QAction(tr("&Options"), this);
  connect(_options, SIGNAL(triggered()), this, SLOT(options()));

  //
  // View
  //
  _viewEtymologyAct = new QAction(tr("&Etymology"), this);
  _viewEtymologyAct->setCheckable(true);
  _viewEtymologyAct->setChecked(Heading::instance().xhtmlVisibility(Heading::Etymology));
  connect(_viewEtymologyAct, SIGNAL(toggled(bool)), this, SLOT(viewEtymologyToggled(bool)));
  connect(_viewEtymologyAct, SIGNAL(toggled(bool)), parent->coordinator(), SLOT(userSettingChanged_SectionVisibility()));

  _viewPronunciationAct = new QAction(tr("&Pronunciation"), this);
  _viewPronunciationAct->setCheckable(true);
  _viewPronunciationAct->setChecked(Heading::instance().xhtmlVisibility(Heading::Pronunciation));
  connect(_viewPronunciationAct, SIGNAL(toggled(bool)), this, SLOT(viewPronunciationToggled(bool)));
  connect(_viewPronunciationAct, SIGNAL(toggled(bool)), parent->coordinator(), SLOT(userSettingChanged_SectionVisibility()));

  _viewInflectionsAct = new QAction(tr("&Inflections"), this);
  _viewInflectionsAct->setCheckable(true);
  _viewInflectionsAct->setChecked(Heading::instance().xhtmlVisibility(Heading::Inflections));
  connect(_viewInflectionsAct, SIGNAL(toggled(bool)), this, SLOT(viewInflectionsToggled(bool)));
  connect(_viewInflectionsAct, SIGNAL(toggled(bool)), parent->coordinator(), SLOT(userSettingChanged_SectionVisibility()));

  _viewTranslationsAct = new QAction(tr("&Translations"), this);
  _viewTranslationsAct->setCheckable(true);
  _viewTranslationsAct->setChecked(Heading::instance().xhtmlVisibility(Heading::Translations));
  connect(_viewTranslationsAct, SIGNAL(toggled(bool)), this, SLOT(viewTranslationsToggled(bool)));
  connect(_viewTranslationsAct, SIGNAL(toggled(bool)), parent->coordinator(), SLOT(userSettingChanged_SectionVisibility()));

  _viewSemanticRelationsAct = new QAction(tr("&Semantic Relations"), this);
  _viewSemanticRelationsAct->setCheckable(true);
  _viewSemanticRelationsAct->setChecked(Heading::instance().xhtmlVisibility(Heading::SemanticRelations));
  connect(_viewSemanticRelationsAct, SIGNAL(toggled(bool)), this, SLOT(viewSemanticRelationsToggled(bool)));
  connect(_viewSemanticRelationsAct, SIGNAL(toggled(bool)), parent->coordinator(), SLOT(userSettingChanged_SectionVisibility()));

  _viewRelatedDerivedAct = new QAction(tr("&Related and Derived Terms"), this);
  _viewRelatedDerivedAct->setCheckable(true);
  _viewRelatedDerivedAct->setChecked(Heading::instance().xhtmlVisibility(Heading::RelatedTerms));
  connect(_viewRelatedDerivedAct, SIGNAL(toggled(bool)), this, SLOT(viewRelatedDerivedToggled(bool)));
  connect(_viewRelatedDerivedAct, SIGNAL(toggled(bool)), parent->coordinator(), SLOT(userSettingChanged_SectionVisibility()));

  _viewAnagramsAct = new QAction(tr("&Anagrams"), this);
  _viewAnagramsAct->setCheckable(true);
  _viewAnagramsAct->setChecked(Heading::instance().xhtmlVisibility(Heading::Anagrams));
  connect(_viewAnagramsAct, SIGNAL(toggled(bool)), this, SLOT(viewAnagramsToggled(bool)));
  connect(_viewAnagramsAct, SIGNAL(toggled(bool)), parent->coordinator(), SLOT(userSettingChanged_SectionVisibility()));

  //
  // Development
  //
  _pageHtmlAct = new QAction(tr("&Page HTML"), this);
  _pageHtmlAct->setStatusTip(tr("Show the HTML code of the currently displayed page."));
  connect(_pageHtmlAct, SIGNAL(triggered()), this, SLOT(pageHtml()));

  _wordXmlAct = new QAction(tr("&XML Source"), this);
  _wordXmlAct->setStatusTip(tr("Show the XML code"));
  connect(_wordXmlAct, SIGNAL(triggered()), this, SLOT(wordXml()));

  _wordWikiAct = new QAction(tr("&Wiki Source"), this);
  _wordWikiAct->setStatusTip(tr("Show the Wiki code"));
  connect(_wordWikiAct, SIGNAL(triggered()), this, SLOT(wordWiki()));

  _algorithmWikiProcessingAct = new QAction(tr("&Wiki Processing"), this);
  _algorithmWikiProcessingAct->setStatusTip(tr("Show the Wiki debug"));
  connect(_algorithmWikiProcessingAct, SIGNAL(triggered()), this, SLOT(algorithmWikiProcessing()));

  _testAct = new QAction(tr("Self-Test"), this);
  connect(_testAct, SIGNAL(triggered()), this, SLOT(test()));

  _profilerAct = new QAction(tr("Profiler results"), this);
#ifndef PROFILER_ENABLED
  _profilerAct->setEnabled(false);
#endif
  connect(_profilerAct, SIGNAL(triggered()), this, SLOT(profilerResults()));

  _showFormat1ToFormat2DialogAct = new QAction(tr("Format1 to Format2 Converter..."), this);
  connect(_showFormat1ToFormat2DialogAct, SIGNAL(triggered()), this, SLOT(showFormat1ToFormat2Dialog()));

  _showFormat2ToFormat3DialogAct = new QAction(tr("Format2 to Format3 Converter..."), this);
  connect(_showFormat2ToFormat3DialogAct, SIGNAL(triggered()), this, SLOT(showFormat2ToFormat3Dialog()));

  _showFormat3ToFormat4DialogAct = new QAction(tr("Format3 to Format4 Converter..."), this);
  connect(_showFormat3ToFormat4DialogAct, SIGNAL(triggered()), this, SLOT(showFormat3ToFormat4Dialog()));

  _showMediaDownloaderAct = new QAction(tr("Media Downloader..."), this);
  connect(_showMediaDownloaderAct, SIGNAL(triggered()), this, SLOT(showMediaDownloaderDialog()));

  _showImageResizerAct = new QAction(tr("Image Resizer..."), this);
  connect(_showImageResizerAct, SIGNAL(triggered()), this, SLOT(showImageResizerDialog()));

  _showMediaPackerAct = new QAction(tr("Media Packer..."), this);
  connect(_showMediaPackerAct, SIGNAL(triggered()), this, SLOT(showMediaPackerDialog()));

  //
  // Help
  //
  _aboutAct = new QAction(tr("&About"), this);
  _aboutAct->setStatusTip(tr("Show the application's About box"));
  connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  // Menus
  _fileMenu = addMenu(tr("&File"));
  _fileMenu->addAction(_quitAct);

  _editMenu = addMenu(tr("&Edit"));
  _editMenu->addAction(_cut);
  _editMenu->addAction(_copy);
  _editMenu->addAction(_paste);
  if (_selectAll) // it is null on Ubuntu 9.04, Qt 4.5
  {
    _editMenu->addSeparator();
    _editMenu->addAction(_selectAll);
  }
  _editMenu->addSeparator();
  _editMenu->addAction(_find);
  _editMenu->addAction(_findNext);
  _editMenu->addSeparator();
  _editMenu->addAction(_options);

  _viewMenu = addMenu(tr("&View"));
  _viewMenu->addAction(_viewEtymologyAct);
  _viewMenu->addAction(_viewPronunciationAct);
  _viewMenu->addAction(_viewInflectionsAct);
  _viewMenu->addAction(_viewTranslationsAct);
  _viewMenu->addAction(_viewSemanticRelationsAct);
  _viewMenu->addAction(_viewRelatedDerivedAct);
  _viewMenu->addAction(_viewAnagramsAct);

  _developmentMenu = addMenu(tr("&Development"));
  _developmentMenu->addAction(_showFormat1ToFormat2DialogAct);
  _developmentMenu->addAction(_showFormat2ToFormat3DialogAct);
  _developmentMenu->addAction(_showFormat3ToFormat4DialogAct);
  _developmentMenu->addAction(_showMediaDownloaderAct);
  _developmentMenu->addAction(_showImageResizerAct);
  _developmentMenu->addAction(_showMediaPackerAct);
  _developmentMenu->addSeparator();
  _developmentMenu->addAction(_pageHtmlAct);
  _developmentMenu->addSeparator();
  _developmentMenu->addAction(_wordXmlAct);
  _developmentMenu->addAction(_wordWikiAct);
  _developmentMenu->addSeparator();
  _developmentMenu->addAction(_algorithmWikiProcessingAct);
  _developmentMenu->addSeparator();
  _developmentMenu->addAction(_testAct);
  _developmentMenu->addAction(_profilerAct);

  _helpMenu = addMenu(tr("&Help"));
  _helpMenu->addAction(_aboutAct);
}

//===========================================================================
MenuBar::~MenuBar()
{
}

//===========================================================================
void MenuBar::find()
{
  _parent->findPanel()->show();
}

//===========================================================================
void MenuBar::findNext()
{
  _parent->findPanel()->nextClicked();
}

//===========================================================================
void MenuBar::options()
{
  OptionsDialog dialog;
  dialog.exec();
}

//===========================================================================
void MenuBar::viewEtymologyToggled(bool checked)
{
  Heading::instance().setXHtmlVisibility(Heading::Etymology, checked);
}

//===========================================================================
void MenuBar::viewPronunciationToggled(bool checked)
{
  Heading::instance().setXHtmlVisibility(Heading::Pronunciation, checked);
}

//===========================================================================
void MenuBar::viewInflectionsToggled(bool checked)
{
  Heading::instance().setXHtmlVisibility(Heading::Inflections, checked);
}

//===========================================================================
void MenuBar::viewTranslationsToggled(bool checked)
{
  Heading::instance().setXHtmlVisibility(Heading::Translations, checked);
}

//===========================================================================
void MenuBar::viewSemanticRelationsToggled(bool checked)
{
  Heading::instance().setXHtmlVisibility(Heading::SemanticRelations, checked);
}

//===========================================================================
void MenuBar::viewRelatedDerivedToggled(bool checked)
{
  Heading::instance().setXHtmlVisibility(Heading::RelatedTerms, checked);
  Heading::instance().setXHtmlVisibility(Heading::DerivedTerms, checked);
}

//===========================================================================
void MenuBar::viewAnagramsToggled(bool checked)
{
  Heading::instance().setXHtmlVisibility(Heading::Anagrams, checked);
}

//===========================================================================
void MenuBar::about()
{
 QMessageBox::about(parentWidget(), tr("About Wikt"),
   tr("Wikt version " WIKT_VERSION ".\n"
       "A computer interactive dictionary.\n"
       "Created by Karel Klic <karelklic@gmail.com>.\n"
       "Distributed under GNU General Public License 3.\n"
       "Uses data from Wiktionary project."));
}

//===========================================================================
void MenuBar::pageHtml()
{
  QString contents = _parent->webView()->toHtml();
  HtmlSourceView *w = new HtmlSourceView(contents);
  w->show();
}

//===========================================================================
void MenuBar::wordXml()
{
  XmlSourceView *w = new XmlSourceView();
  w->setWord(_parent->coordinator()->text());
  w->show();
}

//===========================================================================
void MenuBar::wordWiki()
{
  WikiSourceView *w = new WikiSourceView();
  w->setWord(_parent->coordinator()->text());
  w->show();
}

//===========================================================================
void MenuBar::algorithmWikiProcessing()
{
  WikiProcessingView *w = new WikiProcessingView();
  w->show();
}

//===========================================================================
void MenuBar::test()
{
  UnitTestDialog dialog;
  dialog.show();
}

//===========================================================================
void MenuBar::profilerResults()
{
  PROFILER_RESULTS;
}

//===========================================================================
void MenuBar::showFormat1ToFormat2Dialog()
{
  Format1ToFormat2Dialog generator;
  generator.exec();
}

//===========================================================================
void MenuBar::showFormat2ToFormat3Dialog()
{
  Format2ToFormat3Dialog generator;
  generator.exec();
}

//===========================================================================
void MenuBar::showFormat3ToFormat4Dialog()
{
  Format3ToFormat4Dialog generator;
  generator.exec();
}

//===========================================================================
void MenuBar::showMediaDownloaderDialog()
{
  MediaDownloaderDialog dialog;
  dialog.exec();
}

//===========================================================================
void MenuBar::showImageResizerDialog()
{
  ImageResizerDialog dialog;
  dialog.exec();
}

//===========================================================================
void MenuBar::showMediaPackerDialog()
{
  MediaPackerDialog dialog;
  dialog.exec();
}
