// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#include "vw/core/reductions/print.h"

#include "vw/config/options.h"
#include "vw/core/learner.h"
#include "vw/core/reductions/gd.h"
#include "vw/core/setup_base.h"

#include <cfloat>

using namespace VW980::config;

namespace
{
// TODO: This file should probably(?) use trace_message
class print
{
public:
  print(VW980::workspace* all) : all(all) {}
  VW980::workspace* all;
};  // regressor, feature loop

void print_feature(VW980::workspace& all, float value, uint64_t index)
{
  (*all.trace_message) << index;
  if (value != 1.) { (*all.trace_message) << ":" << value; }
  (*all.trace_message) << " ";
}

void learn(print& p, VW980::example& ec)
{
  assert(p.all != nullptr);
  auto& all = *p.all;
  if (ec.l.simple.label != FLT_MAX)
  {
    (*all.trace_message) << ec.l.simple.label << " ";
    const auto& simple_red_features = ec.ex_reduction_features.template get<VW980::simple_label_reduction_features>();
    if (ec.weight != 1 || simple_red_features.initial != 0)
    {
      (*all.trace_message) << ec.weight << " ";
      if (simple_red_features.initial != 0) { (*all.trace_message) << simple_red_features.initial << " "; }
    }
  }
  if (!ec.tag.empty())
  {
    (*all.trace_message) << '\'';
    (*all.trace_message).write(ec.tag.begin(), ec.tag.size());
  }
  (*all.trace_message) << "| ";
  VW980::foreach_feature<VW980::workspace, uint64_t, print_feature>(*(p.all), ec, *p.all);
  (*all.trace_message) << std::endl;
}
}  // namespace

std::shared_ptr<VW980::LEARNER::learner> VW980::reductions::print_setup(VW980::setup_base_i& stack_builder)
{
  VW980::config::options_i& options = *stack_builder.get_options();
  VW980::workspace& all = *stack_builder.get_all_pointer();
  bool print_option = false;
  option_group_definition new_options("[Reduction] Print Psuedolearner");
  new_options.add(make_option("print", print_option).keep().necessary().help("Print examples"));

  if (!options.add_parse_and_check_necessary(new_options)) { return nullptr; }

  all.weights.stride_shift(0);
  auto learner = VW980::LEARNER::make_bottom_learner(VW980::make_unique<print>(&all), learn, learn,
      stack_builder.get_setupfn_name(print_setup), VW980::prediction_type_t::SCALAR, VW980::label_type_t::SIMPLE)
                     .set_output_example_prediction(VW980::details::output_example_prediction_simple_label<print>)
                     .set_update_stats(VW980::details::update_stats_simple_label<print>)
                     .set_print_update(VW980::details::print_update_simple_label<print>)
                     .build();
  return learner;
}
