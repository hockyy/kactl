/**
 * Author: Neroysq
 * Date: 2012-05-15
 * License: CC0
 * Source: https://github.com/Neroysq/Neroysq-SPOJ/commits/master/Codes/CIRUT.cpp
 * Description: Given N circles, for each K, find the area of Kth-region
 * Time: O(n^2 \log n)
 * Status: Verified https://www.spoj.com/problems/CIRUT/
 */
#include "Point.h"

typedef double db;
typedef pair<P, db> Circle;
const double TAU = 2 * PI;

namespace CIRUT {
const int LIM = 1000;
Circle isi[LIM + 18];
int n, p[LIM * 4 + 18], q[LIM * 4 + 18], qt, ttmp;
db ans[LIM + 18], alp[LIM * 4 + 18];
void reset(int _n) {
  n = _n; qt = ttmp = 0;
  rep(i, 0, (n + 1) * 4 + 2) p[i] = q[i] = alp[i] = 0;
  rep(i, 0, n + 1) ans[i] = 0, isi[i] = Circle();
}

int eps(db x) {
  return x < -1e-8 ? -1 : x > 1e-8;
}

int cmpor(const void *i, const void *j) {
  return (ttmp = eps(alp[*(int *)i] - alp[*(int *)j])) ? ttmp : q[*(int *)j] - q[*(int *)i];
}

int judge(db d, int r0, int r1) {
  if (eps(d - r0 - r1) >= 0) return -1;
  if (eps(d + r1 - r0) <= 0) return 0;
  if (eps(d + r0 - r1) <= 0) return 1;
  return 2;
}

void inter(int a, int b, int dx, int dy, db d, db &a0, db &a1) {
  db da = acos((isi[a].se * isi[a].se + d * d - isi[b].se * isi[b].se) * 0.5 / (isi[a].se * d));
  db ba = atan2(dy, dx); a0 = ba - da, a1 = ba + da;
  if (a0 < 0) a0 += TAU;
  if (a1 < 0) a1 += TAU;
}

db calcarea(int a, db a0, db a1) {
  db da = a1 - a0;
  if (!eps(da)) return 0;
  db x0 = isi[a].fi.x + isi[a].se * cos(a0), y0 = isi[a].fi.y + isi[a].se * sin(a0);
  db x1 = isi[a].fi.x + isi[a].se * cos(a1), y1 = isi[a].fi.y + isi[a].se * sin(a1);
  return isi[a].se * isi[a].se * (da - sin(da)) + (x0 * y1 - x1 * y0);
}

void calc(int X) {
  int covered = 1, dx, dy;
  db d; qt = 0;
  for (int i = 1, tmp; i <= n; ++i)
    if (X != i && (dx = isi[i].fi.x - isi[X].fi.x, dy = isi[i].fi.y - isi[X].fi.y, tmp = judge(d = sqrt(dx * dx + dy * dy), isi[X].se, isi[i].se)) > 0)
      if (tmp == 1) ++covered;
      else {
        inter(X, i, dx, dy, d, alp[qt + 1], alp[qt + 2]);
        q[++qt] = 1, p[qt] = qt;
        q[++qt] = -1, p[qt] = qt;
        if (eps(alp[qt - 1] - alp[qt]) > 0) {
          alp[++qt] = 0, q[qt] = 1, p[qt] = qt;
          alp[++qt] = TAU, q[qt] = -1, p[qt] = qt;
        }
      }
  if (!qt) {ans[covered] += isi[X].se * isi[X].se * TAU; return;}
  qsort(p + 1, qt, sizeof(p[0]), cmpor);
  ans[covered] += calcarea(X, 0, alp[p[1]]) + calcarea(X, alp[p[qt]], TAU);
  for (int i = 1; i < qt; ++i)
    covered += q[p[i]], ans[covered] += calcarea(X, alp[p[i]], alp[p[i + 1]]);
}

void solve() {
  rep(i, 1, n + 1) calc(i);
  rep(i, 1, n + 1) ans[i] -= ans[i + 1], ans[i] *= 0.5;
}
}