#include "test_framework/generic_test.h"
#include <unordered_map>

std::unordered_map<uint8_t, uint8_t> lookup_table;

short Parity(unsigned long long x) {
  // 64 bit can be divided in 8 times 8 bit -> lookup table of parity for 8 bit
  short parity = 0;
  for (short i=0; i<8; i++) {
    short chunk = x & 0xFF;
    parity ^= lookup_table[chunk]; // also work with ShortParity instead of lookup_table
    x >>= 8;
  }
  return parity;
}

short ShortParity(unsigned long long x) {
  short parity = 0;
  while (x) {
    parity ^= x & 1;
    x >>= 1;
  }
  return parity;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  // for (uint8_t c=0; c<UINT8_MAX; c++) {
  //   lookup_table[c] = ShortParity(c);
  // }
  return GenericTestMain(args, "parity.cc", "parity.tsv", &ShortParity,
                         DefaultComparator{}, param_names);
}
