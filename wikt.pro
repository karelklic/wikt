TEMPLATE = app
TARGET = wikt
QT += core \
    gui \
    xml \
    xmlpatterns \
    network \
    svg \
    opengl \
    webkit \
    script \
    phonon \
    testlib
RESOURCES = wikt.qrc
HEADERS = src/Options/OptionsDialog.h \
    src/Categories/CategoriesItem.h \
    src/Categories/CategoriesModel.h \
    src/Categories/CategoriesPanel.h \
    src/Debug/Debug.h \
    src/Debug/ErrorDialog/ErrorDialog.h \
    src/Debug/HtmlSourceView.h \
    src/Debug/HtmlSyntaxHighlighter.h \
    src/Debug/Profiler/Profiler.h \
    src/Debug/Profiler/ProfilerView.h \
    src/Debug/UnitTest/UnitTestDialog.h \
    src/Debug/UnitTest/UnitTestRunner.h \
    src/Debug/WikiProcessingView.h \
    src/Debug/WikiSourceView.h \
    src/Debug/XmlSourceView.h \
    src/Debug/XmlSyntaxHighlighter.h \
    src/DictionaryFile/Comparsion.h \
    src/DictionaryFile/FileUtils.h \
    src/DictionaryFile/Format1ToFormat2/Format1Parser.h \
    src/DictionaryFile/Format1ToFormat2/Format1ToFormat2Dialog.h \
    src/DictionaryFile/Format1ToFormat2/Format2Writer.h \
    src/DictionaryFile/Format2ToFormat3/Format2Reader.h \
    src/DictionaryFile/Format2ToFormat3/Format2ToFormat3Converter.h \
    src/DictionaryFile/Format2ToFormat3/Format2ToFormat3Dialog.h \
    src/DictionaryFile/Format2ToFormat3/Format3Writer.h \
    src/DictionaryFile/Format2ToFormat3/FormattingFunctions/FormattingFunctions.h \
    src/DictionaryFile/Format2ToFormat3/FormattingFunctions/FormattingFunctionsTest.h \
    src/DictionaryFile/Format2ToFormat3/GalleryConverter.h \
    src/DictionaryFile/Format2ToFormat3/NamespaceUrlFunctions/NamespaceUrlFunctions.h \
    src/DictionaryFile/Format2ToFormat3/NamespaceUrlFunctions/NamespaceUrlFunctionsTest.h \
    src/DictionaryFile/Format2ToFormat3/PageNameFunctions/PageNameFunctions.h \
    src/DictionaryFile/Format2ToFormat3/PageNameFunctions/PageNameFunctionsTest.h \
    src/DictionaryFile/Format2ToFormat3/ParameterList.h \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/ExprDriver.h \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/ExprParser.tab.hpp \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/location.hh \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/position.hh \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/stack.hh \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ParserFunctions.h \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ParserFunctionsTest.h \
    src/DictionaryFile/Format2ToFormat3/TemplateSolver/TemplateSolver.h \
    src/DictionaryFile/Format2ToFormat3/TemplateSolver/TemplateSolverTest.h \
    src/DictionaryFile/Format2ToFormat3/TemplateUtils/TemplateUtils.h \
    src/DictionaryFile/Format2ToFormat3/TemplateUtils/TemplateUtilsTest.h \
    src/DictionaryFile/Format3ToFormat4/Format3Reader.h \
    src/DictionaryFile/Format3ToFormat4/Format3ToFormat4Converter.h \
    src/DictionaryFile/Format3ToFormat4/Format3ToFormat4Dialog.h \
    src/DictionaryFile/Format3ToFormat4/Format4Writer.h \
    src/DictionaryFile/Format3ToFormat4/LinkConverter/LinkConverter.h \
    src/DictionaryFile/Format3ToFormat4/LinkConverter/LinkConverterTest.h \
    src/DictionaryFile/Format4Reader.h \
    src/MainWindow/Coordinator.h \
    src/MainWindow/DisplayedPageHistory.h \
    src/MainWindow/FindPanel.h \
    src/MainWindow/LookupPanel.h \
    src/MainWindow/MainWindow.h \
    src/MainWindow/MenuBar.h \
    src/MainWindow/WebView/NetworkAccessManager.h \
    src/MainWindow/WebView/NetworkReplyEmbeddedFile.h \
    src/MainWindow/WebView/NetworkReplyEntry.h \
    src/MainWindow/WebView/NetworkReplyMediaFile.h \
    src/MainWindow/WebView/NetworkReplyStylesheet.h \
    src/MainWindow/WebView/NetworkReplyTitlePage.h \
    src/MainWindow/WebView/UrlUtils.h \
    src/MainWindow/WebView/UrlUtilsTest.h \
    src/MainWindow/WebView/WebView.h \
    src/Media/MediaDownloader.h \
    src/Media/MediaDownloaderDialog.h \
    src/Media/MediaPacker.h \
    src/Media/MediaPackerDialog.h \
    src/Media/MediaPlayer.h \
    src/Media/MediaReader.h \
    src/Media/MediaUtils.h \
    src/Media/MediaWriter.h \
    src/Prerequisites.h \
    src/RelatedPages/ExternalLinkItem.h \
    src/RelatedPages/ExternalLinksRootItem.h \
    src/RelatedPages/InternalLinkItem.h \
    src/RelatedPages/InterwikiRootItem.h \
    src/RelatedPages/Item.h \
    src/RelatedPages/Model.h \
    src/RelatedPages/Panel.h \
    src/RelatedPages/RootItem.h \
    src/TableOfContents/TocItem.h \
    src/TableOfContents/TocModel.h \
    src/TableOfContents/TocPanel.h \
    src/Unicode.h \
    src/Version.h \
    src/Wiki/Namespace.h \
    src/Wiki/Parser/ArticleParser.h \
    src/Wiki/Parser/Block/BlockParser.h \
    src/Wiki/Parser/BoldItalic/BoldItalicParser.h \
    src/Wiki/Parser/BoldItalic/BoldItalicParserTest.h \
    src/Wiki/Parser/Buffer/Buffer.h \
    src/Wiki/Parser/Buffer/BufferTest.h \
    src/Wiki/Parser/Heading/HeadingParser.h \
    src/Wiki/Parser/Heading/HeadingParserTest.h \
    src/Wiki/Parser/Html/BlockHtmlParser.h \
    src/Wiki/Parser/Html/HtmlEntityParser.h \
    src/Wiki/Parser/Html/HtmlEntityParserTest.h \
    src/Wiki/Parser/Html/InlineHtmlParser.h \
    src/Wiki/Parser/Html/InlineHtmlParserTest.h \
    src/Wiki/Parser/Link/ExternalLinkParser.h \
    src/Wiki/Parser/Link/LinkParser.h \
    src/Wiki/Parser/Link/LinkParserTest.h \
    src/Wiki/Parser/List/BulletListParser.h \
    src/Wiki/Parser/List/BulletListParserTest.h \
    src/Wiki/Parser/List/DefinitionListParser.h \
    src/Wiki/Parser/List/ListParser.h \
    src/Wiki/Parser/List/ListParserTest.h \
    src/Wiki/Parser/List/NumberedListParser.h \
    src/Wiki/Parser/List/NumberedListParserTest.h \
    src/Wiki/Parser/Paragraph/ParagraphParser.h \
    src/Wiki/Parser/Paragraph/ParagraphParserTest.h \
    src/Wiki/Parser/Prerequisites.h \
    src/Wiki/Parser/Table/TableCellParser.h \
    src/Wiki/Parser/Table/TableCellParserTest.h \
    src/Wiki/Parser/Table/TableHeadParser.h \
    src/Wiki/Parser/Table/TableParser.h \
    src/Wiki/Parser/Table/TableParserTest.h \
    src/Wiki/Parser/Table/TableRowParser.h \
    src/Wiki/Parser/TestList.h \
    src/Wiki/Parser/TextBlock/TextBlockParser.h \
    src/Wiki/Parser/TextBlock/TextBlockParserTest.h \
    src/Wiki/Project.h \
    src/Wiki/Tree/Article/ArticleNode.h \
    src/Wiki/Tree/Article/ArticleNodeTest.h \
    src/Wiki/Tree/Attribute/AttributeGroupNode.h \
    src/Wiki/Tree/Attribute/AttributeNode.h \
    src/Wiki/Tree/BoldNode.h \
    src/Wiki/Tree/ExtensionTokenNode.h \
    src/Wiki/Tree/Heading/Heading.h \
    src/Wiki/Tree/Heading/HeadingNode.h \
    src/Wiki/Tree/Html/HtmlElementNode.h \
    src/Wiki/Tree/Html/HtmlEntityNode.h \
    src/Wiki/Tree/ItalicsNode.h \
    src/Wiki/Tree/Link/ExternalLinkNode.h \
    src/Wiki/Tree/Link/LinkNode.h \
    src/Wiki/Tree/Link/LinkOptionsNode.h \
    src/Wiki/Tree/Link/LinkTargetNode.h \
    src/Wiki/Tree/Link/LinkTargetNodeTest.h \
    src/Wiki/Tree/List/BulletListNode.h \
    src/Wiki/Tree/List/DefinitionListDefItemNode.h \
    src/Wiki/Tree/List/DefinitionListNode.h \
    src/Wiki/Tree/List/DefinitionListTermItemNode.h \
    src/Wiki/Tree/List/ListItemNode.h \
    src/Wiki/Tree/List/NumberedListNode.h \
    src/Wiki/Tree/Node.h \
    src/Wiki/Tree/ParagraphNode.h \
    src/Wiki/Tree/PreBlock/PreBlockNode.h \
    src/Wiki/Tree/PreBlock/PreLineNode.h \
    src/Wiki/Tree/Table/TableCaptionNode.h \
    src/Wiki/Tree/Table/TableCellNode.h \
    src/Wiki/Tree/Table/TableHeadNode.h \
    src/Wiki/Tree/Table/TableNode.h \
    src/Wiki/Tree/Table/TableRowNode.h \
    src/Wiki/Tree/TextBlockNode.h \
    src/Wiki/Tree/TextTokenNode.h \
    src/Wiki/Language/Language.h \
    src/Wiki/WikiSource.h \
    src/Wiki/WikiSourceCacheItem.h
