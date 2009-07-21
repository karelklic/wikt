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
#include "LinkConverter.h"
#include "../Format3Reader.h"
#include "../../../Media/MediaReader.h"
#include "../../../Wiki/Parser/Link/LinkParser.h"
#include "../../../Wiki/Tree/Link/LinkNode.h"
#include <QUrl>

//===========================================================================
LinkConverter::LinkConverter(Format3Reader &reader, MediaReader &mediaReader)
  : _reader(reader), _mediaReader(mediaReader)
{
}

//===========================================================================
QString LinkConverter::convertedContents(int offs)
{
  QString input = _reader.sourceDirect(offs);
  QString output;
  output.reserve(input.length());

  for (int i = 0; i < input.length(); ++i)
  {
    if (input[i] != '[')
    {
      output.append(input[i]);
      continue;
    }

    Buffer buffer(input.mid(i));
    LinkNode *node = LinkParser::parse(buffer);
    if (!node)
    {
      output.append(input[i]);
      continue;
    }

    // skip interwiki links
    if (node->target().language() != Language::English)
    {
      delete node;
      output.append(input[i]);
      continue;
    }

    // make external link from links to other projects
    if (node->target().project() != Project::Wiktionary)
    {
      output.append(node->toExternalLinkWiki());
      delete node;
      i += buffer.pos() - 1;
      continue;
    }

    // Handle images and sounds.
    if (node->target().namespace_() == Namespace::Image ||
        node->target().namespace_() == Namespace::Media ||
        node->target().namespace_() == Namespace::File)
    {
      if (_mediaReader.exist(node->target().entry()))
        output.append(node->toWiki());
      else
        output.append(node->xhtmlTitle());
    }
    else
    {
      // Prepare name to be searched.
      // Prepend namespace if the link contains it.
      QString entryName = node->target().entry();
      if (node->target().namespace_() != Namespace::Main)
      {
        QString nsName = Namespace::instance().toLocalizedName(node->target().namespace_());
        entryName.prepend(nsName + ":");
      }

      // Check for existence.
      if (_reader.exist(entryName))
        output.append(node->toWiki());
      else
        output.append(node->xhtmlTitle());
    }

    delete node;

    // Set the position in the source *after* the processed link.
    // [[a]]$
    // 012345
    i += buffer.pos() - 1;
  }

  return output;
}

