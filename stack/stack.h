#pragma once
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

const int MAX_SZ = 10000;


template<class T>
class TStack
{
	T* pMem;
	int MaxSize, Num;

public:

	TStack(int _MaxSize = 10);			//����������� �������������
	~TStack();							//����������
	TStack(const TStack& s);			//����������� �����������

	int GetSize();					//������ �����
	
	int GetStartIndex();			// ������ Num
	

	TStack& operator=(const TStack<T>& s); //�������� ������������
	bool operator==(const TStack &s) const;		//��������� �����
	bool operator!=(const TStack &s) const;		//��������� �� �����


	T Pop();
	void Push(T val);						// ���������� �������� � ����
	bool Check(string str);
	void Clear();							// ������� �����
	


	T Top() const;							// ���������� �� ������� �����
	bool Empty() const;						// �������� �� ������� (����� ��-�� = -1)
	bool Full() const;						// �������� �� ������������� (����.���� - 1)


	friend istream& operator>>(istream& in, TStack& s)
	{
		T val;
		cout << "������� �������� ����� (������� 0 ��� ����������): ";
		while (in >> val && val != 0) {
			s.Push(val);
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, const TStack& s)
	{
		for (int i = 0; i <= s.Num; i++) {
			out << s.pMem[i] << " ";
		}
		return out;
	}


};


template <class T>
TStack <T>::TStack(int _MaxSize)		// ����������� �������������
{
	if (_MaxSize<0 || _MaxSize>MAX_SZ)
	{
		//throw - 1;
		throw "������������ ������ �����";
	}
	MaxSize = _MaxSize;
	Num = -1;
	pMem = new T[MaxSize];
}


template <class T>
TStack<T>::~TStack()					// ����������
{
	if (pMem)
	{
		delete[] pMem;
		pMem = nullptr;
	}
}


template <class T>
TStack<T>::TStack(const TStack& s)		// ����������� �����������
{
	if (s.MaxSize<0 || s.MaxSize>MAX_SZ || s.Num < -1 || s.Num >= s.MaxSize)
	{
		throw "������������ ������ �����";
	}
	MaxSize = s.MaxSize;
	Num = s.Num;
	pMem = new T[MaxSize];
	for (int i = 0; i <= Num; i++)
	{
		pMem[i] = s.pMem[i];
	}
}


template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& s) 	// �������� ������������
{
	if (this != &s)
	{
		if (MaxSize != s.MaxSize)
		{
			delete[] pMem;
			MaxSize = s.MaxSize;
			pMem = new T[MaxSize];
		}
		Num = s.Num;
		for (int i = 0; i <= Num; i++)
		{
			pMem[i] = s.pMem[i];
		}
	}
	return *this;
}


template <class T>
bool TStack<T>::operator==(const TStack& s) const // �������� ���������
{
	if (this == &s)
	{
		return true;
	}
	if (MaxSize != s.MaxSize)
	{
		return false;
	}
	if (Num != s.Num)
	{
		return false;
	}
	for (int i = 0; i <= Num; i++)
	{
		if (pMem[i] != s.pMem[i])
		{
			return false;
		}
	}
	return true;

}


template <class T>
bool TStack<T>::operator!=(const TStack& s) const // �������� ���������
{
	if (MaxSize != s.MaxSize || Num != s.Num) {
		return false;
	}
	return !(*this == s);
}


template <class T>
T TStack<T>::Pop()
{
	if (Empty())
	{
		throw -2;
	}
	T tmp = pMem[Num];
	Num--;
	return tmp;
}


template <class T>
void TStack<T>::Push(T val)
{
	if (Full())
	{
		throw -2;
	}
	Num++;
	pMem[Num] = val;
}


template <class T>
bool TStack<T>::Check(string str)
{
	TStack <char> s;
	bool res = true;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
		{
			s.Push('(');
		}
		if (str[i] == ')')
		{
			if (s.Empty())
			{
				return false;
				
			}
			s.Pop();
		}
	}
	/*if (!s.Empty())
	{
		return false;
	}*/
	return true;
}


template <class T>
bool TStack<T>::Empty() const
{
	return (Num == -1);
}


template <class T>
bool TStack<T>::Full() const
{
	return (Num == MaxSize - 1);
}


template <class T>
T TStack<T>::Top() const
{
	if (Empty())
	{
		throw "������: ������� ������� � ������� ������� �����";
	}
	return pMem[Num];
}


