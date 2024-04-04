//
// Created by George Thiruvathukal on 2/17/24.
//

#include <gtest/gtest.h>

#include "int_stack.hh"

TEST(IntStackTests, Initialization)
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    ASSERT_EQ(int_stack_capacity(&stack1), 10);
}

TEST(IntStackTests, PushToCapacityAndOverflow)
{
    // create stack that can hold 10 items
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // ensure it's full
    ASSERT_EQ(int_stack_size(&stack1), capacity);

    // try to add one more
    int result = int_stack_push(&stack1, capacity+1);

    // and make sure it is an overflow (error)
    ASSERT_FALSE(result);
}


TEST(IntStackTests, PushToCapcacityPopUntilUnderflow)
{
    // create stack that can hold 10 items [similar to previous test]
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // now drain it one item at a time, ensuring each item is the value expected
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }

    // try to remove from empty stack and ensure it fails
    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, PushPopPushPop)
{
    // create stack that can hold 10 items 
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // now drain it one item at a time, ensuring each item is the value expected
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }

    // try to remove from empty stack and ensure it fails
    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);

    // fill it again
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // now drain it one item at a time, ensuring each item is the value expected
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }

    // try to remove from empty stack and ensure it fails
    result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, DupSwap){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    int_stack_dup(&stack1);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);

    int_stack_swap(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-2);
}

TEST(IntStackTests, ArithmeticOperations)
{
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    int_stack_add(&stack1);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 45);

    int_stack_subtract(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 5);

    int_stack_mult(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 20);

    int_stack_div(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);

}

TEST(IntStackTests, Two_dupswap){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    int_stack_2dup(&stack1);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-2);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-2);

    int_stack_2swap(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-2);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-4);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-3);

}

TEST(IntStackTests, mod_divmod){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    int_stack_mod(&stack1);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);

    int_stack_divmod(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 4);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);

}

TEST(IntStackTests,rot_over){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    int_stack_rot(&stack1);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-2);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-3);

    int_stack_over(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-3);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-2);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, capacity-1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}