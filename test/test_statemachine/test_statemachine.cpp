#include <Arduino.h>
#include <unity.h>
#include "StateMachine.h"

void setUp(void){
    StateMachine::previousState = 0b11;
}
void tearDown(void){}

void test_initial_state() {
    using namespace StateMachine;
    TEST_ASSERT_EQUAL_UINT16(0, clockwise);
    TEST_ASSERT_EQUAL_UINT16(0, anticlockwise);
}

void test_clockwise_increment() {
    using namespace StateMachine;
    // Simulate a sequence that should increment clockwise
    update(0b10); // previousState = 0b11, newState = 0b10
    TEST_ASSERT_EQUAL_UINT16(1, clockwise);
    TEST_ASSERT_EQUAL_UINT16(0, anticlockwise);
    TEST_ASSERT_EQUAL(0b01, take());
    TEST_ASSERT_EQUAL(0, clockwise);
    TEST_ASSERT_EQUAL(0, take());
}

void test_anticlockwise_increment() {
    using namespace StateMachine;
    // Simulate a sequence that should increment anticlockwise
    update(0b01); // previousState = 0b11, newState = 0b01
    TEST_ASSERT_EQUAL_UINT16(0, clockwise);
    TEST_ASSERT_EQUAL_UINT16(1, anticlockwise);
    TEST_ASSERT_EQUAL(0b10, take());
    TEST_ASSERT_EQUAL(0, take());
}

void test_multiple_transitions() {
    using namespace StateMachine;
    update(0b10); // clockwise++
    update(0b11); // anticlockwise++
    update(0b01); // anticlockwise++
    update(0b00); // anticlockwise++
    update(0b01); // clockwise++
    TEST_ASSERT_EQUAL_UINT16(2, clockwise);
    TEST_ASSERT_EQUAL_UINT16(3, anticlockwise);

    TEST_ASSERT_EQUAL(0b11, take());
    TEST_ASSERT_EQUAL(0b11, take());
    TEST_ASSERT_EQUAL(0b10, take());

    TEST_ASSERT_EQUAL(0, take());
}

void RUN_UNITY_TESTS(){
  UNITY_BEGIN();
    RUN_TEST(test_initial_state);
    RUN_TEST(test_clockwise_increment);
    RUN_TEST(test_anticlockwise_increment);
    RUN_TEST(test_multiple_transitions);
  UNITY_END();
}

#ifdef native_env
void WinMain(){
  RUN_UNITY_TESTS();
}
#endif