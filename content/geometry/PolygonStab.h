/**
 * Author: Hocky Yudhiono
 * Date: 2020-03-09
 * License: CC0
 * Source: own work
 * Description: Stab the polygon isi, with line a, b, find the longest segment with valid stab
 * Time: O(N^2 \log N)
 * Status: tested
 */

#include "Point.h"

P isi[1005];
template<class P>
P PolygonStab(P a, P b) {
  vector<intersectPoint> all;
  for (int k = 1; k <= n; k++) {
    auto res = lineInter(a, b, isi[k], isi[k + 1 <= n ? k + 1 : 1]);
    if (res.fi == 1 && onSegment(isi[k], isi[k + 1 <= n ? k + 1 : 1], res.se)) {
      all.pb({res.se, {a.ccw(b, isi[k]), a.ccw(b, isi[k + 1 <= n ? k + 1 : 1])}});
    }
  }
  sort(all.begin(), all.end());
  int isInside = -1, pre;
  LD curAns = 0; P lst;
  for (int k = 0; k < all.size(); k++) {
    if (isInside >= 0) curAns += (all[k].fi - all[k - 1].fi).dist();
    if (all[k].se.fi * all[k].se.se == -1) isInside = -isInside;
    else if (isInside == 0) isInside = (all[k].se.fi + all[k].se.se) * pre;
    else {
      pre = (all[k].se.fi + all[k].se.se) * isInside;
      isInside = 0;
    }
    ans = doubleMax(ans, curAns);
    if (isInside == -1) curAns = 0, lst = all[k + 1 <= (int)(all.size()) - 1 ? k + 1 : 0].fi;
  }
  return curAns;
}
