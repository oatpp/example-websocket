//
// Created by Leonid  on 2019-06-07.
//

#include "WSListener.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WSListener

void WSListener::onPing(const WebSocket& socket, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onPing");
  socket.sendPong(message);
}

void WSListener::onPong(const WebSocket& socket, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onPong");
}

void WSListener::onClose(const WebSocket& socket, v_word16 code, const oatpp::String& message) {
  OATPP_LOGD(TAG, "onClose code=%d", code);
}

void WSListener::readMessage(const WebSocket& socket, p_char8 data, oatpp::data::v_io_size size) {

  if(size == 0) { // message transfer finished

    auto wholeMessage = m_messageBuffer.toString();
    m_messageBuffer.clear();
    onCompleteMessage(wholeMessage);

  } else if(size > 0) { // message frame received
    m_messageBuffer.write(data, size);
  }

}
