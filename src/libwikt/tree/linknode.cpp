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
#include "linknode.h"
#include "linktargetnode.h"
#include "linkoptionsnode.h"
#include "../mediautils.h"
#include <QImage>
#include <QSvgRenderer>
#include <QUrl>

LinkNode::LinkNode(bool emptyPipeAtEnd, bool forcedLink)
  : Node(Node::Link), _emptyPipeAtEnd(emptyPipeAtEnd),
  _forcedLink(forcedLink), _target(0)
{
}

QString LinkNode::toXHtml() const
{
  if (!_xhtmlVisible) return "";

  // Category links are not rendered to the XHTML output.
  if (!_forcedLink && target().namespace_() == Namespace::Category) return "";

  // Interwiki links are not rendered to the XHTML output.
  if (isInterwiki()) return "";

  // Images are rendered differently.
  if (isDisplayableImage())
    return toXHtmlImage();

  int opts = getOptionCount();
  if (opts == 1)
  {
    LinkOptionsNode *opt = getOption(0);
    return QString("<a href=\"%1\">%2</a>")
      .arg(target().toXHtmlLink())
      .arg(opt->toXHtml());
  }
  else
  {
    return QString("<a href=\"%1\">%2</a>")
      .arg(target().toXHtmlLink())
      .arg(target().toXHtml());
  }
}

QString LinkNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent +
    QString("<link emptyPipeAtEnd=\"%1\" forcedLink=\"%2\">\n")
      .arg(_emptyPipeAtEnd ? "true" : "false")
      .arg(_forcedLink ? "true" : "false") +
    childrenToXml(indentLevel+1) +
    indent + "</link>\n";
}

QString LinkNode::toText() const
{
  // Category links, interwiki links, and images are not rendered to the text output.
  if (!_forcedLink && target().namespace_() == Namespace::Category) return "";
  if (isInterwiki()) return "";
  if (isDisplayableImage()) return "";

  int opts = getOptionCount();
  if (opts == 1)
  {
    LinkOptionsNode *opt = getOption(0);
    return opt->toText();
  }
  else
    return target().toText();
}

QString LinkNode::toWiki() const
{
  QString result = "[[";
  if (forcedLink())
    result.append(':');
  result.append(target().toText());
  foreach(LinkOptionsNode *node, _options)
  {
    result.append('|');
    result.append(node->toText());
  }
  result.append("]]");
  return result;
}

QString LinkNode::toExternalLinkWiki() const
{
  QString result;
  QString baseUrl = Project::instance().toUrl(target().project(), target().language());
  QString namespaceUrl = Namespace::instance().toLocalizedName(target().namespace_());
  QString entryUrl = QString::fromAscii(QUrl::toPercentEncoding(target().entry()));

  if (namespaceUrl.length() > 0)
    entryUrl.prepend(namespaceUrl + ":");

  return QString("[%1%2 %3]").arg(baseUrl, entryUrl, xhtmlTitle());
}

void LinkNode::append(Node *child)
{
  Node::append(child);
  if (child->type() == Node::LinkTarget)
    _target = dynamic_cast<LinkTargetNode*>(child);
  else if (child->type() == Node::LinkOption)
    _options.append(dynamic_cast<LinkOptionsNode*>(child));
}

QString LinkNode::xhtmlTitle() const
{
  if (target().language() != Language::English)
    return Language::instance().toInterwikiName(target().language());

  int opts = getOptionCount();
  if (opts == 1)
  {
    LinkOptionsNode *opt = getOption(0);
    return opt->toXHtml();
  }
  else
    return target().toXHtml();
}

bool LinkNode::isInterwiki() const
{
  return !_forcedLink &&
    target().project() == Project::Wiktionary &&
    target().language() != Language::English;
}

bool LinkNode::isDisplayableImage() const
{
  if (_forcedLink) return false;
  if (target().namespace_() == Namespace::Image) return true;
  if (target().namespace_() == Namespace::File && 
      MediaUtils::imageTypeFromFileName(target().entry()) != MediaUtils::Invalid)
    return true;
  return false;
}

