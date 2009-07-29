TEMPLATE = lib
TARGET = wikt

DEFINES = WIKT_LIBRARY
DESTDIR = ../../bin

QT += core \
    gui \
    xml \
    xmlpatterns \
    network \
    svg \
    testlib

HEADERS = \
    Wiki/Parser/Table/TableCaptionParser.h \
    Debug/Debug.h \
    Debug/Profiler/Profiler.h \
    Debug/Profiler/ProfilerView.h \
    DictionaryFile/Comparsion.h \
    DictionaryFile/FileUtils.h \
    DictionaryFile/Format3Reader.h \
    DictionaryFile/Format4Reader.h \
    Media/MediaReader.h \
    Media/MediaUtils.h \
    Prerequisites.h \
    Unicode.h \
    UrlUtils.h \
    Version.h \
    Wiki/Namespace.h \
    Wiki/Parser/ArticleParser.h \
    Wiki/Parser/Block/BlockParser.h \
    Wiki/Parser/BoldItalic/BoldItalicParser.h \
    Wiki/Parser/BoldItalic/BoldItalicParserTest.h \
    Wiki/Parser/Buffer/Buffer.h \
    Wiki/Parser/Buffer/BufferTest.h \
    Wiki/Parser/Heading/HeadingParser.h \
    Wiki/Parser/Heading/HeadingParserTest.h \
    Wiki/Parser/Html/BlockHtmlParser.h \
    Wiki/Parser/Html/HtmlEntityParser.h \
    Wiki/Parser/Html/HtmlEntityParserTest.h \
    Wiki/Parser/Html/InlineHtmlParser.h \
    Wiki/Parser/Html/InlineHtmlParserTest.h \
    Wiki/Parser/Link/ExternalLinkParser.h \
    Wiki/Parser/Link/LinkParser.h \
    Wiki/Parser/Link/LinkParserTest.h \
    Wiki/Parser/List/BulletListParser.h \
    Wiki/Parser/List/BulletListParserTest.h \
    Wiki/Parser/List/DefinitionListParser.h \
    Wiki/Parser/List/ListParser.h \
    Wiki/Parser/List/ListParserTest.h \
    Wiki/Parser/List/NumberedListParser.h \
    Wiki/Parser/List/NumberedListParserTest.h \
    Wiki/Parser/Paragraph/ParagraphParser.h \
    Wiki/Parser/Paragraph/ParagraphParserTest.h \
    Wiki/Parser/Prerequisites.h \
    Wiki/Parser/Table/TableCellParser.h \
    Wiki/Parser/Table/TableCellParserTest.h \
    Wiki/Parser/Table/TableHeadParser.h \
    Wiki/Parser/Table/TableParser.h \
    Wiki/Parser/Table/TableParserTest.h \
    Wiki/Parser/Table/TableRowParser.h \
    Wiki/Parser/TestList.h \
    Wiki/Parser/TextBlock/TextBlockParser.h \
    Wiki/Parser/TextBlock/TextBlockParserTest.h \
    Wiki/Project.h \
    Wiki/Tree/Article/ArticleNode.h \
    Wiki/Tree/Article/ArticleNodeTest.h \
    Wiki/Tree/Attribute/AttributeGroupNode.h \
    Wiki/Tree/Attribute/AttributeNode.h \
    Wiki/Tree/BoldNode.h \
    Wiki/Tree/ExtensionTokenNode.h \
    Wiki/Tree/Heading/Heading.h \
    Wiki/Tree/Heading/HeadingNode.h \
    Wiki/Tree/Html/HtmlElementNode.h \
    Wiki/Tree/Html/HtmlEntityNode.h \
    Wiki/Tree/ItalicsNode.h \
    Wiki/Tree/Link/ExternalLinkNode.h \
    Wiki/Tree/Link/LinkNode.h \
    Wiki/Tree/Link/LinkOptionsNode.h \
    Wiki/Tree/Link/LinkTargetNode.h \
    Wiki/Tree/Link/LinkTargetNodeTest.h \
    Wiki/Tree/List/BulletListNode.h \
    Wiki/Tree/List/DefinitionListDefItemNode.h \
    Wiki/Tree/List/DefinitionListNode.h \
    Wiki/Tree/List/DefinitionListTermItemNode.h \
    Wiki/Tree/List/ListItemNode.h \
    Wiki/Tree/List/NumberedListNode.h \
    Wiki/Tree/Node.h \
    Wiki/Tree/ParagraphNode.h \
    Wiki/Tree/PreBlock/PreBlockNode.h \
    Wiki/Tree/PreBlock/PreLineNode.h \
    Wiki/Tree/Table/TableCaptionNode.h \
    Wiki/Tree/Table/TableCellNode.h \
    Wiki/Tree/Table/TableHeadNode.h \
    Wiki/Tree/Table/TableNode.h \
    Wiki/Tree/Table/TableRowNode.h \
    Wiki/Tree/TextBlockNode.h \
    Wiki/Tree/TextTokenNode.h \
    Wiki/Language/Language.h \
    Wiki/WikiSource.h \
    Wiki/WikiSourceCacheItem.h
