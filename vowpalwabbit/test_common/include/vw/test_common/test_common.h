// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/config/options.h"
#include "vw/config/options_cli.h"
#include "vw/core/vw.h"
#include "vw/json_parser/parse_example_json.h"

#include <vector>

namespace vwtest
{

constexpr float EXPLICIT_FLOAT_TOL = 0.0001f;

/// Helper to convert a list of strings into a unique_ptr<options_cli>
/// \code
/// auto args = make_args("--quiet", "--chain_hash", "--cb_explore_adf");
/// \endcode
template <typename... ArgsT>
std::unique_ptr<VW980::config::options_i> make_args(ArgsT const&... args)
{
  return std::unique_ptr<VW980::config::options_cli>(new VW980::config::options_cli(std::vector<std::string>({args...})));
}

VW980::multi_ex parse_json(VW980::workspace& all, const std::string& line);

VW980::multi_ex parse_dsjson(
    VW980::workspace& all, std::string line, VW980::parsers::json::decision_service_interaction* interaction = nullptr);
}  // namespace vwtest
