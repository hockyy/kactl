/**
 * Author: Hocky Yudhiono
 * Date: 2023-10-15
 * License: CC0
 * Source: https://codeforces.com/gym/104160/submission/226742278
 * Description: Given a simple polygon, for all pair,
 * compute whether the two index's segment lies entirely inside the polygon
 * Time: O(N^3)
 * Status: Verified https://codeforces.com/gym/104160/problem/K
 */
#include "segInter.h"
#include "inPolygon.h"
int isBad[205][205];
 
template<class P>
int solve(int u, int v, const vector <P> &poly) {
  if (u == v) return 0;
  if (u > v) return solve(v, u, poly);
  int &ret = isBad[u][v];
  if (~ret) return ret;
  int n = sz(poly);
  rep(k, 0, n) {
    if (k == u || k == v || (k + 1) % n == u || (k + 1) % n == v) continue;
    auto &a = poly[k], &b = poly[(k + 1) % n];
    auto &c = poly[u], &d = poly[v];
    if (onSegment(c, d, a)) return ret = solve(u, k, poly) || solve(k, v, poly);
    if (onSegment(c, d, b)) return ret = solve(u, (k + 1) % n, poly) || solve((k + 1) % n, v, poly);
    auto res = segInter(a, b, c, d);
    if (res) return ret = 1;
  }
 
  return ret = !inPolygon(poly, (poly[u] + poly[v]) / 2, false);
}