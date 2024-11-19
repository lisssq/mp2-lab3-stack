// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <locale.h>
#include "stack.h"


using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    // создание стека с размером 5
    TStack<int> stack(5);
    int k = 1;
    for (int i = 0; i < 5; i++)
    {
        stack.Push(k);
        k = k + 3;
    }

    cout << "Содержимое стека: ";
    cout << stack << endl;
    cout << "----------" << endl;


    TCalc calculator;


    calculator.SetInfix("(3 + 5 * (2 - 8 / 4) + 7)* (4 + 3 * 2 - (1 + 2))");
    cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожижается ответ:   35284/-*+7+432*+12+-*
    // 
    // вычисляем значение постфиксного выражения и выводим результат
    double result = calculator.CalcPostfix();
    double res2 = calculator.Calc();
    cout << "Результат выражения: " << result << endl;
    cout << "Результат выражения через Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;






    calculator.SetInfix("3+5*2-8/4");
    cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:   352*+84/-

    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "Результат выражения: " << result << endl;
    cout << "Результат выражения через Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;





    calculator.SetInfix("(((1+5)*7-9*(4/2)-1)+15-3)");
    cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  15+7*942/*-1-15+3-

    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "Результат выражения: " << result << endl;
    cout << "Результат выражения через Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;




    calculator.SetInfix("3+5*2^3-4");
    cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  3 5 2 3 ^ * + 4 -
    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "Результат выражения: " << result << endl;
    cout << "Результат выражения через Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;






    calculator.SetInfix("(21/5)+9+18");
    cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  21 5 / 9 + 18 +
    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "Результат выражения: " << result << endl;
    cout << "Результат выражения через Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;






    calculator.SetInfix("(21/5)+9-18");
    cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  21 5 / 9 + 18 +
    // вычисляем значение постфиксного выражения и выводим результат
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "Результат выражения: " << result << endl;
    cout << "Результат выражения через Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;





    calculator.SetInfix("-5+3*(-2-4)");
    cout << "Инфиксное представление: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "Постфиксное представление: " << calculator.GetPostfix() << endl;
    // ожидается ответ:  21 5 / 9 + 18 +
    // вычисляем значение постфиксного выражения и выводим результат
    //result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "Результат выражения: " << result << endl;
    cout << "Результат выражения через Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;

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