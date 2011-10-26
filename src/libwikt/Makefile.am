lib_LTLIBRARIES = libwikt.la

libwikt_parser_HEADERS = \
    parser/articleparser.h \
    parser/blockparser.h \
    parser/blockhtmlparser.h \
    parser/bolditalicparser.h \
    parser/buffer.h \
    parser/bulletlistparser.h \
    parser/definitionlistparser.h \
    parser/externallinkparser.h \
    parser/headingparser.h \
    parser/htmlentityparser.h \
    parser/inlinehtmlparser.h \
    parser/prerequisites.h \
    parser/linkparser.h \
    parser/listparser.h \
    parser/numberedlistparser.h \
    parser/paragraphparser.h \
    parser/tablecaptionparser.h \
    parser/tablecellparser.h \
    parser/tableheadparser.h \
    parser/tableparser.h \
    parser/tablerowparser.h \
    parser/textblockparser.h
libwikt_parserdir = $(includedir)/libwikt/parser

libwikt_tree_HEADERS = \
    tree/articlenode.h \
    tree/attributegroupnode.h \
    tree/attributenode.h \
    tree/boldnode.h \
    tree/bulletlistnode.h \
    tree/definitionlistdefitemnode.h \
    tree/definitionlistnode.h \
    tree/definitionlisttermitemnode.h \
    tree/extensiontokennode.h \
    tree/externallinknode.h \
    tree/heading.h \
    tree/headingnode.h \
    tree/htmlelementnode.h \
    tree/htmlentitynode.h \
    tree/italicsnode.h \
    tree/linknode.h \
    tree/linkoptionsnode.h \
    tree/linktargetnode.h \
    tree/listitemnode.h \
    tree/node.h \
    tree/numberedlistnode.h \
    tree/paragraphnode.h \
    tree/preblocknode.h \
    tree/prelinenode.h \
    tree/tablecaptionnode.h \
    tree/tablecellnode.h \
    tree/tableheadnode.h \
    tree/tablenode.h \
    tree/tablerownode.h \
    tree/textblocknode.h \
    tree/texttokennode.h
libwikt_treedir = $(includedir)/libwikt/tree

libwikt_HEADERS = \
    comparsion.h \
    debug.h \
    fileutils.h \
    format3reader.h \
    format4reader.h \
    language.h \
    mediareader.h \
    mediautils.h \
    namespace.h \
    project.h \
    stringutils.h \
    unicode.h \
    urlutils.h \
    version.h
libwiktdir = $(includedir)/libwikt

nodist_libwikt_la_SOURCES = \
    moc_format3reader.cpp \
    moc_mediareader.cpp

libwikt_la_SOURCES = \
    $(libwikt_HEADERS) \
    $(libwikt_parser_HEADERS) \
    $(libwikt_tree_HEADERS) \
    debug.cpp \
    fileutils.cpp \
    format3reader.cpp \
    format4reader.cpp \
    language.cpp  \
    mediareader.cpp \
    mediautils.cpp  \
    namespace.cpp \
    project.cpp \
    quicksort.h \
    stringutils.cpp \
    unicode.cpp  \
    urlutils.cpp \
    parser/articleparser.cpp \
    parser/blockparser.cpp \
    parser/blockhtmlparser.cpp \
    parser/bolditalicparser.cpp \
    parser/buffer.cpp \
    parser/bulletlistparser.cpp \
    parser/definitionlistparser.cpp \
    parser/externallinkparser.cpp \
    parser/headingparser.cpp \
    parser/htmlentityparser.cpp \
    parser/inlinehtmlparser.cpp \
    parser/linkparser.cpp \
    parser/listparser.cpp \
    parser/numberedlistparser.cpp \
    parser/paragraphparser.cpp \
    parser/tablecaptionparser.cpp \
    parser/tablecellparser.cpp \
    parser/tableheadparser.cpp \
    parser/tableparser.cpp \
    parser/tablerowparser.cpp \
    parser/textblockparser.cpp \
    tree/articlenode.cpp \
    tree/attributegroupnode.cpp \
    tree/attributenode.cpp \
    tree/boldnode.cpp \
    tree/bulletlistnode.cpp \
    tree/definitionlistdefitemnode.cpp \
    tree/definitionlistnode.cpp \
    tree/definitionlisttermitemnode.cpp \
    tree/extensiontokennode.cpp \
    tree/externallinknode.cpp \
    tree/heading.cpp \
    tree/headingnode.cpp \
    tree/htmlelementnode.cpp \
    tree/htmlentitynode.cpp \
    tree/italicsnode.cpp \
    tree/linknode.cpp \
    tree/linkoptionsnode.cpp \
    tree/linktargetnode.cpp \
    tree/listitemnode.cpp \
    tree/node.cpp \
    tree/numberedlistnode.cpp \
    tree/paragraphnode.cpp \
    tree/preblocknode.cpp \
    tree/prelinenode.cpp \
    tree/tablecaptionnode.cpp \
    tree/tablecellnode.cpp \
    tree/tableheadnode.cpp \
    tree/tablenode.cpp \
    tree/tablerownode.cpp \
    tree/textblocknode.cpp \
    tree/texttokennode.cpp

libwikt_la_CPPFLAGS = -I.. $(QTCORE_CFLAGS) $(QTGUI_CFLAGS) $(QTSVG_CFLAGS)
libwikt_la_LDFLAGS = $(QTCORE_LDFLAGS) $(QTGUI_LDFLAGS) $(QTSVG_LDFLAGS)
libwikt_la_LIBADD = $(QTCORE_LIBS) $(QTGUI_LIBS) $(QTSVG_LIBS)
EXTRA_DIST = languagesgenerated.h.inc languagesgenerated.cpp.inc

moc_%.cpp : %.h
	moc-qt4 -o "$@" "$<"

clean-moc-extra:
	rm -vf moc_*.cpp

clean-local: clean-moc-extra
