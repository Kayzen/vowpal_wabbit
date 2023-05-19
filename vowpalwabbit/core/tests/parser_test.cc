// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "vw/core/parse_args.h"
#include "vw/core/parse_example.h"
#include "vw/core/parse_primitives.h"
#include "vw/core/vw.h"
#include "vw/test_common/test_common.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Parser, DecodeInlineHexTest)
{
  auto nl = VW980::io::create_null_logger();
  EXPECT_EQ(VW980::decode_inline_hex("test", nl), "test");
  EXPECT_EQ(VW980::decode_inline_hex("10", nl), "10");
  EXPECT_EQ(VW980::decode_inline_hex("\\x01", nl), "\x01");
  EXPECT_EQ(VW980::decode_inline_hex("\\xab", nl), "\xab");
  EXPECT_EQ(VW980::decode_inline_hex("\\x01 unrelated \\x56", nl), "\x01 unrelated \x56");
}

TEST(Parser, ParseTextWithExtents)
{
  auto vw = VW980::initialize(vwtest::make_args("--no_stdin", "--quiet"));
  auto* ex = VW980::read_example(*vw, "|features a b |new_features a b |features2 c d |empty |features c d");

  EXPECT_EQ(ex->feature_space['f'].size(), 6);
  EXPECT_EQ(ex->feature_space['n'].size(), 2);
  EXPECT_EQ(ex->feature_space['3'].size(), 0);

  EXPECT_EQ(ex->feature_space['f'].namespace_extents.size(), 3);
  EXPECT_EQ(ex->feature_space['n'].namespace_extents.size(), 1);

  EXPECT_EQ(ex->feature_space['f'].namespace_extents[0], (VW980::namespace_extent{0, 2, VW980::hash_space(*vw, "features")}));
  EXPECT_EQ(
      ex->feature_space['f'].namespace_extents[1], (VW980::namespace_extent{2, 4, VW980::hash_space(*vw, "features2")}));
  EXPECT_EQ(ex->feature_space['f'].namespace_extents[2], (VW980::namespace_extent{4, 6, VW980::hash_space(*vw, "features")}));

  VW980::finish_example(*vw, *ex);
}

TEST(Parser, TrimWhitespaceTest)
{
  EXPECT_TRUE("" == VW980::trim_whitespace(VW980::string_view("")));
  EXPECT_TRUE("abc" == VW980::trim_whitespace(VW980::string_view("abc")));
  EXPECT_TRUE("abc" == VW980::trim_whitespace(VW980::string_view("              abc               ")));
  EXPECT_TRUE("ab     c" == VW980::trim_whitespace(VW980::string_view("              ab     c               ")));
  EXPECT_TRUE("a\nb     c" == VW980::trim_whitespace(VW980::string_view("              a\nb     c               ")));
  EXPECT_TRUE(
      "a\nb     \tc" == VW980::trim_whitespace(VW980::string_view("     \t         a\nb     \tc        \t\t       ")));
  EXPECT_TRUE("" == VW980::trim_whitespace(VW980::string_view("     \t                 \t\t       ")));
  EXPECT_TRUE("" == VW980::trim_whitespace(std::string("")));
  EXPECT_TRUE("abc" == VW980::trim_whitespace(std::string("abc")));
  EXPECT_TRUE("abc" == VW980::trim_whitespace(std::string("              abc               ")));
  EXPECT_TRUE("ab     c" == VW980::trim_whitespace(std::string("              ab     c               ")));
  EXPECT_TRUE("a\nb     c" == VW980::trim_whitespace(std::string("              a\nb     c               ")));
  EXPECT_TRUE("a\nb     \tc" == VW980::trim_whitespace(std::string("     \t         a\nb     \tc        \t\t       ")));
  EXPECT_TRUE("" == VW980::trim_whitespace(std::string("     \t                 \t\t       ")));
}