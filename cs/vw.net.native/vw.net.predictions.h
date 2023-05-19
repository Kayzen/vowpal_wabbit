#pragma once

#include "vw.net.native.h"
#include "vw/core/vw.h"

namespace vw_net_native
{
struct scalar_confidence_t
{
  float value;
  float confidence;
};
}  // namespace vw_net_native

extern "C"
{
  API float GetPredictionScalar(VW980::example* ex);
  API vw_net_native::scalar_confidence_t GetPredictionScalarConfidence(VW980::workspace* vw, VW980::example* ex);
  API size_t GetPredictionScalarsCount(VW980::workspace* vw, VW980::example* ex);
  API vw_net_native::dotnet_size_t GetPredictionScalars(
      VW980::workspace* vw, VW980::example* ex, float* values, vw_net_native::dotnet_size_t count);
  API float GetPredictionProb(VW980::workspace* vw, VW980::example* ex);
  API float GetPredictionCostSensitive(VW980::workspace* vw, VW980::example* ex);
  API uint32_t GetPredictionMulticlassClass(VW980::workspace* vw, VW980::example* ex);
  API size_t GetPredictionMultilabelCount(VW980::workspace* vw, VW980::example* ex);
  API vw_net_native::dotnet_size_t GetPredictionMultilabel(
      VW980::workspace* vw, VW980::example* ex, uint32_t* values, vw_net_native::dotnet_size_t count);
  API size_t GetPredictionActionScoresCount(VW980::workspace* vw, VW980::example* ex);
  API vw_net_native::dotnet_size_t GetPredictionActionScores(
      VW980::workspace* vw, VW980::example* ex, VW980::action_score* values, vw_net_native::dotnet_size_t count);
  API size_t GetPredictionTopicProbsCount(VW980::workspace* vw, VW980::example* ex);
  API vw_net_native::dotnet_size_t GetPredictionTopicProbs(
      VW980::workspace* vw, VW980::example* ex, float* values, vw_net_native::dotnet_size_t count);
  API uint32_t GetPredictionActiveMulticlassClass(VW980::workspace* vw, VW980::example* ex);
  API size_t GetPredictionActiveMulticlassMoreInfoRequiredClassesCount(VW980::workspace* vw, VW980::example* ex);
  API vw_net_native::dotnet_size_t GetPredictionActiveMulticlassMoreInfoRequiredClasses(
      VW980::workspace* vw, VW980::example* ex, int32_t* values, vw_net_native::dotnet_size_t count);
}