SOURCES = src/Options/OptionsDialog.cpp \
    src/Categories/CategoriesItem.cpp \
    src/Categories/CategoriesModel.cpp \
    src/Categories/CategoriesPanel.cpp \
    src/Debug/Debug.cpp \
    src/Debug/ErrorDialog/ErrorDialog.cpp \
    src/Debug/HtmlSourceView.cpp \
    src/Debug/HtmlSyntaxHighlighter.cpp \
    src/Debug/Profiler/Profiler.cpp \
    src/Debug/Profiler/ProfilerView.cpp \
    src/Debug/UnitTest/UnitTestDialog.cpp \
    src/Debug/UnitTest/UnitTestRunner.cpp \
    src/Debug/WikiProcessingView.cpp \
    src/Debug/WikiSourceView.cpp \
    src/Debug/XmlSourceView.cpp \
    src/Debug/XmlSyntaxHighlighter.cpp \
    src/DictionaryFile/FileUtils.cpp \
    src/DictionaryFile/Format1ToFormat2/Format1Parser.cpp \
    src/DictionaryFile/Format1ToFormat2/Format1ToFormat2Dialog.cpp \
    src/DictionaryFile/Format1ToFormat2/Format2Writer.cpp \
    src/DictionaryFile/Format2ToFormat3/Format2Reader.cpp \
    src/DictionaryFile/Format2ToFormat3/Format2ToFormat3Converter.cpp \
    src/DictionaryFile/Format2ToFormat3/Format2ToFormat3Dialog.cpp \
    src/DictionaryFile/Format2ToFormat3/Format3Writer.cpp \
    src/DictionaryFile/Format2ToFormat3/FormattingFunctions/FormattingFunctions.cpp \
    src/DictionaryFile/Format2ToFormat3/FormattingFunctions/FormattingFunctionsTest.cpp \
    src/DictionaryFile/Format2ToFormat3/GalleryConverter.cpp \
    src/DictionaryFile/Format2ToFormat3/NamespaceUrlFunctions/NamespaceUrlFunctions.cpp \
    src/DictionaryFile/Format2ToFormat3/NamespaceUrlFunctions/NamespaceUrlFunctionsTest.cpp \
    src/DictionaryFile/Format2ToFormat3/PageNameFunctions/PageNameFunctions.cpp \
    src/DictionaryFile/Format2ToFormat3/PageNameFunctions/PageNameFunctionsTest.cpp \
    src/DictionaryFile/Format2ToFormat3/ParameterList.cpp \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/ExprDriver.cpp \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/ExprParser.tab.cpp \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ExprParser/ExprScanner.cpp \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ParserFunctions.cpp \
    src/DictionaryFile/Format2ToFormat3/ParserFunctions/ParserFunctionsTest.cpp \
    src/DictionaryFile/Format2ToFormat3/TemplateSolver/TemplateSolver.cpp \
    src/DictionaryFile/Format2ToFormat3/TemplateSolver/TemplateSolverTest.cpp \
    src/DictionaryFile/Format2ToFormat3/TemplateUtils/TemplateUtils.cpp \
    src/DictionaryFile/Format2ToFormat3/TemplateUtils/TemplateUtilsTest.cpp \
    src/DictionaryFile/Format3ToFormat4/Format3Reader.cpp \
    src/DictionaryFile/Format3ToFormat4/Format3ToFormat4Converter.cpp \
    src/DictionaryFile/Format3ToFormat4/Format3ToFormat4Dialog.cpp \
    src/DictionaryFile/Format3ToFormat4/Format4Writer.cpp \
    src/DictionaryFile/Format3ToFormat4/LinkConverter/LinkConverter.cpp \
    src/DictionaryFile/Format3ToFormat4/LinkConverter/LinkConverterTest.cpp \
    src/DictionaryFile/Format4Reader.cpp \
    src/Main.cpp \
    src/MainWindow/Coordinator.cpp \
    src/MainWindow/DisplayedPageHistory.cpp \
    src/MainWindow/FindPanel.cpp \
    src/MainWindow/LookupPanel.cpp \
    src/MainWindow/MainWindow.cpp \
    src/MainWindow/MenuBar.cpp \
    src/MainWindow/WebView/NetworkAccessManager.cpp \
    src/MainWindow/WebView/NetworkReplyEmbeddedFile.cpp \
    src/MainWindow/WebView/NetworkReplyEntry.cpp \
    src/MainWindow/WebView/NetworkReplyMediaFile.cpp \
    src/MainWindow/WebView/NetworkReplyStylesheet.cpp \
    src/MainWindow/WebView/NetworkReplyTitlePage.cpp \
    src/MainWindow/WebView/UrlUtils.cpp \
    src/MainWindow/WebView/UrlUtilsTest.cpp \
    src/MainWindow/WebView/WebView.cpp \
    src/Media/MediaDownloader.cpp \
    src/Media/MediaDownloaderDialog.cpp \
    src/Media/MediaPacker.cpp \
    src/Media/MediaPackerDialog.cpp \
    src/Media/MediaPlayer.cpp \
    src/Media/MediaReader.cpp \
    src/Media/MediaUtils.cpp \
    src/Media/MediaWriter.cpp \
    src/RelatedPages/ExternalLinkItem.cpp \
    src/RelatedPages/ExternalLinksRootItem.cpp \
    src/RelatedPages/InternalLinkItem.cpp \
    src/RelatedPages/InterwikiRootItem.cpp \
    src/RelatedPages/Item.cpp \
    src/RelatedPages/Model.cpp \
    src/RelatedPages/Panel.cpp \
    src/RelatedPages/RootItem.cpp \
    src/TableOfContents/TocItem.cpp \
    src/TableOfContents/TocModel.cpp \
    src/TableOfContents/TocPanel.cpp \
    src/Unicode.cpp \
    src/Wiki/Namespace.cpp \
    src/Wiki/Parser/ArticleParser.cpp \
    src/Wiki/Parser/Block/BlockParser.cpp \
    src/Wiki/Parser/BoldItalic/BoldItalicParser.cpp \
    src/Wiki/Parser/BoldItalic/BoldItalicParserTest.cpp \
    src/Wiki/Parser/Buffer/Buffer.cpp \
    src/Wiki/Parser/Buffer/BufferTest.cpp \
    src/Wiki/Parser/Heading/HeadingParser.cpp \
    src/Wiki/Parser/Heading/HeadingParserTest.cpp \
    src/Wiki/Parser/Html/BlockHtmlParser.cpp \
    src/Wiki/Parser/Html/HtmlEntityParser.cpp \
    src/Wiki/Parser/Html/HtmlEntityParserTest.cpp \
    src/Wiki/Parser/Html/InlineHtmlParser.cpp \
    src/Wiki/Parser/Html/InlineHtmlParserTest.cpp \
    src/Wiki/Parser/Link/ExternalLinkParser.cpp \
    src/Wiki/Parser/Link/LinkParser.cpp \
    src/Wiki/Parser/Link/LinkParserTest.cpp \
    src/Wiki/Parser/List/BulletListParser.cpp \
    src/Wiki/Parser/List/BulletListParserTest.cpp \
    src/Wiki/Parser/List/DefinitionListParser.cpp \
    src/Wiki/Parser/List/ListParser.cpp \
    src/Wiki/Parser/List/ListParserTest.cpp \
    src/Wiki/Parser/List/NumberedListParser.cpp \
    src/Wiki/Parser/List/NumberedListParserTest.cpp \
    src/Wiki/Parser/Paragraph/ParagraphParser.cpp \
    src/Wiki/Parser/Paragraph/ParagraphParserTest.cpp \
    src/Wiki/Parser/Table/TableCellParser.cpp \
    src/Wiki/Parser/Table/TableCellParserTest.cpp \
    src/Wiki/Parser/Table/TableHeadParser.cpp \
    src/Wiki/Parser/Table/TableParser.cpp \
    src/Wiki/Parser/Table/TableParserTest.cpp \
    src/Wiki/Parser/Table/TableRowParser.cpp \
    src/Wiki/Parser/TextBlock/TextBlockParser.cpp \
    src/Wiki/Parser/TextBlock/TextBlockParserTest.cpp \
    src/Wiki/Project.cpp \
    src/Wiki/Tree/Article/ArticleNode.cpp \
    src/Wiki/Tree/Article/ArticleNodeTest.cpp \
    src/Wiki/Tree/Attribute/AttributeGroupNode.cpp \
    src/Wiki/Tree/Attribute/AttributeNode.cpp \
    src/Wiki/Tree/BoldNode.cpp \
    src/Wiki/Tree/ExtensionTokenNode.cpp \
    src/Wiki/Tree/Heading/Heading.cpp \
    src/Wiki/Tree/Heading/HeadingNode.cpp \
    src/Wiki/Tree/Html/HtmlElementNode.cpp \
    src/Wiki/Tree/Html/HtmlEntityNode.cpp \
    src/Wiki/Tree/ItalicsNode.cpp \
    src/Wiki/Tree/Link/ExternalLinkNode.cpp \
    src/Wiki/Tree/Link/LinkNode.cpp \
    src/Wiki/Tree/Link/LinkOptionsNode.cpp \
    src/Wiki/Tree/Link/LinkTargetNode.cpp \
    src/Wiki/Tree/Link/LinkTargetNodeTest.cpp \
    src/Wiki/Tree/List/BulletListNode.cpp \
    src/Wiki/Tree/List/DefinitionListDefItemNode.cpp \
    src/Wiki/Tree/List/DefinitionListNode.cpp \
    src/Wiki/Tree/List/DefinitionListTermItemNode.cpp \
    src/Wiki/Tree/List/ListItemNode.cpp \
    src/Wiki/Tree/List/NumberedListNode.cpp \
    src/Wiki/Tree/Node.cpp \
    src/Wiki/Tree/ParagraphNode.cpp \
    src/Wiki/Tree/PreBlock/PreBlockNode.cpp \
    src/Wiki/Tree/PreBlock/PreLineNode.cpp \
    src/Wiki/Tree/Table/TableCaptionNode.cpp \
    src/Wiki/Tree/Table/TableCellNode.cpp \
    src/Wiki/Tree/Table/TableHeadNode.cpp \
    src/Wiki/Tree/Table/TableNode.cpp \
    src/Wiki/Tree/Table/TableRowNode.cpp \
    src/Wiki/Tree/TextBlockNode.cpp \
    src/Wiki/Tree/TextTokenNode.cpp \
    src/Wiki/Language/Language.cpp \
    src/Wiki/WikiSource.cpp \
    src/Wiki/WikiSourceCacheItem.cpp
FORMS = src/Options/OptionsDialog.ui \
    src/Debug/ErrorDialog/ErrorDialog.ui \
    src/Debug/UnitTest/UnitTestDialog.ui \
    src/DictionaryFile/Format1ToFormat2/Format1ToFormat2Dialog.ui \
    src/DictionaryFile/Format2ToFormat3/Format2ToFormat3Dialog.ui \
    src/DictionaryFile/Format3ToFormat4/Format3ToFormat4Dialog.ui \
    src/Media/MediaDownloaderDialog.ui \
    src/Media/MediaPackerDialog.ui
