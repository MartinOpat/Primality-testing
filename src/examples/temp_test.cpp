
#include "helpers.hpp"

using namespace std;

int main() {
  __int128 a = 0;
  const char *num = "3317044064679887385961981";
  for (int i = 0; num[i]; i++)
    a = a * 10 + (num[i] - '0');

  cout << a + 1 << endl;
  return (0);
}
