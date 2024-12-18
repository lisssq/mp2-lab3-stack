#include "../stack/TStackList.h"
//#include "../stack/TStack.h"
#include "../stack/TCalc.h"

#include <string>
#include "gtest.h"


TEST(TCalc, test1)
{
    TCalc calc;
    calc.SetInfix("3+5*2-8/4");
    calc.ToPostfix();
    ASSERT_EQ(calc.GetPostfix(), "3 5 2 * + 8 4 / - ");
    ASSERT_EQ(calc.Calc(), 11);
}


TEST(TCalc, test2)
{
    TCalc calc;
    calc.SetInfix("(5+9-8)*4-14/7+5");
    calc.ToPostfix();
    ASSERT_EQ(calc.GetPostfix(), "5 9 + 8 - 4 * 14 7 / - 5 + ");
    ASSERT_EQ(calc.Calc(), 27);
}
TEST(TCalc, test3)
{
    TCalc calc;
    calc.SetInfix("(3+5*(2-8/4)+7)*(4+3*2-(1+2))");
    calc.ToPostfix();
    ASSERT_EQ(calc.GetPostfix(), "3 5 2 8 4 / - * + 7 + 4 3 2 * + 1 2 + - * ");
    ASSERT_EQ(calc.Calc(), 70);
}

TEST(TCalc, test4)
{
    TCalc calc;
    calc.SetInfix("(((1+5)*7-9*(4/2)-1)+15-3)");
    calc.ToPostfix();
    ASSERT_EQ(calc.GetPostfix(), "1 5 + 7 * 9 4 2 / * - 1 - 15 + 3 - ");
    ASSERT_EQ(calc.Calc(), 35);
}

TEST(TCalc, test5)
{
    TCalc calc;
    calc.SetInfix("3+5*2^3-4");
    calc.ToPostfix();
    ASSERT_EQ(calc.GetPostfix(), "3 5 2 3 ^ * + 4 - ");
    ASSERT_EQ(calc.Calc(), 39);
}

TEST(TCalc, test6)
{
    TCalc calc;
    calc.SetInfix("(21/5)+9+18");
    calc.ToPostfix();
    ASSERT_EQ(calc.GetPostfix(), "21 5 / 9 + 18 + ");
    ASSERT_EQ(calc.Calc(), 31.2);
}

TEST(TCalc, test7)
{
    TCalc calc;
    calc.SetInfix("(25/8)+7.5-18*3/4-(((14+5)*7)-9)");
    calc.ToPostfix();
    ASSERT_EQ(calc.GetPostfix(), "25 8 / 7.5 + 18 3 * 4 / - 14 5 + 7 * 9 - - ");
    double a = (25.0 / 8) + 7.5 - 18 * 3.0 / 4 - (((14 + 5) * 7) - 9);
    //
    ASSERT_EQ(calc.Calc(), a);
}







// тесты стек на списке

TEST(TStack, can_initialize_stack)      // проверяем, можно ли создать стек
{
   
    ASSERT_NO_THROW(TStack<int> stack);
}

TEST(TStack, can_copy_existing_stack)
{
    
    TStack<int> stack;
    stack.Push(1);
    ASSERT_NO_THROW(TStack<int> stack1(stack));
}

TEST(TStack, stack_is_empty_after_creation)         // проверяем, что только что созданный стек пустой.
{
    TStack<int> stack;
    EXPECT_TRUE(stack.Empty());
}

TEST(TStack, stack_with_elements_is_not_empty)      // проверяем что стек не пустой 
{
   
    TStack<int> stack;
    stack.Push(1);
    EXPECT_FALSE(stack.Empty());
}

TEST(TStack, created_stack_is_not_full)             // проверяем что созданный пустой стек не полон
{
    TStack<int> stack;
    EXPECT_FALSE(stack.Full());
}

TEST(TStack, stack_with_few_elements_is_not_full)   // проверяем что наполненный стек не полон
{
    TStack<int> stack;
    stack.Push(5);
    stack.Push(10);
    EXPECT_FALSE(stack.Full());
}

TEST(TStack, stack_is_empty_after_popping_last_element)
{
    TStack<int> stack;
    stack.Push(2);
    stack.Pop();
    EXPECT_TRUE(stack.Empty());
}

