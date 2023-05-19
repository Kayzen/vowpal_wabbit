// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#ifdef _WIN32
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif

#  include <WS2tcpip.h>
#  include <WinSock2.h>
#  include <Windows.h>
#  include <io.h>

#  define CLOSESOCK closesocket
#  define inet_ntop InetNtopA

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef int socklen_t;
typedef SOCKET socket_t;

namespace std
{
// forward declare promise as C++/CLI doesn't allow usage in header files
template <typename T>
class future;
}  // namespace std
#else
#  include <arpa/inet.h>
#  include <netdb.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <strings.h>
#  include <sys/socket.h>
#  include <unistd.h>

#  define CLOSESOCK close

using socket_t = int;

#  include <future>
#endif

#include "vw/common/future_compat.h"

namespace VW980  // NOLINT
{
class spanning_tree
{
public:
  spanning_tree(short unsigned int port = 26543, bool quiet = false);
  ~spanning_tree();

  VW_DEPRECATED(
      "VW980::SpanningTree::BoundPort renamed to VW980::spanning_tree::bound_port. VW980::SpanningTree::BoundPort will be "
      "removed in VW 10.")
  inline short unsigned int BoundPort()  // NOLINT
  {
    return bound_port();
  }
  short unsigned int bound_port();

  VW_DEPRECATED(
      "VW980::SpanningTree::Start renamed to VW980::spanning_tree::start. VW980::SpanningTree::Start will be removed in VW 10.")
  inline void Start()  // NOLINT
  {
    return start();
  }
  void start();

  VW_DEPRECATED(
      "VW980::SpanningTree::Run renamed to VW980::spanning_tree::run. VW980::SpanningTree::Run will be removed in VW 10.")
  inline void Run()  // NOLINT
  {
    return run();
  }
  void run();

  VW_DEPRECATED(
      "VW980::SpanningTree::Stop renamed to VW980::spanning_tree::stop. VW980::SpanningTree::Stop will be removed in VW 10.")
  inline void Stop()  // NOLINT
  {
    return stop();
  }
  void stop();

private:
  bool _stop;
  socket_t _sock;
  uint16_t _port;

  // future to signal end of thread running.
  // Need a pointer since C++/CLI doesn't like futures yet
  std::future<void>* _future;

  bool _quiet;
};

using SpanningTree VW_DEPRECATED(
    "VW980::SpanningTree renamed to VW980::spanning_tree. VW980::SpanningTree will be removed in VW 10.") = spanning_tree;
}  // namespace VW980
