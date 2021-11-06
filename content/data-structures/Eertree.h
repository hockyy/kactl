/**
 * Author: Hocky Yudhiono
 * Date: 2021-10-21
 * License: CC0
 * Source: own work
 * Description: Eertree for palindrome operations, can be improved using direct link dp
 * Time: O(N)
 * Status: Tested on several problems
 */
#pragma once

struct EerTree {
  struct Node {
    int next[26], suffixLink, length, occ;
    Node() {
      memset(next, 0, sizeof(next));
      suffixLink = length = occ = 0;
    }
  };
  string s;
  int n, lastPointer, lastIndex;
  vector <Node> tree;
  EerTree(int _n) {
    s = ""; tree.resize(3); init();
  }
  void append(char ch) {
    s += ch; assert(sz(tree) > sz(s));
    addChar(s.back());
  }
  void init() {
    tree[0].suffixLink = 0; tree[0].length = -1;
    tree[1].suffixLink = tree[1].length = 0; lastPointer = n = 0;
    lastIndex = 1;
  }
  void addChar(char ch) {
    int let = ch - 'a';
    while (n - tree[lastPointer].length - 1 < 0 || s[n - tree[lastPointer].length - 1] != ch)
      lastPointer = tree[lastPointer].suffixLink;
    if (!tree[lastPointer].next[let]) {
      tree[lastPointer].next[let] = ++lastIndex;
      if (lastIndex >= sz(tree)) tree.push_back(Node());
      tree[lastIndex].length = tree[lastPointer].length + 2;
      if (tree[lastIndex].length == 1) tree[lastIndex].suffixLink = 1;
      else {
        int ancestor = tree[lastPointer].suffixLink;
        while (s[n - tree[ancestor].length - 1] != ch) ancestor = tree[ancestor].suffixLink;
        tree[lastIndex].suffixLink = tree[ancestor].next[let];
      }
    }
    lastPointer = tree[lastPointer].next[let];
    tree[lastPointer].occ++;
    n++;
  }
  void printAns() {
    long long ans = 0;
    for (int i = lastIndex; i >= 2; i--) {
      long long curval = 1LL * tree[i].occ * tree[i].length;
      if (curval > ans) {
        ans = curval;
      }
      tree[tree[i].suffixLink].occ += tree[i].occ;
    }
    cout << ans << endl;
  }
};