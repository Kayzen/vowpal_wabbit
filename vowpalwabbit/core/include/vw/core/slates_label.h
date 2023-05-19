// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/core/action_score.h"
#include "vw/core/label_parser.h"
#include "vw/core/vw_fwd.h"

#include <fmt/format.h>

#include <cstdint>

namespace VW980
{
namespace slates
{
enum class example_type : uint8_t
{
  UNSET = 0,
  SHARED = 1,
  ACTION = 2,
  SLOT = 3
};

class label
{
public:
  // General data
  example_type type;
  float weight;
  // Because these labels provide both structural information as well as a
  // label, this field will only be true is there is a label attached (label in
  // the sense of cost)
  bool labeled;

  // For shared examples
  // Only valid if labeled
  float cost;

  // For action examples
  uint32_t slot_id;

  // For slot examples
  // Only valid if labeled
  VW980::action_scores probabilities;

  label() { reset_to_default(); }

  void reset_to_default()
  {
    type = example_type::UNSET;
    weight = 1.f;
    labeled = false;
    cost = 0.f;
    slot_id = 0;
    probabilities.clear();
  }
};

void default_label(VW980::slates::label& v);
void parse_label(slates::label& ld, VW980::label_parser_reuse_mem& reuse_mem, const std::vector<VW980::string_view>& words,
    VW980::io::logger& logger);

extern VW980::label_parser slates_label_parser;
}  // namespace slates

VW980::string_view to_string(VW980::slates::example_type);

namespace model_utils
{
size_t read_model_field(io_buf&, VW980::slates::label&);
size_t write_model_field(io_buf&, const VW980::slates::label&, const std::string&, bool);
}  // namespace model_utils
}  // namespace VW980

namespace fmt
{
template <>
class formatter<VW980::slates::example_type> : public formatter<std::string>
{
public:
  auto format(VW980::slates::example_type c, format_context& ctx) -> decltype(ctx.out())
  {
    return formatter<std::string>::format(std::string{VW980::to_string(c)}, ctx);
  }
};
}  // namespace fmt