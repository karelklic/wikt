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
#ifndef PROFILER_H_
#define PROFILER_H_

#include <QString>

/// Uncomment the following line to enable embedded profiler.
//#define PROFILER_ENABLED

#ifdef PROFILER_ENABLED
#define PROFILER ProfilerBlock __profBlockInstance(__PRETTY_FUNCTION__)
#define PROFILER_RESULTS Profiler::saveResultsToFile("profiler.txt")
#else
#define PROFILER {}
#define PROFILER_RESULTS {}
#endif

class Profiler
{
public:
  static void begin(const char *fn);
  static void end();
  static void saveResultsToFile(const QString &fileName);
  static void showResultsInWindow();
  /// Removes all measured data.
  static void clear();

protected:
  /// Calculates how many ticks reported by RDTSC the computer uses
  /// in one second.
  /// This method takes 0.5 second to run.
  static unsigned long long clockPerSec();
};

/// Manages profiler inside a code block.
class ProfilerBlock
{
public:
  ProfilerBlock(const char *fn) { Profiler::begin(fn); }
  ~ProfilerBlock() { Profiler::end(); }
};

#endif /* PROFILER_H_ */
