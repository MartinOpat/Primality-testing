#pragma once

#include <iostream>

using lll = __int128;

inline __int128 strToInt(const char *num) {
  __int128 a = 0;
  for (int i = 0; num[i]; i++)
    a = a * 10 + (num[i] - '0');
  return a;
}

inline std::ostream &operator<<(std::ostream &o, __int128 n) {
  auto t = n < 0 ? -n : n;
  char b[128], *d = std::end(b);
  do
    *--d = '0' + t % 10, t /= 10;
  while (t);
  if (n < 0)
    *--d = '-';
  o.rdbuf()->sputn(d, std::end(b) - d);
  return o;
}

inline lll mod_pow(lll base, lll exp, lll mod) {
  if (mod == 1)
    return 0;
  if (exp == 0)
    return 1;
  if (exp == 1)
    return base;

  lll res = 1;
  base %= mod;
  while (exp) {
    if (exp % 2 == 1)
      res = (res * base) % mod;
    exp >>= 1;
    base = (base * base) % mod;
  }

  return res % mod;
}


// Upper is exclusive, lower is inclusive. TODO: Move to `helpers.hpp`
inline lll bounded_rand(lll lower, lll upper) {
  return std::rand() % (upper - lower) + lower;
}