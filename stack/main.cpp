// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <locale.h>
#include"TCalc.h"
#include "TStack.h"


//using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    // создание стека с размером 5

   // double a = 1.0 / 2;
    //std::cout << a;
    TStack<int> stack(5);
    int k = 1;
    for (int i = 0; i < 5; i++)
    {
        stack.Push(k);
        k = k + 3;
    }

    std::cout << "Содержимое стека: ";
    std::cout << stack << std::endl;
    std::cout << "----------" << std::endl;


    TCalc calculator;


    calculator.SetInfix("(3 + 5 * (2 - 8 / 4) + 7)* (4 + 3 * 2 - (1 + 2))");
    std::cout << "Инфиксное представление: " << calculator.GetInfix() << std::endl;
    calculator.ToPostfix();
    std::cout << "Постфиксное представление: " << calculator.GetPostfix() << std::endl;
    // ожижается ответ:   35284/-*+7+432*+12+-*
    // 
    // вычисляем значение постфиксного выражения и выводим результат
    double result = calculator.CalcPostfix();
    double res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    std::cout << "Результат выражения через Calc(): " << res2 << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "----------" << std::endl;






    calculator.SetInfix("3+5*2-8/4");
    std::cout << "Инфиксное представление: " << calculator.GetInfix() << std::endl;
    calculator.ToPostfix();
    std::cout << "Постфиксное представление: " << calculator.GetPostfix() << std::endl;
    // ожидается ответ:   352*+84/-

    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    std::cout << "Результат выражения через Calc(): " << res2 << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "----------" << std::endl;



/*

    calculator.SetInfix("(((1+5)*7-9*(4/2)-1)+15-3)");
    std::cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    std::cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  15+7*942/*-1-15+3-

    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    std::cout << "Результат выражения через Calc(): " << res2 << endl;
    std::cout << "----------" << endl;
    std::cout << "----------" << endl;




    calculator.SetInfix("3+5*2^3-4");
    std::cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    std::cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  3 5 2 3 ^ * + 4 -
    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    std::cout << "Результат выражения через Calc(): " << res2 << endl;
    std::cout << "----------" << endl;
    std::cout << "----------" << endl;






    calculator.SetInfix("(21/5)+9+18");
    std::cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    std::cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  21 5 / 9 + 18 +
    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    std::cout << "Результат выражения через Calc(): " << res2 << endl;
    std::cout << "----------" << endl;
    std::cout << "----------" << endl;






    calculator.SetInfix("(21/5)+9-18");
    std::cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    std::cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  21 5 / 9 + 18 +
    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    std::cout << "Результат выражения через Calc(): " << res2 << endl;
    std::cout << "----------" << endl;
    std::cout << "----------" << endl;

    



    calculator.SetInfix("-5+3*(-2-4)");
    std::cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    std::cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  21 5 / 9 + 18 +
    // вычисляем значение постфиксного выражения и выводим результат
    //result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    std::cout << "Результат выражения через Calc(): " << res2 << endl;
    std::cout << "----------" << endl;
    std::cout << "----------" << endl;
    */



    //calculator.SetInfix("-5+3*(-2-4)");
    //cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    //calculator.ToPostfix();
    //cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    //// ожидается ответ:  -5 3 2 4 - - * +
    //// вычисляем значение постфиксного выражения и выводим результат
    //result = calculator.CalcPostfix();
    //cout << "Результат выражения: " << result << endl;
    //cout << "----------" << endl;

    return 0;
}