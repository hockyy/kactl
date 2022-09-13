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

LL goodPrimes[] = {196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
struct rollingHash {
  LL base, N;
  vi *arr;
  vector<LL> precBase, hash;
  rollingHash() {}
  rollingHash(vi *x, int curBase = 53) {
    arr = x; N = arr->size(); base = curBase;
    hash.resize(N); precBase.resize(N);
    makeHash();
  }
  void makeHash() {
    if (N == 0) return;
    precBase[0] = 1;
    for (int i = 1; i < N; i++) precBase[i] = (precBase[i - 1] * base) % MOD;
    for (int i = 0; i < N; i++) {
      int curlet = (*arr)[i];
      hash[i] = (curlet * precBase[N - i - 1]) % MOD;
      if (i) hash[i] = (hash[i] + hash[i - 1]) % MOD;
    }
  }
  inline LL getHash(PII a) { return (hash[a.se] - (a.fi > 0 ? hash[a.fi - 1] : 0) + MOD) % MOD; }
  bool isSame(PII a, PII b) {
    if (a.se - a.fi != b.se - b.fi) return 0;
    LL valA = getHash(a), valB = getHash(b);
    if (a.fi < b.fi) swap(a, b), swap(valA, valB);
    valA = (valA * precBase[a.fi - b.fi]) % MOD;
    return valA == valB;
  }
  bool isHash(PII a, LL sHash) {
    sHash = (sHash * precBase[N - a.se - 1]) % MOD;
    return getHash(a) == sHash;
  }
};

const int HASH = 2;

bool isSame(pii a, pii b, vector <rollingHash> &solver) {
  if (max(a.fi, a.se) >= solver[0].N || max(b.fi, b.se) >= solver[0].N) return 0;
  if (min(a.fi, a.se) < 0 || min(b.fi, b.se) < 0) return 0;
  for (int i = 0; i < HASH; i++) if (!solver[i].isSame(a, b)) return 0;
  return 1;
}