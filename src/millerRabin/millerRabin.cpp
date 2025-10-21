
#include "millerRabin.hpp"
//#include "helpers.hpp"
#include <cstdlib>

bool MillerRabin::isPrime(BigInt n) {
  if (n <= 1)
    return false;

  if (n == 2 || n == 3)
    return true;

  if (n%2 == 0)
    return false;

  BigInt r = 0, s = n - 1;
  BigInt a, x;
  while (s%2 == 0) {
    ++r;
    s /= 2;
  }

  for (BigInt i = 0; i < _k; ++i) {
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
