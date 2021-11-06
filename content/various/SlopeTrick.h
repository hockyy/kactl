/**
 * Author: Hocky Yudhiono
 * License: CC0
 * Description: Slope Trick making it increasing with cost to up and down different
 * Time: O(N \log N)
 */
 
int solve() {
  int n; cin >> n;
  vector<LL> isi(n);
  vector<PLL> cost(n);
  trav(cur, isi) cin >> cur;
  trav(cur, cost) cin >> cur.fi;
  trav(cur, cost) cin >> cur.se;
  LL ans = 0;
  priority_queue <PLL> solve;
  rep(i, 0, n) {
    auto &cur = cost[i];
    // Push ke isi[i], gradiennya cur.fi + cur.se
    solve.push({isi[i], cur.fi + cur.se});
    // Push lagi buat kurangin gradien
    solve.push({max(isi[i], solve.top().fi), -cur.fi});
    ans += (solve.top().fi - isi[i]) * cur.fi;
    // Maintain minimum
    while (solve.size() >= 2){
      PLL now = solve.top(); solve.pop();
      PLL pre = solve.top(); solve.pop();
      // Merge dua slope
      if(now.fi == pre.fi){
        now.se += pre.se;
        solve.push(now);
        continue;
      }else if(pre.fi < now.fi && now.se <= 0){
        // Slope trick, geser opt
        pre.se += now.se;
        solve.push(pre);
        ans += (now.fi - pre.fi) * now.se;
        continue;
      }else{
        solve.push(pre);
        solve.push(now);
        break;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
