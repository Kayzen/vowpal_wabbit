#include "vw/core/reduction_stack.h"

#include "vw/config/options.h"
#include "vw/config/options_name_extractor.h"
#include "vw/core/cached_learner.h"
#include "vw/core/global_data.h"  // to get vw struct
#include "vw/core/learner.h"
#include "vw/core/simple_label_parser.h"
#include "vw/core/vw_fwd.h"

// reductions / setup functions
#include "vw/core/reductions/active.h"
#include "vw/core/reductions/active_cover.h"
#include "vw/core/reductions/audit_regressor.h"
#include "vw/core/reductions/autolink.h"
#include "vw/core/reductions/automl.h"
#include "vw/core/reductions/baseline.h"
#include "vw/core/reductions/baseline_challenger_cb.h"
#include "vw/core/reductions/bfgs.h"
#include "vw/core/reductions/binary.h"
#include "vw/core/reductions/boosting.h"
#include "vw/core/reductions/bs.h"
#include "vw/core/reductions/cats.h"
#include "vw/core/reductions/cats_pdf.h"
#include "vw/core/reductions/cats_tree.h"
#include "vw/core/reductions/cb/cb_actions_mask.h"
#include "vw/core/reductions/cb/cb_adf.h"
#include "vw/core/reductions/cb/cb_algs.h"
#include "vw/core/reductions/cb/cb_dro.h"
#include "vw/core/reductions/cb/cb_explore.h"
#include "vw/core/reductions/cb/cb_explore_adf_bag.h"
#include "vw/core/reductions/cb/cb_explore_adf_cover.h"
#include "vw/core/reductions/cb/cb_explore_adf_first.h"
#include "vw/core/reductions/cb/cb_explore_adf_greedy.h"
#include "vw/core/reductions/cb/cb_explore_adf_large_action_space.h"
#include "vw/core/reductions/cb/cb_explore_adf_regcb.h"
#include "vw/core/reductions/cb/cb_explore_adf_rnd.h"
#include "vw/core/reductions/cb/cb_explore_adf_softmax.h"
#include "vw/core/reductions/cb/cb_explore_adf_squarecb.h"
#include "vw/core/reductions/cb/cb_explore_adf_synthcover.h"
#include "vw/core/reductions/cb/cb_explore_pdf.h"
#include "vw/core/reductions/cb/cb_sample.h"
#include "vw/core/reductions/cb/cb_to_cb_adf.h"
#include "vw/core/reductions/cb/cbify.h"
#include "vw/core/reductions/cb/warm_cb.h"
#include "vw/core/reductions/cbzo.h"
#include "vw/core/reductions/classweight.h"
#include "vw/core/reductions/conditional_contextual_bandit.h"
#include "vw/core/reductions/confidence.h"
#include "vw/core/reductions/count_label.h"
#include "vw/core/reductions/cs_active.h"
#include "vw/core/reductions/csoaa.h"
#include "vw/core/reductions/csoaa_ldf.h"
#include "vw/core/reductions/ect.h"
#include "vw/core/reductions/eigen_memory_tree.h"
#include "vw/core/reductions/epsilon_decay.h"
#include "vw/core/reductions/explore_eval.h"
#include "vw/core/reductions/expreplay.h"
#include "vw/core/reductions/freegrad.h"
#include "vw/core/reductions/ftrl.h"
#include "vw/core/reductions/gd.h"
#include "vw/core/reductions/gd_mf.h"
#include "vw/core/reductions/generate_interactions.h"
#include "vw/core/reductions/get_pmf.h"
#include "vw/core/reductions/interact.h"
#include "vw/core/reductions/interaction_ground.h"
#include "vw/core/reductions/kernel_svm.h"
#include "vw/core/reductions/lda_core.h"
#include "vw/core/reductions/log_multi.h"
#include "vw/core/reductions/lrq.h"
#include "vw/core/reductions/lrqfa.h"
#include "vw/core/reductions/marginal.h"
#include "vw/core/reductions/memory_tree.h"
#include "vw/core/reductions/metrics.h"
#include "vw/core/reductions/mf.h"
#include "vw/core/reductions/multilabel_oaa.h"
#include "vw/core/reductions/mwt.h"
#include "vw/core/reductions/nn.h"
#include "vw/core/reductions/noop.h"
#include "vw/core/reductions/oaa.h"
#include "vw/core/reductions/offset_tree.h"
#include "vw/core/reductions/oja_newton.h"
#include "vw/core/reductions/plt.h"
#include "vw/core/reductions/pmf_to_pdf.h"
#include "vw/core/reductions/print.h"
#include "vw/core/reductions/recall_tree.h"
#include "vw/core/reductions/sample_pdf.h"
#include "vw/core/reductions/scorer.h"
#include "vw/core/reductions/search/search.h"
#include "vw/core/reductions/sender.h"
#include "vw/core/reductions/shared_feature_merger.h"
#include "vw/core/reductions/slates.h"
#include "vw/core/reductions/stagewise_poly.h"
#include "vw/core/reductions/svrg.h"
#include "vw/core/reductions/topk.h"

#include <unordered_map>

