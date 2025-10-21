#pragma once

// #include "helpers.hpp"
#include "primalityTest/primalityTest.hpp"

class MillerRabin : public PrimalityTest {
private:
  BigInt _k =
      40; // Number of iterations, optimals seems to be 40, see
          // http://stackoverflow.com/questions/6325576/how-many-iterations-of-rabin-miller-should-i-use-for-cryptographic-safe-primes
public:
  MillerRabin(BigInt k = 40) { this->_k = k; }
  ~MillerRabin() = default;

  bool isPrime(BigInt) override;
};
