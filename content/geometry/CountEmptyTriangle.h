/**
 * Author: hocky
 * Date: 2023-10-18
 * License: Unknown
 * Source: https://codeforces.com/contest/13/problem/D
 * Description: Count how many empty red triangles
 * Time: $O(N^3)$, where $N$ is the total number of points
 * Status: Tested
 */

LL solve(vector <P> &red, vector <P> &blue) {
  sort(all(red)); sort(all(blue));
  int n = sz(red), m = sz(blue);
  vvi dp(n, vi(n));
  rep(i, 0, n) rep(j, i + 1, n) rep(k, 0, m) {
    if (!(red[i] < blue[k] && blue[k] < red[j])) continue;
    if (red[i].ccw(red[j], blue[k]) > 0) dp[i][j]++;
  }
  LL ans = 0;
  rep(i, 0, n) rep(j, i + 1, n) rep(k, i + 1, j)
    ans += (dp[i][k] + dp[k][j] == dp[i][j]);
  return ans;
}
