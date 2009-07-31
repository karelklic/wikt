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
#include "Profiler.h"
#include "ProfilerView.h"

#include <map>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstring>
#include <QFile>

/// A time profile of a function or method.
struct SProfilerOffRecord
{
  const char *fn; // nazev funkce
  /// Total time spent in the function.
  unsigned long long totalt;
  /// Number of function calls.
  unsigned cnt;
  /// Minimal time spent by one function call.
  unsigned long long min;
  /// Maximal time spent by one function call.
  unsigned long long max; // max. cas straveny jednim volanim fce

  unsigned long long timestamp;
  unsigned long long pausestamp;
};

struct SProfilerRecRecord
{
  unsigned long long timestamp;
  unsigned long long pausestamp;
};

typedef std::map<quint32, SProfilerOffRecord> offmap;
typedef std::stack<quint32> hashstack;
typedef std::stack<SProfilerRecRecord> recstack_t;
static offmap offlist;
static hashstack callstack;
static recstack_t recstack;

//=============================================================================
extern __inline__ unsigned long long int rdtsc()
{
  unsigned long long int x;
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
  return x;
}

//=============================================================================
static quint32 hash(const char *str)
{
  quint32 hash = 5381;
  while (int c = *str++) hash = ((hash << 5) + hash) + c;
  return hash;
}

//=============================================================================
void Profiler::begin(const char *fn)
{
  quint32 h = hash(fn);
  offmap::iterator it = offlist.find(h);
  if (it == offlist.end())
  {
    SProfilerOffRecord offRecord;
    offRecord.fn = fn;
    offRecord.totalt = offRecord.max = 0;
    offRecord.cnt = 0;
    offRecord.min = -1;
    offRecord.pausestamp = offRecord.timestamp = 0;
    offlist.insert(std::pair<quint32, SProfilerOffRecord>(h, offRecord));
    it = offlist.find(h);
    assert(it != offlist.end());
  }

  if (!callstack.empty())
  {
    offmap::iterator sit = offlist.find(callstack.top());
    /// Stop counting the time for the parent function.
    sit->second.pausestamp = rdtsc();
  }

  if (it->second.pausestamp > 0)
  {
    // Recursive function, paused.
    SProfilerRecRecord r;
    r.pausestamp = it->second.pausestamp;
    r.timestamp = it->second.timestamp;
    recstack.push(r);
    it->second.pausestamp = 0;
  }

  it->second.timestamp = rdtsc();
  callstack.push(h);
}

//=============================================================================
void Profiler::end()
{
  offmap::iterator sit = offlist.find(callstack.top());
  sit->second.pausestamp = rdtsc();
  sit->second.pausestamp -= sit->second.timestamp;
  sit->second.totalt += sit->second.pausestamp;
  sit->second.min = std::min(sit->second.min, sit->second.pausestamp);
  sit->second.max = std::max(sit->second.max, sit->second.pausestamp);
  ++sit->second.cnt;
  sit->second.pausestamp = sit->second.timestamp = 0;
  callstack.pop();

  if (callstack.empty())
    return;

  sit = offlist.find(callstack.top());
  if (sit->second.pausestamp <= 0)
  {
    assert(!recstack.empty());
    sit->second.pausestamp = recstack.top().pausestamp;
    sit->second.timestamp = recstack.top().timestamp;
    recstack.pop();
  }

  sit->second.pausestamp -= sit->second.timestamp;
  sit->second.timestamp = rdtsc();
  sit->second.timestamp -= sit->second.pausestamp;
  sit->second.pausestamp = 0;
}

//=============================================================================
static bool cmp(const SProfilerOffRecord &a, const SProfilerOffRecord &b) {
  return a.totalt > b.totalt;
}

//=============================================================================
/// For Profiler::saveResultsToFile
static std::string format(unsigned long long val, unsigned long long clockPerSec)
{
  const int clocksPerMSec = clockPerSec / 1000;
  const int clocksPerUSec = clockPerSec / 1000000;
  std::stringstream ret;

  // Seconds
  if (0 < val / clockPerSec)
    ret << val / clockPerSec << "s";

  // Milliseconds
  clock_t lessThanSecond = val % clockPerSec;
  if (0 < lessThanSecond / clocksPerMSec)
    ret << lessThanSecond / clocksPerMSec << "ms";

  // Microseconds
  clock_t lessThanMillisecond = lessThanSecond % clocksPerMSec;
  if (0 < lessThanMillisecond / clocksPerUSec)
    ret << lessThanMillisecond / clocksPerUSec << "us";

  std::string result = ret.str();
  if (result.length() == 0)
    result = "0us";
  return result;
}

