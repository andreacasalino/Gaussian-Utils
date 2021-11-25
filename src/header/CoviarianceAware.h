#pragma once

#include <Eigen/Core>

namespace gauss {
class CovarianceAware {
public:
  virtual ~CovarianceAware() = default;

  virtual Eigen::MatrixXd getCovariance() const = 0;
  virtual Eigen::MatrixXd getCovarianceInv() const = 0;
  virtual double getAbsDeterminantCovarianceInv() const = 0;

protected:
  CovarianceAware() = default;
};

} // namespace gauss
