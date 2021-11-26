/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>
#include <stdexcept>

namespace gauss {
constexpr double PI_GREEK = 3.14159;

template <typename Iterable>
Eigen::VectorXd computeMean(const Iterable &samples) {
  if (samples.empty()) {
    throw std::runtime_error("empty samples container");
  }
  Eigen::VectorXd result(samples.front().size());
  result.setZero();
  double coeff = 1.0 / static_cast<double>(samples.size());
  for (const Eigen::VectorXd &sample : samples) {
    result += coeff * sample;
  }
  return result;
}

template <typename Iterable>
Eigen::MatrixXd computeCovariance(const Iterable &samples) {
  Eigen::MatrixXd temp;
  return computeCovariance(samples, temp);
}

template <typename Iterable>
Eigen::MatrixXd computeCovariance(const Iterable &samples,
                                  Eigen::VectorXd &mean) {
  if (samples.empty()) {
    throw std::runtime_error("empty samples container");
  }
  mean = computeMean(samples);
  Eigen::MatrixXd result(samples.front().size(), samples.front().size());
  result.setZero();
  double coeff = 1.0 / static_cast<double>(samples.size());
  for (const Eigen::VectorXd &sample : samples) {
    result += coeff * (sample - mean) * (sample - mean).transpose();
  }
  return result;
}

void computeCovarianceInvert(Eigen::MatrixXd &sigma_inverse,
                             const Eigen::MatrixXd &sigma);

bool isSuitableCovarianceMatrix(const Eigen::MatrixXd &sigma);
} // namespace gauss
