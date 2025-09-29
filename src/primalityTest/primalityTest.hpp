#pragma once

// An abstract parent class for all primality tests

class PrimalityTest {
public:
  // NOTE: Constructor and destructor is kept as default, we do not care
  PrimalityTest() = default;
  virtual ~PrimalityTest() = default;

  virtual bool isPrime(__int128 n) = 0;
};
