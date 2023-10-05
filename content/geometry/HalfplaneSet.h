/**
 * Author: retrograd
 * Description: Data structure that dynamically keeps track
 * of the intersection of halfplanes.
 * Status: tested on codechef ALLPOLY
 */
#include <bits/stdc++.h>
using namespace std;
using T = int; 
using T2 = long long;
using T4 = __int128_t;
const T2 INF = 2e9;
struct Line { T a, b; T2 c; };
bool operator<(Line m, Line n) {
  auto half = [&](Line m) { 
    return m.b < 0 || m.b == 0 && m.a < 0; };
  return make_tuple(half(m), (T2)m.b * n.a) < 
    make_tuple(half(n), (T2)m.a * n.b);
}
tuple<T4, T4, T2> LineIntersection(Line m, Line n) {
  T2 d = (T2)m.a * n.b - (T2)m.b * n.a; // assert(d);
  T4 x = (T4)m.c * n.b - (T4)m.b * n.c; 
  T4 y = (T4)m.a * n.c - (T4)m.c * n.a;
  return {x, y, d};
}
Line LineFromPoints(T x1, T y1, T x2, T y2) {
  T a = y1 - y2, b = x2 - x1;
  T2 c = (T2)a * x1 + (T2)b * y1;
  return {a, b, c};
}
ostream& operator<<(ostream& out, Line l) {
  out << "(" << l.a << " * x + " << l.b << " * y <= " << l.c << ")";
  return out;
}
struct HalfplaneSet : multiset<Line> {
  HalfplaneSet() {
    insert({+1, 0, INF}); insert({0, +1, INF});
    insert({-1, 0, INF}); insert({0, -1, INF});
  };
 
  auto prv(auto it) { return --(it == begin() ? end() : it); }
  auto nxt(auto it) { return (++it == end() ? begin() : it); }
  bool bad(auto it) {
    auto l = *it, pl = *prv(it), nl = *nxt(it);
    T4 x, y; T2 d; tie(x, y, d) = LineIntersection(pl, nl);
    // auto [x, y, d] = LineIntersection(pl, nl);
    T4 sat = l.a * x + l.b * y - (T4)l.c * d;
    if (d < 0 && sat < 0) {
      clear(); // infeasible
    }
    return d > 0 && sat <= 0 || d == 0 && sat < 0;
  }
  void Cut(Line l) { // add ax + by <= c
    if (empty()) return;
    auto it = insert(l);
    if (bad(it)) { erase(it); return; }
    while (size()) {
      auto nit = nxt(it);
      if (bad(nit)) erase(nit);
      else break;
    }
    while (size()) {
      auto pit = prv(it);
      if (bad(pit)) erase(pit);
      else break;
    }
  }
  double Maximize(T a, T b) { // max ax + by
    if (empty()) return -1/0.;
    auto it = lower_bound({-b, a});
    if (it == end()) it = begin();
    // auto [x, y, d] = LineIntersection(*prv(it), *it);
    // return (1.0 * a * x + 1.0 * b * y) / d;
  }
  double Area() {
    long double total = 0.;
    for (auto it = begin(); it != end(); ++it) {
      T4 x1, y1; T2 d1; tie(x1, y1, d1) = LineIntersection(*prv(it), *it);
      T4 x2, y2; T2 d2; tie(x2, y2, d2) = LineIntersection(*it, *nxt(it));
      total += (1.0L * x1/d1 * y2/d2 - 1.0L * x2/d2 * y1/d1);
    }
    return total * 0.5L;
  }
};
int main() {
  //ifstream cin("camera.in");
  //ofstream cout("camera.out");
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<T> x(n), y(n);
    for (int i = 0; i < n; ++i) 
      cin >> x[i] >> y[i];
    HalfplaneSet HS;
    for (int j = n - 1, i = 0; i < n; j = i++) 
      HS.Cut(LineFromPoints(x[j], y[j], x[i], y[i]));
    cout << fixed << setprecision(6) << HS.Area() / 4e14 << '\n';
  }
  return 0;
}