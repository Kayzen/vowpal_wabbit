// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once
#include "vw/core/cb.h"
#include "vw/core/gen_cs_example.h"
#include "vw/core/vw_fwd.h"
#include "vw/core/vw_versions.h"

#include <memory>
#include <vector>

namespace VW980
{
VW980::example* test_cb_adf_sequence(const VW980::multi_ex& ec_seq);
VW980::cb_class get_observed_cost_or_default_cb_adf(const VW980::multi_ex& examples);
namespace reductions
{
std::shared_ptr<VW980::LEARNER::learner> cb_adf_setup(VW980::setup_base_i& stack_builder);

class cb_adf
{
public:
  void learn(VW980::LEARNER::learner& base, VW980::multi_ex& ec_seq);
  void predict(VW980::LEARNER::learner& base, VW980::multi_ex& ec_seq);
  bool update_statistics(const VW980::example& ec, const VW980::multi_ex& ec_seq, VW980::shared_data& sd) const;

  cb_adf(VW980::cb_type_t cb_type, bool rank_all, float clip_p, bool no_predict, size_t feature_width_above,
      VW980::workspace* all)
      : _no_predict(no_predict), _rank_all(rank_all), _clip_p(clip_p), _gen_cs(feature_width_above), _all(all)
  {
    _gen_cs.cb_type = cb_type;
  }

  void set_scorer(VW980::LEARNER::learner* scorer) { _gen_cs.scorer = scorer; }

  bool get_rank_all() const { return _rank_all; }

  const VW980::details::cb_to_cs_adf& get_gen_cs() const { return _gen_cs; }
  VW980::details::cb_to_cs_adf& get_gen_cs() { return _gen_cs; }

  const VW980::version_struct* get_model_file_ver() const;

  bool learn_returns_prediction() const
  {
    return ((_gen_cs.cb_type == VW980::cb_type_t::MTR) && !_no_predict) || _gen_cs.cb_type == VW980::cb_type_t::IPS ||
        _gen_cs.cb_type == VW980::cb_type_t::DR || _gen_cs.cb_type == VW980::cb_type_t::DM ||
        _gen_cs.cb_type == VW980::cb_type_t::SM;
  }

  VW980::cb_class* known_cost() { return &_gen_cs.known_cost; }
  const VW980::cb_class* known_cost() const { return &_gen_cs.known_cost; }

private:
  void learn_ips(VW980::LEARNER::learner& base, VW980::multi_ex& examples);
  void learn_dr(VW980::LEARNER::learner& base, VW980::multi_ex& examples);
  void learn_dm(VW980::LEARNER::learner& base, VW980::multi_ex& examples);
  void learn_sm(VW980::LEARNER::learner& base, VW980::multi_ex& examples);
  template <bool predict>
  void learn_mtr(VW980::LEARNER::learner& base, VW980::multi_ex& examples);

  std::vector<VW980::cb_label> _cb_labels;
  VW980::cs_label _cs_labels;
  std::vector<VW980::cs_label> _prepped_cs_labels;

  VW980::action_scores _a_s;              // temporary storage for mtr and sm
  VW980::action_scores _a_s_mtr_cs;       // temporary storage for mtr cost sensitive example
  VW980::action_scores _prob_s;           // temporary storage for sm; stores softmax values
  VW980::v_array<uint32_t> _backup_nf;    // temporary storage for sm; backup for numFeatures in examples
  VW980::v_array<float> _backup_weights;  // temporary storage for sm; backup for weights in examples

  uint64_t _offset = 0;
  uint64_t _offset_index = 0;
  const bool _no_predict;
  const bool _rank_all;
  const float _clip_p;
  VW980::details::cb_to_cs_adf _gen_cs;

  VW980::workspace* _all = nullptr;
};
}  // namespace reductions
}  // namespace VW980

namespace CB_ADF  // NOLINT
{
VW_DEPRECATED("Moved into VW namespace.") inline VW980::example* test_adf_sequence(const VW980::multi_ex& ec_seq)
{
  return VW980::test_cb_adf_sequence(ec_seq);
}
VW_DEPRECATED("Moved into VW namespace.")
inline VW980::cb_class get_observed_cost_or_default_cb_adf(const VW980::multi_ex& examples)
{
  return VW980::get_observed_cost_or_default_cb_adf(examples);
}
using cb_adf VW_DEPRECATED("Moved into VW namespace.") = VW980::reductions::cb_adf;
}  // namespace CB_ADF
