/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

namespace gauss {
template <typename ModelT> class DivergenceAware {
public:
  virtual ~DivergenceAware() = default;

  virtual double
  evaluateKullbackLeiblerDivergence(const ModelT &other) const = 0;

protected:
  DivergenceAware() = default;
};

} // namespace gauss
