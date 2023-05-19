// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/common/future_compat.h"
#include "vw/core/v_array.h"

#include <cstdint>

namespace VW980
{
enum class ccb_example_type : uint8_t
{
  UNSET = 0,
  SHARED = 1,
  ACTION = 2,
  SLOT = 3
};

class ccb_reduction_features
{
public:
  ccb_example_type type;
  VW980::v_array<uint32_t> explicit_included_actions;
  void clear() { explicit_included_actions.clear(); }
};
}  // namespace VW980

namespace VW980
{
const char* to_string(ccb_example_type type);
}  // namespace VW980

namespace CCB  // NOLINT
{
using example_type VW_DEPRECATED(
    "VW980::ccb_example_type renamed to VW980::ccb_example_type. VW980::ccb_example_type will be removed in VW 10.") =
    VW980::ccb_example_type;
using reduction_features VW_DEPRECATED(
    "CCB::reduction_features renamed to VW980::ccb_reduction_features. CCB::reduction_features will be removed in VW "
    "10.") = VW980::ccb_reduction_features;
}  // namespace CCB
