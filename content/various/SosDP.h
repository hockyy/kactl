/**
 * Author: Hocky Yudhiono
 * License: CC0
 * Description: Consider using FWHT
 */

void sos() {
  //Dp[mask] contain all numbers of submask
  for (int i = 0; i <= 23; i++)
    for (int mask = (1LL << 24) - 1; mask >= 0; mask--)
      if (mask & (1LL << i)) dp[mask] += dp[mask ^ (1LL << i)];
  LL ans = 0;
  for (int mask = (1LL << 24) - 1; mask >= 0; mask--)
    dp[mask] = n - dp[mask], ans ^= (dp[mask] * dp[mask]);
}
