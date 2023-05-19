// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/core/vw_fwd.h"

#include <memory>

namespace VW980
{
namespace reductions
{
std::shared_ptr<VW980::LEARNER::learner> lrqfa_setup(VW980::setup_base_i& stack_builder);
}
}  // namespace VW980