#ifndef KlineCandlestickListener_hpp
#define KlineCandlestickListener_hpp

#include "Model.hpp"
#include "WSEventListener.hpp"

/**
 * Listener for Trade events
 */
class KlineCandlestickListener : public WSEventListener<oatpp::Object<Candlestick>> {
public:

  KlineCandlestickListener(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& mapper)
    : WSEventListener<oatpp::Object<Candlestick>>(mapper)
  {}

  void onEvent(const oatpp::Object<Candlestick>& obj) override {

    OATPP_LOGI("Kline/Candlesticks", "%s - startTime=%d, closeTime=%d / openPrice=%s, closePrice=%s, highPrice=%s, lowPrice=%s",
      obj->symbol->c_str(),
      *obj->kline->klineStartTime,
      *obj->kline->klineCloseTime,
      obj->kline->openPrice->c_str(),
      obj->kline->closePrice->c_str(),
      obj->kline->highPrice->c_str(),
      obj->kline->lowPrice->c_str()
    );

  }

};

#endif // KlineCandlestickListener_hpp
