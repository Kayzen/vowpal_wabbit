#pragma once

#include "vw/core/setup_base.h"
#include "vw/core/vw_fwd.h"

#include <memory>
#include <string>

namespace VW980
{
class cached_learner : public setup_base_i
{
public:
  std::shared_ptr<VW980::LEARNER::learner> setup_base_learner(size_t) override { return _cached; }

  operator bool() const { return !(_cached == nullptr); }

  void delayed_state_attach(VW980::workspace& all, VW980::config::options_i& options) override
  {
    _options_impl = &options;
    _all_ptr = &all;
  }

  cached_learner() : _cached(nullptr) {}

  cached_learner(std::shared_ptr<VW980::LEARNER::learner> learner) : _cached(std::move(learner)) {}

  cached_learner(VW980::workspace& all, VW980::config::options_i& options, std::shared_ptr<VW980::LEARNER::learner> learner)
      : _cached(std::move(learner))
  {
    delayed_state_attach(all, options);
  }

  VW980::config::options_i* get_options() override { return _options_impl; }

  VW980::workspace* get_all_pointer() override { return _all_ptr; }

  std::string get_setupfn_name(reduction_setup_fn) override { return ""; }

  size_t get_feature_width_above() override { return 1; }

private:
  std::shared_ptr<VW980::LEARNER::learner> _cached;
  VW980::config::options_i* _options_impl = nullptr;
  VW980::workspace* _all_ptr = nullptr;
};
}  // namespace VW980
