// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/common/future_compat.h"
#include "vw/json_parser/parse_example_json.h"

namespace VW980
{
template <bool audit>
VW_DEPRECATED("read_line_json_s moved to VW980::parsers::json::read_line_json")
void read_line_json_s(const VW980::label_parser& lbl_parser, hash_func_t hash_func, uint64_t hash_seed,
    uint64_t parse_mask, bool chain_hash, VW980::label_parser_reuse_mem* reuse_mem, const VW980::named_labels* ldict,
    VW980::multi_ex& examples, char* line, size_t length, example_factory_t example_factory, VW980::io::logger& logger,
    std::unordered_map<std::string, std::set<std::string>>* ignore_features,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples = nullptr)
{
  VW980::parsers::json::read_line_json<audit>(lbl_parser, hash_func, hash_seed, parse_mask, chain_hash, reuse_mem, ldict,
      examples, line, length, std::move(example_factory), logger, ignore_features, dedup_examples);
}

template <bool audit>
VW_DEPRECATED("read_line_json_s moved to VW980::parsers::json::read_line_json")
void read_line_json_s(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples = nullptr)
{
  VW980::parsers::json::read_line_json<audit>(all, examples, line, length, std::move(example_factory), dedup_examples);
}

// returns true if succesfully parsed, returns false if not and logs warning
template <bool audit>
VW_DEPRECATED("read_line_decision_service_json moved to VW980::parsers::json::read_line_decision_service_json")
bool read_line_decision_service_json(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    bool copy_line, example_factory_t example_factory, VW980::parsers::json::decision_service_interaction* data)
{
  return VW980::parsers::json::read_line_decision_service_json<audit>(
      all, examples, line, length, copy_line, std::move(example_factory), data);
}
}  // namespace VW980

template <bool audit>
VW_DEPRECATED("parse_line_json moved to VW980::parsers::json::details::parse_line_json")
bool parse_line_json(VW980::workspace* all, char* line, size_t num_chars, VW980::multi_ex& examples)
{
  return VW980::parsers::json::details::parse_line_json<audit>(all, line, num_chars, examples);
}

// This is used by the python parser
template <bool audit>
VW_DEPRECATED("line_to_examples_json moved to VW980::parsers::json::line_to_examples_json")
void line_to_examples_json(VW980::workspace* all, VW980::string_view sv, VW980::multi_ex& examples)
{
  VW980::parsers::json::line_to_examples_json<audit>(all, sv, examples);
}

template <bool audit>
VW_DEPRECATED("read_features_json moved to VW980::parsers::json::read_features_json")
int read_features_json(VW980::workspace* all, VW980::io_buf& buf, VW980::multi_ex& examples)
{
  return VW980::parsers::json::read_features_json<audit>(all, buf, examples);
}

// Define extern template specializations so they don't get initialized when this file is included
extern template void VW980::read_line_json_s<true>(const VW980::label_parser& lbl_parser, hash_func_t hash_func,
    uint64_t hash_seed, uint64_t parse_mask, bool chain_hash, VW980::label_parser_reuse_mem* reuse_mem,
    const VW980::named_labels* ldict, VW980::multi_ex& examples, char* line, size_t length, example_factory_t example_factory,
    VW980::io::logger& logger, std::unordered_map<std::string, std::set<std::string>>* ignore_features,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
extern template void VW980::read_line_json_s<false>(const VW980::label_parser& lbl_parser, hash_func_t hash_func,
    uint64_t hash_seed, uint64_t parse_mask, bool chain_hash, VW980::label_parser_reuse_mem* reuse_mem,
    const VW980::named_labels* ldict, VW980::multi_ex& examples, char* line, size_t length, example_factory_t example_factory,
    VW980::io::logger& logger, std::unordered_map<std::string, std::set<std::string>>* ignore_features,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

extern template void VW980::read_line_json_s<true>(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
extern template void VW980::read_line_json_s<false>(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

extern template bool VW980::read_line_decision_service_json<true>(VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, bool copy_line, example_factory_t example_factory,
    VW980::parsers::json::decision_service_interaction* data);
extern template bool VW980::read_line_decision_service_json<false>(VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, bool copy_line, example_factory_t example_factory,
    VW980::parsers::json::decision_service_interaction* data);

extern template bool parse_line_json<true>(VW980::workspace* all, char* line, size_t num_chars, VW980::multi_ex& examples);
extern template bool parse_line_json<false>(VW980::workspace* all, char* line, size_t num_chars, VW980::multi_ex& examples);

extern template void line_to_examples_json<true>(VW980::workspace* all, VW980::string_view, VW980::multi_ex& examples);
extern template void line_to_examples_json<false>(VW980::workspace* all, VW980::string_view, VW980::multi_ex& examples);

extern template int read_features_json<true>(VW980::workspace* all, VW980::io_buf& buf, VW980::multi_ex& examples);
extern template int read_features_json<false>(VW980::workspace* all, VW980::io_buf& buf, VW980::multi_ex& examples);
