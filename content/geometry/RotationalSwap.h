/**
 * Author: Yusuf Sholeh
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Find whether exists triangle whose area is exactly S.
 * Status: tested, except for phi and theta
 */
struct point {
  ll x, y;
  point() {}
  point(ll _x, ll _y) {
    x = _x, y = _y;
  }
};
ll cross(point a, point b) {
  return a.x * b.y - a.y * b.x;
}
ll area(point p, point q, point r) {
  return abs(cross(p, q) + cross(q, r) + cross(r, p));
}
struct seg {
  int i, j;
  point a, b, vec;
  seg() {}
  seg(int _i, int _j, point _a, point _b, point _vec) {
    i = _i, j = _j, a = _a, b = _b, vec = _vec;
  };
};
const int N = 2005;
ll n, s;
point arr[N];
bool cmp(point a, point b) {
  if (a.y == b.y) return a.x < b.x;
  return a.y < b.y;
}
bool cmp2(seg a, seg b) {
  return cross(a.vec, b.vec) > 0;
}
vector<seg> segment;
int ranked[N], id[N];
int main() {
  scanf("%lld %lld", &n, &s); s *= 2;
  for (int i = 1; i <= n; i++) {
    scanf("%lld %lld", &arr[i].x, &arr[i].y);
  }
  sort(arr + 1, arr + n + 1, cmp);
  for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++) {
      segment.push_back(seg(i, j, arr[i], arr[j], point(arr[i].x - arr[j].x, arr[i].y - arr[j].y)));
    }
  sort(segment.begin(), segment.end(), cmp2);
  for (int i = 1; i <= n; i++) ranked[i] = id[i] = i;
  for (auto cur : segment) {
    int a = id[cur.j], b = id[cur.i];
    int l = 1, r = a - 1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      ll hasil = area(arr[ranked[mid]], cur.a, cur.b);
      if (hasil == s) {
        printf("Yes\n");
        printf("%lld %lld\n", arr[ranked[mid]].x, arr[ranked[mid]].y);
        printf("%lld %lld\n", cur.a.x, cur.a.y);
        printf("%lld %lld\n", cur.b.x, cur.b.y);
        return 0;
      } else if (hasil < s) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    l = b + 1, r = n;
    while (l <= r) {
      int mid = (l + r) >> 1;
      ll hasil = area(arr[ranked[mid]], cur.a, cur.b);
      if (hasil == s) {
        printf("Yes\n");
        printf("%lld %lld\n", arr[ranked[mid]].x, arr[ranked[mid]].y);
        printf("%lld %lld\n", cur.a.x, cur.a.y);
        printf("%lld %lld\n", cur.b.x, cur.b.y);
        return 0;
      } else if (hasil > s) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    assert(a + 1 == b);
    swap(ranked[a], ranked[b]);
    swap(id[cur.i], id[cur.j]);
  }
  printf("No\n");
  return 0;
}