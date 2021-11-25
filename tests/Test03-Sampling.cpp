#include <GaussianDistribution.h>
#include <Packer.h>
#include <Sampler.h>
#include <TestSampler.h>
#include <Utils.h>
#include <gtest/gtest.h>
#include <vector>

constexpr std::size_t SAMPLES = 100000;

constexpr double TOLL = 0.025;
#define EXPECT_SIMILAR(VAL_A, VAL_B) EXPECT_LE(abs(VAL_A - VAL_B), TOLL)

void expect_similar(const Eigen::VectorXd &a, const Eigen::VectorXd &b) {
  EXPECT_EQ(a.size(), b.size());
  for (std::size_t k = 0; k < a.size(); ++k) {
    EXPECT_SIMILAR(a(k), b(k));
  }
};

void expect_similar(const Eigen::MatrixXd &a, const Eigen::MatrixXd &b) {
  EXPECT_EQ(a.rows(), b.rows());
  EXPECT_EQ(a.cols(), b.cols());
  for (std::size_t c = 0; c < a.cols(); ++c) {
    for (std::size_t r = 0; r < a.rows(); ++r) {
      EXPECT_SIMILAR(a(r, c), b(r, c));
    }
  }
};

std::vector<Eigen::VectorXd>
make_samples(const gauss::GaussianDistribution &distr) {
  gauss::Sampler sampler(distr);
  std::vector<Eigen::VectorXd> samples;
  samples.reserve(SAMPLES);
  for (int k = 0; k < SAMPLES; ++k) {
    samples.push_back(sampler.getSample());
  }
  return samples;
}

TEST(Sampling, 3d) {
  Eigen::VectorXd mean = gauss::test::make_vector({1.0, -2.0, 1.5});
  Eigen::MatrixXd sigma = gauss::test::make_matrix(
      {{1.0, 0.0, 0.0}, {0.0, 1.5, 0.0}, {0.0, 0.0, 0.3}});

  auto samples = make_samples(gauss::GaussianDistribution(mean, sigma));
  Eigen::VectorXd samples_mean;
  auto samples_cov = gauss::computeCovariance(samples, samples_mean);

  expect_similar(mean, samples_mean);
  expect_similar(sigma, samples_cov);
}

TEST(Sampling, 6d) {
  Eigen::VectorXd mean = gauss::test::make_sample(6, 5.0);
  Eigen::MatrixXd sigma = gauss::test::make_covariance(6, 3.0);

  auto samples = make_samples(gauss::GaussianDistribution(mean, sigma));
  Eigen::VectorXd samples_mean;
  auto samples_cov = gauss::computeCovariance(samples, samples_mean);

  expect_similar(mean, samples_mean);
  expect_similar(sigma, samples_cov);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
