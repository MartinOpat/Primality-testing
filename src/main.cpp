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
  pt2 = new MillerRabin(1);
  pt3 = new BailliePSW();

  const char *maxIntStr =
      "2000000000000000000000000000000000"; // NOTE:Not the actual __128 limit, rather the limit
                           // of how big ints we want to test
  lll maxInt = strToInt(maxIntStr);
  std::cout << maxInt << std::endl;

  // const char *aStr = "100000000";
  const char *aStr = "1";
  lll a = strToInt(aStr);

  std::vector<lll> mr_wrong;
  std::vector<lll> pse_wrong;
  
  bool gt, mr, pse;
  start = std::chrono::high_resolution_clock::now();
  // for (i = maxInt; i < a; ++i) {
  int c = 10000000;
  while (c>0) {

    i = bounded_rand(a, maxInt);
  
    gt = pt1->isPrime(i);
    mr = pt2->isPrime(i);
    pse = pt3->isPrime(i);

    if (mr != gt) {
      mr_wrong.push_back(i);
      std::cout << i << std::endl;
    }


    if (pse != gt) {
      pse_wrong.push_back(i);
      std::cout << i << std::endl;
    }

    --c;
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
