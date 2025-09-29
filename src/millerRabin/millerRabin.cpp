
#include "millerRabin.hpp"
#include "helpers.hpp"
#include <cstdlib>

// Upper is exclusive, lower is inclusive. TODO: Move to `helpers.hpp`
lll bounded_rand(lll lower, lll upper) {
  return std::rand() % (upper - lower) + lower;
}

bool MillerRabin::isPrime(__int128 n) {
  if (n <= 1)
    return false;

  if (n == 2 || n == 3)
    return true;

  if (!(n & 1))
    return false;

  lll r = 0, s = n - 1;
  lll a, x;
  while (!(s & 1)) {
    ++r;
    s /= 2;
  }

  for (lll i = 0; i < _k; ++i) {
    a = bounded_rand(2, n - 1);
    x = mod_pow(a, s, n);

    if (x == 1 || x == n - 1)
      continue;

    bool broke = false;
    for (int j = 0; j < r - 1; ++j) {
      x = mod_pow(x, 2, n);
      if (x == n - 1) {
        broke = true;
        break;
      }
    }
    if (!broke)
      return false;
  }
  return true;
}
