// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "vw/core/constant.h"
#include "vw/core/feature_group.h"
#include "vw/core/vw.h"
#include "vw/fb_parser/parse_example_flatbuffer.h"
#include "vw/test_common/test_common.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

flatbuffers::Offset<void> get_label(flatbuffers::FlatBufferBuilder& builder, VW980::parsers::flatbuffer::Label label_type)
{
  flatbuffers::Offset<void> label;
  if (label_type == VW980::parsers::flatbuffer::Label_SimpleLabel)
  {
    label = VW980::parsers::flatbuffer::CreateSimpleLabel(builder, 0.0, 1.0).Union();
  }

  return label;
}

flatbuffers::Offset<VW980::parsers::flatbuffer::ExampleRoot> sample_flatbuffer_collection(
    flatbuffers::FlatBufferBuilder& builder, VW980::parsers::flatbuffer::Label label_type)
{
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Example>> examples;
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Namespace>> namespaces;
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Feature>> fts;

  auto label = get_label(builder, label_type);

  fts.push_back(VW980::parsers::flatbuffer::CreateFeatureDirect(builder, "hello", 2.23f, VW980::details::CONSTANT));
  namespaces.push_back(
      VW980::parsers::flatbuffer::CreateNamespaceDirect(builder, nullptr, VW980::details::CONSTANT_NAMESPACE, &fts, 128));
  examples.push_back(VW980::parsers::flatbuffer::CreateExampleDirect(builder, &namespaces, label_type, label));

  auto eg_collection = VW980::parsers::flatbuffer::CreateExampleCollectionDirect(builder, &examples);
  return CreateExampleRoot(builder, VW980::parsers::flatbuffer::ExampleType_ExampleCollection, eg_collection.Union());
}

flatbuffers::Offset<VW980::parsers::flatbuffer::ExampleRoot> sample_flatbuffer(
    flatbuffers::FlatBufferBuilder& builder, VW980::parsers::flatbuffer::Label label_type)
{
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Namespace>> namespaces;
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Feature>> fts;

  auto label = get_label(builder, label_type);

  fts.push_back(VW980::parsers::flatbuffer::CreateFeatureDirect(builder, "hello", 2.23f, VW980::details::CONSTANT));
  namespaces.push_back(
      VW980::parsers::flatbuffer::CreateNamespaceDirect(builder, nullptr, VW980::details::CONSTANT_NAMESPACE, &fts, 128));
  auto example = VW980::parsers::flatbuffer::CreateExampleDirect(builder, &namespaces, label_type, label);

  return CreateExampleRoot(builder, VW980::parsers::flatbuffer::ExampleType_Example, example.Union());
}

TEST(FlatbufferParser, FlatbufferStandaloneExample)
{
  auto all = VW980::initialize(vwtest::make_args("--no_stdin", "--quiet", "--flatbuffer"));

  flatbuffers::FlatBufferBuilder builder;

  auto root = sample_flatbuffer(builder, VW980::parsers::flatbuffer::Label_SimpleLabel);
  builder.FinishSizePrefixed(root);

  uint8_t* buf = builder.GetBufferPointer();

  VW980::multi_ex examples;
  examples.push_back(&VW980::get_unused_example(all.get()));
  VW980::io_buf unused_buffer;
  all->flat_converter->parse_examples(all.get(), unused_buffer, examples, buf);

  auto example = all->flat_converter->data()->example_obj_as_Example();
  EXPECT_EQ(example->namespaces()->size(), 1);
  EXPECT_EQ(example->namespaces()->Get(0)->features()->size(), 1);
  EXPECT_FLOAT_EQ(example->label_as_SimpleLabel()->label(), 0.0);
  EXPECT_FLOAT_EQ(example->label_as_SimpleLabel()->weight(), 1.0);
  EXPECT_EQ(example->namespaces()->Get(0)->hash(), VW980::details::CONSTANT_NAMESPACE);
  EXPECT_EQ(example->namespaces()->Get(0)->full_hash(), VW980::details::CONSTANT_NAMESPACE);
  EXPECT_STREQ(example->namespaces()->Get(0)->features()->Get(0)->name()->c_str(), "hello");
  EXPECT_EQ(example->namespaces()->Get(0)->features()->Get(0)->hash(), VW980::details::CONSTANT);
  EXPECT_FLOAT_EQ(example->namespaces()->Get(0)->features()->Get(0)->value(), 2.23);

  // Check vw example
  EXPECT_EQ(examples.size(), 1);
  EXPECT_FLOAT_EQ(examples[0]->l.simple.label, 0.f);
  const auto& red_features = examples[0]->ex_reduction_features.template get<VW980::simple_label_reduction_features>();
  EXPECT_FLOAT_EQ(red_features.weight, 1.f);

  EXPECT_EQ(examples[0]->indices[0], VW980::details::CONSTANT_NAMESPACE);
  EXPECT_FLOAT_EQ(examples[0]->feature_space[examples[0]->indices[0]].values[0], 2.23f);
  EXPECT_EQ(examples[0]->feature_space[examples[0]->indices[0]].namespace_extents.size(), 1);
  EXPECT_EQ(examples[0]->feature_space[examples[0]->indices[0]].namespace_extents[0],
      (VW980::namespace_extent{0, 1, VW980::details::CONSTANT_NAMESPACE}));

  VW980::finish_example(*all, *examples[0]);
}

