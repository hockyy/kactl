/**
 * Author: hocky
 * License: CC0
 * Source: Own work
 * Description: Getchar unlocked
 * Status: tested
 */
#define GC getchar_unlocked
inline void fastll(LL &inp) {
  inp = 0; int ch = GC(); int sign = 1;
  while (ch < '0' || ch > '9') {
    if (ch == '-') sign = -1;
    ch = GC();
  }
  while (ch >= '0' && ch <= '9') {
    inp = (inp << 3) + (inp << 1) + ch - '0';
    ch = GC();
  }
  inp *= sign;
}