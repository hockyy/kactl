/**
 * Author: hocky, Takanori Maehara
 * Date: 2023-10-20
 * License: CC0
 * Source:
 * Description: Triangulate a polygon
 * Time: O(n)
 * Status: Untested
 */

LD triangulate(vector<P> ps) {
  int n = ps.size();
  vector<int> next(n);
  for (int i = 0; i < n-1; ++i) next[i] = i+1;
  auto is_ear = [&](int i, int j, int k) {
    if(sgn(ps[i].cross(ps[j], ps[k])) <= 0) return 0;
    for (int l = next[k]; l != i; l = next[l])
      if (sgn(ps[l].cross(ps[i], ps[j])) >= 0
       && sgn(ps[l].cross(ps[j], ps[k])) >= 0
       && sgn(ps[l].cross(ps[k], ps[i])) >= 0) return false;
    return true;
  };
  LD area = 0;
  for (int i = 0; next[next[i]] != i; ) {
    if (is_ear(i, next[i], next[next[i]])) {
      area  += abs(ps[i].cross(ps[next[i]], ps[next[next[i]]])) / 2;
      next[i] = next[next[i]];
    } else i = next[i];
  }
  return area;
}