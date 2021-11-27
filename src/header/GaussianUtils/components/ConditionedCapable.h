/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>
#include <vector>

namespace gauss {
template <typename ModelT> class ConditionedAware {
public:
  virtual ~ConditionedAware() = default;

  virtual ModelT
  getConditioned(const Eigen::VectorXd &point,
                 const std::vector<std::size_t> &point_indices) const = 0;

protected:
  ConditionedAware() = default;
};

} // namespace gauss
