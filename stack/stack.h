#pragma once
#include <string.h>

template<class T>
class TStack
{
	T* pMem;
	int MaxSize, Num;

public:

	TStack(int _MaxSize = 10);			//конструктор инициализации
	~TStack();							//деструктор
	TStack(const TStack& s);			//конструктор копирования

	int GetSize()
	{
		return MaxSize;
	}
	int GetStartIndex()
	{
		return Num;
	}

	TStack operator=(const TStack<T> s);			//оператор присваивания
	bool operator==(const TStack<T> s) const;		//сравнение равно
	bool operator!=(const TStack<T> s) const;		//сравнение не равно


	T Pop();
	void Push(T val);
	bool Check(string str);
	void Clear();
	TStack& operator=(const TStack<T>& s);


	T Top() const;
	bool Empty() const;
	bool Full() const;


	friend istream& operator>>(istream& in, TStack& s)
	{

	}

	friend ostream& operator<<(ostream& out, const TStack& s)
	{

	}





	/*bool Check(string stz)
	{
		TStack <char> s;
		bool res = true;
		for (int i = 0; i < stz.Size(); i++)
		{
			if (stz[i] == '(')
			{
				s.push('(');
			}
			if (stz[i] == ')')
			{
				if (s.empty())
				{
					return false;
					s.pop();
				}
			}
		}
		if (!s.empty())
		{
			return false;
		}
		return true;
	}*/


};


template <class T>
TStack <T>::TStack(int _MaxSize)
{

}


template <class T>
TStack<T>::~TStack()
{

}


template <class T>
TStack<T>::TStack(const TStack& s)
{

}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& s)
{

}

template <class T>
bool TStack<T>::operator==(const TStack<T>& s) const
{

}


template <class T>
bool TStack<T>::operator!=(const TStack<T>& s) const
{

}

