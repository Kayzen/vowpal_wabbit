// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once

#include "vw/common/string_view.h"
#include "vw/core/multi_ex.h"
#include "vw/core/vw_fwd.h"

#include <cstdint>

namespace VW980
{
namespace parsers
{
namespace text
{
namespace details
{
void substring_to_example(VW980::workspace* all, VW980::example* ae, VW980::string_view example);
size_t read_features(io_buf& buf, char*& line, size_t& num_chars);
}  // namespace details

void read_line(VW980::workspace& all, example* ex, VW980::string_view line);  // read example from the line.
void read_lines(VW980::workspace* all, VW980::string_view lines_view,
    VW980::multi_ex& examples);  // read examples from the new line separated strings.

int read_features_string(VW980::workspace* all, io_buf& buf, VW980::multi_ex& examples);
}  // namespace text
}  // namespace parsers
}  // namespace VW980
