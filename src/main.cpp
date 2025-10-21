#include <chrono>
#include <csignal>
#include <iostream>
#include <string>

#include "bailliePsw/bailliePsw.hpp"
//#include "millerRabin/millerRabin.hpp"
// #include "primalityTest/primalityTest.hpp"
#include "trialDivision/trial.hpp"

// #include "helpers.hpp"

// Global variables for efficient (async) info. logging
BigInt i = 0;
std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
PrimalityTest *pt = nullptr;

void signal_handler(int signal) {
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Reached: " << i << std::endl;
  std::cout << "Duration: " << elapsed.count() << " s" << std::endl;
  delete pt;
  std::exit(0);
}

// TODO: Make a unified main for all tests that does the timing
int main(int argc, char *argv[]) {
  std::signal(SIGINT, signal_handler);

  std::string algPickStr = argv[1];
  int algPick = std::stoi(algPickStr);

  std::cout << "Algorithm picked: " << algPick << std::endl;

  switch (algPick) {
  case 0:
    std::cout << "Picked Trial Division\n";
    pt = new TrialDivision();
    break;
  case 1:
    std::cout << "Picked Miller Rabin\n";
    pt = new MillerRabin();
    break;
  case 2:
    pt = new BailliePSW();
    std::cout << "Picked BailliePSW\n";
    break;
  default:
    std::cout << "Invalid algorithm pick, stopping...\n";
    return 0;
  }

  const char *maxIntStr =
      "46116860184273879040000000000000000000000000000000000000000000"; // NOTE:Not the actual __128 limit, rather the
                             // limit of how big ints we want to test
  BigInt maxInt;
  maxInt = "46116860184273879040000000000000000000000000000000000000000000";
  std::cout << maxInt << std::endl;

  // const char *aStr = "100000000";
  // const char *aStr = "200";

  int reps = 10;
  // int wsize =
  // 1000000000000; // Every time measurements includes `wsize`-many ints

  const char *wsizeStr = "1";
  BigInt wsize = strToInt(wsizeStr);
  start = std::chrono::high_resolution_clock::now();
  for (i = 0; i < maxInt; i += wsize) { // Sped-up version
    wsize *= 2;
    for (int r = 0; r < reps; ++r) {
      pt->isPrime(i);
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double tavg = elapsed.count() / reps;
    std::cout << "Time elapsed: " << tavg << "s" << std::endl;
    start = std::chrono::high_resolution_clock::now();
  }

  delete pt;

  return 0;
}
