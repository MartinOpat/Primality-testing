#pragma once

#include "helpers.hpp"

// An abstract parent class for all primality tests

class PrimalityTest {
public:
  // NOTE: Constructor and destructor is kept as default, we do not care
  PrimalityTest() = default;
  virtual ~PrimalityTest() = default;

  virtual bool isPrime(BigInt) = 0;
};
