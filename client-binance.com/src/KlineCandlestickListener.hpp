//
// Created by Leonid  on 2019-06-12.
//

#ifndef KlineCandlestickListener_hpp
#define KlineCandlestickListener_hpp

#include "Model.hpp"
#include "WSEventListener.hpp"

/**
 * Listener for Trade events
 */
class KlineCandlestickListener : public WSEventListener<Candlestick> {
public:

  KlineCandlestickListener(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& mapper)
    : WSEventListener<Candlestick>(mapper)
  {}

  void onEvent(const Candlestick::ObjectWrapper& obj) override {

    OATPP_LOGI("Kline/Candlesticks", "%s - startTime=%d, closeTime=%d / openPrice=%s, closePrice=%s, highPrice=%s, lowPrice=%s",
      obj->symbol->getData(),
      obj->kline->klineStartTime->getValue(),
      obj->kline->klineCloseTime->getValue(),
      obj->kline->openPrice->getData(),
      obj->kline->closePrice->getData(),
      obj->kline->highPrice->getData(),
      obj->kline->lowPrice->getData()
    );

  }

};

#endif // KlineCandlestickListener_hpp
