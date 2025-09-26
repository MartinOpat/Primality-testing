#include <chrono>
#include <iostream>

#include "trialDivision/trial.hpp"
#include "primalityTest/primalityTest.hpp"

#include "helpers.hpp"



// TODO: Make a unified main for all tests that does the timing
int main() {
  PrimalityTest *pt = new TrialDivision();


  const char *maxIntStr = "340000000000000000000000000000000000000";
  lll maxInt = strToInt(maxIntStr);

  const char *aStr = "34";
  lll a = strToInt(aStr);




  for (lll i = 0; i < a; i++) {
    std::cout << i << "is a prime?";
    std::cout << "Trial division says: " << (pt->isPrime(i) ? "yes" : "no") << std::endl;
  }

  delete pt;

  return 0;
}
