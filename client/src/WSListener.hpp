//
// Created by Leonid  on 2019-06-07.
//

#ifndef WSListener_hpp
#define WSListener_hpp

#include "oatpp-websocket/ConnectionHandler.hpp"
#include "oatpp-websocket/WebSocket.hpp"

/**
 * WebSocket listener listens on incoming WebSocket events.
 */
class WSListener : public oatpp::websocket::WebSocket::Listener {
private:
  static constexpr const char* TAG = "Client_WSListener";
private:
  std::mutex& m_writeMutex;
  /**
   * Buffer for messages. Needed for multi-frame messages.
   */
  oatpp::data::stream::ChunkedBuffer m_messageBuffer;
public:

  WSListener(std::mutex& writeMutex)
    : m_writeMutex(writeMutex)
  {}

  /**
   * Called on "ping" frame.
   */
  void onPing(const WebSocket& socket, const oatpp::String& message) override;

  /**
   * Called on "pong" frame
   */
  void onPong(const WebSocket& socket, const oatpp::String& message) override;

  /**
   * Called on "close" frame
   */
  void onClose(const WebSocket& socket, v_word16 code, const oatpp::String& message) override;

  /**
   * Called on each message frame. After the last message will be called once-again with size == 0 to designate end of the message.
   */
  void readMessage(const WebSocket& socket, p_char8 data, oatpp::data::v_io_size size) override;

};

#endif // WSListener_hpp
