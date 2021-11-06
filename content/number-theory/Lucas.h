/**
 * Author: Hocky Yudhiono
 * Source: me
 * Description: Lucas Theorem for Combinatorics arbitrary mod
 * Time: O(p^2 \log_p(n))
 * Status: Slightly tested
 */
#pragma once

struct Lucas {
  // Needs Euclid, CRT, Prime, Expo
  VVL factorialModPE; int mod;
  vector <PLI> primeFactors;
  vector <LL> factors;

  Lucas(LL tmpMod) {
    assert(sz(prime));
    mod = tmpMod;
    // Factorize mod
    trav(curPrime, prime) {
      if (tmpMod == 1) break;
      if (curPrime * curPrime > tmpMod) break;
      if (tmpMod % curPrime) continue;
      int factorCount = 0;
      LL curFactor = 1;
      while (tmpMod % curPrime == 0) {
        factorCount++;
        tmpMod /= curPrime;
        curFactor *= curPrime;
      }
      factors.pb(curFactor);
      primeFactors.pb({curPrime, factorCount});
    }
    if (tmpMod != 1) primeFactors.pb({tmpMod, 1}), factors.pb(tmpMod);
    factorialModPE.resize(sz(factors));
    for (int i = 0; i < sz(factors); i++) {
      LL curFactor = factors[i];
      LL curPrime = primeFactors[i].fi;
      factorialModPE[i].resize(curFactor + 1);
      factorialModPE[i][0] = 1;
      for (int j = 1; j <= curFactor; j++) {
        factorialModPE[i][j] = ((j % curPrime == 0 ? 1 : j) * factorialModPE[i][j - 1]) % curFactor;
      }
    }
  }

  LL legendre(LL n, LL p) {
    LL ret = 0;
    while (n) n /= p, ret += n;
    return ret;
  }

  LL F(LL n, LL i) {
    LL curFactor = factors[i];
    LL curPrime = primeFactors[i].fi;
    if (n <= 1) return 1;
    LL ret = 1;
    while (n > 1) {
      LL a = expo(factorialModPE[i][curFactor - 1], n / curFactor, curFactor);
      LL b = factorialModPE[i][n % curFactor];
      ret = (ret * ((a * b) % curFactor)) % curFactor;
      n /= curPrime;
    }
    return ret;
  }

  LL getCombination(LL n, LL r) {
    if (r == 0) return 1;
    if (n < r) return 0;
    LL ret = 0;
    LL remainder = 1;
    for (int i = 0; i < sz(factors); i++) {
      LL curFactor = factors[i];
      LL curPrime = primeFactors[i].fi;
      LL b = legendre(n, curPrime) - legendre(r, curPrime) - legendre(n - r, curPrime);
      LL topPart = (F(n, i) * expo(curPrime, b, curFactor)) % curFactor;
      LL bottomPart = (F(r, i) * F(n - r, i)) % curFactor;
      bottomPart = getInverse(bottomPart, curFactor);
      LL result = (topPart * bottomPart) % curFactor;

      // Do CRT, with remainder ret, and modulo curFactor
      if (remainder == 1) ret = result;
      else ret = crt(ret, remainder, result, curFactor);
      remainder *= curFactor;
    }
    return ret;
  }
};