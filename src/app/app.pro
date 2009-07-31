TEMPLATE = app
TARGET = wikt
QT += webkit network phonon svg

SOURCES += \
  Main.cpp \
  CategoriesItem.cpp \
  CategoriesModel.cpp \
  CategoriesPanel.cpp \
  HtmlSourceView.cpp \
  HtmlSyntaxHighlighter.cpp \
  WikiProcessingView.cpp \
  ErrorDialog.cpp \
  InterestingPagesItem.cpp \
  InterestingPagesLanguagesRootItem.cpp \
  InterestingPagesLinkItem.cpp \
  InterestingPagesModel.cpp \
  InterestingPagesPanel.cpp \
  InterestingPagesRootItem.cpp \
  Coordinator.cpp \
  DisplayedPageHistory.cpp \
  FindPanel.cpp \
  LookupPanel.cpp \
  MainWindow.cpp \
  MenuBar.cpp \
  NetworkAccessManager.cpp \
  NetworkReplyEmbeddedFile.cpp \
  NetworkReplyEntry.cpp \
  NetworkReplyMediaFile.cpp \
  NetworkReplyStylesheet.cpp \
  NetworkReplyTitlePage.cpp \
  WebView.cpp \
  MediaPlayer.cpp \
  OptionsDialog.cpp \
  RelPagesExternalLinkItem.cpp \
  RelPagesExternalLinksRootItem.cpp \
  RelPagesInternalLinkItem.cpp \
  RelPagesInterwikiRootItem.cpp \
  RelPagesItem.cpp \
  RelPagesModel.cpp \
  RelPagesPanel.cpp \
  RelPagesRootItem.cpp \
  TocItem.cpp \
  TocModel.cpp \
  TocPanel.cpp \
  WikiSource.cpp \
  WikiSourceCacheItem.cpp

HEADERS += \
  CategoriesItem.h \
  CategoriesModel.h \
  CategoriesPanel.h \
  HtmlSourceView.h \
  HtmlSyntaxHighlighter.h \
  WikiProcessingView.h \
  ErrorDialog.h \
  InterestingPagesItem.h \
  InterestingPagesLanguagesRootItem.h \
  InterestingPagesLinkItem.h \
  InterestingPagesModel.h \
  InterestingPagesPanel.h \
  InterestingPagesRootItem.h \
  Coordinator.h \
  DisplayedPageHistory.h \
  FindPanel.h \
  LookupPanel.h \
  MainWindow.h \
  MenuBar.h \
  NetworkAccessManager.h \
  NetworkReplyEmbeddedFile.h \
  NetworkReplyEntry.h \
  NetworkReplyMediaFile.h \
  NetworkReplyStylesheet.h \
  NetworkReplyTitlePage.h \
  WebView.h \
  MediaPlayer.h \
  OptionsDialog.h \
  RelPagesExternalLinkItem.h \
  RelPagesExternalLinksRootItem.h \
  RelPagesInternalLinkItem.h \
  RelPagesInterwikiRootItem.h \
  RelPagesItem.h \
  RelPagesModel.h \
  RelPagesPanel.h \
  RelPagesRootItem.h \
  TocItem.h \
  TocModel.h \
  TocPanel.h \
  WikiSource.h \
  WikiSourceCacheItem.h

FORMS = ErrorDialog.ui OptionsDialog.ui

RESOURCES = wikt.qrc
  
LIBS *= -lwikt
LIBS += -L../../bin
INCLUDEPATH += ..
DESTDIR = ../../bin
