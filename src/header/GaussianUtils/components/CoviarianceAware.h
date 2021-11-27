/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>

namespace gauss {
class CovarianceAware {
public:
  virtual ~CovarianceAware() = default;

  virtual Eigen::MatrixXd getCovariance() const = 0;
  virtual Eigen::MatrixXd getCovarianceInv() const = 0;
  virtual double getCovarianceDeterminant() const = 0;

protected:
  CovarianceAware() = default;
};

} // namespace gauss