TEST(TStack, pop_removes_top_element)
{
    TStack<int> stack;
    stack.Push(3);
    stack.Push(10);
    stack.Pop();
    EXPECT_EQ(stack.Top(), 3);
}

TEST(TStack, can_clear_stack)
{
    TStack<int> stack;
    stack.Push(5);
    stack.Clear();
    EXPECT_TRUE(stack.Empty());
}

TEST(TStack, identical_stacks_are_equal)
{
    TStack<int> stack;
    stack.Push(5);
    stack.Push(2);

    TStack<int> copiedStack(stack);
    EXPECT_TRUE(stack == copiedStack);
}

TEST(TStack, different_stacks_are_not_equal)
{
    TStack<int> stack;
    TStack<int> anotherStack;
    stack.Push(5);
    stack.Push(10);

    anotherStack.Push(10);
    anotherStack.Push(5);

    EXPECT_TRUE(stack != anotherStack);
}

TEST(TStack, can_compare_equal_stacks) {
    TStack<int> stack1;
    TStack<int> stack2;
    stack1.Push(10);
    stack2.Push(10);
    EXPECT_TRUE(stack1 == stack2);
}



TEST(TStack, throws_when_popping_from_empty_stack)
{
    TStack<int> stack;
    EXPECT_ANY_THROW(stack.Pop());
}

TEST(TStack, can_push_when_memory_available)
{
    TStack<int> stack;
    ASSERT_NO_THROW(stack.Push(3));
}

TEST(TStack, copied_stack_is_identical_to_original)
{
    TStack<int> stack;
    stack.Push(1);
    stack.Push(2);
    TStack<int> copiedStack(stack);
    EXPECT_TRUE(stack == copiedStack);
}

TEST(TStack, stacks_with_different_elements_are_not_equal)
{
    TStack<int> stack;
    TStack<int> anotherStack;
    stack.Push(1);
    anotherStack.Push(2);
    EXPECT_TRUE(stack != anotherStack);
}























// тесты стека на массиве
/*
TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> stack(10));  // Проверка на создание стека с положительным размером
}

TEST(TStack, can_push_and_pop_elements)
{
    TStack<int> stack(5);
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    ASSERT_EQ(stack.Pop(), 3);  // Проверка на правильность извлечения последнего элемента
    ASSERT_EQ(stack.Pop(), 2);  // Проверка на правильность извлечения следующего элемента
    ASSERT_EQ(stack.Pop(), 1);  // Проверка на правильность извлечения первого элемента
}


TEST(TStack, can_check_if_stack_is_empty)
{
    TStack<int> stack(5);
    ASSERT_TRUE(stack.Empty());  // Проверка на пустоту стека
    stack.Push(1);
    ASSERT_FALSE(stack.Empty());  // Проверка на непустоту стека
}


TEST(TStack, can_peek_at_top_element)
{
    TStack<int> stack(5);
    stack.Push(10);
    ASSERT_EQ(stack.Top(), 10);  // Проверка на получение верхнего элемента без его извлечения
}


TEST(TStack, can_copy_stack)
{
    TStack<int> stack1(5);
    stack1.Push(1);
    stack1.Push(2);
    TStack<int> stack2 = stack1;  // Использование конструктора копирования

    ASSERT_EQ(stack2.Pop(), 2);  // Проверка на корректность копирования стека
    ASSERT_EQ(stack2.Pop(), 1);
}


TEST(TStack, can_assign_stack)
{
    TStack<int> stack1(5);
    stack1.Push(1);
    stack1.Push(2);
    TStack<int> stack2(5);
    stack2 = stack1;  // Присваивание стека

    ASSERT_EQ(stack2.Pop(), 2);  // Проверка на корректность присваивания стека
    ASSERT_EQ(stack2.Pop(), 1);
}


TEST(TStack, cant_create_too_large_size)
{
    ASSERT_ANY_THROW(TStack<int> a(1000000));
}

TEST(TStack, can_clear_stack)
{
    TStack<int> s(5);
    s.Push(1);
    s.Push(2);
    s.Clear();
    EXPECT_TRUE(s.Empty());

}

TEST(TStack, stacks_with_different_sizes_are_not_equal1)
{
    TStack<int> s1(8);
    TStack<int> s2(2);
    EXPECT_FALSE(s1 == s2);

}
*/