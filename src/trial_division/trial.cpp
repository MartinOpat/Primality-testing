#include <iostream>

using lll = __int128;

// NOTE: This is technically not exactly trial division. Trial division requires
// getting a set of all primes smaller than sqrt(n) (e.g. via Sieve), and
// returns the factors of n. However, since we only care about whether n is a
// prime and not its factors, the below implementation is a slightly more
// efficient version.
bool trial_division(lll n) {
  for (lll i = 1; i * i <= n; ++i) {
    if (!(n % i))
      return false;
  }
  return true;
}

int main() {
  __int128 a = 0;
  const char *num = "3317044064679887385961981";
  for (int i = 0; num[i]; i++)
    a = a * 10 + (num[i] - '0');

  std::cout << trial_division(a) << std::endl;
}
