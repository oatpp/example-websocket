
#include "WSListener.hpp"

#include "TradesListener.hpp"

#include "oatpp-websocket/WebSocket.hpp"
#include "oatpp-websocket/Connector.hpp"

#include "oatpp-mbedtls/client/ConnectionProvider.hpp"
#include "oatpp-mbedtls/Config.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include <thread>

namespace {

  const char* TAG = "websocket-client-binance.com";

}

/**
 * Connect to "trade" tream and listen for trading events
 * @param connector
 * @param objectMapper
 */
void readTrades(const std::shared_ptr<oatpp::websocket::Connector>& connector,
                const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper)
{

  auto connection = connector->connect("ws/bnbbtc@trade");

  oatpp::websocket::WebSocket socket(connection, true /* maskOutgoingMessages must be true for clients */);

  socket.setListener(std::make_shared<TradesListener>(objectMapper));

  socket.listen();

}

// TODO - add other stream tasks here

void run() {

  OATPP_LOGI(TAG, "Application Started");

  /* mbedtls config */
  auto config = oatpp::mbedtls::Config::createDefaultClientConfigShared();

  /* secure connection provider for stream.binance.com */
  auto connectionProvider = oatpp::mbedtls::client::ConnectionProvider::createShared(config, "stream.binance.com", 9443);

  /* websocket connector */
  auto connector = oatpp::websocket::Connector::createShared(connectionProvider);

  /* object mapper for DTO objects */
  auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

  /* start trades read task in the thread */
  std::thread tradesThread(readTrades, connector, objectMapper);

  /* join tasks */
  tradesThread.join();

}

int main() {
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
}
