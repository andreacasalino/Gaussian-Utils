#include <TestSampler.h>
#include <random>

namespace gauss::test {
Eigen::VectorXd make_sample(const std::size_t size, const double scale) {
  Eigen::VectorXd sample(size);
  sample.setRandom();
  sample *= scale;
  return sample;
}

namespace {
void make_orthogonal(Eigen::VectorXd &vector,
                     const Eigen::VectorXd &direction) {
  vector -= (vector.dot(direction)) * direction;
}

Eigen::MatrixXd sample_rotation(const std::size_t size) {
  Eigen::MatrixXd rotation(size, size);
  for (std::size_t k = 0; k < size; ++k) {
    auto col = make_sample(size, 1.0);
    for (std::size_t k2 = 0; k2 < k; ++k2) {
      make_orthogonal(col, rotation.col(k2));
    }
    col *= 1.0 / col.norm();
    rotation.col(k) = col;
  }
  return rotation;
}
} // namespace

Eigen::MatrixXd make_covariance(const Eigen::VectorXd &eig_vals) {
  auto direction = make_sample(eig_vals.size(), 1.0);
  direction *= 1.0 / direction.norm();
  double angle =
      2.0 * 3.141 * static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

  Eigen::MatrixXd covariance(eig_vals.size(), eig_vals.size());
  covariance.setZero();
  for (std::size_t k = 0; k < eig_vals.size(); ++k) {
    covariance(k, k) = eig_vals(k);
  }

  Eigen::MatrixXd rotation = sample_rotation(eig_vals.size());

  return rotation * covariance * rotation.transpose();
}

Eigen::MatrixXd make_covariance(const std::size_t size, const double scale) {
  auto eigs = make_sample(size, scale);
  for (std::size_t k = 0; k < eigs.size(); ++k) {
    eigs(k) = abs(eigs(k));
  }
  return make_covariance(eigs);
}
} // namespace gauss::test
