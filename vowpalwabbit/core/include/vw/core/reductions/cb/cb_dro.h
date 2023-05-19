#pragma once

#include "vw/core/vw_fwd.h"

#include <memory>

namespace VW980
{
namespace reductions
{
std::shared_ptr<VW980::LEARNER::learner> cb_dro_setup(VW980::setup_base_i& stack_builder);
}
}  // namespace VW980