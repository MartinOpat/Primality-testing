
#pragma once

#include "millerRabin/millerRabin.hpp"
// #include "primalityTest/primalityTest.hpp"
// #include "helpers.hpp"

class BailliePSW : public PrimalityTest {
public:
  BailliePSW() = default;
  ~BailliePSW() = default;

  bool isPrime(BigInt n) override;

private:
  MillerRabin millerRabin{1};
};
