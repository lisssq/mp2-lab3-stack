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


    TCalc calculator;

    //calculator.SetInfix("4 * (7 + 3) - 6 / 2");
    calculator.SetInfix("(3 + 5 * (2 - 8 / 4) + 7)* (4 + 3 * 2 - (1 + 2))");

    calculator.ToPostfix();

    cout << "����������� �������������: " << calculator.GetPostfix() << endl;

    // ��������� �������� ������������ ��������� � ������� ���������
    double result = calculator.CalcPostfix();
    cout << "���������: " << result << endl;
    
    return 0;
}