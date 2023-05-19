#pragma once

#include "vw/common/string_view.h"
#include "vw/core/vw_fwd.h"

namespace VW980
{
bool try_extract_random_seed(const VW980::example& ex, VW980::string_view& view);
}  // namespace VW980
