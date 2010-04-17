lib_LTLIBRARIES = libwikt.la

libwikt_la_SOURCES = \
    debug.cpp debug.h \
    dictionary.cpp dictionary.h \
    comparsion.h \
    fileutils.cpp fileutils.h \
    format3reader.cpp format3reader.h \
    format4reader.cpp format4reader.h \
    isspace_clocale.c isspace_clocale.h \
    languages.c languages.h \
    utils.c utils.h \
    mediareader.cpp mediareader.h \
    mediautils.cpp mediautils.h \
    namespace.cpp namespace.h \
    project.cpp project.h \
    quicksort.h \
    strdup_trimmed.c strdup_trimmed.h \
    stringutils.cpp stringutils.h \
    unicode.cpp unicode.h \
    urlutils.cpp urlutils.h \
    version.h \
    parser/articleparser.cpp parser/articleparser.h \
    parser/blockparser.cpp parser/blockparser.h \
    parser/blockhtmlparser.cpp parser/blockhtmlparser.h \
    parser/bolditalicparser.cpp parser/bolditalicparser.h \
    parser/buffer.cpp parser/buffer.h \
    parser/bulletlistparser.cpp parser/bulletlistparser.h \
    parser/definitionlistparser.cpp parser/definitionlistparser.h \
    parser/externallinkparser.cpp parser/externallinkparser.h \
    parser/headingparser.cpp parser/headingparser.h \
    parser/htmlentityparser.cpp parser/htmlentityparser.h \
    parser/inlinehtmlparser.cpp parser/inlinehtmlparser.h \
    parser/linkparser.cpp parser/linkparser.h \
    parser/listparser.cpp parser/listparser.h \
    parser/numberedlistparser.cpp parser/numberedlistparser.h \
    parser/paragraphparser.cpp parser/paragraphparser.h \
    parser/tablecaptionparser.cpp parser/tablecaptionparser.h \
    parser/tablecellparser.cpp parser/tablecellparser.h \
    parser/tableheadparser.cpp parser/tableheadparser.h \
    parser/tableparser.cpp parser/tableparser.h \
    parser/tablerowparser.cpp parser/tablerowparser.h \
    parser/textblockparser.cpp parser/textblockparser.h \
    tree/articlenode.cpp tree/articlenode.h \
    tree/attributegroupnode.cpp tree/attributegroupnode.h \
    tree/attributenode.cpp tree/attributenode.h \
    tree/boldnode.cpp tree/boldnode.h \
    tree/bulletlistnode.cpp tree/bulletlistnode.h \
    tree/definitionlistdefitemnode.cpp tree/definitionlistdefitemnode.h \
    tree/definitionlistnode.cpp tree/definitionlistnode.h \
    tree/definitionlisttermitemnode.cpp tree/definitionlisttermitemnode.h \
    tree/extensiontokennode.cpp tree/extensiontokennode.h \
    tree/externallinknode.cpp tree/externallinknode.h \
    tree/heading.cpp tree/heading.h \
    tree/headingnode.cpp tree/headingnode.h \
    tree/htmlelementnode.cpp tree/htmlelementnode.h \
    tree/htmlentitynode.cpp tree/htmlentitynode.h \
    tree/italicsnode.cpp tree/italicsnode.h \
    tree/linknode.cpp tree/linknode.h \
    tree/linkoptionsnode.cpp tree/linkoptionsnode.h \
    tree/linktargetnode.cpp tree/linktargetnode.h \
    tree/listitemnode.cpp tree/listitemnode.h \
    tree/node.cpp tree/node.h \
    tree/numberedlistnode.cpp tree/numberedlistnode.h \
    tree/paragraphnode.cpp tree/paragraphnode.h \
    tree/preblocknode.cpp tree/preblocknode.h \
    tree/prelinenode.cpp tree/prelinenode.h \
    tree/tablecaptionnode.cpp tree/tablecaptionnode.h \
    tree/tablecellnode.cpp tree/tablecellnode.h \
    tree/tableheadnode.cpp tree/tableheadnode.h \
    tree/tablenode.cpp tree/tablenode.h \
    tree/tablerownode.cpp tree/tablerownode.h \
    tree/textblocknode.cpp tree/textblocknode.h \
    tree/texttokennode.cpp tree/texttokennode.h

libwikt_la_CPPFLAGS = \
  -I.. \
  $(QTCORE_CFLAGS) \
  $(QTGUI_CFLAGS) \
  $(QTSVG_CFLAGS)

libwikt_la_LDFLAGS = \
  $(QTCORE_LDFLAGS) \
  $(QTGUI_LDFLAGS) \
  $(QTSVG_LDFLAGS)

libwikt_la_LIBADD = \
  $(QTCORE_LIBS) \
  $(QTGUI_LIBS) \
  $(QTSVG_LIBS)