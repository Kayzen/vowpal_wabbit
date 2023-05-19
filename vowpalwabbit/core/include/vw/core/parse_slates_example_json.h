#pragma once

#include "vw/common/future_compat.h"
#include "vw/json_parser/parse_example_slates_json.h"

template <bool audit>
VW_DEPRECATED("parse_slates_example_json moved to VW980::parsers::json::details::parse_slates_example_json")
void parse_slates_example_json(const VW980::label_parser& lbl_parser, VW980::hash_func_t hash_func, uint64_t hash_seed,
    uint64_t parse_mask, bool chain_hash, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples = nullptr)
{
  VW980::parsers::json::details::parse_slates_example_json<audit>(lbl_parser, hash_func, hash_seed, parse_mask, chain_hash,
      examples, line, length, std::move(example_factory), dedup_examples);
}

template <bool audit>
VW_DEPRECATED("parse_slates_example_json moved to VW980::parsers::json::details::parse_slates_example_json")
void parse_slates_example_json(const VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples = nullptr)
{
  VW980::parsers::json::details::parse_slates_example_json<audit>(
      all, examples, line, length, std::move(example_factory), dedup_examples);
}

template <bool audit>
VW_DEPRECATED("parse_slates_example_dsjson moved to VW980::parsers::json::details::parse_slates_example_dsjson")
void parse_slates_example_dsjson(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, VW980::parsers::json::decision_service_interaction* data,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples = nullptr)
{
  VW980::parsers::json::details::parse_slates_example_dsjson<audit>(
      all, examples, line, length, std::move(example_factory), data, dedup_examples);
}

// Define extern template specializations so they don't get initialized when this file is included
extern template void parse_slates_example_json<true>(const VW980::label_parser& lbl_parser, VW980::hash_func_t hash_func,
    uint64_t hash_seed, uint64_t parse_mask, bool chain_hash, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
extern template void parse_slates_example_json<false>(const VW980::label_parser& lbl_parser, VW980::hash_func_t hash_func,
    uint64_t hash_seed, uint64_t parse_mask, bool chain_hash, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

extern template void parse_slates_example_json<true>(const VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, VW980::example_factory_t example_factory,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
extern template void parse_slates_example_json<false>(const VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, VW980::example_factory_t example_factory,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

extern template void parse_slates_example_dsjson<true>(VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, VW980::example_factory_t example_factory, VW980::parsers::json::decision_service_interaction* data,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
extern template void parse_slates_example_dsjson<false>(VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, VW980::example_factory_t example_factory, VW980::parsers::json::decision_service_interaction* data,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
