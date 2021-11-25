#pragma once

#include <Distribution.h>
#include <stdexcept>

namespace gauss {
constexpr double PI_GREEK = 3.14159;
static const double LOG_2_PI = log(2.0 * PI_GREEK);

template <typename Iterable>
Eigen::VectorXd computeMean(const Iterable &samples) {
  if (samples.empty()) {
    throw std::runtime_error("empty samples container");
  }
  Eigen::VectorXd result;
  double coeff = 1.0 / static_cast<double>(samples.size());
  for (const Eigen::VectorXd &sample : samples) {
    result += coeff * sample;
  }
  return result;
}

template <typename Iterable>
Eigen::MatrixXd computeCovariance(const Iterable &samples) {
  return computeCovariance(samples, computeMean(samples));
}

template <typename Iterable>
Eigen::MatrixXd computeCovariance(const Iterable &samples,
                                  const Eigen::VectorXd &mean) {
  if (samples.empty()) {
    throw std::runtime_error("empty samples container");
  }
  Eigen::MatrixXd result;
  double coeff = 1.0 / static_cast<double>(samples.size());
  for (const Eigen::VectorXd &sample : samples) {
    result += (sample - mean) * (sample - mean).transpose();
  }
  return result;
}

void computeCovarianceInvert(Eigen::MatrixXd &sigma_inverse,
                             const Eigen::MatrixXd &sigma);

bool isSymmetricPositive(const Eigen::MatrixXd &sigma);

double evalNormalLogDensity(const Distribution &distribution,
                            const Eigen::VectorXd &point);
} // namespace gauss
