#include <TestSampler.h>
#include <random>

namespace gauss::test {
Eigen::VectorXd make_sample(const std::size_t size, const double scale) {
  Eigen::VectorXd sample(size);
  sample.setRandom();
  sample *= scale;
  return sample;
}
} // namespace gauss::test
