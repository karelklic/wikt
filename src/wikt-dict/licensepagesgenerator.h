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
/* This file is required by commandMidToDict. */
#ifndef LICENSEPAGESGENERATOR_H_
#define LICENSEPAGESGENERATOR_H_

class Format4Writer;

/// Creates two wiki pages with the text of licenses.
class LicensePagesGenerator
{
public:
  LicensePagesGenerator();

  void write(Format4Writer &destination);
};

#endif /* LICENSEPAGESGENERATOR_H_ */
