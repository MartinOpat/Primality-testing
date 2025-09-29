#pragma once

#include "primalityTest/primalityTest.hpp"

class MillerRabin : public PrimalityTest {
private:
  __int128 _k =
      40; // Number of iterations, optimals seems to be 40, see
          // http://stackoverflow.com/questions/6325576/how-many-iterations-of-rabin-miller-should-i-use-for-cryptographic-safe-primes
public:
  MillerRabin(__int128 k = 40) { this->_k = k; }
  ~MillerRabin() = default;

  bool isPrime(__int128 n) override;
};
