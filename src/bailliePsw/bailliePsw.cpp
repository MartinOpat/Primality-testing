
#include "bailliePsw.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <utility>

// normalize into [0, m)
static inline BigInt norm_mod(BigInt x, BigInt m) {
  x %= m;
  if (x < 0)
    x += m;
  return x;
}

// (a + b) mod m
static inline BigInt addmod(BigInt a, BigInt b, BigInt m) {
  BigInt s = a + b;
  if (s >= m)
    s -= m;
  return s;
}

// (a * b) mod m
static inline BigInt mulmod(BigInt a, BigInt b, BigInt m) {
  a %= m;
  if (a < 0)
    a += m;
  b %= m;
  if (b < 0)
    b += m;
  BigInt t = a * b;
  t %= m;
  if (t < 0)
    t += m;
  return t;
}

BigInt modTwoInv(BigInt x, BigInt m) {
  x %= m;
  if (x < 0)
    x += m;
  if (x % 2 == 1)
    x += m;
  return x / 2;
}

std::pair<BigInt, BigInt> uv(BigInt k, BigInt n, BigInt p, BigInt d) {
  BigInt u = 1, v = norm_mod(p, n);

  // build binary of k without bitset
  std::string bin;
  for (BigInt t = k; t != 0; t /= 2)
    bin.push_back(t % 2 != 0 ? '1' : '0');
  std::reverse(bin.begin(), bin.end());

  bool trail = true;
  for (char c : bin) {
    if (trail && c == '0')
      continue;
    if (trail) {
      // skip first 1
      trail = false;
      continue;
    }

    BigInt temp = u;
    u = mulmod(u, v, n);

    BigInt vv = mulmod(v, v, n);
    BigInt tt = mulmod(temp, temp, n);
    BigInt dtt = mulmod(d, tt, n);
    v = modTwoInv(addmod(vv, dtt, n), n);

    if (c == '1') {
      temp = u;
      BigInt pu = mulmod(p, u, n);
      u = modTwoInv(addmod(pu, v, n), n);

      BigInt dt = mulmod(d, temp, n);
      BigInt pv = mulmod(p, v, n);
      v = modTwoInv(addmod(dt, pv, n), n);
    }
  }
  return std::make_pair(u, v);
}

bool lucas_helper(BigInt n, BigInt d, BigInt p, BigInt q) {
  auto [u, v] = uv(n + 1, n, p, d);
  return u == 0;
}

bool lucas(BigInt n, BigInt d) { return lucas_helper(n, d, 1, (1 - d) / 4); }

bool isPerfectSquare(BigInt n) {
  if (n <= 0)
    return n == 0;

  BigInt x = 1, y = n, m;
  while (x + 1 < y) {
    m = x + (y - x) / 2;
    if (m * m < n) {
      x = m;
    } else {
      y = m;
    }
  }
  return n == x * x || n == (x + 1) * (x + 1);
}

BigInt jacobi(BigInt a, BigInt n) {
  a %= n;
  a += n;
  a %= n;

  BigInt result = 1;

  while (a != 0) {
    while (a % 2 == 0) {
      a /= 2;
      if (n % 8 == 3 || n % 8 == 5)
        result = -result;
    }
    std::swap(a, n);
    if (a % 4 == 3 && n % 4 == 3)
      result = -result;
    a %= n;
    a += n;
    a %= n;
  }

  if (n == 1)
    return result;
  else
    return 0;
}

std::pair<BigInt, BigInt> getVal(BigInt n) {
  BigInt d = 5;
  BigInt j = jacobi(d, n);

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

bool BailliePSW::isPrime(BigInt n) {
  if (n <= 1)
    return false;
  if (n % 2 == 0) // even
    return n == 2;

  // Test small primes "manually"
  BigInt ps[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

  for (auto &p : ps) {
    if (n % p == 0)
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
