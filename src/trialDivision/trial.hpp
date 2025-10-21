#pragma once

#include "primalityTest/primalityTest.hpp"
// #include "helpers.hpp"

// TODO: Link stuff using cmake

class TrialDivision : public PrimalityTest {
public:
  TrialDivision() = default;
  ~TrialDivision() = default;

  bool isPrime(BigInt n) override;
};
