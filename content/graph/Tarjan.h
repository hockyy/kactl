/**
 * Author: Hocky Yudhiono
 * Date: 2009-10-28
 * License: CC0
 * Description: Finds AP and Bridge.
 * Time: O(E + V)
 */
#pragma once

void tarjan(LL pos, LL par) {
  low[pos] = num[pos] = ++dfscnt;
  trav(nx, edge[pos]){
    if (nx == par) continue;
    if (!num[nx]) {
      if (pos == curroot) curchild++;
      tarjan(nx, pos);
      if (low[nx] >= num[pos]) isArticulationPoint[pos] = 1;
      // if(low[nx] > num[pos]) isBridge[pos][nx] = 1;
      low[pos] = min(low[pos], low[nx]);
    } else low[pos] = min(low[pos], num[nx]);
  }
}

int main() {
  for (int i = 1; i <= n; i++) {
    if (num[i]) continue;
    curroot = i;
    curchild = 0;
    tarjan(i, -1);
    isArticulationPoint[i] = (curchild > 1);
  }
}