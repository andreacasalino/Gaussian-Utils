#include <Packer.h>
#include <gtest/gtest.h>

#include <GaussianUtils/GaussianDistribution.h>

TEST(ConditionedGaussian, single_observation) {
  double sigmas[2] = {0.5, 1.0};
  double mean = 2.0;

  gauss::GaussianDistribution distribution(
      gauss::test::make_vector({mean, 0.0}),
      gauss::test::make_matrix({{sigmas[0], 0}, {0, sigmas[1]}}));

  auto conditioned = distribution.getConditioned(1, 0.0);
  EXPECT_EQ(conditioned.getCovariance().rows(), 1);
  EXPECT_LE(abs(conditioned.getCovariance()(0, 0) - sigmas[0]), 0.001);
  EXPECT_LE(abs(conditioned.getMean()(0) - mean), 0.001);
}

TEST(ConditionedGaussian, multiple_observations) {
  double sigmas[2] = {0.5, 1.0};
  double mean = 2.0;

  gauss::GaussianDistribution distribution(
      gauss::test::make_vector({mean, 0.0, mean, 0.0}),
      gauss::test::make_matrix({{sigmas[0], 0, 0, 0},
                                {0, sigmas[1], 0, 0},
                                {0, 0, sigmas[0], 0},
                                {0, 0, 0, sigmas[1]}}));

  auto conditioned =
      distribution.getConditioned({1, 3}, Eigen::VectorXd::Zero(2));
  EXPECT_EQ(conditioned.getCovariance().rows(), 2);
  EXPECT_LE(abs(conditioned.getCovariance()(0, 0) - sigmas[0]), 0.001);
  EXPECT_LE(abs(conditioned.getCovariance()(1, 1) - sigmas[0]), 0.001);
  EXPECT_LE(abs(conditioned.getMean()(0) - mean), 0.001);
  EXPECT_LE(abs(conditioned.getMean()(1) - mean), 0.001);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
