#include "vw.net.api_status.h"

API VW980::experimental::api_status* CreateApiStatus() { return new VW980::experimental::api_status(); }

API void DeleteApiStatus(VW980::experimental::api_status* status) { delete status; }

API const char* GetApiStatusErrorMessage(VW980::experimental::api_status* status) { return status->get_error_msg(); }

API int GetApiStatusErrorCode(VW980::experimental::api_status* status) { return status->get_error_code(); }

// API void UpdateApiStatusSafe(VW980::experimental::api_status* status, int error_code, const char* message)
// {
//     // api_status takes a copy of the message string coming in, since it has no way to enforce that its callers
//     // do not deallocate the buffer after calling try_update.
//     VW980::experimental::api_status::try_update(status, error_code, message);
// }

// API void ClearApiStatusSafe(VW980::experimental::api_status* status)
// {
//     VW980::experimental::api_status::try_clear(status);
// }