//
// Created by Leonid  on 2019-06-12.
//

#ifndef Model_hpp
#define Model_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * DTO representing "Trade Stream" object from binance-exchange.
 * See https://github.com/binance-exchange/binance-official-api-docs/blob/master/web-socket-streams.md#trade-streams
 */
class Trade : public oatpp::data::mapping::type::Object {

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

#include OATPP_CODEGEN_END(DTO) ///< End DTO codegen section

#endif // Model_hpp
