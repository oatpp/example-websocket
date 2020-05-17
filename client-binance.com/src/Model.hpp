
#ifndef Model_hpp
#define Model_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * DTO representing "Aggregate Trade Stream" object from binance-exchange.
 * See https://github.com/binance-exchange/binance-official-api-docs/blob/master/web-socket-streams.md#aggregate-trade-streams
 */
class AggregateTrade : public oatpp::Object {

  DTO_INIT(AggregateTrade, Object)

  DTO_FIELD(String, eventType, "e");
  DTO_FIELD(Int64, eventTime, "E");
  DTO_FIELD(String, symbol, "s");
  DTO_FIELD(Int64, aggregateTradeId, "a");
  DTO_FIELD(String, price, "p");
  DTO_FIELD(String, quantity, "q");
  DTO_FIELD(Int64, firstTradeId, "f");
  DTO_FIELD(Int64, lastTradeId, "l");
  DTO_FIELD(Int64, tradeTime, "T");
  DTO_FIELD(Boolean, marketMaker, "m");
  DTO_FIELD(Boolean, ignore, "M");

};

/**
 * DTO representing "Trade Stream" object from binance-exchange.
 * See https://github.com/binance-exchange/binance-official-api-docs/blob/master/web-socket-streams.md#trade-streams
 */
class Trade : public oatpp::Object {

  DTO_INIT(Trade, Object)

  DTO_FIELD(String, eventType, "e");
  DTO_FIELD(Int64, eventTime, "E");
  DTO_FIELD(String, symbol, "s");
  DTO_FIELD(Int64, tradeId, "t");
  DTO_FIELD(String, price, "p");
  DTO_FIELD(String, quantity, "q");
  DTO_FIELD(Int64, buyerOrderId, "b");
  DTO_FIELD(Int64, sellerOrderId, "a");
  DTO_FIELD(Int64, tradeTime, "T");
  DTO_FIELD(Boolean, marketMaker, "m");
  DTO_FIELD(Boolean, ignore, "M");

};

/**
 * Nested object for Candlestick
 */
class Kline : public oatpp::Object {

  DTO_INIT(Kline, Object)

  DTO_FIELD(Int64, klineStartTime, "t");
  DTO_FIELD(Int64, klineCloseTime, "T");
  DTO_FIELD(String, symbol, "s");
  DTO_FIELD(String, interval, "i");

  DTO_FIELD(Int64, firstTradeId, "f");
  DTO_FIELD(Int64, lastTradeId, "L");

  DTO_FIELD(String, openPrice, "o");
  DTO_FIELD(String, closePrice, "c");
  DTO_FIELD(String, highPrice, "h");
  DTO_FIELD(String, lowPrice, "l");
  DTO_FIELD(String, baseAssetVolume, "v");

  DTO_FIELD(Int64, numberOfTrades, "n");
  DTO_FIELD(Boolean, isKlineClosed, "x");

  DTO_FIELD(String, quoteAssetVolume, "q");
  DTO_FIELD(String, takerBuyBaseAssetVolume, "V");
  DTO_FIELD(String, takerBuyQuoteAssetVolume, "Q");
  DTO_FIELD(String, ignore, "B");

};

/**
 * DTO representing "Kline/Candlestick Stream" object from binance-exchange.
 * See https://github.com/binance-exchange/binance-official-api-docs/blob/master/web-socket-streams.md#klinecandlestick-streams
 */
class Candlestick : public oatpp::Object {

  DTO_INIT(Candlestick, Object)

  DTO_FIELD(String, eventType, "e");
  DTO_FIELD(Int64, eventTime, "E");
  DTO_FIELD(String, symbol, "s");
  DTO_FIELD(Kline::ObjectWrapper, kline, "k");

};

#include OATPP_CODEGEN_END(DTO) ///< End DTO codegen section

#endif // Model_hpp
