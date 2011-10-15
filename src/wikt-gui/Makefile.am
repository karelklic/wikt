bin_PROGRAMS = wikt-gui

wikt_gui_SOURCES = \
  categoriesitem.cpp categoriesitem.h \
  categoriesmodel.cpp categoriesmodel.h moc_categoriesmodel.cpp \
  categoriespanel.cpp categoriespanel.h moc_categoriespanel.cpp \
  coordinator.cpp coordinator.h moc_coordinator.cpp \
  displayedpagehistory.cpp displayedpagehistory.h moc_displayedpagehistory.cpp \
  findpanel.cpp findpanel.h moc_findpanel.cpp \
  htmlsourceview.cpp htmlsourceview.h moc_htmlsourceview.cpp \
  htmlsyntaxhighlighter.cpp htmlsyntaxhighlighter.h moc_htmlsyntaxhighlighter.cpp \
  interestingpagesitem.cpp interestingpagesitem.h \
  interestingpageslanguagesrootitem.cpp interestingpageslanguagesrootitem.h \
  interestingpageslinkitem.cpp interestingpageslinkitem.h \
  interestingpagesmodel.cpp interestingpagesmodel.h moc_interestingpagesmodel.cpp \
  interestingpagespanel.cpp interestingpagespanel.h moc_interestingpagespanel.cpp \
  interestingpagesrootitem.cpp interestingpagesrootitem.h \
  lookuppanel.cpp lookuppanel.h moc_lookuppanel.cpp \
  main.cpp \
  mainwindow.cpp mainwindow.h moc_mainwindow.cpp \
  mediaplayer.cpp mediaplayer.h moc_mediaplayer.cpp \
  menubar.cpp menubar.h moc_menubar.cpp \
  networkaccessmanager.cpp networkaccessmanager.h \
  networkreplyembeddedfile.cpp networkreplyembeddedfile.h moc_networkreplyembeddedfile.cpp \
  networkreplyentry.cpp networkreplyentry.h moc_networkreplyentry.cpp \
  networkreplyjavascript.cpp networkreplyjavascript.h moc_networkreplyjavascript.cpp \
  networkreplymediafile.cpp networkreplymediafile.h moc_networkreplymediafile.cpp \
  networkreplynotfound.cpp networkreplynotfound.h moc_networkreplynotfound.cpp \
  networkreplystylesheet.cpp networkreplystylesheet.h moc_networkreplystylesheet.cpp \
  networkreplytitlepage.cpp networkreplytitlepage.h \
  optionsdialog.cpp optionsdialog.h moc_optionsdialog.cpp \
  relpagesexternallinkitem.cpp relpagesexternallinkitem.h \
  relpagesexternallinksrootitem.cpp relpagesexternallinksrootitem.h \
  relpagesinternallinkitem.cpp relpagesinternallinkitem.h \
  relpagesinterwikirootitem.cpp relpagesinterwikirootitem.h \
  relpagesitem.cpp relpagesitem.h \
  relpagesmodel.cpp relpagesmodel.h moc_relpagesmodel.cpp \
  relpagespanel.cpp relpagespanel.h moc_relpagespanel.cpp \
  relpagesrootitem.cpp relpagesrootitem.h \
  tocitem.cpp tocitem.h \
  tocmodel.cpp tocmodel.h moc_tocmodel.cpp \
  tocpanel.cpp tocpanel.h moc_tocpanel.cpp \
  webview.cpp webview.h moc_webview.cpp \
  wikisource.cpp wikisource.h moc_wikisource.cpp \
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
