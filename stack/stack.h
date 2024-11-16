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

	TStack(int _MaxSize = 10);			//конструктор инициализации
	~TStack();							//деструктор
	TStack(const TStack& s);			//конструктор копирования

	int GetSize();					//размер стека
	
	int GetStartIndex();			// индекс Num
	

	TStack& operator=(const TStack<T> s);			//оператор присваивания
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
	delete[] pMem;
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
TStack<T>& TStack<T>::operator=(const TStack<T> s) 	// оператор присваивания
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
	if (this->Empty())
	{
		//throw "Ошибка: попытка извлечь элемент из пустого стека";
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
		throw "Ошибка: стек переполнен";
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
	TCalc();
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
		if (i > 0 && postfix[i] >= '0' && postfix[i] <= '9' && postfix[i - 1] == '_')		//ищем отрицательное число
		{
			StNum.Push((postfix[i] - '0') * (-1));
		}
		else if (postfix[i] >= '0' && postfix[i] <= '9')
		{
			StNum.Push(postfix[i] - '0');		// преобразование символа в число
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
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
		//throw "Ошибка: неверное количество операндов в выражении";
		throw - 1;
	}
	return StNum.Pop();
}



void TCalc::ToPostfix()
{
	postfix = "";
	StChar.Clear();
	string sim = "(" + infix + ")";				//  текущий символ 
	if (!StChar.Check(infix)) {
		throw - 1;
	}
	for (int i = 0; i < sim.length(); i++)		// проходим по каждому символу инфикс-строки
	{
		if (sim[i] == '(')					// если это (
		{
			StChar.Push(sim[i]);					// помещаем ее в стек для дальнейшей обработки
		}

		else if (sim[i - 1] == '(' && sim[i] == '-')	//обработка унарного минуса
		{
			postfix += '_';
		}

		else if (sim[i] >= '0' && sim[i] <= '9' || sim[i] == '.')		// если это цифра (операнда), то 
		{
			postfix += sim[i];								// добавляем ее в постфиксное выражение
			
		}
		 
		else if (sim[i] == ')')					// если это )
		{
			char a = StChar.Pop();
			while (a!='(')	// то извлекаем операнды до тех пор пока не найдем "("
			{
				//postfix += " ";
				postfix += a;				// добавляем каждый операнд в постфиксное выражение
				a = StChar.Pop();

				//postfix += " ";
			}
			//StChar.Pop();									// удаляем "(" из стека 
		}
		else if (sim[i] == '+' || sim[i] == '-' || sim[i] == '*' || sim[i] == '/')		// если символ - оператор 
		{
			while (!StChar.Empty() && GetPriority(StChar.Top()) >= GetPriority(sim[i]))	// извлекаем операторы из стека с приоритетом >= текущему оператору
			{
				//postfix += " ";
				postfix += StChar.Pop();					// добавляем извлеченный оператор в постф.выражение
				//postfix += " ";
			}
			StChar.Push(sim[i]);								// помещаем текущий оператор в стек 
		}	
	}
	while (!StChar.Empty())				// перемещаем оставшиеся операторы из стека в постф выражение 
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
					if (second_num == 0)				// обработка деления на ноль
					{
						throw "Ошибка : деление на ноль недопустимо!";
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
					if (second_num == 0)				// обработка деления на ноль
					{
						throw "Ошибка : деление на ноль недопустимо!";
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