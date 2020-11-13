#include "test_framework/generic_test.h"

unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  unsigned long long lowest_set_bit = x & ~(x-1);
  if (lowest_set_bit != 1) {
    x -= lowest_set_bit;
    lowest_set_bit >>= 1;
    x += lowest_set_bit;
  } else {
    unsigned long long x1 = x;
    unsigned pos = 0;
    while ((x1 & 1) == 1) {
      x1 >>= 1;
      pos += 1;
    }
    x ^= ((1UL << (pos-1)) | (1UL << (pos)));
  }
  return x;

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