//=============================================================================
/// For Profiler::saveResultsToFile
static void widths(unsigned long long clockPerSec, unsigned &wfn,
    unsigned &wtotal, unsigned &wavg, unsigned &wmin, unsigned &wmax)
{
  wfn = wtotal = wavg = wmin = wmax = 0;
  for (offmap::iterator it = offlist.begin(); it != offlist.end(); ++it)
  {
    wfn =    std::max(wfn,    (unsigned)std::strlen(it->second.fn));
    wtotal = std::max(wtotal, (unsigned)format(it->second.totalt, clockPerSec).length());
    wavg = std::max(wavg, (unsigned)format((it->second.totalt/it->second.cnt), clockPerSec).length());
    wmin = std::max(wmin, (unsigned)format(it->second.min, clockPerSec).length());
    wmax = std::max(wmax, (unsigned)format(it->second.max, clockPerSec).length());
  }
  ++wfn; ++wtotal; ++wavg; ++wmin; ++wmax;
}

//=============================================================================
void Profiler::saveResultsToFile(const QString &fileName)
{
  typedef std::vector<SProfilerOffRecord> recvec;
  recvec sorted;
  for (offmap::iterator it = offlist.begin(); it != offlist.end(); ++it)
    sorted.push_back(it->second);
  std::sort(sorted.begin(), sorted.end(), cmp);

  unsigned long long clocks = clockPerSec();
  unsigned wfn, wtotal, wavg, wmin, wmax;
  widths(clocks, wfn, wtotal, wavg, wmin, wmax);

  using namespace std;
  stringstream fp;
  fp << setw(wfn) << "Name" << setw(wtotal) << "Total" << setw(6) << "Count" <<
    setw(wavg) << "Avg" << setw(wmax) << "Max" << setw(wmin) << "Min" << endl;
  fp << "------------------------------------------------------------------"
    "--------------------------------------------------------------------"
    "------------------------" << endl;

  for (recvec::iterator it = sorted.begin(); it != sorted.end(); ++it)
  {
    fp << setw(wfn)    << it->fn
       << setw(wtotal) << format(it->totalt, clocks)
       << setw(10)     << it->cnt
       << setw(wavg)   << format(it->totalt/it->cnt, clocks)
       << setw(wmax)   << format(it->max, clocks)
       << setw(wmin)   << format(it->min, clocks) << endl;
  }

  QFile output(fileName);
  output.open(QFile::WriteOnly);
  output.write(fp.str().c_str());
  output.close();
}

//=============================================================================
void Profiler::showResultsInWindow()
{
  ProfilerView *view = new ProfilerView();

  typedef std::vector<SProfilerOffRecord> recvec;
  recvec sorted;
  for (offmap::iterator it = offlist.begin(); it != offlist.end(); ++it)
    sorted.push_back(it->second);
  std::sort(sorted.begin(), sorted.end(), cmp);

  unsigned long long clocks = clockPerSec();
  view->setRowCount(sorted.size());
  view->setColumnCount(6);
  view->setHorizontalHeaderItem(0, "Name");
  view->setHorizontalHeaderItem(1, "Total");
  view->setHorizontalHeaderItem(2, "Count");
  view->setHorizontalHeaderItem(3, "Average");
  view->setHorizontalHeaderItem(4, "Maximum");
  view->setHorizontalHeaderItem(5, "Minimum");
  for (recvec::iterator it = sorted.begin(); it != sorted.end(); ++it)
  {
    int row = it - sorted.begin();
    view->setItem(row, 0, it->fn);
    view->setItem(row, 1, QString::fromStdString(format(it->totalt, clocks)));
    view->setItem(row, 2, QString("%1").arg(it->cnt));
    view->setItem(row, 3, QString::fromStdString(format(it->totalt/it->cnt, clocks)));
    view->setItem(row, 4, QString::fromStdString(format(it->max, clocks)));
    view->setItem(row, 5, QString::fromStdString(format(it->min, clocks)));
  }

  view->show();
}

//=============================================================================
void Profiler::clear()
{
  offlist.clear();
  callstack = hashstack();
  recstack = recstack_t();
}

//=============================================================================
unsigned long long Profiler::clockPerSec()
{
  std::clock_t start = clock();
  unsigned long long start2 = rdtsc();
  while (clock() - start < (CLOCKS_PER_SEC / 2)) {}
  return (rdtsc() - start2) * 2;
}

