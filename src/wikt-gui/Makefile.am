bin_PROGRAMS = wikt-gui

nodist_wikt_gui_SOURCES = \
  moc_categoriesmodel.cpp \
  moc_categoriespanel.cpp \
  moc_coordinator.cpp \
  moc_displayedpagehistory.cpp \
  moc_findpanel.cpp \
  moc_htmlsourceview.cpp \
  moc_htmlsyntaxhighlighter.cpp \
  moc_interestingpagesmodel.cpp \
  moc_interestingpagespanel.cpp \
  moc_lookuppanel.cpp \
  moc_mainwindow.cpp \
  moc_mediaplayer.cpp \
  moc_menubar.cpp \
  moc_networkreplyembeddedfile.cpp \
  moc_networkreplyentry.cpp \
  moc_networkreplyjavascript.cpp \
  moc_networkreplymediafile.cpp \
  moc_networkreplynotfound.cpp \
  moc_networkreplystylesheet.cpp \
  moc_optionsdialog.cpp \
  moc_relpagesmodel.cpp \
  moc_relpagespanel.cpp \
  moc_tocmodel.cpp \
  moc_tocpanel.cpp \
  moc_webview.cpp \
  moc_wikisource.cpp

wikt_gui_SOURCES = \
  categoriesitem.cpp categoriesitem.h \
  categoriesmodel.cpp categoriesmodel.h \
  categoriespanel.cpp categoriespanel.h \
  coordinator.cpp coordinator.h \
  displayedpagehistory.cpp displayedpagehistory.h \
  findpanel.cpp findpanel.h \
  htmlsourceview.cpp htmlsourceview.h \
  htmlsyntaxhighlighter.cpp htmlsyntaxhighlighter.h \
  interestingpagesitem.cpp interestingpagesitem.h \
  interestingpageslanguagesrootitem.cpp interestingpageslanguagesrootitem.h \
  interestingpageslinkitem.cpp interestingpageslinkitem.h \
  interestingpagesmodel.cpp interestingpagesmodel.h \
  interestingpagespanel.cpp interestingpagespanel.h \
  interestingpagesrootitem.cpp interestingpagesrootitem.h \
  lookuppanel.cpp lookuppanel.h \
  main.cpp \
  mainwindow.cpp mainwindow.h \
  mediaplayer.cpp mediaplayer.h \
  menubar.cpp menubar.h \
  networkaccessmanager.cpp networkaccessmanager.h \
  networkreplyembeddedfile.cpp networkreplyembeddedfile.h \
  networkreplyentry.cpp networkreplyentry.h \
  networkreplyjavascript.cpp networkreplyjavascript.h \
  networkreplymediafile.cpp networkreplymediafile.h \
  networkreplynotfound.cpp networkreplynotfound.h \
  networkreplystylesheet.cpp networkreplystylesheet.h \
  networkreplytitlepage.cpp networkreplytitlepage.h \
  optionsdialog.cpp optionsdialog.h \
  relpagesexternallinkitem.cpp relpagesexternallinkitem.h \
  relpagesexternallinksrootitem.cpp relpagesexternallinksrootitem.h \
  relpagesinternallinkitem.cpp relpagesinternallinkitem.h \
  relpagesinterwikirootitem.cpp relpagesinterwikirootitem.h \
  relpagesitem.cpp relpagesitem.h \
  relpagesmodel.cpp relpagesmodel.h \
  relpagespanel.cpp relpagespanel.h \
  relpagesrootitem.cpp relpagesrootitem.h \
  tocitem.cpp tocitem.h \
  tocmodel.cpp tocmodel.h \
  tocpanel.cpp tocpanel.h \
  webview.cpp webview.h \
  wikisource.cpp wikisource.h \
  wikisourcecacheitem.cpp wikisourcecacheitem.h \
  qrc_wikt.cpp

wikt_gui_CPPFLAGS = \
  -I.. \
  $(QTCORE_CFLAGS) \
  $(QTGUI_CFLAGS) \
  $(QTWEBKIT_CFLAGS) \
  $(QTNETWORK_CFLAGS) \
  $(QTSVG_CFLAGS) \
  $(PHONON_CFLAGS)

wikt_gui_LDFLAGS = \
  $(QTCORE_LDFLAGS) \
  $(QTGUI_LDFLAGS) \
  $(QTWEBKIT_LDFLAGS) \
  $(QTNETWORK_LDFLAGS) \
  $(QTSVG_LDFLAGS) \
  $(PHONON_LDFLAGS)

wikt_gui_LDADD = \
  ../libwikt/libwikt.la \
  $(QTCORE_LIBS) \
  $(QTGUI_LIBS) \
  $(QTWEBKIT_LIBS) \
  $(QTNETWORK_LIBS) \
  $(QTSVG_LIBS) \
  $(PHONON_LIBS)

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

IMAGES = \
  images/edit-paste.svg \
  images/logo.svg \
  images/sort-up.gif \
  images/go-next.svg \
  images/magnify-clip.png \
  images/bullet.gif \
  images/sort-down.gif \
  images/edit-select-all.svg \
  images/edit-find.svg \
  images/loudspeaker.png \
  images/preferences-system.svg \
  images/emblem-unreadable.svg \
  images/sort-none.gif \
  images/edit-cut.svg \
  images/go-home.svg \
  images/go-previous.svg \
  images/edit-copy.svg \
  images/system-shutdown.svg \
  images/loudspeaker.svg

EXTRA_DIST = wikt.qrc $(IMAGES)

qrc_wikt.cpp: wikt.qrc $(IMAGES)
	/usr/bin/rcc -name wikt wikt.qrc -o qrc_wikt.cpp

clean-rcc-extra:
	rm -vf qrc_*.cpp

clean-local: clean-moc-extra clean-rcc-extra
