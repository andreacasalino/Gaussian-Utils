#include <GaussianDistribution.h>
#include <Packer.h>
#include <TestSampler.h>
#include <Utils.h>
#include <gtest/gtest.h>
#include <random>

constexpr double TOLL = 0.001;
#define EXPECT_SIMILAR(VAL_A, VAL_B) EXPECT_LE(abs(VAL_A - VAL_B), TOLL)

constexpr std::size_t TRIALS = 20;

double eval_log_density_1d(const double mean, const double sigma,
                           const double point) {
  return -0.5 * log(2.0 * gauss::PI_GREEK * sigma) -
         0.5 * pow(point - mean, 2) / sigma;
}

TEST(PdfEvaluation, 1d) {
  double mean = 0.0;
  double sigma = 1.0;

  {
    gauss::GaussianDistribution distribution(
        gauss::test::make_vector({mean}), gauss::test::make_vector({{sigma}}));
    for (int k = 0; k < TRIALS; ++k) {
      const auto sample = gauss::test::make_sample(1, 5.0);
      EXPECT_SIMILAR(distribution.evalNormalLogDensity(sample),
                     eval_log_density_1d(mean, sigma, sample(0)));
    }
  }

  mean = 1.0;
  {
    gauss::GaussianDistribution distribution(
        gauss::test::make_vector({mean}), gauss::test::make_vector({{sigma}}));
    for (int k = 0; k < TRIALS; ++k) {
      const auto sample = gauss::test::make_sample(1, 5.0);
      EXPECT_SIMILAR(distribution.evalNormalLogDensity(sample),
                     eval_log_density_1d(mean, sigma, sample(0)));
    }
  }

  mean = -1.0;
  {
    gauss::GaussianDistribution distribution(
        gauss::test::make_vector({mean}), gauss::test::make_vector({{sigma}}));
    for (int k = 0; k < TRIALS; ++k) {
      const auto sample = gauss::test::make_sample(1, 5.0);
      EXPECT_SIMILAR(distribution.evalNormalLogDensity(sample),
                     eval_log_density_1d(mean, sigma, sample(0)));
    }
  }

  mean = 1.3;
  sigma = 0.2;
  {
    gauss::GaussianDistribution distribution(
        gauss::test::make_vector({mean}), gauss::test::make_vector({{sigma}}));
    for (int k = 0; k < TRIALS; ++k) {
      const auto sample = gauss::test::make_sample(1, 5.0);
      EXPECT_SIMILAR(distribution.evalNormalLogDensity(sample),
                     eval_log_density_1d(mean, sigma, sample(0)));
    }
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
