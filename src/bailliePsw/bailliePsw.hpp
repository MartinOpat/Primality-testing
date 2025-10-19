
#pragma once

#include "millerRabin/millerRabin.hpp"
#include "primalityTest/primalityTest.hpp"

class BailliePSW : public PrimalityTest {
public:
  BailliePSW() = default;
  ~BailliePSW() = default;

  bool isPrime(__int128 n) override;

private:
  MillerRabin millerRabin = MillerRabin(1);
};