TEST(FlatbufferParser, FlatbufferCollection)
{
  auto all = VW980::initialize(vwtest::make_args("--no_stdin", "--quiet", "--flatbuffer"));

  flatbuffers::FlatBufferBuilder builder;

  auto root = sample_flatbuffer_collection(builder, VW980::parsers::flatbuffer::Label_SimpleLabel);
  builder.FinishSizePrefixed(root);

  uint8_t* buf = builder.GetBufferPointer();

  VW980::multi_ex examples;
  examples.push_back(&VW980::get_unused_example(all.get()));
  VW980::io_buf unused_buffer;
  all->flat_converter->parse_examples(all.get(), unused_buffer, examples, buf);

  auto collection_examples = all->flat_converter->data()->example_obj_as_ExampleCollection()->examples();
  EXPECT_EQ(collection_examples->size(), 1);
  EXPECT_EQ(collection_examples->Get(0)->namespaces()->size(), 1);
  EXPECT_EQ(collection_examples->Get(0)->namespaces()->Get(0)->features()->size(), 1);
  EXPECT_FLOAT_EQ(collection_examples->Get(0)->label_as_SimpleLabel()->label(), 0.0);
  EXPECT_FLOAT_EQ(collection_examples->Get(0)->label_as_SimpleLabel()->weight(), 1.0);
  EXPECT_EQ(collection_examples->Get(0)->namespaces()->Get(0)->hash(), VW980::details::CONSTANT_NAMESPACE);
  EXPECT_EQ(collection_examples->Get(0)->namespaces()->Get(0)->full_hash(), VW980::details::CONSTANT_NAMESPACE);
  EXPECT_STREQ(collection_examples->Get(0)->namespaces()->Get(0)->features()->Get(0)->name()->c_str(), "hello");
  EXPECT_EQ(collection_examples->Get(0)->namespaces()->Get(0)->features()->Get(0)->hash(), VW980::details::CONSTANT);
  EXPECT_FLOAT_EQ(collection_examples->Get(0)->namespaces()->Get(0)->features()->Get(0)->value(), 2.23);

  // check vw example
  EXPECT_EQ(examples.size(), 1);
  EXPECT_FLOAT_EQ(examples[0]->l.simple.label, 0.f);
  const auto& red_features = examples[0]->ex_reduction_features.template get<VW980::simple_label_reduction_features>();
  EXPECT_FLOAT_EQ(red_features.weight, 1.f);

  EXPECT_EQ(examples[0]->indices[0], VW980::details::CONSTANT_NAMESPACE);
  EXPECT_FLOAT_EQ(examples[0]->feature_space[examples[0]->indices[0]].values[0], 2.23f);
  EXPECT_EQ(examples[0]->feature_space[examples[0]->indices[0]].namespace_extents.size(), 1);
  EXPECT_EQ(examples[0]->feature_space[examples[0]->indices[0]].namespace_extents[0],
      (VW980::namespace_extent{0, 1, VW980::details::CONSTANT_NAMESPACE}));

  VW980::finish_example(*all, *examples[0]);
}
