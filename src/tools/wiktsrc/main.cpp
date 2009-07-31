#include <libwikt/DictionaryFile/Format4Reader.h>
#include <libwikt/Wiki/Parser/ArticleParser.h>
#include <QTextStream>
#include <QCoreApplication>
#include <QStringList>

//==============================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  static const QString PATH_A("../data/");
  static const QString PATH_B("/usr/share/wikt/");
  QString dictionaryData;
  static const QString DICT_NAME("enwiktionary-20090203-pages-articles.ei4");
  if (QFile::exists(PATH_A + DICT_NAME))
    dictionaryData = PATH_A + DICT_NAME;
  else if (QFile::exists(PATH_B + DICT_NAME))
    dictionaryData = PATH_B + DICT_NAME;

  QStringList args = a.arguments();
  QString word = args.last();
  args.removeLast();
  bool exist = args.contains("--exists") || args.contains("--exist") || args.contains("-e");
  bool xml = args.contains("--xml") || args.contains("-x");

  Format4Reader reader(dictionaryData);
  QTextStream out(stdout, QIODevice::WriteOnly);
  if (xml)
  {
    QString source = reader.source(word);
    ArticleNode *node = ArticleParser::parse(word, source);
    out << node->toXml() << endl;
    delete node;
  }
  else
  {
    if (exist)
      out << (reader.exist(word) ? "Yes" : "No") << endl;
    else
      out << reader.source(word) << endl;
  }

  return 0;
}

