#include "../stack/stack.h"

#include <string>
#include "gtest.h"


TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> stack(10));  // Проверка на создание стека с положительным размером
}

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


