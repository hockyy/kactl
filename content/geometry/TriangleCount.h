/**
 * Author: hocky
 * Date: 2023-10-20
 * License: CC0
 * Source:
 * Description: Count how many points inside triangle i j k
 * Time: O(n^3)
 * Status: Tested
 */

int cntIn(int i, int j, int k) {
  assert(i <= j && j <= k);
  int cnt = cntTop[i][j] + cntTop[j][k] - cntTop[i][k];
  return cnt >= 0 ? cnt : -cnt - 1;
}
void prep() {
  // Replace the k with the obstacle, and [isi[i] <= isi[k] < isi[j]]
  // rep(k, 0, m) {
  //   if (!(red[i] < blue[k] && blue[k] < red[j])) continue;
  rep(i, 0, n) rep(j, i + 1, n) rep(k, i + 1, j) {
    if (isi[i].fi.ccw(isi[j].fi, isi[k].fi) > 0)
      cntTop[i][j]++;
  }
}