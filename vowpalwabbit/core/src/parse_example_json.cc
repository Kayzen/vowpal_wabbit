// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "vw/core/parse_example_json.h"

// Explicitly instantiate templates only in this source file
template void VW980::read_line_json_s<true>(const VW980::label_parser& lbl_parser, hash_func_t hash_func, uint64_t hash_seed,
    uint64_t parse_mask, bool chain_hash, VW980::label_parser_reuse_mem* reuse_mem, const VW980::named_labels* ldict,
    VW980::multi_ex& examples, char* line, size_t length, example_factory_t example_factory, VW980::io::logger& logger,
    std::unordered_map<std::string, std::set<std::string>>* ignore_features,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
template void VW980::read_line_json_s<false>(const VW980::label_parser& lbl_parser, hash_func_t hash_func, uint64_t hash_seed,
    uint64_t parse_mask, bool chain_hash, VW980::label_parser_reuse_mem* reuse_mem, const VW980::named_labels* ldict,
    VW980::multi_ex& examples, char* line, size_t length, example_factory_t example_factory, VW980::io::logger& logger,
    std::unordered_map<std::string, std::set<std::string>>* ignore_features,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

template void VW980::read_line_json_s<true>(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
template void VW980::read_line_json_s<false>(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

template bool VW980::read_line_decision_service_json<true>(VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, bool copy_line, example_factory_t example_factory,
    VW980::parsers::json::decision_service_interaction* data);
template bool VW980::read_line_decision_service_json<false>(VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, bool copy_line, example_factory_t example_factory,
    VW980::parsers::json::decision_service_interaction* data);

template bool parse_line_json<true>(VW980::workspace* all, char* line, size_t num_chars, VW980::multi_ex& examples);
template bool parse_line_json<false>(VW980::workspace* all, char* line, size_t num_chars, VW980::multi_ex& examples);

template void line_to_examples_json<true>(VW980::workspace* all, VW980::string_view sv, VW980::multi_ex& examples);
template void line_to_examples_json<false>(VW980::workspace* all, VW980::string_view sv, VW980::multi_ex& examples);

template int read_features_json<true>(VW980::workspace* all, VW980::io_buf& buf, VW980::multi_ex& examples);
template int read_features_json<false>(VW980::workspace* all, VW980::io_buf& buf, VW980::multi_ex& examples);
