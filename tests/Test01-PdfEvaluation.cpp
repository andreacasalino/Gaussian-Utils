#include <Distribution.h>
#include <gtest/gtest.h>

TEST(Range, binaryGroupSmall) {
  VariablePtr A = makeVariable(2, "A");
  VariablePtr B = makeVariable(2, "B");
  Range rangeAB({A, B});

  compare(rangeAB, {makeCombination({0, 0}), makeCombination({0, 1}),
                    makeCombination({1, 0}), makeCombination({1, 1})});
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
