// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/cache_parser/parse_example_cache.h"
#include "vw/common/future_compat.h"

namespace VW980
{
VW_DEPRECATED("VW980::write_example_to_cache moved to VW980::parsers::cache::write_example_to_cache")
inline void write_example_to_cache(io_buf& output, VW980::example* ex_ptr, VW980::label_parser& lbl_parser,
    uint64_t parse_mask, VW980::parsers::cache::details::cache_temp_buffer& temp_buffer)
{
  return VW980::parsers::cache::write_example_to_cache(output, ex_ptr, lbl_parser, parse_mask, temp_buffer);
}
VW_DEPRECATED("VW980::read_example_from_cache moved to VW980::parsers::cache::read_example_from_cache")
inline int read_example_from_cache(VW980::workspace* all, io_buf& input, VW980::multi_ex& examples)
{
  return VW980::parsers::cache::read_example_from_cache(all, input, examples);
}
}  // namespace VW980
