/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

vvi automaton(string s, char ch, int charSize) {
  s += '$'; vi ff = pi(s);
  vvi aut(sz(s), vi(charSize));
  rep(i, 0, sz(s)) {
    rep(c, 0, charSize) {
      aut[i][c] = ((i > 0 && ch + c != s[i]) ? aut[ff[i - 1]][c] : (i + (ch + c == s[i])));
    }
  }
  return aut;
}
