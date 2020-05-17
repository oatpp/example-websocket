
#ifndef TradesListener_hpp
#define TradesListener_hpp

#include "Model.hpp"
#include "WSEventListener.hpp"

/**
 * Listener for Trade events
 */
class TradesListener : public WSEventListener<Trade> {
public:

  TradesListener(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& mapper)
    : WSEventListener<Trade>(mapper)
  {}

  void onEvent(const Trade::ObjectWrapper& trade) override {

    OATPP_LOGI("Trades", "%s - quantity=%s, price=%s, time=%d",
      trade->symbol->c_str(),
      trade->quantity->c_str(),
      trade->price->c_str(),
      *trade->tradeTime
    );

  }

};

#endif // TradesListener_hpp
