/**
 * Author: Yusuf Sholeh
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Find whether exists triangle whose area is exactly S.
 * Status: tested, except for phi and theta
 */
struct Segment {
  PL v; int a, b;
  bool operator<(const Segment &other)const {
    return v.cross(other.v) > 0;
    // Sort dari gradien terkecil, goes from -90 -> 0 -> 90
  }
};

int main() {
  LL n; cin >> n >> target;
  target *= 2;
  vector <PL> isi(n);
  for (auto &cur : isi) cin >> cur.x >> cur.y;
  sort(begin(isi), end(isi));
  vector <Segment> events;
  vector <int> pointOrder(n), positionOfIndex(n);
  rep(i, 0, n) rep(j, i + 1, n) events.pb({isi[j] - isi[i], i, j});
  rep(i, 0, n) pointOrder[i] = positionOfIndex[i] = i;
  sort(begin(events), end(events));
  rep(i, 0, sz(events)) {
    int &a = positionOfIndex[events[i].a];
    int &b = positionOfIndex[events[i].b];
    // Can replace with segtree
    {
      int kiri = 0, kanan = min(a, b) - 1;
      while (kiri <= kanan) {
        LL mid = (kiri + kanan) >> 1;
        LL curArea = getArea2(isi[events[i].a], isi[events[i].b], isi[pointOrder[mid]]);
        if (curArea < target) kanan = mid - 1;
        else kiri = mid + 1;
      }
    }
    {
      int kiri = max(a, b) + 1, kanan = n - 1;
      while (kiri <= kanan) {
        LL mid = (kiri + kanan) >> 1;
        LL curArea = getArea2(isi[events[i].a], isi[events[i].b], isi[pointOrder[mid]]);
        if (curArea < target) kiri = mid + 1;
        else kanan = mid - 1;
      }
    }
    swap(pointOrder[a], pointOrder[b]);
    swap(a, b);
  }
  cout << "No" << endl;
}