//
// Created by Leonid  on 2019-06-12.
//

#ifndef AggregateTradesListener_hpp
#define AggregateTradesListener_hpp

#include "Model.hpp"
#include "WSEventListener.hpp"

/**
 * Listener for Aggregate Trade events
 */
class AggregateTradesListener : public WSEventListener<AggregateTrade> {
public:

  AggregateTradesListener(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& mapper)
    : WSEventListener<AggregateTrade>(mapper)
  {}

  void onEvent(const AggregateTrade::ObjectWrapper& trade) override {

    OATPP_LOGI("AggregateTrades", "%s - quantity=%s, price=%s, time=%d / firstTradeId=%d, lastTradeId=%d",
      trade->symbol->getData(),
      trade->quantity->getData(),
      trade->price->getData(),
      trade->tradeTime->getValue(),
      trade->firstTradeId->getValue(),
      trade->lastTradeId->getValue()
    );

  }

};

#endif // AggregateTradesListener_hpp
