//
// Created by Leonid  on 2019-06-07.
//

#ifndef WSListener_hpp
#define WSListener_hpp

#include "oatpp-websocket/AsyncConnectionHandler.hpp"
#include "oatpp-websocket/AsyncWebSocket.hpp"

/**
 * WebSocket listener listens on incoming WebSocket events.
 */
class WSListener : public oatpp::websocket::AsyncWebSocket::Listener {
private:
  static constexpr const char* TAG = "Server_WSListener";
private:
  /**
   * Buffer for messages. Needed for multi-frame messages.
   */
  oatpp::data::stream::ChunkedBuffer m_messageBuffer;
public:

  /**
   * Called on "ping" frame.
   */
  CoroutineStarter onPing(const std::shared_ptr<AsyncWebSocket>& socket, const oatpp::String& message) override;

  /**
   * Called on "pong" frame
   */
  CoroutineStarter onPong(const std::shared_ptr<AsyncWebSocket>& socket, const oatpp::String& message) override;

  /**
   * Called on "close" frame
   */
  CoroutineStarter onClose(const std::shared_ptr<AsyncWebSocket>& socket, v_word16 code, const oatpp::String& message) override;

  /**
   * Called on each message frame. After the last message will be called once-again with size == 0 to designate end of the message.
   */
  CoroutineStarter readMessage(const std::shared_ptr<AsyncWebSocket>& socket, p_char8 data, oatpp::data::v_io_size size) override;

};

/**
 * Listener on new WebSocket connections.
 */
class WSInstanceListener : public oatpp::websocket::AsyncConnectionHandler::SocketInstanceListener {
private:
  static constexpr const char* TAG = "Server_WSInstanceListener";
public:
  /**
   * Counter for connected clients.
   */
  static std::atomic<v_int32> SOCKETS;
public:

  /**
   *  Called when socket is created
   */
  void onAfterCreate_NonBlocking(const std::shared_ptr<WSListener::AsyncWebSocket>& socket, const std::shared_ptr<const ParameterMap>& params) override;

  /**
   *  Called before socket instance is destroyed.
   */
  void onBeforeDestroy_NonBlocking(const std::shared_ptr<WSListener::AsyncWebSocket>& socket) override;

};

#endif // WSListener_hpp