LinkNode::Image LinkNode::getImageParams() const
{
  Image image;

  // See http://en.wikipedia.org/wiki/Image_markup for a complete
  // list of options.

  // Parse options
  QString caption;
  foreach(LinkOptionsNode* option, _options)
  {
    QString text = option->toText();

    // THUMBNAIL option.
    if (text == "thumb" || text == "thumbnail")
    {
      image.size.setWidth(180);
      image.type = Image::Thumbnail;
      continue;
    }

    if (text == "frame")  { image.type = Image::Frame; continue; }
    if (text == "border") { image.type = Image::Border; continue; }
    if (text == "left")   { image.location = Image::Left; continue; }
    if (text == "right")  { image.location = Image::Right; continue; }
    if (text == "center") { image.location = Image::Center; continue; }
    if (text == "none")   { image.location = Image::None; continue; }

    // 333x666px option.
    QRegExp pxSize("(\\d+)x(\\d+)px");
    if (pxSize.indexIn(text) != -1)
    {
      bool ok;
      int requestedWidth = pxSize.cap(1).toInt(&ok, 10);
      if (!ok) continue;
      int requestedHeight = pxSize.cap(2).toInt(&ok, 10);
      if (!ok) continue;
      image.size = QSize(requestedWidth, requestedHeight);
      continue;
    }

    // 999px option.
    QRegExp pxWidth("(\\d+)px");
    if (pxWidth.indexIn(text) != -1)
    {
      bool ok;
      int requestedWidth = pxWidth.cap(1).toInt(&ok, 10);
      if (!ok) continue;
      image.size.setWidth(requestedWidth);
      continue;
    }

    image.caption = option->toXHtml();
  }

  return image;
}

QString LinkNode::toXHtmlImage() const
{
  Image image = getImageParams();
  QString style;
  if (image.size.width() >= 0)
    style += QString("max-width:%1px;").arg(image.size.width());
  if (image.size.height() >= 0)
    style += QString("max-height:%1px").arg(image.size.height());

  QString code;
  switch (image.type)
  {
  case Image::Thumbnail:
    code = QString("<div class=\"thumb tright\">");
    code += QString("<div class=\"thumbinner\" style=\"width:%1px;\">").arg(image.size.width());
    code += QString("<img src=\"%1\" style=\"%2\" border=\"0\" class=\"thumbimage\"/>")
      .arg(target().toXHtmlLink())
      .arg(style);
    code += QString("<div class=\"thumbcaption\">");
    code += QString("<div class=\"magnify\"><a href=\"http://en.wiktionary.org/wiki/File:%1\"><img src=\"embedded:///images/magnify-clip.png\"/></a></div>").arg(target().entry());
    code += image.caption;
    code += QString("</div>");
    code += QString("</div>");
    code += QString("</div>");
    break;
  case Image::Frame:
    code = QString("<div class=\"thumb tright\">");
    code += QString("<div class=\"thumbinner\" style=\"width:%1px;\">").arg(image.size.width());
    code += QString("<img src=\"%1\" style=\"%2\" border=\"0\" class=\"thumbimage\"/>")
      .arg(target().toXHtmlLink())
      .arg(style);
    code += QString("<div class=\"thumbcaption\">");
    code += image.caption;
    code += QString("</div>");
    code += QString("</div>");
    code += QString("</div>");
    break;
  case Image::Border:
    code = QString("<img src=\"%1\" style=\"%2\" border=\"0\" class=\"thumbborder\"/>")
    .arg(target().toXHtmlLink())
    .arg(style);
    break;
  case Image::Simple:
  default:
    code = QString("<img src=\"%1\" style=\"%2\" border=\"0\"/>")
    .arg(target().toXHtmlLink())
    .arg(style);
    break;
  }

  switch (image.location)
  {
  case Image::Left:
    code = QString("<div class=\"floatleft\">%1</div>").arg(code);
    break;
  case Image::Right:
    code = QString("<div class=\"floatright\">%1</div>").arg(code);
    break;
  case Image::Center:
    code = QString("<div class=\"center\"><div class=\"floatnone\">%1</div></div>").arg(code);
    break;
  case Image::None:
    code = QString("<div class=\"floatnone\">%1</div>").arg(code);
    break;
  case Image::Default:
  default:
    break;
  }

  return code;
}
