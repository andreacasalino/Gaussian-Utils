#pragma once

#include <Eigen/Core>

namespace gauss::test {
Eigen::VectorXd make_sample(const std::size_t size, const double scale);

Eigen::MatrixXd make_covariance(const Eigen::VectorXd &eig_vals);

Eigen::MatrixXd make_covariance(const std::size_t size, const double scale);
} // namespace gauss::test