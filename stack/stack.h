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

	TStack(int _MaxSize = 10);			//конструктор инициализации
	~TStack();							//деструктор
	TStack(const TStack& s);			//конструктор копирования

	int GetSize();					//размер стека
	
	int GetStartIndex();			// индекс Num
	

	TStack& operator=(const TStack<T>& s); //оператор присваивания
	bool operator==(const TStack &s) const;		//сравнение равно
	bool operator!=(const TStack &s) const;		//сравнение не равно


	T Pop();
	void Push(T val);						// добавление элемента в стек
	bool Check(string str);
	void Clear();							// очистка стека
	


	T Top() const;							// посмотреть на вершину стека
	bool Empty() const;						// проверка на пустоту (номер эл-та = -1)
	bool Full() const;						// проверка на заполненность (макс.сайз - 1)


	friend istream& operator>>(istream& in, TStack& s)
	{
		T val;
		cout << "Введите элементы стека (введите 0 для завершения): ";
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
TStack <T>::TStack(int _MaxSize)		// конструктор инициализации
{
	if (_MaxSize<0 || _MaxSize>MAX_SZ)
	{
		//throw - 1;
		throw "Недопустимый размер стека";
	}
	MaxSize = _MaxSize;
	Num = -1;
	pMem = new T[MaxSize];
}


template <class T>
TStack<T>::~TStack()					// деструктор
{
	if (pMem)
	{
		delete[] pMem;
		pMem = nullptr;
	}
}


template <class T>
TStack<T>::TStack(const TStack& s)		// конструктор копирования
{
	if (s.MaxSize<0 || s.MaxSize>MAX_SZ || s.Num < -1 || s.Num >= s.MaxSize)
	{
		throw "Недопустимый размер стека";
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
TStack<T>& TStack<T>::operator=(const TStack<T>& s) 	// оператор присваивания
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
bool TStack<T>::operator==(const TStack& s) const // оператор сравнение
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
bool TStack<T>::operator!=(const TStack& s) const // оператор сравнение
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
		throw "Ошибка: попытка доступа к вершине пустого стека";
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
int TStack<T>::GetStartIndex()					// индекс Num
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
	void ToPostfix();			// преобразовать из infix в postfix
	double CalcPostfix();		// перевод в постфиксную форму
	double Calc();				// вычисления по постфиксной записи
	
	int GetPriority(char op);	// выдача приоритета для операций

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
			number += sim;		// собираем число
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
				//throw "Ошибка: недостаточно операндов для выполнения операции";
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
				if (secondNum == 0)				// обработка деления на ноль
				{
					throw "Ошибка : деление на ноль недопустимо!";
				}
				StNum.Push(firstNum / secondNum);
				break;
			case '^':
				StNum.Push(pow(firstNum, secondNum)); // uспользуем функцию pow из <cmath>
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
		throw "Ошибка: неверное количество операндов в выражении";
	}
	return StNum.Pop();
}



void TCalc::ToPostfix()
{
	postfix = "";
	StChar.Clear();

	

	for (int i = 0; i < infix.size(); i++)		// проходим по каждому символу инфикс-строки
	{
		char sim = infix[i];					// извлекаем текущий символ 

		if (isdigit(sim))		// если это цифра (операнда), то 
		{
			while (i < infix.size() && isdigit(infix[i]))
			{
				postfix += infix[i];		
				//postfix += " ";
				i++; // добавляем ее в постфиксное выражение

			}
			postfix += " ";  // добавляем пробел после числа
			i--;  // компенсируем лишний инкремент
		}
		else if (sim == '(')					// если это (
		{
			StChar.Push(sim);					// помещаем ее в стек для дальнейшей обработки
		}
		else if (sim == ')')					// если это )
		{
			while (!StChar.Empty() && StChar.Top() != '(')	// то извлекаем операнды до тех пор пока не найдем "("
			{
				//postfix += " ";
				postfix += StChar.Pop();					// добавляем каждый операнд в постфиксное выражение
				postfix += " ";
			}
			StChar.Pop();									// удаляем "(" из стека 
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^') 	// если символ - оператор 
		{
			while (!StChar.Empty() && ((sim != '^' && GetPriority(StChar.Top()) >= GetPriority(sim) || (sim == '^' && GetPriority(StChar.Top()) > GetPriority(sim)))))		// извлекаем операторы из стека с приоритетом >= текущему оператору
			{
				//postfix += " ";
				postfix += StChar.Pop();					// добавляем извлеченный оператор в постф.выражение
				postfix += " ";
			}
			StChar.Push(sim);								// помещаем текущий оператор в стек 
		}	
	}
	while (!StChar.Empty())				// перемещаем оставшиеся операторы из стека в постф выражение 
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