TEMPLATE = app
TARGET = wikt

QT += webkit network phonon

SOURCES += \
  Main.cpp \
  Categories/CategoriesItem.cpp \
  Categories/CategoriesModel.cpp \
  Categories/CategoriesPanel.cpp \
  Debug/HtmlSourceView.cpp \
  Debug/HtmlSyntaxHighlighter.cpp \
  Debug/WikiProcessingView.cpp \
  Debug/WikiSourceView.cpp \
  Debug/XmlSourceView.cpp \
  Debug/XmlSyntaxHighlighter.cpp \
  Debug/ErrorDialog/ErrorDialog.cpp \
  Debug/UnitTest/UnitTestDialog.cpp \
  Debug/UnitTest/UnitTestRunner.cpp \
  InterestingPages/InterestingPagesItem.cpp \
  InterestingPages/InterestingPagesLanguagesRootItem.cpp \
  InterestingPages/InterestingPagesLinkItem.cpp \
  InterestingPages/InterestingPagesModel.cpp \
  InterestingPages/InterestingPagesPanel.cpp \
  InterestingPages/InterestingPagesRootItem.cpp \
  MainWindow/Coordinator.cpp \
  MainWindow/DisplayedPageHistory.cpp \
  MainWindow/FindPanel.cpp \
  MainWindow/LookupPanel.cpp \
  MainWindow/MainWindow.cpp \
  MainWindow/MenuBar.cpp \
  MainWindow/WebView/NetworkAccessManager.cpp \
  MainWindow/WebView/NetworkReplyEmbeddedFile.cpp \
  MainWindow/WebView/NetworkReplyEntry.cpp \
  MainWindow/WebView/NetworkReplyMediaFile.cpp \
  MainWindow/WebView/NetworkReplyStylesheet.cpp \
  MainWindow/WebView/NetworkReplyTitlePage.cpp \
  MainWindow/WebView/WebView.cpp \
  Media/MediaPlayer.cpp \
  Options/OptionsDialog.cpp \
  RelatedPages/ExternalLinkItem.cpp \
  RelatedPages/ExternalLinksRootItem.cpp \
  RelatedPages/InternalLinkItem.cpp \
  RelatedPages/InterwikiRootItem.cpp \
  RelatedPages/Item.cpp \
  RelatedPages/Model.cpp \
  RelatedPages/Panel.cpp \
  RelatedPages/RootItem.cpp \
  TableOfContents/TocItem.cpp \
  TableOfContents/TocModel.cpp \
  TableOfContents/TocPanel.cpp

HEADERS += \
  Categories/CategoriesItem.h \
  Categories/CategoriesModel.h \
  Categories/CategoriesPanel.h \
  Debug/HtmlSourceView.h \
  Debug/HtmlSyntaxHighlighter.h \
  Debug/WikiProcessingView.h \
  Debug/WikiSourceView.h \
  Debug/XmlSourceView.h \
  Debug/XmlSyntaxHighlighter.h \
  Debug/ErrorDialog/ErrorDialog.h \
  Debug/UnitTest/UnitTestDialog.h \
  Debug/UnitTest/UnitTestRunner.h \
  InterestingPages/InterestingPagesItem.h \
  InterestingPages/InterestingPagesLanguagesRootItem.h \
  InterestingPages/InterestingPagesLinkItem.h \
  InterestingPages/InterestingPagesModel.h \
  InterestingPages/InterestingPagesPanel.h \
  InterestingPages/InterestingPagesRootItem.h \
  MainWindow/Coordinator.h \
  MainWindow/DisplayedPageHistory.h \
  MainWindow/FindPanel.h \
  MainWindow/LookupPanel.h \
  MainWindow/MainWindow.h \
  MainWindow/MenuBar.h \
  MainWindow/WebView/NetworkAccessManager.h \
  MainWindow/WebView/NetworkReplyEmbeddedFile.h \
  MainWindow/WebView/NetworkReplyEntry.h \
  MainWindow/WebView/NetworkReplyMediaFile.h \
  MainWindow/WebView/NetworkReplyStylesheet.h \
  MainWindow/WebView/NetworkReplyTitlePage.h \
  MainWindow/WebView/WebView.h \
  Media/MediaPlayer.h \
  Options/OptionsDialog.h \
  RelatedPages/ExternalLinkItem.h \
  RelatedPages/ExternalLinksRootItem.h \
  RelatedPages/InternalLinkItem.h \
  RelatedPages/InterwikiRootItem.h \
  RelatedPages/Item.h \
  RelatedPages/Model.h \
  RelatedPages/Panel.h \
  RelatedPages/RootItem.h \
  TableOfContents/TocItem.h \
  TableOfContents/TocModel.h \
  TableOfContents/TocPanel.h

FORMS = \
  Debug/ErrorDialog/ErrorDialog.ui \
  Debug/UnitTest/UnitTestDialog.ui \
  Options/OptionsDialog.ui

RESOURCES = wikt.qrc
  

LIBS *= -lwikt
LIBS += -L../../bin

INCLUDEPATH += ../lib
DESTDIR = ../../bin
