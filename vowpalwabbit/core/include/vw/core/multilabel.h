// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once

#include "vw/core/label_parser.h"
#include "vw/core/multi_ex.h"
#include "vw/core/multiclass.h"
#include "vw/core/v_array.h"
#include "vw/core/vw_fwd.h"

namespace VW980
{
class multilabel_label
{
public:
  VW980::v_array<uint32_t> label_v;

  void reset_to_default();
  bool is_test() const;
};

class multilabel_prediction
{
public:
  VW980::v_array<uint32_t> label_v;
};

extern VW980::label_parser multilabel_label_parser_global;
std::string to_string(const VW980::multilabel_label& multilabels);
std::string to_string(const VW980::multilabel_prediction& multilabels);

namespace model_utils
{
size_t read_model_field(io_buf&, VW980::multilabel_label&);
size_t write_model_field(io_buf&, const VW980::multilabel_label&, const std::string&, bool);
}  // namespace model_utils

namespace details
{
void update_stats_multilabel(const VW980::workspace& all, const VW980::example& ec);
void output_example_prediction_multilabel(VW980::workspace& all, const VW980::example& ec);
void print_update_multilabel(VW980::workspace& all, const VW980::example& ec);
}  // namespace details

}  // namespace VW980

namespace MULTILABEL  // NOLINT
{
using labels VW_DEPRECATED("Renamed to VW980::multilabel_labels") = VW980::multilabel_label;
}