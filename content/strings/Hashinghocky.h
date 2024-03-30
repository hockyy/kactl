/**
 * Author: Hocky Yudhiono
 * Date: 2022-09-13
 * License: CC0
 * Source: own work
 * This is hashing int, please mind you're
 * hashing string and map 'a'-> 1, 'b'-> 2, and such
 * Avoid mapping to zero to avoid "hash([0 0 0]) = hash([0 0])"
 * Usage:
 * vi tmp = {6,9,4,2,0};
 * vector <rollingHash> solver(HASH);
 * solver[0] = rollingHash(\&tmp, goodPrimes[0]);
 * Description: Self-explanatory methods for string hashing.
 * Status: tested
 */
#pragma once

 
const int HASH = 3;
vector <vector<LL>> base;
const int LIM = 2e6 + 5;
struct RollingHash {
  LL baseIdx, N;
  vi *arr;
  vector<LL> hash;
  RollingHash() {}
  RollingHash(vi *x, LL bs) {
    baseIdx = bs;
    arr = x;
    N = arr->size();
    hash.resize(N);
    makeHash();
  }
  void makeHash() {
    if (N == 0) return;
    assert(sz(base[baseIdx]) >= N);
    for (int i = 0; i < N; i++) {
      int curlet = (*arr)[i];
      hash[i] = (curlet * base[baseIdx][i]) % MOD;
      if (i) hash[i] = (hash[i] + hash[i - 1]) % MOD;
    }
  }
  inline LL getHash(PII a) { return (hash[a.se] - (a.fi > 0 ? hash[a.fi - 1] : 0) + MOD) % MOD * base[baseIdx][(LIM - a.fi - 1)] % MOD; }
};
 
void initBase() {
  base.resize(HASH, vector<LL>(LIM + 5));
  rep(i, 0, HASH) {
    base[i][0] = 1;
    rep(j, 1, LIM + 5) {
      base[i][j] = base[i][j - 1] * goodPrimes[i] % MOD;
    }
  }
}
