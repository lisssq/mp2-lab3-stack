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
    // �������� ����� � �������� 5
    TStack<int> stack(5);
    int k = 1;
    for (int i = 0; i < 5; i++)
    {
        stack.Push(k);
        k = k + 3;
    }

    cout << "���������� �����: ";
    cout << stack << endl;
    cout << "----------" << endl;


    TCalc calculator;

    
    calculator.SetInfix("(3 + 5 * (2 - 8 / 4) + 7)* (4 + 3 * 2 - (1 + 2))");
    cout << "��������� �������������: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    // ��������� �����:   35284/-*+7+432*+12+-*
    // 
    // ��������� �������� ������������ ��������� � ������� ���������
    double result = calculator.CalcPostfix();
    double res2 = calculator.Calc();
    cout << "��������� ���������: " << result << endl;
    cout << "��������� ��������� ����� Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;






    calculator.SetInfix("3+5*2-8/4");
    cout << "��������� �������������: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    // ��������� �����:   352*+84/-

    // ��������� �������� ������������ ��������� � ������� ���������
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "��������� ���������: " << result << endl;
    cout << "��������� ��������� ����� Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;





    calculator.SetInfix("(((1+5)*7-9*(4/2)-1)+15-3)");
    cout << "��������� �������������: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    // ��������� �����:  15+7*942/*-1-15+3-

    // ��������� �������� ������������ ��������� � ������� ���������
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "��������� ���������: " << result << endl;
    cout << "��������� ��������� ����� Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;




    calculator.SetInfix("3+5*2^3-4");
    cout << "��������� �������������: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    // ��������� �����:  3 5 2 3 ^ * + 4 -
    // ��������� �������� ������������ ��������� � ������� ���������
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "��������� ���������: " << result << endl;
    cout << "��������� ��������� ����� Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;

    




    calculator.SetInfix("(21/5)+9+18");
    cout << "��������� �������������: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    // ��������� �����:  21 5 / 9 + 18 +
    // ��������� �������� ������������ ��������� � ������� ���������
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "��������� ���������: " << result << endl;
    cout << "��������� ��������� ����� Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;






    calculator.SetInfix("(21/5)+9-18");
    cout << "��������� �������������: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    // ��������� �����:  21 5 / 9 + 18 +
    // ��������� �������� ������������ ��������� � ������� ���������
    result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    cout << "��������� ���������: " << result << endl;
    cout << "��������� ��������� ����� Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;





    calculator.SetInfix("-5+3*(-2-4)");
    cout << "��������� �������������: " << calculator.GetInfix() << endl;
    calculator.ToPostfix();
    cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    // ��������� �����:  21 5 / 9 + 18 +
    // ��������� �������� ������������ ��������� � ������� ���������
    //result = calculator.CalcPostfix();
    res2 = calculator.Calc();
    //cout << "��������� ���������: " << result << endl;
    cout << "��������� ��������� ����� Calc(): " << res2 << endl;
    cout << "----------" << endl;
    cout << "----------" << endl;

    //calculator.SetInfix("-5+3*(-2-4)");
    //cout << "��������� �������������: " << calculator.GetInfix() << endl;
    //calculator.ToPostfix();
    //cout << "����������� �������������: " << calculator.GetPostfix() << endl;
    //// ��������� �����:  -5 3 2 4 - - * +
    //// ��������� �������� ������������ ��������� � ������� ���������
    //result = calculator.CalcPostfix();
    //cout << "��������� ���������: " << result << endl;
    //cout << "----------" << endl;

    return 0;
}