#include <chrono>
#include <iostream>

#include "millerRabin/millerRabin.hpp"
#include "primalityTest/primalityTest.hpp"
#include "trialDivision/trial.hpp"

#include "helpers.hpp"

// TODO: Make a unified main for all tests that does the timing
int main() {
  // PrimalityTest *pt = new TrialDivision();
  PrimalityTest *pt = new MillerRabin(1);

  const char *maxIntStr = "340000000000000000000000000000000000000";
  lll maxInt = strToInt(maxIntStr);

  const char *aStr = "100000000";
  // const char *aStr = "34";
  lll a = strToInt(aStr);

  auto start = std::chrono::high_resolution_clock::now();
  for (lll i = 0; i < a; ++i) {
    // std::cout << i << " is a prime?";
    // std::cout << " Trial division says: " << (pt->isPrime(i) ? "yes" : "no")
    // << std::endl;
    pt->isPrime(i);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time ellapsed: " << elapsed.count() << "s" << std::endl;

  delete pt;

  return 0;
}
