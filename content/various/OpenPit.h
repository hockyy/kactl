/**
 * Author: Hocky Yudhiono
 * Description: Open Pit
 */

for (int i = 1; i <= n; i++) {
  int a, b; cin >> a >> b;
  isi[i] = a - b; int m; cin >> m;
  while (m--) { int v; cin >> v; edges.pb({i, v}); }
}
PushRelabel solve(n + 2);
for (int i = 1; i <= n; i++) {
  int curcost = abs(isi[i]);
  if (isi[i] == curcost) ans += curcost, solve.add_edge(0, i, curcost);
  else solve.add_edge(i, n + 1, curcost);
}
trav(edge, edges) solve.add_edge(edge.se, edge.fi, INF);
cout << ans - solve.maxflow(0, n + 1) << endl;