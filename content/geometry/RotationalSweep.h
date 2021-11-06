/**
 * Author: Hocky Yudhiono
 * Date: 2020-03-09
 * License: CC0
 * Source: own work
 * Description: Codechef blue red
 * Time: O(N^2 \log N)
 * Status: tested
 */

#include "Point.h"

template<class P>
P RotationalSweep(vector<P> &all) {
  for (int i = 0; i < n; i++) {
    vector <PP> kiri, kanan;
    for (int j = 0; j < n; j++) {
      PP curtmp = all[j];
      curtmp.center = curtmp.center - all[i].center;
      if (i == j) continue;
      if (curtmp.center.y >= 0) kiri.pb(curtmp);
      else kanan.pb(curtmp);
    }
    sort(kiri.begin(), kiri.end());
    sort(kanan.begin(), kanan.end());
    kiri.insert(kiri.end(), kanan.begin(), kanan.end());
    LL cnt[2] = {0, 0};
    LL N = kiri.size();
    LL hi = 0;
    cnt[kiri[0].color]++;
    for (int j = 0; j < N; j++) {
      do {
        LL nx = (hi + 1) % N;
        if (pivot.ccw(kiri[j].center, kiri[nx].center) <= 0) break;
        cnt[kiri[nx].color]++;
        hi = nx;
      } while (1);
      LL curcnt[2] = {initialColor[0] - cnt[0], initialColor[1] - cnt[1]};
      curcnt[all[i].color]--;
      cnt[kiri[j].color]--;
      ans = min(ans, cnt[0] + curcnt[1]);
      ans = min(ans, cnt[1] + curcnt[0]);
      cnt[kiri[j].color]++;
      if (hi == j) {
        LL nx = (hi + 1) % N;
        cnt[kiri[nx].color]++;
        hi = nx;
      }
      cnt[kiri[j].color]--;
    }
  }
}
