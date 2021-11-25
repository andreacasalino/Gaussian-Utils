#include <Packer.h>
#include <gtest/gtest.h>

#include <GaussianDistribution.h>
std::unique_ptr<gauss::GaussianDistribution>
make_distribution(const Eigen::VectorXd &mean,
                  const Eigen::MatrixXd &covariance) {
  std::unique_ptr<gauss::GaussianDistribution> result;
  try {
    result = std::make_unique<gauss::GaussianDistribution>(mean, covariance);
  } catch (...) {
    result = nullptr;
  }
  return result;
}

TEST(DistributionCreation, 1d) {
  EXPECT_FALSE(make_distribution(gauss::test::make_vector({0}),
                                 gauss::test::make_matrix({{1}})) == nullptr);

  EXPECT_FALSE(make_distribution(gauss::test::make_vector({1}),
                                 gauss::test::make_matrix({{1}})) == nullptr);

  EXPECT_FALSE(make_distribution(gauss::test::make_vector({-1}),
                                 gauss::test::make_matrix({{1}})) == nullptr);

  EXPECT_TRUE(make_distribution(gauss::test::make_vector({0}),
                                gauss::test::make_matrix({{-1}})) == nullptr);

  EXPECT_TRUE(make_distribution(gauss::test::make_vector({0}),
                                gauss::test::make_matrix({{-10}})) == nullptr);
}

TEST(DistributionCreation, 2d) {
  EXPECT_FALSE(make_distribution(gauss::test::make_vector({0, 0}),
                                 gauss::test::make_matrix({{1, 0}, {0, 2}})) ==
               nullptr);

  EXPECT_FALSE(make_distribution(gauss::test::make_vector({1, -1}),
                                 gauss::test::make_matrix({{1, 0}, {0, 2}})) ==
               nullptr);

  EXPECT_FALSE(make_distribution(gauss::test::make_vector({-1, 1}),
                                 gauss::test::make_matrix({{1, 0}, {0, 2}})) ==
               nullptr);

  EXPECT_TRUE(make_distribution(gauss::test::make_vector({0, 0}),
                                gauss::test::make_matrix({{-1, 0}, {0, 2}})) ==
              nullptr);

  EXPECT_TRUE(make_distribution(gauss::test::make_vector({0, 0}),
                                gauss::test::make_matrix({{1, 0}, {0, -2}})) ==
              nullptr);

  EXPECT_TRUE(make_distribution(gauss::test::make_vector({0, 0}),
                                gauss::test::make_matrix({{1, 1}, {0, 2}})) ==
              nullptr);

  EXPECT_FALSE(make_distribution(gauss::test::make_vector({0, 0}),
                                 gauss::test::make_matrix(
                                     {{1, -0.1}, {-0.1, 2}})) == nullptr);

  EXPECT_TRUE(make_distribution(
                  gauss::test::make_vector({0, 0}),
                  gauss::test::make_matrix({{0.1, -1}, {-1, 0.1}})) == nullptr);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
