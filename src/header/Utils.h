#pragma once

#include <Distribution.h>

namespace gauss {
constexpr double PI_GREEK = 3.14159;
static const double LOG_2_PI = log(2.0 * PI_GREEK);

template <typename Iterable>
Eigen::VectorXd computeMean(const Iterable &samples);

template <typename Iterable>
Eigen::MatrixXd computeCovariance(const Iterable &samples);

template <typename Iterable>
Eigen::MatrixXd computeCovariance(const Iterable &samples,
                                  Eigen::VectorXd &mean);

void computeCovarianceInvert(Eigen::MatrixXd &sigma_inverse,
                             const Eigen::MatrixXd &sigma);

double evalNormalLogDensity(const Distribution &distribution,
                            const Eigen::VectorXd &point);

bool isValidCovariance(const Eigen::MatrixXd &sigma);
} // namespace gauss
