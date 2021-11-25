#pragma once

#include <CoviarianceAware.h>
#include <MeanAware.h>

namespace gauss {

class Distribution : public CovarianceAware, public MeanAware {
protected:
  Distribution() = default;
};
} // namespace gauss
