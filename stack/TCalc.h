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
	void ToPostfix();			// ������������� �� infix � postfix
	double CalcPostfix();		// ������� � ����������� �����
	double Calc();				// ���������� �� ����������� ������

	double PerformOperation(double firstNum, double secondNum, char op);		// �������� �������� �������� �������

	int GetPriority(char op);	// ������ ���������� ��� ��������

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
			number += sim;		// �������� �����
		}
		else if (sim == ' ' && !number.empty())
		{
			double num = stod(number);
			StNum.Push(num);
			//cout << "��������� ����� � ����: " << num << endl; // ��� �������
			number = "";
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^' || sim == '~')
		{
			if (StNum.GetStartIndex() <2)
			{
				throw "������: ������������ ��������� ��� ��������";
			}
			double secondNum = StNum.Pop();
			double firstNum = StNum.Pop();
			double result = PerformOperation(firstNum, secondNum, postfix[i]);
			StNum.Push(result);
		}
		else if (!isspace(sim))
		{
			throw "������: ������������ ������ � ���������!";
		}
	}

	if (!number.empty()) {
		double val = stod(number);
		StNum.Push(val);
	}
	if (StNum.GetStartIndex() != 1) 
	{
		throw "������: �������� ���������� ��������� � ���������!";
	}
	/*if (StNum.GetStartIndex() != 0)
	{
		throw "������: �������� ���������� ��������� � ���������";
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
			number += sim;  // �������� ����� (������� ���������� �����)
			if (i == infix.size() - 1 || (!isdigit(infix[i + 1]) && infix[i + 1] != '.'))		// ��������, ��� ����� ����� ���� ������ ��� ������ ��������
			{
				postfix += number + " ";
				number = "";
				operandCount++;  // ��������� �������
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
				throw "������: ������ ����������� ������";
			}
			StChar.Pop();
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^') 
		{
			// �������� �� ������� �����
			if (sim == '-' && (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '+' ||
				infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/')) 
			{
				postfix += "0 ";  // ��������� 0 ��� �������� ������
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
			throw "������: ������������ ������ � ���������";
		}
	}
	while (!StChar.Empty())		// ���������� ���������� ��������� �� ����� � ����������� ���������
	{
		char op = StChar.Pop();
		if (op == '(') 
		{
			throw "������: ������ ����������� ������";
		}
		postfix += op;
		postfix += " ";
		operatorCount++;
	}
	if (operandCount - operatorCount != 1) 
	{
		throw "������: �������� ���������� ���������� � ���������!";
	}
}




double TCalc::Calc()
{
	std::string str = "(" + infix + ")";
	StNum.Clear();
	StChar.Clear();

	if (!StChar.Check(infix))			// ��������� ������������ ������ �� ��������
	{
		throw "������: ������������ ��������� (�������� ������)!";
	}

	for (int i = 0; i < str.size(); ++i)
	{
		char tmp = str[i];

		if (tmp == '(')
		{
			StChar.Push(tmp);		// �������� � ���� ����������
		}
		else if (tmp == '-')
		{
			if (i == 0 || str[i - 1] == '(')		// �������� �� ������� �����
			{
				str[i] = '_';		// ���������� ������� ����� ��� ��������� ������
			}
			else					// ��� �������� �����
			{
				while (!StChar.Empty() && GetPriority(StChar.Top()) >= GetPriority(tmp))		// ��������� ��� �������� �� ����� >= �� ����������
				{
					char op = StChar.Pop();
					double secondNum = StNum.Pop();
					double firstNum = StNum.Pop();
					StNum.Push(PerformOperation(firstNum, secondNum, op));
				}
				StChar.Push(tmp);			// ������ ����� � ���� ����������
			}
		}
		else if (isdigit(tmp) || tmp == '.')		// ����� ��� �����
		{
			size_t idx;
			double num = stod(str.substr(i), &idx);		// �������������� ������ � �����
			StNum.Push(num);							// ������ � ���� �����
			i += idx - 1;
		}
		else if (tmp == ')')
		{
			while (!StChar.Empty() && StChar.Top() != '(')		// ��������� ��� �������� � ������� ������� 
			{
				char op = StChar.Pop();
				double num2 = StNum.Pop();
				double num1 = StNum.Pop();
				StNum.Push(PerformOperation(num1, num2, op));
			}
			StChar.Pop();				// ������� ����������� ������
		}
		else if (tmp == '+' || tmp == '*' || tmp == '/' || tmp == '^')
		{			// ��������� ��� �������� � ����������� >= �������
			while (!StChar.Empty() && GetPriority(StChar.Top()) >= GetPriority(tmp)) {
				char op = StChar.Pop();
				double num2 = StNum.Pop();
				double num1 = StNum.Pop();
				StNum.Push(PerformOperation(num1, num2, op));
			}
			StChar.Push(tmp);
		}
		else if (tmp == '_')		// ����������� � ������������� ����� 
		{
			size_t idx;
			double num = std::stod(str.substr(i + 1), &idx);
			//double num = atof(&str[i + 1]);			// *** - ������ ������ - ����� ����
			//StNum.Push(-num);
			i += idx;
		}
	}
	/*if (StNum.GetStartIndex() != 0) {
		throw "������: �������� ���������� ��������� � ���������!";
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
			throw "������: ������� �� ����!";
		}
		return num1 / num2;
	case '^': return pow(num1, num2);
	default: throw "������: ����������� ��������!";
	}
}





//������ ��� ������ str = "(_123.45)":
//����� tmp == '_', ��� �������� atof(&str[i + 1]).
//��������& str[i + 1] ��������� �� ��������� "123.45)".
//
//atof ���������� ������ ) � ���������� 123.45.
//
//�������� ������������ � ���������� num.
//����� ����� ���������� num ���������� ������ 123.45.
//
//� ����� ����������� ���� �����(-num).
//����� �������, -123.45 ����� ������ ��� ���������� ��������.


