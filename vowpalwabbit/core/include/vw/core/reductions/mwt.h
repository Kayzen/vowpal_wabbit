// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once

#include "vw/core/v_array.h"
#include "vw/core/vw_fwd.h"

#include <memory>

namespace VW980
{
namespace reductions
{
std::shared_ptr<VW980::LEARNER::learner> mwt_setup(VW980::setup_base_i& stack_builder);
}
}  // namespace VW980

// TODO: move this somewhere else
namespace VW980
{
namespace details
{
void print_scalars(
    VW980::io::writer* f, const VW980::v_array<float>& scalars, const VW980::v_array<char>& tag, VW980::io::logger& logger);
}
}  // namespace VW980