void register_reductions(std::vector<VW980::reduction_setup_fn>& reductions,
    std::vector<std::tuple<std::string, VW980::reduction_setup_fn>>& reduction_stack)
{
  std::unordered_map<VW980::reduction_setup_fn, std::string> allowlist = {{VW980::reductions::gd_setup, "gd"},
      {VW980::reductions::ftrl_setup, "ftrl"}, {VW980::reductions::sender_setup, "sender"}, {VW980::reductions::nn_setup, "nn"},
      {VW980::reductions::oaa_setup, "oaa"}, {VW980::reductions::scorer_setup, "scorer"},
      {VW980::reductions::csldf_setup, "csoaa_ldf"},
      {VW980::reductions::cb_explore_adf_greedy_setup, "cb_explore_adf_greedy"},
      {VW980::reductions::cb_explore_adf_regcb_setup, "cb_explore_adf_regcb"},
      {VW980::reductions::shared_feature_merger_setup, "shared_feature_merger"},
      {VW980::reductions::generate_interactions_setup, "generate_interactions"},
      {VW980::reductions::count_label_setup, "count_label"}, {VW980::reductions::cb_to_cb_adf_setup, "cb_to_cbadf"},
      {VW980::reductions::cb_actions_mask_setup, "cb_actions_mask"}};

  auto name_extractor = VW980::config::options_name_extractor();
  VW980::workspace dummy_all(VW980::io::create_null_logger());

  VW980::cached_learner null_ptr_learner(dummy_all, name_extractor, nullptr);

  for (auto setup_fn : reductions)
  {
    if (allowlist.count(setup_fn)) { reduction_stack.push_back(std::make_tuple(allowlist[setup_fn], setup_fn)); }
    else
    {
      auto base = setup_fn(null_ptr_learner);

      if (!base) { reduction_stack.push_back(std::make_tuple(name_extractor.generated_name, setup_fn)); }
      else
        THROW("fatal: under register_reduction() all setup functions must return nullptr");
    }
  }
}

void prepare_reductions(std::vector<std::tuple<std::string, VW980::reduction_setup_fn>>& reduction_stack)
{
  std::vector<VW980::reduction_setup_fn> reductions;

  // Base algorithms
  reductions.push_back(VW980::reductions::gd_setup);
  reductions.push_back(VW980::reductions::kernel_svm_setup);
  reductions.push_back(VW980::reductions::ftrl_setup);
  reductions.push_back(VW980::reductions::freegrad_setup);
  reductions.push_back(VW980::reductions::svrg_setup);
  reductions.push_back(VW980::reductions::sender_setup);
  reductions.push_back(VW980::reductions::gd_mf_setup);
  reductions.push_back(VW980::reductions::print_setup);
  reductions.push_back(VW980::reductions::noop_setup);
  reductions.push_back(VW980::reductions::bfgs_setup);
  reductions.push_back(VW980::reductions::oja_newton_setup);

  reductions.push_back(VW980::reductions::mf_setup);

  reductions.push_back(VW980::reductions::generate_interactions_setup);

  // Score Users
  reductions.push_back(VW980::reductions::baseline_setup);
  reductions.push_back(VW980::reductions::expreplay_setup<'b', VW980::simple_label_parser_global>);
  reductions.push_back(VW980::reductions::active_setup);
  reductions.push_back(VW980::reductions::active_cover_setup);
  reductions.push_back(VW980::reductions::confidence_setup);
  reductions.push_back(VW980::reductions::nn_setup);
  reductions.push_back(VW980::reductions::marginal_setup);
  reductions.push_back(VW980::reductions::autolink_setup);
  reductions.push_back(VW980::reductions::lrq_setup);
  reductions.push_back(VW980::reductions::lrqfa_setup);
  reductions.push_back(VW980::reductions::stagewise_poly_setup);
  reductions.push_back(VW980::reductions::scorer_setup);
  reductions.push_back(VW980::reductions::lda_setup);
  reductions.push_back(VW980::reductions::cbzo_setup);

  // Reductions
  reductions.push_back(VW980::reductions::bs_setup);
  reductions.push_back(VW980::reductions::binary_setup);

  reductions.push_back(VW980::reductions::expreplay_setup<'m', VW980::multiclass_label_parser_global>);
  reductions.push_back(VW980::reductions::topk_setup);
  reductions.push_back(VW980::reductions::oaa_setup);
  reductions.push_back(VW980::reductions::boosting_setup);
  reductions.push_back(VW980::reductions::ect_setup);
  reductions.push_back(VW980::reductions::log_multi_setup);
  reductions.push_back(VW980::reductions::recall_tree_setup);
  reductions.push_back(VW980::reductions::eigen_memory_tree_setup);
  reductions.push_back(VW980::reductions::memory_tree_setup);
  reductions.push_back(VW980::reductions::classweight_setup);
  reductions.push_back(VW980::reductions::multilabel_oaa_setup);
  reductions.push_back(VW980::reductions::plt_setup);

  reductions.push_back(VW980::reductions::cs_active_setup);
  reductions.push_back(VW980::reductions::csoaa_setup);
  reductions.push_back(VW980::reductions::interact_setup);
  reductions.push_back(VW980::reductions::csldf_setup);
  reductions.push_back(VW980::reductions::cb_algs_setup);
  reductions.push_back(VW980::reductions::cb_adf_setup);
  reductions.push_back(VW980::reductions::interaction_ground_setup);
  reductions.push_back(VW980::reductions::mwt_setup);
  reductions.push_back(VW980::reductions::cats_tree_setup);
  reductions.push_back(VW980::reductions::baseline_challenger_cb_setup);
  reductions.push_back(VW980::reductions::automl_setup);
  reductions.push_back(VW980::reductions::cb_explore_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_large_action_space_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_greedy_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_softmax_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_rnd_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_regcb_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_squarecb_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_synthcover_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_first_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_cover_setup);
  reductions.push_back(VW980::reductions::cb_explore_adf_bag_setup);
  reductions.push_back(VW980::reductions::cb_dro_setup);
  reductions.push_back(VW980::reductions::cb_sample_setup);
  reductions.push_back(VW980::reductions::epsilon_decay_setup);
  reductions.push_back(VW980::reductions::explore_eval_setup);
  reductions.push_back(VW980::reductions::cb_actions_mask_setup);
  reductions.push_back(VW980::reductions::shared_feature_merger_setup);
  reductions.push_back(VW980::reductions::ccb_explore_adf_setup);
  reductions.push_back(VW980::reductions::slates_setup);
  // cbify/warm_cb can generate multi-examples. Merge shared features after them
  reductions.push_back(VW980::reductions::warm_cb_setup);
  reductions.push_back(VW980::reductions::get_pmf_setup);
  reductions.push_back(VW980::reductions::pmf_to_pdf_setup);
  reductions.push_back(VW980::reductions::cb_explore_pdf_setup);
  reductions.push_back(VW980::reductions::cats_pdf_setup);
  reductions.push_back(VW980::reductions::sample_pdf_setup);
  reductions.push_back(VW980::reductions::cats_setup);
  reductions.push_back(VW980::reductions::cbify_setup);
  reductions.push_back(VW980::reductions::cbifyldf_setup);
  reductions.push_back(VW980::reductions::cb_to_cb_adf_setup);
  reductions.push_back(VW980::reductions::offset_tree_setup);
  reductions.push_back(VW980::reductions::expreplay_setup<'c', VW980::cs_label_parser_global>);
  reductions.push_back(VW980::reductions::search_setup);
  reductions.push_back(VW980::reductions::audit_regressor_setup);
  reductions.push_back(VW980::reductions::metrics_setup);
  reductions.push_back(VW980::reductions::count_label_setup);

  register_reductions(reductions, reduction_stack);
}

