// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "vw/core/global_data.h"
#include "vw/io/io_adapter.h"
#include "vw/io/logger.h"

#include <memory>

namespace VW980
{
class model_delta
{
public:
  // model_delta takes ownership of the workspace
  explicit model_delta(VW980::workspace* ws) : _ws(ws) {}
  explicit model_delta(std::unique_ptr<VW980::workspace>&& ws) : _ws(std::move(ws)) {}

  // retrieve a raw pointer to the underlying VW980::workspace
  // unsafe, only for use in implementation of model merging and its corresponding unit tests
  VW980::workspace* unsafe_get_workspace_ptr() const { return _ws.get(); }

  // release ownership of the pointer to the underlying VW980::workspace, and return it
  // unsafe, only for use in implementation of model merging and its corresponding unit tests
  VW980::workspace* unsafe_release_workspace_ptr() { return _ws.release(); }

  void serialize(VW980::io::writer&) const;
  // Must only load what was previously serialized with the serialize function.
  static std::unique_ptr<model_delta> deserialize(VW980::io::reader&);

private:
  std::unique_ptr<VW980::workspace> _ws;
};

/**
 * Merge the differences of several workspaces into the given base workspace. This merges weights
 * and all training state. All given workspaces must be compatible with the base workspace, meaning they
 * should have the same reduction stack and same training based options.
 *
 * If the base workspace was not given, it is assumed that the given workspaces were trained from fresh.
 *
 * Note: This is an experimental API.
 *
 * @param base_workspace Optional common base model that all other models continued training from. If not supplied, then
 * all models are assumed to be trained from scratch.
 * @param workspaces_to_merge Vector of workspaces to merge.
 * @param logger Optional logger to be used for logging during function and is given to the resulting workspace
 * @return std::unique_ptr<VW980::workspace> Pointer to the resulting workspace.
 */
std::unique_ptr<VW980::workspace> merge_models(const VW980::workspace* base_workspace,
    const std::vector<const VW980::workspace*>& workspaces_to_merge, VW980::io::logger* logger = nullptr);

/**
 * Merge several model deltas into a single delta. This merges weights
 * and all training state. All given deltas must be from compatible models, meaning they
 * should have the same reduction stack and same training based options. All deltas are
 * assumed to be generated using a single shared base workspace.
 *
 * Note: This is an experimental API.
 *
 * @param deltas_to_merge Vector of model deltas to merge.
 * @param logger Optional logger to be used for logging during function and is given to the resulting workspace
 * @return std::unique_ptr<VW980::workspace> Pointer to the resulting workspace.
 */
VW980::model_delta merge_deltas(
    const std::vector<const VW980::model_delta*>& deltas_to_merge, VW980::io::logger* logger = nullptr);

std::unique_ptr<VW980::workspace> operator+(const VW980::workspace& ws, const VW980::model_delta& md);
VW980::model_delta operator-(const VW980::workspace& ws1, const VW980::workspace& ws2);
}  // namespace VW980
