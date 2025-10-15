#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <vector>

#include "bailliePsw/bailliePsw.hpp"
#include "millerRabin/millerRabin.hpp"
#include "primalityTest/primalityTest.hpp"
#include "trialDivision/trial.hpp"

#include "helpers.hpp"

// Global variables for efficient (async) info. logging
lll i = 0;
std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
PrimalityTest *pt1 = nullptr;
PrimalityTest *pt2 = nullptr;
PrimalityTest *pt3 = nullptr;


// TODO: Make a unified main for all tests that does the timing
int main(int argc, char *argv[]) {

  pt1 = new TrialDivision();
  pt2 = new MillerRabin();
  pt3 = new BailliePSW();

  const char *maxIntStr =
      "13000000000000000000"; // NOTE:Not the actual __128 limit, rather the limit
                           // of how big ints we want to test ...rather sqrt(__128)
  lll maxInt = strToInt(maxIntStr);
  
  // const char *aStr = "100000000";
  // const char *aStr = "200000000000000000000";  // > 2^64
  const char *aStr = "1";  // > 2^64
  lll a = strToInt(aStr);
  std::cout << "Testing range: " << a << " - " << maxInt << std::endl;
  
  std::vector<lll> mr_wrong;
  std::vector<lll> pse_wrong;

  const char *tStr = "12451237685321571221";  // > 2^64
  std::cout << "Testing: " << "12451237685321571221" << std::endl;
  lll t = strToInt(tStr);
  if (pt3->isPrime(t))
    std::cout << "Success" << std::endl;
  else
    std::cout << "Fail" << std::endl;
  
  bool gt, mr, pse;
  start = std::chrono::high_resolution_clock::now();

  int c = 0;
  int cmax = 1000;
  std::cout << "Testing " << c << " random numbers" << std::endl;
  int perc = 0;
  while (c < cmax) {

    i = bounded_rand(a, maxInt);
    // std::cout << i << std::endl;
  
    gt = pt1->isPrime(i);
    mr = pt2->isPrime(i);
    pse = pt3->isPrime(i);

    if (mr != gt) {
      mr_wrong.push_back(i);
      std::cout << "mr: " << i << std::endl;
    }


    if (pse != gt) {
      pse_wrong.push_back(i);
      std::cout << "bsw: " << i << std::endl;
    }

    ++c;

    if (100 * (c % (cmax / 100)) == 0) {
      ++perc;
      std::cout << perc << "% " << std::endl;
    }
  }

  std::cout << "mr: " << mr_wrong.size() << std::endl;
  std::cout << "pse: " << pse_wrong.size() << std::endl;
  // for(auto&x:mr_wrong)
  //   std::cout << x << " ";
  // std::cout << std::endl;

  // for(auto&x:pse_wrong)
  //   std::cout << x << " ";
  // std::cout << std::endl;


  delete pt1;
  delete pt2;
  delete pt3;

  return 0;
}
