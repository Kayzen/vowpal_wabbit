// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/core/action_score.h"
#include "vw/core/constant.h"
#include "vw/core/v_array.h"

#include <vector>

namespace VW980
{
// Each position in outer array is implicitly the decision corresponding to that index. Each inner array is the result
// of CB for that call.
using decision_scores_t = std::vector<VW980::action_scores>;

void print_decision_scores(VW980::io::writer* f, const VW980::decision_scores_t& decision_scores, VW980::io::logger& logger);
std::string to_string(
    const VW980::decision_scores_t& decision_scores, int decimal_precision = VW980::details::DEFAULT_FLOAT_PRECISION);

void print_update_ccb(VW980::workspace& all, const std::vector<example*>& slots,
    const VW980::decision_scores_t& decision_scores, size_t num_features);
void print_update_slates(VW980::workspace& all, const std::vector<example*>& slots,
    const VW980::decision_scores_t& decision_scores, size_t num_features);
}  // namespace VW980
