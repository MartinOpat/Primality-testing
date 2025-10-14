
#include "bailliePsw.hpp"
#include "helpers.hpp"
#include <bitset>
#include <cassert>
#include <cmath>
#include <utility>

lll modTwoInv(lll n, lll m) {
  // n div 2 (mod m)
  if (n & 1)
    return ((n + m) >> 1) % m;
  else
    return (n >> 1) % m;
}

std::pair<lll, lll> uv(lll k, lll n, lll p, lll d) {
  lll u = 1, v = p;
  std::string bin = std::bitset<128>(k).to_string();

  lll temp;
  bool trail = true;
  for (auto &c : bin) {
    if (trail && c == '0')
      continue;
    if (trail) {
      // Skip the first non-zero digit
      trail = false;
      continue;
    }

    temp = u;
    u = (u * v) % n;
    v = modTwoInv(v * v + d * temp * temp, n);

    if (c == '1') {
      temp = u;
      u = modTwoInv(p * u + v, n);
      v = modTwoInv(d * temp + p * v, n);
    }
  }
  return std::make_pair(u, v);
}

bool lucas_helper(lll n, lll d, lll p, lll q) {
  auto [u, v] = uv(n + 1, n, p, d);
  return u == 0;
}

bool lucas(lll n, lll d) { return lucas_helper(n, d, 1, (1 - d) / 4); }

bool isPerfectSquare(lll n) {
  lll guess = std::sqrt(n);
  lll r = std::floor(guess);
  if (r * r == n)
    return true;
  else {
    r = std::ceil(guess);
    return r * r == n;
  }
}

lll jacobi(lll a, lll n) {
  a = (a+n) % n;
  if (a < 0) a += n;
  lll result = 1;

  while (a != 0) {
    while (!(a & 1)) {
      a /= 2;
      if (n % 8 == 3 || n % 8 == 5)
        result = -result;
    }
    std::swap(a, n);
    if (a % 4 == 3 && n % 4 == 3)
      result = -result;
    a = (a+n) % n;
  }

  if (n == 1)
    return result;
  else
    return 0;
}

std::pair<lll, lll> getVal(lll n) {
  lll d = 5;
  lll j = jacobi(d, n);

  while (j > 0) {
    if (d > 0)
      d += 2;
    else
      d -= 2;
    d *= -1;

    if (d == -15) {
      if (isPerfectSquare(n))
        return std::make_pair(0, 0);
    }
    j = jacobi(d, n);
  }
  return std::make_pair(d, j);
}

bool BailliePSW::isPrime(__int128 n) {
  if (n <= 1)
    return false;
  if (!(n & 1)) // even
    return false;

  // Test small primes "manually"
  lll ps[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
              43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

  for (auto &p : ps) {
    if (!(n % p))
      return n == p;
  }

  // First call regular millerRabin
  if (!(millerRabin.isPrime(n))) {
    // std::cout << "Don't blame me ... " << std::endl;
    return false;
  }

  auto [d, j] = getVal(n);
  if (j == 0) {
    return false;
  }

  return lucas(n, d);
}
