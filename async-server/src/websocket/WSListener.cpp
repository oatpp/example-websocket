
#include "WSListener.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WSListener

oatpp::async::CoroutineStarter WSListener::onPing(const std::shared_ptr<AsyncWebSocket>& socket, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onPing");
  return socket->sendPongAsync(message);
}

oatpp::async::CoroutineStarter WSListener::onPong(const std::shared_ptr<AsyncWebSocket>& socket, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onPong");
  return nullptr; // do nothing
}

oatpp::async::CoroutineStarter WSListener::onClose(const std::shared_ptr<AsyncWebSocket>& socket, v_uint16 code, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onClose code=%d", code);
  return nullptr; // do nothing
}

oatpp::async::CoroutineStarter WSListener::readMessage(const std::shared_ptr<AsyncWebSocket>& socket, v_uint8 opcode, p_char8 data, oatpp::v_io_size size) {

  if(size == 0) { // message transfer finished

    auto wholeMessage = m_messageBuffer.toString();
    m_messageBuffer.setCurrentPosition(0);

    OATPP_LOGD(TAG, "onMessage message='%s'", wholeMessage->c_str());

    /* Send message in reply */
    return socket->sendOneFrameTextAsync( "Hello from oatpp!: " + wholeMessage);

  } else if(size > 0) { // message frame received
    m_messageBuffer.writeSimple(data, size);
  }

  return nullptr; // do nothing

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WSInstanceListener

std::atomic<v_int32> WSInstanceListener::SOCKETS(0);

void WSInstanceListener::onAfterCreate_NonBlocking(const std::shared_ptr<WSListener::AsyncWebSocket>& socket, const std::shared_ptr<const ParameterMap>& params) {

  SOCKETS ++;
  OATPP_LOGD(TAG, "New Incoming Connection. Connection count=%d", SOCKETS.load());

  /* In this particular case we create one WSListener per each connection */
  /* Which may be redundant in many cases */
  socket->setListener(std::make_shared<WSListener>());
}

void WSInstanceListener::onBeforeDestroy_NonBlocking(const std::shared_ptr<WSListener::AsyncWebSocket>& socket) {

  SOCKETS --;
  OATPP_LOGD(TAG, "Connection closed. Connection count=%d", SOCKETS.load());

}