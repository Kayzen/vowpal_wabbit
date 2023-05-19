// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "vw/core/label_parser.h"

#include "vw/common/vw_exception.h"
#include "vw/core/cb.h"
#include "vw/core/cb_continuous_label.h"
#include "vw/core/ccb_label.h"
#include "vw/core/cost_sensitive.h"
#include "vw/core/multiclass.h"
#include "vw/core/multilabel.h"
#include "vw/core/no_label.h"
#include "vw/core/simple_label_parser.h"
#include "vw/core/slates_label.h"

VW980::label_parser VW980::get_label_parser(VW980::label_type_t label_type)
{
  switch (label_type)
  {
    case VW980::label_type_t::SIMPLE:
      return VW980::simple_label_parser_global;

    case VW980::label_type_t::CB:
      return VW980::cb_label_parser_global;

    case VW980::label_type_t::CB_EVAL:
      return VW980::cb_eval_label_parser_global;

    case VW980::label_type_t::CS:
      return VW980::cs_label_parser_global;

    case VW980::label_type_t::MULTILABEL:
      return VW980::multilabel_label_parser_global;

    case VW980::label_type_t::MULTICLASS:
      return VW980::multiclass_label_parser_global;

    case VW980::label_type_t::CCB:
      return VW980::ccb_label_parser_global;

    case VW980::label_type_t::SLATES:
      return VW980::slates::slates_label_parser;

    case VW980::label_type_t::NOLABEL:
      return VW980::no_label_parser_global;

    case VW980::label_type_t::CONTINUOUS:
      return VW980::cb_continuous::the_label_parser;
  }

  THROW("Unknown label type in get_label_parser. This should be unreachable code.")
}
