#include "primalityTest/primalityTest.hpp"

// TODO: Link stuff using cmake

class TrialDivision : PrimalityTest {
public:
  TrialDivision() = default;
  ~TrialDivision() = default;

  bool isPrime(__int128 n) override;
};
