// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once

#include "vw/common/future_compat.h"
#include "vw/core/feature_group.h"
#include "vw/core/vw_fwd.h"

#include <cstddef>

namespace VW980
{
class simple_label
{
public:
  float label = 0.f;

  simple_label();
  simple_label(float label);
  void reset_to_default();
};

inline bool operator==(const simple_label& lhs, const simple_label& rhs) { return lhs.label == rhs.label; }
inline bool operator!=(const simple_label& lhs, const simple_label& rhs) { return !(lhs == rhs); }

class simple_label_reduction_features
{
public:
  float weight;
  float initial;

  simple_label_reduction_features() { reset_to_default(); }
  simple_label_reduction_features(float weight, float initial) : weight(weight), initial(initial) {}
  void reset_to_default() noexcept
  {
    weight = 1.f;
    initial = 0.f;
  }
};

namespace details
{
void return_simple_example(VW980::workspace& all, void*, VW980::example& ec);
bool summarize_holdout_set(VW980::workspace& all, size_t& no_win_counter);
void print_update(VW980::workspace& all, const VW980::example& ec);
void output_and_account_example(VW980::workspace& all, const VW980::example& ec);
void update_stats_simple_label(
    const VW980::workspace& all, shared_data& sd, const VW980::example& ec, VW980::io::logger& logger);
void output_example_prediction_simple_label(VW980::workspace& all, const VW980::example& ec, VW980::io::logger& logger);
void print_update_simple_label(VW980::workspace& all, shared_data& sd, const VW980::example& ec, VW980::io::logger& logger);

template <typename UnusedDataT>
void update_stats_simple_label(const VW980::workspace& all, shared_data& sd, const UnusedDataT& /* unused */,
    const VW980::example& ec, VW980::io::logger& logger)
{
  update_stats_simple_label(all, sd, ec, logger);
}
template <typename UnusedDataT>
void output_example_prediction_simple_label(
    VW980::workspace& all, const UnusedDataT& /* unused */, const VW980::example& ec, VW980::io::logger& logger)
{
  output_example_prediction_simple_label(all, ec, logger);
}
template <typename UnusedDataT>
void print_update_simple_label(
    VW980::workspace& all, shared_data& sd, const UnusedDataT& /* unused */, const VW980::example& ec, VW980::io::logger& logger)
{
  print_update_simple_label(all, sd, ec, logger);
}
}  // namespace details
}  // namespace VW980

using label_data VW_DEPRECATED(
    "label_data renamed to VW980::simple_label. label_data will be removed in VW 10.") = VW980::simple_label;
using simple_label_reduction_features VW_DEPRECATED(
    "simple_label_reduction_features renamed to VW980::simple_label_reduction_features. simple_label_reduction_features "
    "will be removed in VW 10.") = VW980::simple_label_reduction_features;