namespace VW980
{
default_reduction_stack_setup::default_reduction_stack_setup(VW980::workspace& all, VW980::config::options_i& options)
{
  // push all reduction functions into the stack
  prepare_reductions(_reduction_stack);
  delayed_state_attach(all, options);
}

default_reduction_stack_setup::default_reduction_stack_setup() { prepare_reductions(_reduction_stack); }

// this should be reworked, but its setup related to how setup is tied with all object
// which is not applicable to everything
void default_reduction_stack_setup::delayed_state_attach(VW980::workspace& all, VW980::config::options_i& options)
{
  _all_ptr = &all;
  _options_impl = &options;
  // populate setup_fn -> name map to be used to lookup names in setup_base

  for (auto&& setup_tuple : _reduction_stack) { _setup_name_map[std::get<1>(setup_tuple)] = std::get<0>(setup_tuple); }
}

std::string default_reduction_stack_setup::get_setupfn_name(reduction_setup_fn setup_fn)
{
  const auto loc = _setup_name_map.find(setup_fn);
  if (loc != _setup_name_map.end()) { return loc->second; }
  return "NA";
}

// this function consumes all the _reduction_stack until it's able to construct a learner
// same signature/code as the old setup_base(...) from parse_args.cc
std::shared_ptr<VW980::LEARNER::learner> default_reduction_stack_setup::setup_base_learner(size_t feature_width)
{
  if (!_reduction_stack.empty())
  {
    auto func_map = _reduction_stack.back();
    reduction_setup_fn setup_func = std::get<1>(func_map);
    std::string setup_func_name = std::get<0>(func_map);
    _reduction_stack.pop_back();

    _feature_width_above *= feature_width;
    // 'hacky' way of keeping track of the option group created by the setup_func about to be created
    _options_impl->tint(setup_func_name);
    std::shared_ptr<VW980::LEARNER::learner> result = setup_func(*this);
    _options_impl->reset_tint();

    // returning nullptr means that setup_func (any reduction) was not 'enabled' but
    // only added their respective command args and did not add itself into the
    // chain of learners, therefore we call into setup_base again
    if (result == nullptr) { return this->setup_base_learner(); }
    else
    {
      if (result->get_base_learner() == nullptr)
      {
        result->feature_width = get_all_pointer()->weights.stride();
        result->feature_width_below = result->feature_width;
      }
      _reduction_stack.clear();
      return result;
    }
  }

  return nullptr;
}

}  // namespace VW980
