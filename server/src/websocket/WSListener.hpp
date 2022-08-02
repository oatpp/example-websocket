#ifndef WSListener_hpp
#define WSListener_hpp

#include "oatpp-websocket/ConnectionHandler.hpp"
#include "oatpp-websocket/WebSocket.hpp"


/**
 *
 */
class SocketHandle {
private:
    const oatpp::websocket::WebSocket* m_socket;
    std::mutex m_mutex;
public:

    SocketHandle(const oatpp::websocket::WebSocket* pSocket)
        : m_socket(pSocket)
    {}

    void socketWrite(const oatpp::String& text) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_socket)
            m_socket->sendOneFrameText(text);
    }

    void invalidate() {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_socket = nullptr;
    }

    bool isValid() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_socket != nullptr;
    }

};

/**
 * WebSocket listener listens on incoming WebSocket events.
 */
class WSListener : public oatpp::websocket::WebSocket::Listener {
private:
  static constexpr const char* TAG = "Server_WSListener";
private:
    std::shared_ptr<SocketHandle> m_socketHandle;
  /**
   * Buffer for messages. Needed for multi-frame messages.
   */
  oatpp::data::stream::BufferOutputStream m_messageBuffer;
public:

    WSListener(const std::shared_ptr<SocketHandle>& socketHandle)
        : m_socketHandle(socketHandle)
    {}

    ~WSListener() {
        m_socketHandle->invalidate();
    }

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
  void onClose(const WebSocket& socket, v_uint16 code, const oatpp::String& message) override;

  /**
   * Called on each message frame. After the last message will be called once-again with size == 0 to designate end of the message.
   */
  void readMessage(const WebSocket& socket, v_uint8 opcode, p_char8 data, oatpp::v_io_size size) override;

};

class WSTask {
private:
    std::shared_ptr<SocketHandle> m_handle;
public:
    WSTask(const std::shared_ptr<SocketHandle>& socketHandle);
};

/**
 * Listener on new WebSocket connections.
 */
class WSInstanceListener : public oatpp::websocket::ConnectionHandler::SocketInstanceListener {
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
  void onAfterCreate(const oatpp::websocket::WebSocket& socket, const std::shared_ptr<const ParameterMap>& params) override;

  /**
   *  Called before socket instance is destroyed.
   */
  void onBeforeDestroy(const oatpp::websocket::WebSocket& socket) override;

};

#endif // WSListener_hpp
