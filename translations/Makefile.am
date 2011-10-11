LANGUAGES = cs

translations_DATA = ${LANGUAGES:%=wikt_%.qm}
translationsdir = $(pkgdatadir)/translations
EXTRA_DIST = ${LANGUAGES:%=wikt_%.ts} ${translations_DATA}

lupdate:
	(cd $(top_srcdir) && $(LUPDATE) -locations relative -no-ui-lines src -ts ${LANGUAGES:%=translations/wikt_%.ts})

.ts.qm:
	$(LRELEASE) $< -qm $@
