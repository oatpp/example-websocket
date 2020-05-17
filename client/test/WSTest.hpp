
#ifndef MY_PROJECT_WEBSOCKETTEST_HPP
#define MY_PROJECT_WEBSOCKETTEST_HPP


#include "oatpp-test/UnitTest.hpp"

class WSTest : public oatpp::test::UnitTest {
public:

  WSTest():UnitTest("TEST[WSTest]"){}
  void onRun() override;

};


#endif //MY_PROJECT_WEBSOCKETTEST_HPP
