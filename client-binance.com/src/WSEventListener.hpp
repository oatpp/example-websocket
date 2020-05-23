
#ifndef WSEventListener_hpp
#define WSEventListener_hpp

#include "WSListener.hpp"

#include "oatpp/core/data/mapping/ObjectMapper.hpp"

/**
 * Template event listener class.
 * Basically it waits for a message and deserializes message to a given DTO (model) class.
 * @tparam T
 */
template<class T>
class WSEventListener : public WSListener {
private:
  std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_mapper;
public:

  WSEventListener(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& mapper)
    : m_mapper(mapper)
  {}

  void onCompleteMessage(const oatpp::String& message) override {
    auto eventObject = m_mapper->readFromString<T>(message);
    onEvent(eventObject);
  }

  virtual void onEvent(const T& eventObject) = 0;

};

#endif // WSEventListener_hpp
