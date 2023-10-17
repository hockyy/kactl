/**
 * Author: Takanori Maehara
 * Date: 2015-09-01
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc
 * Description: Get the maximum amount of point coverable by a circle with radius r
 * Time: O(n \log^2 n)
 * Status: Verified https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1132
 */
#include "Point.h"
int maxCircleCover(vector<P> ps, double r) {
  const double dx[] = {1, -1, -1, 1}, dy[] = {1, 1, -1, -1};
  P best_p;
  int best = 0;
  function<void(P, double, vector<P>)>
  rec = [&](P p, double w, vector<P> ps) {
    w /= 2;
    P qs[4];
    vector<P> pss[4];
    for (int i = 0; i < 4; ++i) {
      qs[i] = p + P(dx[i], dy[i]) * w;
      int lo = 0;
      for (P q : ps) {
        auto d = (qs[i] - q).dist();
        if (sgn(d - r) <= 0) ++lo;
        if (sgn(d - w * sqrt(2) - r) <= 0) pss[i].push_back(q);
      }
      if (lo > best) { best = lo; best_p = qs[i]; }
    }
    for (int i = 0, j; i < 4; ++i) {
      for (int j = i + 1; j < 4; ++j)
        if (pss[i].size() < pss[j].size())
          swap(pss[i], pss[j]), swap(qs[i], qs[j]);
      if (pss[i].size() <= best) break;
      rec(qs[i], w, pss[i]);
    }
  };
  double w = 0;
  for (P p : ps) w = max(w, max(abs(p.x), abs(p.y)));
  rec(P(0, 0), w, ps);
  return best; //best_p;
}
