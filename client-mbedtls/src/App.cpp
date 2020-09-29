
#include "WSListener.hpp"

#include "oatpp-websocket/WebSocket.hpp"
#include "oatpp-websocket/Connector.hpp"

#include "oatpp-mbedtls/client/ConnectionProvider.hpp"
#include "oatpp-mbedtls/Config.hpp"

#include <thread>

namespace {

  const char* TAG = "websocket-client-mbedtls";

  bool finished = false;

  void socketTask(const std::shared_ptr<oatpp::websocket::WebSocket>& websocket) {
    websocket->listen();
    OATPP_LOGD(TAG, "SOCKET CLOSED!!!");
    finished = true;
  }

}

void run() {

  OATPP_LOGI(TAG, "Application Started");

  auto config = oatpp::mbedtls::Config::createDefaultClientConfigShared();

  auto connectionProvider = oatpp::mbedtls::client::ConnectionProvider::createShared(config, {"echo.websocket.org", 443});

  auto connector = oatpp::websocket::Connector::createShared(connectionProvider);

  auto connection = connector->connect("/");

  OATPP_LOGI(TAG, "Connected");

  auto socket = oatpp::websocket::WebSocket::createShared(connection, true /* maskOutgoingMessages must be true for clients */);

  std::mutex socketWriteMutex;

  socket->setListener(std::make_shared<WSListener>(socketWriteMutex));

  std::thread thread(socketTask, socket);

  while(!finished) {
    {
      OATPP_LOGD(TAG, "sending message...");
      std::lock_guard<std::mutex> lock(socketWriteMutex);
      socket->sendOneFrameText("hello");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  thread.join();

}

int main() {
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
}
