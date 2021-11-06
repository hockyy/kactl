/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 * Time: O(N^2)
 */
 
 int main() {
  for (int i = 1; i < n; i++) {
    memo[i][i + 1] = isi[i] + isi[i + 1];
    opt[i][i + 1] = i;
  }
  for (int i = 2; i <= n; i++) {
    //Compute for i+1 segment
    for (int j = 1; j + i <= n; j++) {
      LL cur = LINF;
      for (int k = opt[j][j + i - 1]; k <= opt[j + 1][j + i]; k++) {
        LL now = memo[j][k] + memo[k + 1][j + i];
        if (cur > now) {
          cur = now;
          opt[j][j + i] = k;
        }
      }
      memo[j][j + i] = cur + (psum[j + i] - psum[j - 1]);
    }
  }
}
