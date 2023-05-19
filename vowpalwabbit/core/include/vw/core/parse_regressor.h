// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once
#include "vw/config/options.h"
#include "vw/core/vw_fwd.h"

#include <string>

namespace VW980
{
namespace details
{
void read_regressor_file(VW980::workspace& all, const std::vector<std::string>& files, VW980::io_buf& io_temp);

void finalize_regressor(VW980::workspace& all, const std::string& reg_name);
void initialize_regressor(VW980::workspace& all);

void save_predictor(VW980::workspace& all, const std::string& reg_name, size_t current_pass);
void save_load_header(VW980::workspace& all, VW980::io_buf& model_file, bool read, bool text, std::string& file_options,
    VW980::config::options_i& options);

void parse_mask_regressor_args(
    VW980::workspace& all, const std::string& feature_mask, std::vector<std::string> initial_regressors);

void dump_regressor(VW980::workspace& all, io_buf& buf, bool as_text);
void dump_regressor(VW980::workspace& all, const std::string& reg_name, bool as_text);
}  // namespace details
}  // namespace VW980
