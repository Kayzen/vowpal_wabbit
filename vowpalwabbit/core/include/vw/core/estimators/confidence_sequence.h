// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/core/vw_fwd.h"

#include <cstdint>
#include <string>
#include <vector>

namespace VW980
{
namespace details
{
constexpr float CS_DEFAULT_ALPHA = 0.05f;
class incremental_f_sum
{
public:
  std::vector<double> partials;
  incremental_f_sum operator+=(double x);
  incremental_f_sum operator+(incremental_f_sum const& other) const;
  operator double() const;
};
}  // namespace details

namespace estimators
{
class confidence_sequence
{
public:
  double alpha;
  double rmin_init;
  double rmax_init;
  bool adjust;

  double rmin;
  double rmax;
  double eta;
  double s;
  int t;

  VW980::details::incremental_f_sum sumwsqrsq;
  VW980::details::incremental_f_sum sumwsqr;
  VW980::details::incremental_f_sum sumwsq;
  VW980::details::incremental_f_sum sumwr;
  VW980::details::incremental_f_sum sumw;
  VW980::details::incremental_f_sum sumwrxhatlow;
  VW980::details::incremental_f_sum sumwxhatlow;
  VW980::details::incremental_f_sum sumxhatlowsq;
  VW980::details::incremental_f_sum sumwrxhathigh;
  VW980::details::incremental_f_sum sumwxhathigh;
  VW980::details::incremental_f_sum sumxhathighsq;

  uint64_t update_count;
  double last_w;
  double last_r;

  confidence_sequence(
      double alpha = VW980::details::CS_DEFAULT_ALPHA, double rmin_init = 0.0, double rmax_init = 1.0, bool adjust = true);
  void update(double w, double r, double p_drop = 0.0, double n_drop = -1.0);
  void persist(metric_sink&, const std::string&) const;
  void reset_stats();
  float lower_bound() const;
  float upper_bound() const;

private:
  double approxpolygammaone(double b) const;
  double lblogwealth(double sumXt, double v, double eta, double s, double lb_alpha) const;
};
}  // namespace estimators

namespace model_utils
{
size_t read_model_field(io_buf&, VW980::details::incremental_f_sum&);
size_t write_model_field(io_buf&, const VW980::details::incremental_f_sum&, const std::string&, bool);
size_t read_model_field(io_buf&, VW980::estimators::confidence_sequence&);
size_t write_model_field(io_buf&, const VW980::estimators::confidence_sequence&, const std::string&, bool);
}  // namespace model_utils
}  // namespace VW980
