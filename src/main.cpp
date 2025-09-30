#include <chrono>
#include <csignal>
#include <iostream>

#include "millerRabin/millerRabin.hpp"
#include "primalityTest/primalityTest.hpp"
#include "trialDivision/trial.hpp"

#include "helpers.hpp"

lll i = 0;

void signal_handler(int signal) {
  std::cout << "Reached: " << i << std::endl;
  std::exit(0);
}

// TODO: Make a unified main for all tests that does the timing
int main() {

  std::signal(SIGINT, signal_handler);

  // PrimalityTest *pt = new TrialDivision();
  PrimalityTest *pt = new MillerRabin(1);

  const char *maxIntStr = "340000000000000000000000000000000000000";
  lll maxInt = strToInt(maxIntStr);

  const char *aStr = "100000000";
  // const char *aStr = "34";
  lll a = strToInt(aStr);

  auto start = std::chrono::high_resolution_clock::now();
  for (i = 0; i < a; ++i) {
    pt->isPrime(i);
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time ellapsed: " << elapsed.count() << "s" << std::endl;

  delete pt;

  return 0;
}
