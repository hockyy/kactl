/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits) { // (optional)
  //this is just 3 times faster than stl sort for N=10^6
  int mask = (1 << bits) - 1;
  rep(it, 0, 2) {
    int move = it * bits;
    vi q(1 << bits), w(sz(q) + 1);
    rep(i, 0, sz(b))
    q[(b[i].first >> move) & mask]++;
    partial_sum(q.begin(), q.end(), w.begin() + 1);
    vector<pli> res(b.size());
    rep(i, 0, sz(b))
    res[w[(b[i].first >> move) & mask]++] = b[i];
    swap(b, res);
  }
}
struct SuffixArray {
  vi a, rank;
  string s;
  SuffixArray(const string& _s) : s(_s + '\0') {
    int N = sz(s);
    vector<pli> b(N);
    a.resize(N);
    rank.resize(N);
    rep(i, 0, N) {
      b[i].first = s[i];
      b[i].second = i;
    }

    int q = 8;
    while ((1 << q) < N) q++;
    for (int moc = 0;; moc++) {
      count_sort(b, q); // sort(all(b)) can be used as well
      a[b[0].second] = 0;
      rep(i, 1, N)
      a[b[i].second] = a[b[i - 1].second] +
                       (b[i - 1].first != b[i].first);

      if ((1 << moc) >= N) break;
      rep(i, 0, N) {
        b[i].first = (ll)a[i] << q;
        if (i + (1 << moc) < N)
          b[i].first += a[i + (1 << moc)];
        b[i].second = i;
      }
    }
    rep(i, 0, sz(a)) {
      a[i] = b[i].second;
      rank[a[i]] = i;
    }
  }
  vi lcp() {
    // longest common prefixes: res[i] = lcp(a[i], a[i-1])
    int n = sz(a), h = 0;
    vi inv(n), res(n);
    rep(i, 0, n) inv[a[i]] = i;
    rep(i, 0, n) if (inv[i] > 0) {
      int p0 = a[inv[i] - 1];
      while (s[i + h] == s[p0 + h]) h++;
      res[inv[i]] = h;
      if (h > 0) h--;
    }
    return res;
  }
};

namespace LcpFinder{
  SuffixArray *suffixArray;
  RMQ <int> *rmq;
  vi lcp;
  void initLCP(){
    lcp = suffixArray->lcp();
    rmq = new RMQ(lcp);
  }
  int getLCP(int a, int b){
    if(b >= sz(suffixArray->rank)) return 0;
    if(a >= sz(suffixArray->rank)) return 0;
    if(a == b) return sz(suffixArray->rank) - a - 1;
    assert(rmq != nullptr);
    assert(suffixArray != nullptr);
    assert(sz(lcp));
    a = suffixArray->rank[a];
    b = suffixArray->rank[b];
    if(a > b) swap(a, b);
    a++; b++;
    return rmq->query(a, b);
  }
};


  // suffixArray = new SuffixArray(tmp);
  // initLCP();