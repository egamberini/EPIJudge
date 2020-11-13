#include "test_framework/generic_test.h"

unsigned ComputeWeight(unsigned long long x) {
  unsigned w = 0;
  while (x != 0) {
    x &= (x - 1);
    w += 1;
  }
  return w;
}

unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  unsigned w = ComputeWeight(x);
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
    x -= (1UL << (pos-1));
    x += (1UL << (pos));
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
