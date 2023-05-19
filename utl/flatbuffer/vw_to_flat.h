// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/core/vw.h"
VW_WARNING_STATE_PUSH
VW_WARNING_DISABLE_BADLY_FORMED_XML
#include "vw/fb_parser/generated/example_generated.h"
VW_WARNING_STATE_POP
#include "vw/core/named_labels.h"
#include "vw/core/simple_label.h"

struct ExampleBuilder
{
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Namespace>> namespaces;
  VW980::parsers::flatbuffer::Label label_type = VW980::parsers::flatbuffer::Label_NONE;
  flatbuffers::Offset<void> label = 0;
  std::string tag;
  bool is_newline = false;

  flatbuffers::Offset<VW980::parsers::flatbuffer::Example> to_flat_example(flatbuffers::FlatBufferBuilder& builder)
  {
    auto ex = VW980::parsers::flatbuffer::CreateExampleDirect(
        builder, &namespaces, label_type, label, tag.empty() ? nullptr : tag.c_str(), is_newline);
    clear();
    return ex;
  }

  void clear()
  {
    namespaces.clear();
    label_type = VW980::parsers::flatbuffer::Label_NONE;
    label = 0;
    tag.clear();
  }
};

struct MultiExampleBuilder
{
  std::vector<ExampleBuilder> examples;
  flatbuffers::Offset<VW980::parsers::flatbuffer::MultiExample> to_flat_example(flatbuffers::FlatBufferBuilder& builder)
  {
    std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Example>> exs;
    for (auto& ex : examples)
    {
      auto flat_ex = ex.to_flat_example(builder);
      exs.push_back(flat_ex);
    }
    examples.clear();
    return VW980::parsers::flatbuffer::CreateMultiExampleDirect(builder, &exs);
  }
};

class to_flat
{
public:
  std::string output_flatbuffer_name;
  uint64_t collection_size = 0;
  bool collection = false;
  void convert_txt_to_flat(VW980::workspace& all);

private:
  flatbuffers::FlatBufferBuilder _builder;
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::Example>> _example_collection;
  std::vector<flatbuffers::Offset<VW980::parsers::flatbuffer::MultiExample>> _multi_example_collection;
  std::map<uint64_t, flatbuffers::Offset<VW980::parsers::flatbuffer::Namespace>> _share_examples;
  size_t _collection_count = 0;
  uint32_t _multi_ex_index = 0;
  int _examples = 0;

  void create_simple_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_cb_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_ccb_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_cb_eval_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_mc_label(VW980::named_labels* ldict, VW980::example* v, ExampleBuilder& ex_builder);
  void create_multi_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_slates_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_cs_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_no_label(VW980::example* v, ExampleBuilder& ex_builder);
  void create_continuous_action_label(VW980::example* v, ExampleBuilder& ex_builder);
  // helpers
  void write_collection_to_file(bool is_multiline, std::ofstream& outfile);
  void write_to_file(bool collection, bool is_multiline, MultiExampleBuilder& multi_ex_builder,
      ExampleBuilder& ex_builder, std::ofstream& outfile);

  flatbuffers::Offset<VW980::parsers::flatbuffer::Namespace> create_namespace(VW980::features::audit_iterator begin,
      VW980::features::audit_iterator end, VW980::namespace_index index, uint64_t hash, bool audit);
};
