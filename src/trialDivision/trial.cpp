#include "trial.hpp"

using lll = __int128;

// NOTE: This is technically not exactly trial division. Trial division requires
// getting a set of all primes smaller than sqrt(n) (e.g. via Sieve), and
// returns the factors of n. However, since we only care about whether n is a
// prime and not its factors, the below implementation is a slightly more
// efficient version.

bool TrialDivision::isPrime(__int128 n) {
  if (n <= 1) return 0;
  for (lll i = 2; i * i <= n; ++i) {
    if (!(n % i))
      return false;
  }
  return true;
}
