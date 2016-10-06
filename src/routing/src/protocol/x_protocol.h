#ifndef ROUTING_XPROTOCOL_INCLUDED
#define ROUTING_XPROTOCOL_INCLUDED

#include "base_protocol.h"

#include <memory>

class XProtocol: public BaseProtocol {
public:
  XProtocol(SocketOperationsBase *socket_operations): BaseProtocol(socket_operations) {}

  /** @brief Function that gets called when the client is being blocked
   *
   * This function is called when the client is being blocked and should handle
   * any communication to the server required by the protocol in such case
   *
   * @param server Descriptor of the server
   * @param log_prefix prefix to be used by the function as a tag for logging
   */
  virtual void on_block_client_host(int /*server*/, const std::string &/*log_prefix*/) override {
    // nothing to be done in case of x-protocol
  }

  /** @brief Reads from sender and writes it back to receiver using select
   *
   * This function reads data from the sender socket and writes it back
   * to the receiver socket. It use `select`.
   *
   * @param sender Descriptor of the sender
   * @param receiver Descriptor of the receiver
   * @param readfds Read descriptors used with FD_ISSET
   * @param buffer Buffer to use for storage
   * @param curr_pktnr Pointer to storage for sequence id of packet
   * @param handshake_done Whether handshake phase is finished or not
   * @param report_bytes_read Pointer to storage to report bytes read
   * @param from server true if the message sender is the server, false
   *                    if it is a client
   *
   * @return 0 on success; -1 on error
   */
  virtual int copy_packets(int sender, int receiver, fd_set *readfds,
                           RoutingProtocolBuffer &buffer, int *curr_pktnr,
                           bool &handshake_done, size_t *report_bytes_read,
                           bool from_server) override;

  /** @brief Sends error message to the provided receiver.
   *
   * This function sends protocol message containing MySQL error
   *
   * @param destination descriptor of the receiver
   * @param code general error code
   * @param message human readable error message
   * @param sql_state SQL state for the error
   * @param log_prefix prefix to be used by the function as a tag for logging
   *
   * @return true on success; false on error
   */
  virtual bool send_error(int destination,
                          unsigned short code,
                          const std::string &message,
                          const std::string &sql_state,
                          const std::string &log_prefix) override;

  /** @brief Gets protocol name. */
  virtual std::string get_name() override {
    return "x";
  }
};

#endif // ROUTING_XPROTOCOL_INCLUDED
