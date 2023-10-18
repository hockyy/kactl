/**
 * Author: Hocky Yudhiono
 * Date: 2023-10-18
 * License: CC0
 * Source: Self
 * Description: This finds the optimal value on a strictly unimodal function
 * this reduce the range to a factor of about $0.6180^{it}$, 40/50 is generally enough
 * Time: O(it \times eval)
 * Status: tested
 */
double search(double kiri, double kanan) {
  PDD p[2];
  constexpr double gss = (sqrt(5) - 1) / 2;
  auto init = [&](int idx) {
    double g = gss * (kanan - kiri);
    if (idx == 0) p[idx].fi = kanan - g;
    else p[idx].fi = kiri + g;
    p[idx].se = eval(p[idx].fi);
  };
  init(0); init(1);
  rep(it, 0, 30) {
    if (p[0].se < p[1].se) { // swap the < to find min
      kiri = p[0].fi, p[0] = p[1], init(1);
    } else {
      kanan = p[1].fi;  p[1] = p[0]; init(0);
    }
  }
}