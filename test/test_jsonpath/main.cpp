#include <unity.h>
#include <jsonpath.h>


void test_buildpath() {
    // arrange
    JsonPath path = JsonPath("object.fields#1");
    // act
    TEST_MESSAGE();
    // assert
}

void setup() {
    delay(2000);
    
    UNITY_BEGIN();
    RUN_TEST(test_buildpath);
}

void loop() {}