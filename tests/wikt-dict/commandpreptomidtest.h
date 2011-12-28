/* This file is part of Wikt.
 *
 * Wikt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Wikt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wikt. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CONVDICT23TEST_H
#define CONVDICT23TEST_H
#include <QTest>
#include <QObject>

class CommandPrepToMidTest : public QObject
{
  Q_OBJECT
private slots:
  void formattingFunctions_basic();
  void formattingFunctions_formatNum();
  void namespaceUrlFunctions_ns();
  void namespaceUrlFunctions_fullUrl();
  void namespaceUrlFunctions_urlencode();
  void pageNameFunctions_pageName();
  void pageNameFunctions_pageNameE();
  void pageNameFunctions_basePageName();
  void pageNameFunctions_basePageNameE();
  void pageNameFunctions_subPageName();
  void pageNameFunctions_subPageNameE();
  void pageNameFunctions_fullPageName();
  void pageNameFunctions_fullPageNameE();
  void pageNameFunctions_nameSpace();
  void pageNameFunctions_nameSpaceE();
  void parserFunctions_if();
  void parserFunctions_ifEq();
  void parserFunctions_switch();
  void parserFunctions_expr();
  void templateSolver_declaringDefaultValue();
  void templateSolver_moreBraces();
  /// Checks a bug with embedded links during template evaluation.
  void templateSolver_formOf();
  /// Checks a bug.
  void templateSolver_isValidPageName();
  /// Checks a bug with evaluated wikisyntax.
  void templateSolver_evaluatedWikiSyntaxSimple();
  /// Checks a cite bug.
  void templateSolver_newlineAddingInTemplates();
  /// Check for [[Template:plural of]] failing for [[stadiums]].
  void templateSolver_pluralOf();
  void templateSolver_embeddedLink();
  void templateUtils_addParameterToList0();
  void templateUtils_addParameterToList1();
  void templateUtils_getParts();
  void templateUtils_evaluateParameter();
};

#endif
