// Copyright (c) by respective owners including Yahoo!)
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "vw/core/cb_type.h"

#include "vw/common/vw_exception.h"
#include "vw/common/vw_throw.h"

#include <cassert>

#define CASE(type) \
  case type:       \
    return #type;

VW980::string_view VW980::to_string(VW980::cb_type_t label_type)
{
  using namespace VW980;
  switch (label_type)
  {
    CASE(cb_type_t::DR)
    CASE(cb_type_t::DM)
    CASE(cb_type_t::IPS)
    CASE(cb_type_t::MTR)
    CASE(cb_type_t::SM)
  }

  // The above enum is exhaustive and will warn on a new label type being added due to the lack of `default`
  // The following is required by the compiler, otherwise it things control can reach the end of this function without
  // returning.
  assert(false);
  return "unknown label type enum";
}

VW980::cb_type_t VW980::cb_type_from_string(VW980::string_view str)
{
  if (str == "dr") { return VW980::cb_type_t::DR; }
  if (str == "dm") { return VW980::cb_type_t::DM; }
  if (str == "ips") { return VW980::cb_type_t::IPS; }
  if (str == "mtr") { return VW980::cb_type_t::MTR; }
  if (str == "sm") { return VW980::cb_type_t::SM; }
  THROW("Unknown cb_type: " << str);
}