/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

void tarjan(LL pos) {
  path.pb(pos); inPath[pos] = 1; low[pos] = num[pos] = ++curtime;
  trav(nx, edge[pos]) {
    if (!num[nx]) tarjan(nx);
    if (inPath[nx]) low[pos] = min(low[pos], low[nx]);
  }
  if (low[pos] == num[pos]) {
    for(LL cur = path.back();;cur = path.back()){
      path.pop_back(); inPath[cur] = 0;
      solver->join(pos, cur);
      if(cur == pos) break;
    }
  }
}

rep(i,0,n) if(!num[i]) tarjan(i);
