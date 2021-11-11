/**
 * Author: Hocky Yudhiono
 * Date: 2017-09-29
 * License: CC0
 * Description: You can use the following special characters: \texttt{\^{}\$.*?|()\{\}}
 * Time: O(NM)
 */
#pragma once

#include <regex>
#include <iostream>
using namespace std;

int main () {
  string s ("this subject has a submarine as a subsequence");
  smatch m; regex e ("(sub)([^ ]*)");   // matches words beginning by "sub"
  // regex search will match the first occurence
  if(regex_match(begin(s), end(s), regex("this .+"))) cout << "OK" << endl;
  while (regex_search (s, m, e)) {
    for (auto x : m) cout << x << " ";
    cout << endl; s = m.suffix().str();
  }
  s = "this subject has a submarine as a subsequence";
  cout << regex_replace (s,e,"sub-$2");
  return 0;
}