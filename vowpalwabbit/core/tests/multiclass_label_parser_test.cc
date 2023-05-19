// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "vw/common/string_view.h"
#include "vw/common/text_utils.h"
#include "vw/core/global_data.h"
#include "vw/core/multiclass.h"
#include "vw/core/parse_primitives.h"
#include "vw/core/parser.h"
#include "vw/core/shared_data.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

void parse_label(VW980::label_parser& lp, VW980::string_view label, VW980::polylabel& l)
{
  std::vector<VW980::string_view> words;
  VW980::tokenize(' ', label, words);
  lp.default_label(l);
  VW980::reduction_features red_fts;
  VW980::label_parser_reuse_mem mem;
  auto null_logger = VW980::io::create_null_logger();
  lp.parse_label(l, red_fts, mem, nullptr, words, null_logger);
}

TEST(MulticlassLabelParser, MulticlassLabelParser)
{
  auto lp = VW980::multiclass_label_parser_global;
  {
    auto plabel = VW980::make_unique<VW980::polylabel>();
    EXPECT_THROW(parse_label(lp, "1,2,3", *plabel), VW980::vw_exception);
  }
  {
    auto plabel = VW980::make_unique<VW980::polylabel>();
    EXPECT_THROW(parse_label(lp, "1a", *plabel), VW980::vw_exception);
  }
  {
    auto plabel = VW980::make_unique<VW980::polylabel>();
    EXPECT_THROW(parse_label(lp, "1 2 3", *plabel), VW980::vw_exception);
  }
  {
    auto plabel = VW980::make_unique<VW980::polylabel>();
    parse_label(lp, "2", *plabel);
    EXPECT_TRUE(plabel->multi.label == 2);
    EXPECT_TRUE(plabel->multi.weight == 1.0);
  }
  {
    auto plabel = VW980::make_unique<VW980::polylabel>();
    parse_label(lp, "2 2", *plabel);
    EXPECT_TRUE(plabel->multi.label == 2);
    EXPECT_TRUE(plabel->multi.weight == 2.0);
  }
}