/**
 * Author: Hocky Yudhiono
 * Date: Unknown
 * License: CC0
 * Description: Edmond's Blossom general Matching, Best known time is $O(V^2\sqrt{V})$ Use with care
 * Time: O(V^3)
 */
struct Edmonds {
  int n, T;
  vector<vi> edge;
  vi mate, p, vis, base, toJoin;
  Edmonds(int N) : n(N), T(0), edge(n), mate(n, -1), p(n), vis(n), base(n) { }
  void add(int a, int b) { edge[a].pb(b); edge[b].pb(a); }
  int getBase(int i) { return base[i] == i ? i : (base[i] = getBase(base[i])); }
  void mark_path(int pos, int nx, int b, vi &path) {
    for (; getBase(pos) != b; pos = p[nx]) {
      p[pos] = nx, nx = mate[pos];
      toJoin.pb(pos); toJoin.pb(nx);
      if (!vis[nx]) vis[nx] = ++T, path.pb(nx);
    }
  }
  bool go(int pos) {
    for (int nx : edge[pos]) {
      int b, bpos = getBase(pos), bnx = getBase(nx);
      if (bpos == bnx) continue;
      else if (vis[nx]) {
        vi path; toJoin.clear();
        if (vis[bnx] < vis[bpos]) mark_path(pos, nx, b = bnx, path);
        else mark_path(nx, pos, b = bpos, path);
        for (int z : toJoin) base[getBase(z)] = b;
        for (int z : path) if (go(z)) return 1;
      } else if (p[nx] == -1) {
        p[nx] = pos;
        if (mate[nx] == -1) {
          for (int y; nx != -1; nx = pos)
            y = p[nx], pos = mate[y], mate[nx] = y, mate[y] = nx;
          return 1;
        }
        if (!vis[mate[nx]]) { vis[mate[nx]] = ++T; if (go(mate[nx])) return 1; }
      }
    }
    return 0;
  }
  void init_dfs() { rep(i, 0, n) vis[i] = 0, p[i] = -1, base[i] = i; }
  bool dfs(int root) {vis[root] = ++T; return go(root); }
  void match() {
    int ans = 0;
    for (int pos = 0; pos < n; pos++) {
      if (mate[pos] != -1) continue;
      for (int nx : edge[pos]) {
        if (mate[nx] == -1) {
          mate[pos] = nx; mate[nx] = pos; ans++; break;
        }
      }
    }
    init_dfs();
    rep(i, 0, n) if (mate[i] == -1 && dfs(i)) ans++, init_dfs();
    cout << ans * 2 << endl;
    rep(i, 0, n) if (i < mate[i])
      cout << i + 1 << " " << mate[i] + 1 << " \n"[i == n - 1];
  }
};