/**
 * Author: Pyqe
 * Date: 2023-10-15
 * Description: Only pyqe understand
 * Time: $O(26N)$
 * Status: tested on https://codeforces.com/gym/102428/problem/G
 */
const long long mm = 26;
long long n, nn = 0, a[200069], pst[200069], nx[400069][mm], lna[400069], pr[400069];

inline void ins(long long x, long long w) {
  long long p;
  nn++; pst[x] = nn; lna[nn] = x;
  for (p = pst[x - 1]; p && !nx[p][w]; p = pr[p]) nx[p][w] = nn;
  if (!p) pr[nn] = pst[0];
  else {
    long long tg = nx[p][w];
    if (lna[tg] == lna[p] + 1) pr[nn] = tg;
    else {
      long long i; pr[nn] = nn + 1;
      for (i = 0; i < mm; i++)
        nx[nn + 1][i] = nx[tg][i];
      lna[nn + 1] = lna[p] + 1;
      pr[nn + 1] = pr[tg]; pr[tg] = nn + 1;
      for (; p && nx[p][w] == tg; p = pr[p]) nx[p][w] = nn + 1;
      nn++;
    }
  }
}