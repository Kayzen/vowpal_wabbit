#pragma once

#include "vw.net.native.h"
#include "vw/core/vw.h"
#include "vw/json_parser/decision_service_utils.h"

extern "C"
{
  API VW980::parsers::json::decision_service_interaction* CreateDecisionServiceInteraction();
  API void DeleteDecisionServiceInteraction(VW980::parsers::json::decision_service_interaction* interaction);

  API char* GetDSInteractionEventIdDup(VW980::parsers::json::decision_service_interaction* interaction);
  API char* GetDSInteractionTimestampDup(VW980::parsers::json::decision_service_interaction* interaction);
  API size_t GetDSInteractionActionsCount(VW980::parsers::json::decision_service_interaction* interaction);
  API vw_net_native::dotnet_size_t GetDSInteractionActions(VW980::parsers::json::decision_service_interaction* interaction,
      unsigned int* values, vw_net_native::dotnet_size_t buffer_size);
  API size_t GetDSInteractionProbabilitiesCount(VW980::parsers::json::decision_service_interaction* interaction);
  API vw_net_native::dotnet_size_t GetDSInteractionProbabilities(
      VW980::parsers::json::decision_service_interaction* interaction, float* values,
      vw_net_native::dotnet_size_t buffer_size);
  API size_t GetDSInteractionBaselineActionsCount(VW980::parsers::json::decision_service_interaction* interaction);
  API vw_net_native::dotnet_size_t GetDSInteractionBaselineActions(
      VW980::parsers::json::decision_service_interaction* interaction, unsigned int* values,
      vw_net_native::dotnet_size_t buffer_size);

  API float GetDSInteractionProbabilityOfDrop(VW980::parsers::json::decision_service_interaction* interaction);
  API float GetDSInteractionOriginalLabelCost(VW980::parsers::json::decision_service_interaction* interaction);
  API float GetDSInteractionOriginalLabelCostFirstSlot(VW980::parsers::json::decision_service_interaction* interaction);
  API int GetDSInteractionSkipLearn(VW980::parsers::json::decision_service_interaction* interaction);
}
