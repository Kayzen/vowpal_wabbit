// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#pragma once

#include "vw/core/vw_fwd.h"
#include "vw/io/io_adapter.h"

#include <string>

namespace VW980
{
namespace details
{
// Opens socket and writes \0 as a handshake to VW accepting binary data over the port.
std::unique_ptr<VW980::io::socket> open_vw_binary_socket(
    const std::string& host_and_optional_port, VW980::io::logger& logger);
// Opens socket and writes \0 as a handshake to VW accepting binary data over the port.
std::unique_ptr<VW980::io::socket> open_vw_binary_socket(const std::string& host, uint16_t port, VW980::io::logger& logger);
}  // namespace details
}  // namespace VW980
