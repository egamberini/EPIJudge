#include "test_framework/generic_test.h"
#include <unordered_map>

std::unordered_map<uint8_t, uint8_t> lookup_table;

uint8_t SwapBits(uint8_t x, int i, int j) {
  if (((x >> i)&1) != ((x >> j)&1)) {
    uint8_t bit_mask = (1 << i) | (1 << j);
    x ^= bit_mask;
  }
  return x;
}

unsigned long long ReverseBits_8(uint8_t x) {
  for (int i=0; i<4; i++) {
    x = SwapBits(x, i, 7-i);
  }
  return x;
}

unsigned long long ReverseBits(unsigned long long x) {
  uint8_t part7 = (x >> 56) & 0xFF;
  uint8_t part6 = (x >> 48) & 0xFF;
  uint8_t part5 = (x >> 40) & 0xFF;
  uint8_t part4 = (x >> 32) & 0xFF;
  uint8_t part3 = (x >> 24) & 0xFF;
  uint8_t part2 = (x >> 16) & 0xFF;
  uint8_t part1 = (x >> 8) & 0xFF;
  uint8_t part0 = x & 0xFF;

  x = (ReverseBits_8(part0) << 56) + (ReverseBits_8(part1) << 48) + (ReverseBits_8(part2) << 40) + (ReverseBits_8(part3) << 32) 
      + (ReverseBits_8(part4) << 24) + (ReverseBits_8(part5) << 16) + (ReverseBits_8(part6) << 8) + ReverseBits_8(part7);

  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
