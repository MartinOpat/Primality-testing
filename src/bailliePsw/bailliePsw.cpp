
#include "bailliePsw.hpp"
#include "helpers.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <utility>

// normalize into [0, m)
static inline lll norm_mod(lll x, lll m) {
  x %= m;
  if (x < 0)
    x += m;
  return x;
}

// (a + b) mod m
static inline lll addmod(lll a, lll b, lll m) {
  a = norm_mod(a, m);
  b = norm_mod(b, m);
  lll s = a + b;
  if (s >= m)
    s -= m; // since a,b < m, s < 2m
  return s;
}

// (a * b) mod m
static inline lll mulmod(lll a, lll b, lll m) {
  a = norm_mod(a, m);
  b = norm_mod(b, m);
  lll res = 0;
  while (b) {
    if (b & 1) {
      res += a;
      if (res >= m)
        res -= m;
    }
    b >>= 1;
    a <<= 1;
    if (a >= m)
      a -= m;
  }
  return res;
}

lll modTwoInv(lll x, lll m) {
  x = norm_mod(x, m);
  if (x & 1)
    x += m;
  return (x >> 1) % m;
}

std::pair<lll, lll> uv(lll k, lll n, lll p, lll d) {
  lll u = 1, v = norm_mod(p, n);

  // build binary of k without bitset
  std::string bin;
  for (lll t =k; t; t >>= 1)
    bin.push_back((t & 1) ? '1' : '0');
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

    lll temp = u;
    u = mulmod(u, v, n);

    lll vv = mulmod(v, v, n);
    lll tt = mulmod(temp, temp, n);
    lll dtt = mulmod(d, tt, n);
    v = modTwoInv(addmod(vv, dtt, n), n);

    if (c == '1') {
      temp = u;
      lll pu = mulmod(p, u, n);
      u = modTwoInv(addmod(pu, v, n), n);

      lll dt = mulmod(d, temp, n);
      lll pv = mulmod(p, v, n);
      v = modTwoInv(addmod(dt, pv, n), n);
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
  if (n <= 0)
    return n == 0;

  lll x = 1, y = n, m;
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

lll jacobi(lll a, lll n) {
  a %= n;
  a += n;
  a %= n;

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
    a %= n;
    a += n;
    a %= n;
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
    return n == 2;

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
