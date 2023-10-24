/**
 * Author: Victor Lecomte
 * Date: 2009-04-14
 * License: CC0
 * Source: https://victorlecomte.com/cp-geo.pdf
 * Description: Get polyhedron volume
 * Usage: reorient the faces first
 * Status: untested
 */
#pragma once
#include "Point3D.h"
struct edge {
  int v; bool same;
};
void reorient(vector<vector<p3>> &fs) {
  int n = fs.size();
  vector<vector<edge>> g(n);
  map<pair<p3, p3>, int> es;
  for (int u = 0; u < n; u++) {
    for (int i = 0, m = fs[u].size(); i < m; i++) {
      p3 a = fs[u][i], b = fs[u][(i + 1) % m];
      if (es.count({a, b})) {
        int v = es[ {a, b}];
        g[u].push_back({v, true});
        g[v].push_back({u, true});
      } else if (es.count({b, a})) {
        int v = es[ {b, a}];
        g[u].push_back({v, false});
        g[v].push_back({u, false});
      } else { // not seen yet
        es[ {a, b}] = u;
      }
    }
  }
  vector<bool> vis(n, false), flip(n);
  flip[0] = false;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (edge e : g[u]) {
      if (!vis[e.v]) {
        vis[e.v] = true;
        flip[e.v] = (flip[u] ^ e.same);
        q.push(e.v);
      }
    }
  }
  for (int u = 0; u < n; u++)
    if (flip[u])
      reverse(fs[u].begin(), fs[u].end());
}

p3 vectorArea2(vector<p3> p) {
  p3 S = p3(0, 0);
  for (int i = 0, n = p.size(); i < n; i++)
    S = S + p[i] * p[(i + 1) % n];
  return S;
}
double area(vector<p3> p) { return vectorArea2(p).dist() / 2.0; }
double volume(vector<vector<p3>> fs) {
  double vol6 = 0.0;
  for (vector<p3> f : fs) vol6 += (vectorArea2(f) | f[0]);
  return abs(vol6) / 6.0;
}