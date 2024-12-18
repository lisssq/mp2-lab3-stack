#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
//#include "TStack.h"
#include "TStackList.h"

//using namespace std;
//const int MAX_SZ = 10000;



class TCalc
{
	std::string infix;
	std::string postfix;
	TStack <double> StNum;
	TStack <char> StChar;

public:
	void ToPostfix();			// преобразовать из infix в postfix
	double CalcPostfix();		// перевод в постфиксную форму
	double Calc();				// вычисления по постфиксной записи

	double PerformOperation(double firstNum, double secondNum, char op);		// алгоритм обратной польской нотации

	int GetPriority(char op);	// выдача приоритета для операций

	void SetInfix(std::string stroka)
	{
		infix = stroka;
	}
	std::string GetPostfix()
	{
		return postfix;
	}
	std::string GetInfix()
	{
		return infix;
	}
};




int TCalc::GetPriority(char op)
{
	if (op == '+' || op == '-')
	{
		return 1;
	}
	if (op == '*' || op == '/')
	{
		return 2;
	}
	if (op == '^')
	{
		return 3;
	}
	return 0;
}



double TCalc::CalcPostfix()
{
	StNum.Clear();
	std::string number = "";

	for (int i = 0; i < postfix.size(); i++)
	{
		char sim = postfix[i];

		if (isdigit(sim) || sim == '.')
		{
			number += sim;		// собираем число
		}
		else if (sim == ' ' && !number.empty())
		{
			double num = stod(number);
			StNum.Push(num);
			//cout << "Добавлено число в стек: " << num << endl; // Для отладки
			number = "";
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^' || sim == '~')
		{
			if (StNum.GetStartIndex() <2)
			{
				throw "Ошибка: недостаточно операндов для операции";
			}
			double secondNum = StNum.Pop();
			double firstNum = StNum.Pop();
			double result = PerformOperation(firstNum, secondNum, postfix[i]);
			StNum.Push(result);
		}
		else if (!isspace(sim))
		{
			throw "Ошибка: недопустимый символ в выражении!";
		}
	}

	if (!number.empty()) {
		double val = stod(number);
		StNum.Push(val);
	}
	if (StNum.GetStartIndex() != 1) 
	{
		throw "Ошибка: неверное количество операндов в выражении!";
	}
	/*if (StNum.GetStartIndex() != 0)
	{
		throw "Ошибка: неверное количество операндов в выражении";
	}*/
	double result = StNum.Pop();
	return result;
}



void TCalc::ToPostfix()
{
	postfix = "";
	StChar.Clear();
	std::string number = "";
	int operandCount = 0;
	int operatorCount = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		char sim = infix[i];
		if (isdigit(sim) || sim == '.')
		{
			number += sim;  // собираем число (включая десятичную точку)
			if (i == infix.size() - 1 || (!isdigit(infix[i + 1]) && infix[i + 1] != '.'))		// проверка, что после числа идет пробел или символ операции
			{
				postfix += number + " ";
				number = "";
				operandCount++;  // добавляем операнд
			}
		}
		else if (sim == '(')
		{
			StChar.Push(sim);
		}
		else if (sim == ')')
		{
			//bool matched = false;
			while (!StChar.Empty() && StChar.Top() != '(')
			{
				postfix += StChar.Pop();
				postfix += " ";
				//matched = true;
				operatorCount++;
			}
			if (StChar.Empty())
			{
				throw "Ошибка: лишняя закрывающая скобка";
			}
			StChar.Pop();
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^') 
		{
			// Проверка на унарный минус
			if (sim == '-' && (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '+' ||
				infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/')) 
			{
				postfix += "0 ";  // Добавляем 0 для унарного минуса
			}
			while (!StChar.Empty() && GetPriority(StChar.Top()) >= GetPriority(sim))
			{
				postfix += StChar.Pop();
				postfix += " ";
				operatorCount++;
			}
			StChar.Push(sim);
		}
		else if (!isspace(sim))
		{
			throw "Ошибка: недопустимый символ в выражении";
		}
	}
	while (!StChar.Empty())		// перемещаем оставшиеся операторы из стека в постфиксное выражение
	{
		char op = StChar.Pop();
		if (op == '(') 
		{
			throw "Ошибка: лишняя открывающая скобка";
		}
		postfix += op;
		postfix += " ";
		operatorCount++;
	}
	if (operandCount - operatorCount != 1) 
	{
		throw "Ошибка: неверное количество операторов и операндов!";
	}
}




double TCalc::Calc()
{
	std::string str = "(" + infix + ")";
	StNum.Clear();
	StChar.Clear();

	if (!StChar.Check(infix))			// проверяем корректность скобок на парность
	{
		throw "ошибка: некорректное выражение (непарные скобки)!";
	}

	for (int i = 0; i < str.size(); ++i)
	{
		char tmp = str[i];

		if (tmp == '(')
		{
			StChar.Push(tmp);		// помещаем в стек операторов
		}
		else if (tmp == '-')
		{
			if (i == 0 || str[i - 1] == '(')		// проверка на унарный минус
			{
				str[i] = '_';		// обозначаем унарный минус как отдельный символ
			}
			else					// это бинарный минус
			{
				while (!StChar.Empty() && GetPriority(StChar.Top()) >= GetPriority(tmp))		// выполняем все операции из стека >= по приоритету
				{
					char op = StChar.Pop();
					double secondNum = StNum.Pop();
					double firstNum = StNum.Pop();
					StNum.Push(PerformOperation(firstNum, secondNum, op));
				}
				StChar.Push(tmp);			// кладем минус в стек операторов
			}
		}
		else if (isdigit(tmp) || tmp == '.')		// цифра или точка
		{
			size_t idx;
			double num = stod(str.substr(i), &idx);		// преобразование строки в число
			StNum.Push(num);							// кладем в стек чисел
			i += idx - 1;
		}
		else if (tmp == ')')
		{
			while (!StChar.Empty() && StChar.Top() != '(')		// вычисляем все операции в текущих скобках 
			{
				char op = StChar.Pop();
				double num2 = StNum.Pop();
				double num1 = StNum.Pop();
				StNum.Push(PerformOperation(num1, num2, op));
			}
			StChar.Pop();				// убираем открывающую скобку
		}
		else if (tmp == '+' || tmp == '*' || tmp == '/' || tmp == '^')
		{			// выполняем все операции с приоритетом >= текущей
			while (!StChar.Empty() && GetPriority(StChar.Top()) >= GetPriority(tmp)) {
				char op = StChar.Pop();
				double num2 = StNum.Pop();
				double num1 = StNum.Pop();
				StNum.Push(PerformOperation(num1, num2, op));
			}
			StChar.Push(tmp);
		}
		else if (tmp == '_')		// преобразуем в отрицательное число 
		{
			size_t idx;
			double num = std::stod(str.substr(i + 1), &idx);
			//double num = atof(&str[i + 1]);			// *** - пример работы - внизу кода
			//StNum.Push(-num);
			i += idx;
		}
	}
	/*if (StNum.GetStartIndex() != 0) {
		throw "Ошибка: неверное количество операндов в выражении!";
	}*/
	return StNum.Pop();
}



double TCalc::PerformOperation(double num1, double num2, char op) {
	switch (op) {
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/':
		if (num2 == 0)
		{
			throw "Ошибка: деление на ноль!";
		}
		return num1 / num2;
	case '^': return pow(num1, num2);
	default: throw "Ошибка: неизвестная операция!";
	}
}





//Пример для строки str = "(_123.45)":
//Когда tmp == '_', код вызывает atof(&str[i + 1]).
//Значение& str[i + 1] указывает на подстроку "123.45)".
//
//atof игнорирует символ ) и возвращает 123.45.
//
//Значение записывается в переменную num.
//После этого переменная num становится равной 123.45.
//
//К числу добавляется знак минус(-num).
//Таким образом, -123.45 будет готово для дальнейших действий.


