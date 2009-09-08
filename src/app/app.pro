include(../../wikt.pri)

TEMPLATE = app
TARGET = wikt
QT += webkit network phonon svg

SOURCES += \
  categoriesitem.cpp \
  categoriesmodel.cpp \
  categoriespanel.cpp \
  coordinator.cpp \
  displayedpagehistory.cpp \
  errordialog.cpp \
  findpanel.cpp \
  htmlsourceview.cpp \
  htmlsyntaxhighlighter.cpp \
  interestingpagesitem.cpp \
  interestingpageslanguagesrootitem.cpp \
  interestingpageslinkitem.cpp \
  interestingpagesmodel.cpp \
  interestingpagespanel.cpp \
  interestingpagesrootitem.cpp \
  lookuppanel.cpp \
  main.cpp \
  mainwindow.cpp \
  mediaplayer.cpp \
  menubar.cpp \
  networkaccessmanager.cpp \
  networkreplyembeddedfile.cpp \
  networkreplyentry.cpp \
  networkreplyjavascript.cpp \
  networkreplymediafile.cpp \
  networkreplynotfound.cpp \
  networkreplystylesheet.cpp \
  networkreplytitlepage.cpp \
  optionsdialog.cpp \
  relpagesexternallinkitem.cpp \
  relpagesexternallinksrootitem.cpp \
  relpagesinternallinkitem.cpp \
  relpagesinterwikirootitem.cpp \
  relpagesitem.cpp \
  relpagesmodel.cpp \
  relpagespanel.cpp \
  relpagesrootitem.cpp \
  tocitem.cpp \
  tocmodel.cpp \
  tocpanel.cpp \
  webview.cpp \
  wikisource.cpp \
  wikisourcecacheitem.cpp

HEADERS += \
  categoriesitem.h \
  categoriesmodel.h \
  categoriespanel.h \
  coordinator.h \
  displayedpagehistory.h \
  errordialog.h \
  findpanel.h \
  htmlsourceview.h \
  htmlsyntaxhighlighter.h \
  interestingpagesitem.h \
  interestingpageslanguagesrootitem.h \
  interestingpageslinkitem.h \
  interestingpagesmodel.h \
  interestingpagespanel.h \
  interestingpagesrootitem.h \
  lookuppanel.h \
  mainwindow.h \
  mediaplayer.h \
  menubar.h \
  networkaccessmanager.h \
  networkreplyembeddedfile.h \
  networkreplyentry.h \
  networkreplyjavascript.h \
  networkreplymediafile.h \
  networkreplynotfound.h \
  networkreplystylesheet.h \
  networkreplytitlepage.h \
  optionsdialog.h \
  relpagesexternallinkitem.h \
  relpagesexternallinksrootitem.h \
  relpagesinternallinkitem.h \
  relpagesinterwikirootitem.h \
  relpagesitem.h \
  relpagesmodel.h \
  relpagespanel.h \
  relpagesrootitem.h \
  tocitem.h \
  tocmodel.h \
  tocpanel.h \
  webview.h \
  wikisource.h \
  wikisourcecacheitem.h

FORMS = ErrorDialog.ui

RESOURCES = wikt.qrc
LIBS *= ../../bin/libwikt.so.0.20
INCLUDEPATH += ..
DESTDIR = ../../bin
