#pragma once

#include <random>
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

  return (res + mod) % mod;
}


// Upper is exclusive, lower is inclusive. TODO: Move to `helpers.hpp`
inline lll bounded_rand(lll lower, lll upper) {
  return std::rand() % (upper - lower) + lower;
}

// inline __uint128_t rand_u128() {
//   static thread_local std::mt19937_64 rng(std::random_device{}());
//   __uint128_t hi = static_cast<__uint128_t>(rng());
//   __uint128_t lo = static_cast<__uint128_t>(rng());
//   return (hi << 64) | lo;
// }

// // [lower, upper)
// inline lll bounded_rand(lll lower, lll upper) {
//   if (!(upper > lower)) return lower; // or assert
//   __uint128_t span = static_cast<__uint128_t>(upper - lower);

//   const __uint128_t max = ~static_cast<__uint128_t>(0);       // UINT128_MAX
//   const __uint128_t limit = max - (max % span);               // rejection limit

//   __uint128_t r;
//   do {
//     r = rand_u128();
//   } while (r >= limit);

//   return static_cast<lll>(static_cast<__int128>(lower) +
//                           static_cast<__int128>(r % span));
// }