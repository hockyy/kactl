/**
 * Author: grhkm
 * Date: 2020-09-23
 * Description: Given the points (i, y[i]) for 1 < i < k, find y[x]
 * Time: O(k)
 */
#pragma once

int evaluate(int x, int k, bool bf = false) {
  if (k == 0) return x;
  vector<LL> pre(k + 2), suf(k + 2), invf(k + 2);
  invf[0] = 1; pre[0] = x; suf[k + 1] = x - (k + 1);
  for (int i = 1; i <= k; i ++) pre[i] = pre[i - 1] * (x - i) % MOD;
  for (int i = k; i >= 1; i --) suf[i] = suf[i + 1] * (x - i) % MOD;
  for (int i = 1; i <= k + 1; i ++) invf[i] = invf[i - 1] * modpow(i, MOD - 2) % MOD;
  LL ans = 0; int yi = 0; // 0^k +~ i^k
  for (int i = 0; i <= k + 1; i ++) {
    yi = (yi + modpow(i, k)) % MOD; // interpolate point: (i, yi)
    LL num = (i - 1 >= 0 ? pre[i - 1] : 1) *
             ((i + 1 < k + 2) ? suf[i + 1] : 1) % MOD; // numerator
    LL denom = invf[i] * invf[k + 1 - i] % MOD; // denominator
    LL mult = ((i + k) & 1) ? 1 : -1;
    ans += (mult * yi * num % MOD) * denom % MOD;
  }
  ans = ans % MOD;
  return ans < 0 ? ans + MOD : ans;
}