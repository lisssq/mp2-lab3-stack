#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
//using namespace std;
const int MAX_SZ = 10000;



template <class T>
struct Node						// узел для хранения элемента стека
{
	T data;
	Node<T>* pNext;				// указатель на следующий узел
};


template<class T>
class TStack
{
	Node<T>* pFirst;
	int size;

public:
	
	TStack();
	~TStack();							//деструктор
	TStack(const TStack& s);			//конструктор копирования

	TStack& operator=(const TStack<T>& s); //оператор присваивания
	bool operator==(const TStack& s) const;		//сравнение равно
	bool operator!=(const TStack& s) const;		//сравнение не равно

	T Pop();
	void Push(T val);						// добавление элемента в стек
	bool Check(std::string str);
	void Clear();							// очистка стека

	T Top() const;							// посмотреть на вершину стека
	bool Empty() const;						// проверка на пустоту (номер эл-та = -1)
	bool Full() const;						// проверка на заполненность (макс.сайз - 1)
	int GetStartIndex() const;			    // Метод, который возвращает размер стека

	friend std::istream& operator>>(std::istream& in, TStack& s)
	{
		T val;
		std::cout << "Введите элементы стека (введите 0 для завершения): ";
		while (in >> val && val != 0) {
			s.Push(val);
		}
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out, const TStack<T>& s)
	{
		for (int i = 0; i <= s.Num; i++) {
			out << s.pFirst->data << " ";
		}
		return out;
	}
};


template <class T>
int TStack<T>::GetStartIndex() const
{
	return size; // возвращаем количество элементов в стеке
}


template <class T>
TStack<T>::TStack()
{
	pFirst = nullptr;
	size = 0;
}


template <class T>
TStack<T>::~TStack()					// деструктор
{
	while (pFirst != nullptr)
	{
		Node<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
}


template <class T>
TStack<T>::TStack(const TStack& s)		// конструктор копирования
{
	if (s.pFirst == nullptr)			// проверка на пустоту верхнего элемента стека (соответственно и всего стека)
	{
		pFirst = nullptr;
	}
	else
	{
		Node<T>* now = s.pFirst;				// указатель для обхода текущего стека
		Node<T>* pPrev = nullptr;				// указатель для последнего узла
		while (now != nullptr)
		{
			Node<T>* node = new Node<T>;		// создаем новый узел
			node->data = now->data;				// копируем данные текущего узла в новый
			node->pNext = nullptr;				// инициализируем новый указатель
			if (pPrev == nullptr)				
			{
				pFirst = node;
			}
			else
			{
				pPrev->pNext = node;
			}
			pPrev = node;						// обновляем указатель на новый узел, чтоб он был последнем
			now = now->pNext;					// сдвигаемся на следующий узел
		}
	}
}


template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& s) 	// оператор присваивания
{
	if (this == &s)
	{
		return *this;
	}
	Clear();
	if (s.pFirst == nullptr)
	{
		pFirst = nullptr;
	}
	else
	{
		Node<T>* now = s.pFirst;
		Node<T>* pPrev = nullptr;
		while (now != nullptr)
		{
			Node<T>* node = new Node<T>;
			node->data = now->data;
			node->pNext = nullptr;
			if (pPrev == nullptr)
			{
				pFirst = node;
			}
			else
			{
				pPrev->pNext = node;
			}
			pPrev = node;
			now = now->pNext;
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
	Node<T>* now1 = pFirst;
	Node<T>* now2 = s.pFirst;
	while (now1 != nullptr and now2 != nullptr)
	{
		if (now1->data != now2->data)
		{
			return false;
		}
		now1 = now1->pNext;
		now2 = now2->pNext;
	}
	return now1 == now2;
}


template <class T>
bool TStack<T>::operator!=(const TStack& s) const // оператор сравнение
{
	return !(*this == s);
}


template <class T>
T TStack<T>::Pop()
{
	if (Empty())
	{
		throw - 2;
	}
	if (pFirst != nullptr)
	{
		T val = pFirst->data;				// данные верхнего узла стека
		Node<T>* tmp = pFirst;				// сохраняем их
		pFirst = pFirst->pNext;				// перемещаем указатель на след.узел
		delete tmp;							// удаляем верхний узел
		size--;
		return val;
	}	
}



template <class T>
void TStack<T>::Push(T val)
{
	if (Full())
	{
		throw - 2;
	}
	Node<T>* node = new Node<T>;
	node->data = val;
	node->pNext = pFirst;
	pFirst = node;
	size++;
}


template <class T>
bool TStack<T>::Check(std::string str)
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
	return true;
}


template <class T>
bool TStack<T>::Empty() const
{
	return pFirst == nullptr;
}


template <class T>
bool TStack<T>::Full() const
{
	Node<T>* node = new Node<T>;
	if (node == nullptr)
	{
		return true;
	}
	delete node;
	return false;
}


template <class T>
T TStack<T>::Top() const
{
	if (Empty())
	{
		throw "ошибка: попытка доступа к вершине пустого стека";
	};
	return pFirst->data;
}


template <class T>
void TStack<T>::Clear()
{
	while (!Empty())
	{
		Pop();
	}
}