
#include "WSListener.hpp"
#include <thread>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WSListener

void WSListener::onPing(const WebSocket& socket, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onPing");
  socket.sendPong(message);
}

void WSListener::onPong(const WebSocket& socket, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onPong");
}

void WSListener::onClose(const WebSocket& socket, v_uint16 code, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onClose code=%d", code);
}

void WSListener::readMessage(const WebSocket& socket, v_uint8 opcode, p_char8 data, oatpp::v_io_size size) {

  if(size == 0) { // message transfer finished

    auto wholeMessage = m_messageBuffer.toString();
    m_messageBuffer.setCurrentPosition(0);

    OATPP_LOGD(TAG, "onMessage message='%s'", wholeMessage->c_str());

    /* Send message in reply */
    /* USE SOCKET HANDLE INSTEAD OF A BARE SOCKET!!! */
    m_socketHandle->socketWrite( "Hello from oatpp!: " + wholeMessage);

  } else if(size > 0) { // message frame received
    m_messageBuffer.writeSimple(data, size);
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WSInstanceListener

std::atomic<v_int32> WSInstanceListener::SOCKETS(0);

void WSInstanceListener::onAfterCreate(const oatpp::websocket::WebSocket& socket, const std::shared_ptr<const ParameterMap>& params) {

  SOCKETS ++;
  OATPP_LOGD(TAG, "New Incoming Connection. Connection count=%d", SOCKETS.load());

  /* In this particular case we create one WSListener per each connection */
  /* Which may be redundant in many cases */

  auto socketHandle = std::make_shared<SocketHandle>(&socket);
  socket.setListener(std::make_shared<WSListener>(socketHandle));

  std::thread t([socketHandle]{
      OATPP_LOGD("Task", "tread started");
      while (socketHandle->isValid()) {
          socketHandle->socketWrite("Hello From Thread!!!");
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
      OATPP_LOGD("Task", "tread stopped");
  });

  t.detach();

}

void WSInstanceListener::onBeforeDestroy(const oatpp::websocket::WebSocket& socket) {

  SOCKETS --;
  OATPP_LOGD(TAG, "Connection closed. Connection count=%d", SOCKETS.load());

}