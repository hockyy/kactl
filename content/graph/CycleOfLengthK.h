/**
 * Author: Chinese
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Find cycle of length K
 * Status: untested
 */
#pragma once
pll cycle(const vector<pair<int, int>> &edges) {
  int n = 0, i;
  for (auto [u, v] : edges) n = max({n, u, v});
  ++n;
  vector d(n, 0), id(d), rk(d), cnt(d);
  vector e(n, vector(0, 0)), lk(n, vector(0, 0));
  for (auto [u, v] : edges) ++d[u], ++d[v];
  iota(all(id), 0); sort(all(id), [&](int x, int y) { return d[x] < d[y]; });
  for (i = 0; i < n; i++) rk[id[i]] = i;
  for (auto [u, v] : edges) {
    if (rk[u] > rk[v]) swap(u, v);
    e[u].push_back(v);
    lk[u].push_back(v);
    lk[v].push_back(u);
  }
  ll c3 = 0;
  for (i = 0; i < n; i++) {
    for (int u : e[i]) cnt[u] = 1;
    for (int u : e[i]) for (int v : e[u]) c3 += cnt[v];
    for (int u : e[i]) cnt[u] = 0;
  }
  ll c4 = 0;
  for (i = 0; i < n; i++) {
    for (int u : lk[i]) for (int v : e[u]) if (rk[v] > rk[i]) c4 += cnt[v]++;
    for (int u : lk[i]) for (int v : e[u]) cnt[v] = 0;
  }
  return {c3, c4};
}