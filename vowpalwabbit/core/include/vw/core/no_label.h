// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once

#include "vw/core/label_parser.h"
#include "vw/core/vw_fwd.h"

namespace VW980
{
struct no_label
{
};

extern VW980::label_parser no_label_parser_global;
namespace details
{
void return_no_label_example(VW980::workspace& all, void*, VW980::example& ec);
void print_no_label_update(VW980::workspace& all, VW980::example& ec);
void output_and_account_no_label_example(VW980::workspace& all, VW980::example& ec);
}  // namespace details
}  // namespace VW980

namespace no_label
{
using no_label VW_DEPRECATED(
    "no_label::no_label renamed to VW980::no_label. no_label::no_label will be removed in VW 10.") = VW980::no_label;
}