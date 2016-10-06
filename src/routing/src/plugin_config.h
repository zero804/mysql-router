/*
  Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PLUGIN_CONFIG_ROUTING_INCLUDED
#define PLUGIN_CONFIG_ROUTING_INCLUDED

#include "mysql/harness/filesystem.h"
#include "mysql/harness/plugin.h"

#include "mysqlrouter/datatypes.h"
#include "mysqlrouter/plugin_config.h"
#include "mysqlrouter/routing.h"
#include "mysqlrouter/uri.h"
#include "mysqlrouter/utils.h"

#include "utils.h"

#include <map>
#include <string>

using std::map;
using std::string;
using mysqlrouter::to_string;
using mysqlrouter::TCPAddress;
using mysqlrouter::URI;
using mysqlrouter::URIError;
using mysqlrouter::URIQuery;

class RoutingPluginConfig final : public mysqlrouter::BasePluginConfig {
public:
  /** @brief Constructor
   *
   * @param section from configuration file provided as ConfigSection
   */
  RoutingPluginConfig(const mysql_harness::ConfigSection *section);

  std::string get_default(const std::string &option);

  bool is_required(const std::string &option);

  /** @brief `protocol` option read from configuration section */
  const std::string protocol_name;
  /** @brief `destinations` option read from configuration section */
  const std::string destinations;
  /** @brief `bind_port` option read from configuration section */
  const int bind_port;
  /** @brief `bind_address` option read from configuration section */
  const mysqlrouter::TCPAddress bind_address;
  /** @brief `socket` option read from configuration section is stored as named_socket */
  const mysql_harness::Path named_socket;
  /** @brief `connect_timeout` option read from configuration section */
  const int connect_timeout;
  /** @brief `mode` option read from configuration section */
  const routing::AccessMode mode;
  /** @brief `max_connections` option read from configuration section */
  const int max_connections;
  /** @brief `max_connect_errors` option read from configuration section */
  const unsigned long long max_connect_errors;
  /** @brief `client_connect_timeout` option read from configuration section */
  const unsigned int client_connect_timeout;
  /** @brief Size of buffer to receive packets */
  const unsigned int net_buffer_length;

protected:

private:
  routing::AccessMode get_option_mode(const mysql_harness::ConfigSection *section, const std::string &option);
  std::string get_option_destinations(const mysql_harness::ConfigSection *section, const std::string &option,
                                      const std::string &protocol);
  std::string get_protocol_name(const mysql_harness::ConfigSection *section, const std::string &option);
};

#endif // PLUGIN_CONFIG_ROUTING_INCLUDED
