#pragma once

#include <Eigen/Core>

namespace gauss::test {
Eigen::VectorXd make_sample(const std::size_t size, const double scale);
} // namespace gauss::test