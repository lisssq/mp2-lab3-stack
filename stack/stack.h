#pragma once
#include <iostream>
#include <string.h>
#include <string>
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
	

	TStack& operator=(const TStack<T> s);			//�������� ������������
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
	delete[] pMem;
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
TStack<T>& TStack<T>::operator=(const TStack<T> s) 	// �������� ������������
{
	if (this != &s)
	{
		if (MaxSize != s.MaxSize)
		{
			MaxSize = s.MaxSize;
			delete[] pMem;
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
	if (this->Empty())
	{
		//throw "������: ������� ������� ������� �� ������� �����";
		throw - 1;
	}
	T tmp = pMem[Num];
	Num--;
	return tmp;
}


template <class T>
void TStack<T>::Push(T val)
{
	if (this->Full())
	{
		throw "������: ���� ����������";
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
				//s.Pop();
			}
			s.Pop();	
		}
	}
	if (!s.Empty())
	{
		return false;
	}
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
	if (this->Empty())
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
	TCalc();
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

TCalc::TCalc()
{
	StNum = TStack<double>(MAX_SZ);
	StChar = TStack<char>(MAX_SZ);
	
}


int TCalc::GetPriority(char op)
{
	if (op == '+' || op == '-')
	{
		return 1;
	}
	else if (op == '*' || op == '/')
	{
		return 2;
	}
	else if (op == '^')
	{
		return 3;
	}
	else
	{
		return 0;
	}
}



double TCalc::CalcPostfix()
{
	StNum.Clear();
	StChar.Clear();
	for (int i = 0; i < postfix.size(); i++)
	{
		if (i > 0 && postfix[i] >= '0' && postfix[i] <= '9' && postfix[i - 1] == '_')		//���� ������������� �����
		{
			StNum.Push((postfix[i] - '0') * (-1));
		}
		else if (postfix[i] >= '0' && postfix[i] <= '9')
		{
			StNum.Push(postfix[i] - '0');		// �������������� ������� � �����
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
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
				int p = pow(secondNum, -1);
				if (p % 2 == 0 && firstNum < 0)
				{
					throw - 1;
				}
				StNum.Push(pow(firstNum, secondNum));
			}
		}
	}
	
	if (StNum.Empty())
	{
		throw - 1;
	}
	
	if (StNum.GetStartIndex() != 0) 
	{
		//throw "������: �������� ���������� ��������� � ���������";
		throw - 1;
	}
	return StNum.Pop();
}



void TCalc::ToPostfix()
{
	postfix = "";
	StChar.Clear();
	string sim = "(" + infix + ")";				//  ������� ������ 
	if (!StChar.Check(infix)) {
		throw - 1;
	}
	for (int i = 0; i < sim.length(); i++)		// �������� �� ������� ������� ������-������
	{
		if (sim[i] == '(')					// ���� ��� (
		{
			StChar.Push(sim[i]);					// �������� �� � ���� ��� ���������� ���������
		}

		else if (sim[i - 1] == '(' && sim[i] == '-')	//��������� �������� ������
		{
			postfix += '_';
		}

		else if (sim[i] >= '0' && sim[i] <= '9' || sim[i] == '.')		// ���� ��� ����� (��������), �� 
		{
			postfix += sim[i];								// ��������� �� � ����������� ���������
			
		}
		 
		else if (sim[i] == ')')					// ���� ��� )
		{
			char a = StChar.Pop();
			while (a!='(')	// �� ��������� �������� �� ��� ��� ���� �� ������ "("
			{
				//postfix += " ";
				postfix += a;				// ��������� ������ ������� � ����������� ���������
				a = StChar.Pop();

				//postfix += " ";
			}
			//StChar.Pop();									// ������� "(" �� ����� 
		}
		else if (sim[i] == '+' || sim[i] == '-' || sim[i] == '*' || sim[i] == '/')		// ���� ������ - �������� 
		{
			while (!StChar.Empty() && GetPriority(StChar.Top()) >= GetPriority(sim[i]))	// ��������� ��������� �� ����� � ����������� >= �������� ���������
			{
				//postfix += " ";
				postfix += StChar.Pop();					// ��������� ����������� �������� � �����.���������
				//postfix += " ";
			}
			StChar.Push(sim[i]);								// �������� ������� �������� � ���� 
		}	
	}
	while (!StChar.Empty())				// ���������� ���������� ��������� �� ����� � ����� ��������� 
	{
		//postfix += " ";
		postfix += StChar.Pop();
		//postfix += " ";
	}
	
}


double TCalc::Calc()
{
	string str = '(' + infix + ')';
	StChar.Clear();
	StNum.Clear();
	if (!StChar.Check(infix))
	{
		throw - 1;
	}
	for (int i = 0; i < str.size(); i++)
	{
		char tmp = str[i];
		if (tmp == '(')
		{
			StChar.Push(tmp);
		}


		else if (str[i - 1] == '(' && tmp == '-')
		{
			str[i] = '_';
		}



		else if (i > 0 && tmp >= '0' && tmp <= '9' && str[i - 1] == '_')
		{
			size_t idx;
			double num = stod(&tmp, &idx);
			StNum.Push(num * (-1.0));
			i += idx - 1;
		}
		else if (tmp >= '0' && tmp <= '9' || tmp == '.')
		{
			size_t idx;
			double num = stod(&tmp, &idx);
			StNum.Push(num);
			i += idx - 1;
		}
		else if (tmp - ')')
		{
			char a = StChar.Pop();
			while (a != '(')
			{
				double second_num = StNum.Pop();
				double first_num = StNum.Pop();
				if (a == '+')
				{
					StNum.Push(first_num + second_num);
				}
				if (a == '-')
				{
					StNum.Push(first_num - second_num);
				}
				if (a == '*')
				{
					StNum.Push(first_num * second_num);
				}
				if (a == '/')
				{
					if (second_num == 0)				// ��������� ������� �� ����
					{
						throw "������ : ������� �� ���� �����������!";
					}
					StNum.Push(first_num / second_num);
				}
				if (a == '^')
				{
					int p = pow(second_num, -1);
					if (p % 2 == 0 && first_num < 0)
					{
						throw - 1;
					}
					StNum.Push(pow(first_num, second_num));
				}
				a = StChar.Pop();
			}
		}
		else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' || tmp == '^')
		{
			while (GetPriority(StChar.Top()) >= GetPriority(tmp))
			{
				double second_num = StNum.Pop();
				double first_num = StNum.Pop();
				char a = StChar.Pop();
				if (a == '+')
				{
					StNum.Push(first_num + second_num);
				}
				if (a == '-')
				{
					StNum.Push(first_num - second_num);
				}
				if (a == '*')
				{
					StNum.Push(first_num * second_num);
				}
				if (a == '/')
				{
					if (second_num == 0)				// ��������� ������� �� ����
					{
						throw "������ : ������� �� ���� �����������!";
					}
					StNum.Push(first_num / second_num);
				}
				if (a == '^')
				{
					int p = pow(second_num, -1);
					if (p % 2 == 0 && first_num < 0)
					{
						throw - 1;
					}
					StNum.Push(pow(first_num, second_num));
				}
			}
			StChar.Push(tmp);
		}
	}
	double a = StNum.Pop();
	if (StNum.Empty())
	{
		throw - 1;
	}
	return a;

}