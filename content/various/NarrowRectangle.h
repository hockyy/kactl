/**
 * Author: Yoga
 * Date: 2015-03-18
 * Description: Slope Trick At Coder Narrow Rectangle Solution
 */

priority_queue<LL> kiri;
priority_queue<LL, vector<LL>, greater<LL> > kanan;
int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];
  LL ans = 0LL, lzl = 0LL, lzr = 0LL;
  kiri.push(l[1]); kanan.push(l[1]);
  for (int i = 2; i <= n; i++) {
    lzr += r[i - 1] - l[i - 1];
    lzl -= r[i] - l[i];
    LL tmpl = kiri.top() + lzl, tmpr = kanan.top() + lzr;
    if (l[i] <= tmpl) {
      kiri.pop(); kiri.push(l[i] - lzl); kiri.push(l[i] - lzl);
      kanan.push(tmpl - lzr); ans += llabs(tmpl - l[i]);
    } else if (l[i] >= tmpr) {
      kanan.pop(); kanan.push(l[i] - lzr); kanan.push(l[i] - lzr);
      kiri.push(tmpr - lzl); ans += llabs(l[i] - tmpr);
    } else {
      kiri.push(l[i] - lzl); kanan.push(l[i] - lzr);
    }
  }
  cout << ans << '\n';
  return 0;
}