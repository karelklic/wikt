#include "TemplateSolverTest.h"
#include <QTest>
#include <QApplication>

#define TEST(__class) { __class c; QTest::qExec(&c); }

//===========================================================================
int main(int argc, char **argv)
{
  QApplication a(argc, argv);

  TEST(TemplateSolverTest);

  return 0;
}

