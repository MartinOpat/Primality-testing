#include "trial.hpp"

// NOTE: This is technically not exactly trial division. Trial division requires
// getting a set of all primes smaller than sqrt(n) (e.g. via Sieve), and
// returns the factors of n. However, since we only care about whether n is a
// prime and not its factors, the below implementation is a slightly more
// efficient version.

bool TrialDivision::isPrime(BigInt n) {
  if (n <= 1) return 0;
  for (BigInt i = 2; i * i <= n; ++i) {
    if (n % i == 0)
      return false;
  }
  return true;
}
