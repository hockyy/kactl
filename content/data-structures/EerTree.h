/**
 * Author: SuprDewd, hocky
 * Date: 2021-10-21
 * License: CC0
 * Source: https://github.com/SuprDewd/CompetitiveProgramming/blob/master/code/strings/eertree.cpp
 * Description: st[i] represents a palindromic substring of s,
 * st[last] is the longest palindromic suffix of s[0,n)
 * st[i].link is the longest palindromic suffix of st[last], `abbab`.link -> `bab`
 * Time: O(N)
 * Status: Tested on several problems
 */
#pragma once

const char BASE = 'a';
struct state {
  int len, link, to[26], occ;
};
struct Eertree {
  int last, idx, n;
  vector <state> st;
  string s;
  Eertree(string S) : last(1), idx(2), n(0), st(S.size() + 3), s(S) {
    st[0].len = st[0].link = -1;
  }
  int extend() {
    int c = s[n++] - BASE; int p = last;
    while (n - st[p].len - 2 < 0 || c != s[n - st[p].len - 2] - BASE)
      p = st[p].link;
    if (!st[p].to[c]) {
      int q = last = idx++;
      st[p].to[c] = q; st[q].len = st[p].len + 2;
      do {  p = st[p].link; }
      while (p != -1 && (n < st[p].len + 2 || c != s[n - st[p].len - 2] - BASE));
      if (p == -1) st[q].link = 1;
      else st[q].link = st[p].to[c];
    } else last = st[p].to[c];
    st[last].occ++;
    return 0;
  }
  LL cntPal() {
    LL tot = 0;
    for (int i = idx; i >= 2; i--) {
      st[st[i].link].occ += st[i].occ;
      tot += st[i].occ;
    }
    return tot;
  }
};