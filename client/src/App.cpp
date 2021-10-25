
#include "WSListener.hpp"

#include "oatpp-websocket/WebSocket.hpp"
#include "oatpp-websocket/Connector.hpp"

#include "oatpp/network/tcp/client/ConnectionProvider.hpp"

#include <thread>

namespace {

  const char* TAG = "websocket-client";

  bool finished = false;

  void socketTask(const std::shared_ptr<oatpp::websocket::WebSocket>& websocket) {
    websocket->listen();
    OATPP_LOGD(TAG, "SOCKET CLOSED!!!");
    finished = true;
  }

}

void run() {

  OATPP_LOGI(TAG, "Application Started");

  auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared({"demo.piesocket.com", 80});

  auto connector = oatpp::websocket::Connector::createShared(connectionProvider);

  auto connection = connector->connect("v3/channel_1?api_key=oCdCMcMPQpbvNjUIzqtvF1d2X2okWpDQj4AwARJuAgtjhzKxVEjQU6IdCjwm&notify_self");

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
