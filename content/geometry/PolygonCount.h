/**
 * Author: hocky
 * Date: 2023-10-20
 * License: CC0
 * Source:
 * Description: Returns the number of convex polygon, perm is the order of points tie(x, y) < tie(o.x, o.y), this can handle collinear points as well, memo[0][a][b] contains the upper hull starting from a and ends at b, slope only contains (-PI/2, PI/2] lines
 * Time: O(n^3)
 * Status: Tested 104160K 104619G
 */
#include "Point.h"
typedef pair<P, PII> Slope;
vector<Slope> slopes;
for (int i = n - 1; i >= 0; i--) rep(j, i + 1, n) {
  if (!isBad[perm[i]][perm[j]]) {
    slopes.pb({isi[perm[j]] - isi[perm[i]], {perm[i], perm[j]}});
    int sameGradient = 0;
    rep(k, i + 1, j) {
      if (isi[perm[k]].cross(isi[perm[i]], isi[perm[j]]) == 0) {
        sameGradient++;
      }
    }
    ans = ans + MOD - pow2[sameGradient * 2] + pow2[sameGradient];
    while (ans >= MOD) ans -= MOD;
  }
}
rep(i, 0, n) memo[0][i][i] = memo[1][i][i] = 1;
rep(iter, 0, 2) {
  // Sort ccw
  stable_sort(all(slopes), [&](const Slope & a, const Slope & b) {
    return a.fi.cross(b.fi) > 0;
  });
  trav(slope, slopes) {
    int i = slope.se.fi, j = slope.se.se;
    if (iter) swap(i, j);
    rep(k, 0, n) {
      memo[iter][i][k] = (memo[iter][i][k] + memo[iter][j][k]) % MOD;
    }
  }
  reverse(all(slopes));
}
rep(i, 0, n) rep(j, 0, n) {
  ans += memo[0][i][j] * memo[1][j][i] % MOD;
}
cout << (ans - n + MOD) % MOD << endl;