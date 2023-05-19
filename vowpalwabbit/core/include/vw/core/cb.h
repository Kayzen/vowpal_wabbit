// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once

#include "vw/core/io_buf.h"
#include "vw/core/label_parser.h"
#include "vw/core/multi_ex.h"
#include "vw/core/v_array.h"
#include "vw/core/vw_fwd.h"

#include <cfloat>
#include <cstdint>
#include <utility>
#include <vector>

namespace VW980
{
// By default a cb class does not contain an observed cost.
class cb_class
{
public:
  float cost = FLT_MAX;      // the cost of this class
  uint32_t action = 0;       // the index of this class
  float probability = -1.f;  // new for bandit setting, specifies the probability the data collection policy chose this
                             // class for importance weighting
  float partial_prediction = 0.f;  // essentially a return value

  cb_class() = default;
  cb_class(float cost, uint32_t action, float probability)
      : cost(cost), action(action), probability(probability), partial_prediction(0.f)
  {
  }

  bool operator==(cb_class j) const { return action == j.action; }

  constexpr bool has_observed_cost() const { return (cost != FLT_MAX && probability > .0); }
};

class cb_label
{
public:
  std::vector<cb_class> costs;
  float weight = 1.f;

  VW_ATTR(nodiscard) bool is_test_label() const;
  VW_ATTR(nodiscard) bool is_labeled() const;
  void reset_to_default();
};

extern VW980::label_parser cb_label_parser_global;

// example headers look like "shared"
bool ec_is_example_header_cb(VW980::example const& ec);

std::pair<bool, cb_class> get_observed_cost_cb(const cb_label& ld);

}  // namespace VW980
namespace VW980
{
namespace details
{
void print_update_cb(VW980::workspace& all, bool is_test, const VW980::example& ec, const VW980::multi_ex* ec_seq,
    bool action_scores, const VW980::cb_class* known_cost);
}
}  // namespace VW980

namespace VW980
{
class cb_eval_label
{
public:
  uint32_t action = 0;
  cb_label event;
};

extern VW980::label_parser cb_eval_label_parser_global;  // for evaluation of an arbitrary policy.
}  // namespace VW980

namespace VW980
{
namespace model_utils
{
size_t read_model_field(io_buf&, VW980::cb_class&);
size_t write_model_field(io_buf&, const VW980::cb_class&, const std::string&, bool);
size_t read_model_field(io_buf&, VW980::cb_label&);
size_t write_model_field(io_buf&, const VW980::cb_label&, const std::string&, bool);
size_t read_model_field(io_buf&, VW980::cb_eval_label&);
size_t write_model_field(io_buf&, const VW980::cb_eval_label&, const std::string&, bool);
}  // namespace model_utils
}  // namespace VW980

namespace CB
{
using cb_class VW_DEPRECATED("Renamed to VW980::cb_class") = VW980::cb_class;
using label VW_DEPRECATED("Renamed to VW980::cb_label") = VW980::cb_label;

VW_DEPRECATED("Renamed to VW980::ec_is_example_header_cb")
inline bool ec_is_example_header(VW980::example const& ec) { return VW980::ec_is_example_header_cb(ec); }

VW_DEPRECATED("Renamed to VW980::get_observed_cost_cb")
inline std::pair<bool, VW980::cb_class> get_observed_cost_cb(const VW980::cb_label& ld)
{
  return VW980::get_observed_cost_cb(ld);
}
}  // namespace CB

namespace CB_EVAL
{
using label VW_DEPRECATED("Renamed to VW980::cb_eval_label") = VW980::cb_eval_label;
}