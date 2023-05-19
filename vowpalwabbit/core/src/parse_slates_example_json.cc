#include "vw/core/parse_slates_example_json.h"

#include "vw/common/future_compat.h"

// Explicitly instantiate templates only in this source file
template void parse_slates_example_json<true>(const VW980::label_parser& lbl_parser, VW980::hash_func_t hash_func,
    uint64_t hash_seed, uint64_t parse_mask, bool chain_hash, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
template void parse_slates_example_json<false>(const VW980::label_parser& lbl_parser, VW980::hash_func_t hash_func,
    uint64_t hash_seed, uint64_t parse_mask, bool chain_hash, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

template void parse_slates_example_json<true>(const VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, VW980::example_factory_t example_factory,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
template void parse_slates_example_json<false>(const VW980::workspace& all, VW980::multi_ex& examples, char* line,
    size_t length, VW980::example_factory_t example_factory,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);

template void parse_slates_example_dsjson<true>(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, VW980::parsers::json::decision_service_interaction* data,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);
template void parse_slates_example_dsjson<false>(VW980::workspace& all, VW980::multi_ex& examples, char* line, size_t length,
    VW980::example_factory_t example_factory, VW980::parsers::json::decision_service_interaction* data,
    const std::unordered_map<uint64_t, VW980::example*>* dedup_examples);