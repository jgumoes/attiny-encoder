#include <Arduino.h>
#include <unity.h>
#include "StateMachine.h"

void setUp(void){}
void tearDown(void){}

void test_initial_state() {
    StateMachine sm;
    TEST_ASSERT_EQUAL_UINT16(0, sm.clockwise);
    TEST_ASSERT_EQUAL_UINT16(0, sm.anticlockwise);
}

void test_clockwise_increment() {
    StateMachine sm;
    // Simulate a sequence that should increment clockwise
    sm.update(0b10); // previousState = 0b11, newState = 0b10
    TEST_ASSERT_EQUAL_UINT16(1, sm.clockwise);
    TEST_ASSERT_EQUAL_UINT16(0, sm.anticlockwise);
    TEST_ASSERT_EQUAL(0b01, sm.take());
    TEST_ASSERT_EQUAL(0, sm.clockwise);
    TEST_ASSERT_EQUAL(0, sm.take());
}

void test_anticlockwise_increment() {
    StateMachine sm;
    // Simulate a sequence that should increment anticlockwise
    sm.update(0b01); // previousState = 0b11, newState = 0b01
    TEST_ASSERT_EQUAL_UINT16(0, sm.clockwise);
    TEST_ASSERT_EQUAL_UINT16(1, sm.anticlockwise);
    TEST_ASSERT_EQUAL(0b10, sm.take());
    TEST_ASSERT_EQUAL(0, sm.take());
}

void test_multiple_transitions() {
    StateMachine sm;
    sm.update(0b10); // clockwise++
    sm.update(0b11); // anticlockwise++
    sm.update(0b01); // anticlockwise++
    sm.update(0b00); // anticlockwise++
    sm.update(0b01); // clockwise++
    TEST_ASSERT_EQUAL_UINT16(2, sm.clockwise);
    TEST_ASSERT_EQUAL_UINT16(3, sm.anticlockwise);

    TEST_ASSERT_EQUAL(0b11, sm.take());
    TEST_ASSERT_EQUAL(0b11, sm.take());
    TEST_ASSERT_EQUAL(0b10, sm.take());

    TEST_ASSERT_EQUAL(0, sm.take());
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