template <class T>
void TStack<T>::Clear()
{
	Num = -1;
}


template <class T>
int TStack<T>::GetSize()
{
	return MaxSize;
}


template <class T>
int TStack<T>::GetStartIndex()					// ������ Num
{
	return Num;
}



// ----------------------------------------------------------------------------------


class TCalc
{
	string infix, postfix;
	TStack <double> StNum;
	TStack <char> StChar;

public:
	void ToPostfix();			// ������������� �� infix � postfix
	double CalcPostfix();		// ������� � ����������� �����
	double Calc();				// ���������� �� ����������� ������
	
	int GetPriority(char op);	// ������ ���������� ��� ��������

	void SetInfix(const string& stroka)
	{
		infix = stroka;
	}
	string GetPostfix() const 
	{ 
		return postfix; 
	}
	string GetInfix() const
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
	string number = "";
	for (int i = 0; i < postfix.size(); i++)
	{
		char sim = postfix[i];

		if (isdigit(sim) || sim == '.')
		{
			number += sim;		// �������� �����
		}
		else if (sim == ' ' && !number.empty())
		{
			StNum.Push(stod(number));
			number = "";
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^')
		{
			if (StNum.GetStartIndex() < 1) 
			{
				//throw "������: ������������ ��������� ��� ���������� ��������";
				throw - 1;
			}
			double secondNum = StNum.Pop();
			double firstNum = StNum.Pop();

			switch (postfix[i])
			{
			case '+':
				StNum.Push(firstNum + secondNum);
				break;
			case '-':
				StNum.Push(firstNum - secondNum);
				break;
			case '*':
				StNum.Push(firstNum * secondNum);
				break;
			case '/':
				if (secondNum == 0)				// ��������� ������� �� ����
				{
					throw "������ : ������� �� ���� �����������!";
				}
				StNum.Push(firstNum / secondNum);
				break;
			case '^':
				StNum.Push(pow(firstNum, secondNum)); // u��������� ������� pow �� <cmath>
				break;
			}
		}
		
	}
	if (!number.empty())
	{
		StNum.Push(stod(number));
	}
	if (StNum.GetStartIndex() != 0) 
	{
		throw "������: �������� ���������� ��������� � ���������";
	}
	return StNum.Pop();
}



void TCalc::ToPostfix()
{
	postfix = "";
	StChar.Clear();

	

	for (int i = 0; i < infix.size(); i++)		// �������� �� ������� ������� ������-������
	{
		char sim = infix[i];					// ��������� ������� ������ 

		if (isdigit(sim))		// ���� ��� ����� (��������), �� 
		{
			while (i < infix.size() && isdigit(infix[i]))
			{
				postfix += infix[i];		
				//postfix += " ";
				i++; // ��������� �� � ����������� ���������

			}
			postfix += " ";  // ��������� ������ ����� �����
			i--;  // ������������ ������ ���������
		}
		else if (sim == '(')					// ���� ��� (
		{
			StChar.Push(sim);					// �������� �� � ���� ��� ���������� ���������
		}
		else if (sim == ')')					// ���� ��� )
		{
			while (!StChar.Empty() && StChar.Top() != '(')	// �� ��������� �������� �� ��� ��� ���� �� ������ "("
			{
				//postfix += " ";
				postfix += StChar.Pop();					// ��������� ������ ������� � ����������� ���������
				postfix += " ";
			}
			StChar.Pop();									// ������� "(" �� ����� 
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^') 	// ���� ������ - �������� 
		{
			while (!StChar.Empty() && ((sim != '^' && GetPriority(StChar.Top()) >= GetPriority(sim) || (sim == '^' && GetPriority(StChar.Top()) > GetPriority(sim)))))		// ��������� ��������� �� ����� � ����������� >= �������� ���������
			{
				//postfix += " ";
				postfix += StChar.Pop();					// ��������� ����������� �������� � �����.���������
				postfix += " ";
			}
			StChar.Push(sim);								// �������� ������� �������� � ���� 
		}	
	}
	while (!StChar.Empty())				// ���������� ���������� ��������� �� ����� � ����� ��������� 
	{
		//postfix += " ";
		postfix += StChar.Pop();
		postfix += " ";
	}
	
}


//double TCalc::Calc()
//{
//	
//}