/**
 * Author: Pikatan Arya Bramajati
 * Date: 2009-10-30
 * License: CC0
 * Description: Solution for Jewel Grab
 * Time: $O(\log N)$.
 * Status: Submitted on Jewel Grab
 */
#pragma once

struct segtree {
  int l, r, mx;
  long long sm;
  segtree *p[2];
  void bd(int lh, int rh) {
    l = lh; r = rh;
    if (l == r) {
      sm = wg[l];
      mx = *prev(ms[a[l]].find(l));
      ls[l] = mx;
    } else {
      int ii, md = (l + r) / 2;
      for (ii = 0; ii < 2; ii++) {
        p[ii] = new segtree;
        p[ii]->bd(!ii ? l : md + 1, !ii ? md : r);
      }
      sm = p[0]->sm + p[1]->sm;
      mx = max(p[0]->mx, p[1]->mx);
    }
  }
  void ud(int x, int w, int w2) {
    if (l > x || r < x);
    else if (l >= x && r <= x) {
      if (w != -1) sm = wg[l] = w;
      if (w2 != -1) mx = ls[l] = w2;
    } else {
      for (int ii = 0; ii < 2; ii++) p[ii]->ud(x, w, w2);
      sm = p[0]->sm + p[1]->sm;
      mx = max(p[0]->mx, p[1]->mx);
    }
  }
  int qr(int lh, int rh) {
    if (l > rh || r < lh) return -inf;
    if (l >= lh && r <= rh) return mx;
    return max(p[0]->qr(lh, rh), p[1]->qr(lh, rh));
  }
  long long qs(int lh, int rh) {
    if (l > rh || r < lh) return 0;
   	if (l >= lh && r <= rh) return sm;
    return p[0]->qs(lh, rh) + p[1]->qs(lh, rh);
  }
  int bl(int x) {
    if (l >= x) {
      if (mx < x) return n + 1;
      if (l == r) return l;
      if (p[0]->mx >= x) return p[0]->bl(x);
      return p[1]->bl(x);
    } else {
      if (r < x)return n + 1;
      else {
        int k = p[0]->bl(x);
        if (k <= p[0]->r) return k;
        return p[1]->bl(x);
      }
    }
  }
};