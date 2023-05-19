#pragma once

#include "vw_slim_predict.h"

namespace vw_slim
{
class example_predict_builder
{
public:
  example_predict_builder(VW980::example_predict* ex, const char* namespace_name, uint32_t feature_index_num_bits = 18);
  example_predict_builder(
      VW980::example_predict* ex, VW980::namespace_index namespace_idx, uint32_t feature_index_num_bits = 18);

  void push_feature_string(const char* feature_idx, VW980::feature_value value);
  void push_feature(VW980::feature_index feature_idx, VW980::feature_value value);

private:
  VW980::example_predict* _ex;
  VW980::namespace_index _namespace_idx;
  uint64_t _namespace_hash;
  uint64_t _feature_index_bit_mask;

  void add_namespace(VW980::namespace_index feature_group);
};
}  // namespace vw_slim
