/**
 * Author: Koosaga
 * License: CC0
 * Source: https://github.com/mochow13/competitive-programming-library/blob/master/DP/IOI%20Aliens%20by%20koosaga.cpp
 * Description: Solution for alien
 * Time: O(N log K)
 */

pi trial(lint l){
  cht.clear();
  for(int i=1; i<=v.size(); i++){
    cht.add_line(2 * 2 * v[i-1].first, dp[i-1].first + 
      2ll * v[i-1].first * v[i-1].first, dp[i-1].second);
    dp[i] = cht.query(-v[i-1].second);
    dp[i].first += 2ll * v[i-1].second * v[i-1].second + l; // l is penalty
    dp[i].second++;
    if(i != v.size()){
      lint c = max(0ll, v[i-1].second - v[i].first);
      dp[i].first -= 2 * c * c;
    }
  }
  return dp[v.size()];
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
  vector<pi> w;
  for(int i=0; i<n; i++){
    if(r[i] > c[i]) swap(r[i], c[i]);
    w.push_back({r[i]-1, c[i]});
  }
  sort(w.begin(), w.end(), [&](const pi &a, const pi &b){
    return pi(a.first, -a.second) < pi(b.first, -b.second);
  });
  for(auto &i : w){
    if(v.empty() || v.back().second < i.second){
      v.push_back(i);
    }
  }
  lint s = 0, e = 2e12;
  while(s != e){
    lint m = (s+e)/2;
    // See how many groups are made with penalty 2*m+1
    if(trial(2 * m + 1).second <= k) e = m;
    else s = m+1;
  }
  return trial(s * 2).first / 2 - s * k;
}