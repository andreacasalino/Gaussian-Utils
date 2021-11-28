/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>
#include <GaussianUtils/Error.h>

namespace gauss {
constexpr double PI_GREEK = 3.14159;

template <typename Iterable, typename SampleExtractor>
Eigen::VectorXd computeMean(const Iterable &samples, const SampleExtractor& extractor) {
  if (samples.empty()) {
    throw gauss::Error("empty samples container, when computing mean");
  }
  Eigen::VectorXd result(extractor(samples.front()).size());
  result.setZero();
  double coeff = 1.0 / static_cast<double>(samples.size());
  for (const auto &sample : samples) {
    result += coeff * extractor(sample);
  }
  return result;
}

template <typename Iterable, typename SampleExtractor>
Eigen::MatrixXd computeCovariance(const Iterable &samples, const SampleExtractor& extractor) {
  Eigen::VectorXd temp;
  return computeCovariance(samples, temp, extractor);
}

template <typename Iterable, typename SampleExtractor>
Eigen::MatrixXd computeCovariance(const Iterable &samples,
                                  Eigen::VectorXd &mean, const SampleExtractor& extractor) {
  if (samples.empty()) {
    throw Error("empty samples container, when computing covariance");
  }
  mean = computeMean(samples, extractor);
  Eigen::MatrixXd result(extractor(samples.front()).size(), extractor(samples.front()).size());
  result.setZero();
  double coeff = 1.0 / static_cast<double>(samples.size());
  for (const auto& sample : samples) {
      const Eigen::VectorXd& sample_ref = extractor(sample);
    result += coeff * (sample_ref - mean) * (sample_ref - mean).transpose();
  }
  return result;
}

Eigen::MatrixXd computeCovarianceInvert(const Eigen::MatrixXd &sigma);

bool isSuitableCovarianceMatrix(const Eigen::MatrixXd &sigma);
} // namespace gauss