SOURCES = \
    Debug/Debug.cpp \
    Debug/Profiler/Profiler.cpp \
    Debug/Profiler/ProfilerView.cpp \
    DictionaryFile/FileUtils.cpp \
    DictionaryFile/Format3Reader.cpp \
    DictionaryFile/Format4Reader.cpp \
    Media/MediaReader.cpp \
    Media/MediaUtils.cpp \
    Unicode.cpp \
    UrlUtils.cpp \
    Wiki/Namespace.cpp \
    Wiki/Parser/ArticleParser.cpp \
    Wiki/Parser/Block/BlockParser.cpp \
    Wiki/Parser/BoldItalic/BoldItalicParser.cpp \
    Wiki/Parser/BoldItalic/BoldItalicParserTest.cpp \
    Wiki/Parser/Buffer/Buffer.cpp \
    Wiki/Parser/Buffer/BufferTest.cpp \
    Wiki/Parser/Heading/HeadingParser.cpp \
    Wiki/Parser/Heading/HeadingParserTest.cpp \
    Wiki/Parser/Html/BlockHtmlParser.cpp \
    Wiki/Parser/Html/HtmlEntityParser.cpp \
    Wiki/Parser/Html/HtmlEntityParserTest.cpp \
    Wiki/Parser/Html/InlineHtmlParser.cpp \
    Wiki/Parser/Html/InlineHtmlParserTest.cpp \
    Wiki/Parser/Link/ExternalLinkParser.cpp \
    Wiki/Parser/Link/LinkParser.cpp \
    Wiki/Parser/Link/LinkParserTest.cpp \
    Wiki/Parser/List/BulletListParser.cpp \
    Wiki/Parser/List/BulletListParserTest.cpp \
    Wiki/Parser/List/DefinitionListParser.cpp \
    Wiki/Parser/List/ListParser.cpp \
    Wiki/Parser/List/ListParserTest.cpp \
    Wiki/Parser/List/NumberedListParser.cpp \
    Wiki/Parser/List/NumberedListParserTest.cpp \
    Wiki/Parser/Paragraph/ParagraphParser.cpp \
    Wiki/Parser/Paragraph/ParagraphParserTest.cpp \
    Wiki/Parser/Table/TableCellParser.cpp \
    Wiki/Parser/Table/TableCellParserTest.cpp \
    Wiki/Parser/Table/TableHeadParser.cpp \
    Wiki/Parser/Table/TableParser.cpp \
    Wiki/Parser/Table/TableParserTest.cpp \
    Wiki/Parser/Table/TableRowParser.cpp \
    Wiki/Parser/Table/TableCaptionParser.cpp \
    Wiki/Parser/TextBlock/TextBlockParser.cpp \
    Wiki/Parser/TextBlock/TextBlockParserTest.cpp \
    Wiki/Project.cpp \
    Wiki/Tree/Article/ArticleNode.cpp \
    Wiki/Tree/Article/ArticleNodeTest.cpp \
    Wiki/Tree/Attribute/AttributeGroupNode.cpp \
    Wiki/Tree/Attribute/AttributeNode.cpp \
    Wiki/Tree/BoldNode.cpp \
    Wiki/Tree/ExtensionTokenNode.cpp \
    Wiki/Tree/Heading/Heading.cpp \
    Wiki/Tree/Heading/HeadingNode.cpp \
    Wiki/Tree/Html/HtmlElementNode.cpp \
    Wiki/Tree/Html/HtmlEntityNode.cpp \
    Wiki/Tree/ItalicsNode.cpp \
    Wiki/Tree/Link/ExternalLinkNode.cpp \
    Wiki/Tree/Link/LinkNode.cpp \
    Wiki/Tree/Link/LinkOptionsNode.cpp \
    Wiki/Tree/Link/LinkTargetNode.cpp \
    Wiki/Tree/Link/LinkTargetNodeTest.cpp \
    Wiki/Tree/List/BulletListNode.cpp \
    Wiki/Tree/List/DefinitionListDefItemNode.cpp \
    Wiki/Tree/List/DefinitionListNode.cpp \
    Wiki/Tree/List/DefinitionListTermItemNode.cpp \
    Wiki/Tree/List/ListItemNode.cpp \
    Wiki/Tree/List/NumberedListNode.cpp \
    Wiki/Tree/Node.cpp \
    Wiki/Tree/ParagraphNode.cpp \
    Wiki/Tree/PreBlock/PreBlockNode.cpp \
    Wiki/Tree/PreBlock/PreLineNode.cpp \
    Wiki/Tree/Table/TableCaptionNode.cpp \
    Wiki/Tree/Table/TableCellNode.cpp \
    Wiki/Tree/Table/TableHeadNode.cpp \
    Wiki/Tree/Table/TableNode.cpp \
    Wiki/Tree/Table/TableRowNode.cpp \
    Wiki/Tree/TextBlockNode.cpp \
    Wiki/Tree/TextTokenNode.cpp \
    Wiki/Language/Language.cpp \
    Wiki/WikiSource.cpp \
    Wiki/WikiSourceCacheItem.cpp
