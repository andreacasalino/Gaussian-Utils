#include "Packer.hpp"
#include <GaussianDistribution.h>
#include <Utils.h>
#include <gtest/gtest.h>

TEST(PdfEvaluation, 3d) {
  Eigen::VectorXd mean = gauss::test::make_vector({1.0, -2.0, 1.5});
  Eigen::MatrixXd sigma = gauss::test::make_matrix(
      {{1.0, 0.0, 0.0}, {0.0, 1.5, 0.0}, {0.0, 0.0, 0.3}});

  {
    gauss::GaussianDistribution distribution(mean, sigma);
    for (int k = 0; k < TRIALS; ++k) {
      const auto sample = make_sample(3);
      EXPECT_SIMILAR(distribution.evalNormalLogDensity(sample),
                     eval_log_density_nd(mean, sigma, sample));
    }
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
