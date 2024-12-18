#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
//using namespace std;
const int MAX_SZ = 10000;



template <class T>
struct Node						// ���� ��� �������� �������� �����
{
	T data;
	Node<T>* pNext;				// ��������� �� ��������� ����
};


template<class T>
class TStack
{
	Node<T>* pFirst;
	int size;

public:
	
	TStack();
	~TStack();							//����������
	TStack(const TStack& s);			//����������� �����������

	TStack& operator=(const TStack<T>& s); //�������� ������������
	bool operator==(const TStack& s) const;		//��������� �����
	bool operator!=(const TStack& s) const;		//��������� �� �����

	T Pop();
	void Push(T val);						// ���������� �������� � ����
	bool Check(std::string str);
	void Clear();							// ������� �����

	T Top() const;							// ���������� �� ������� �����
	bool Empty() const;						// �������� �� ������� (����� ��-�� = -1)
	bool Full() const;						// �������� �� ������������� (����.���� - 1)
	int GetStartIndex() const;			    // �����, ������� ���������� ������ �����

	friend std::istream& operator>>(std::istream& in, TStack& s)
	{
		T val;
		std::cout << "������� �������� ����� (������� 0 ��� ����������): ";
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
	return size; // ���������� ���������� ��������� � �����
}


template <class T>
TStack<T>::TStack()
{
	pFirst = nullptr;
	size = 0;
}


template <class T>
TStack<T>::~TStack()					// ����������
{
	while (pFirst != nullptr)
	{
		Node<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
}


template <class T>
TStack<T>::TStack(const TStack& s)		// ����������� �����������
{
	if (s.pFirst == nullptr)			// �������� �� ������� �������� �������� ����� (�������������� � ����� �����)
	{
		pFirst = nullptr;
	}
	else
	{
		Node<T>* now = s.pFirst;				// ��������� ��� ������ �������� �����
		Node<T>* pPrev = nullptr;				// ��������� ��� ���������� ����
		while (now != nullptr)
		{
			Node<T>* node = new Node<T>;		// ������� ����� ����
			node->data = now->data;				// �������� ������ �������� ���� � �����
			node->pNext = nullptr;				// �������������� ����� ���������
			if (pPrev == nullptr)				
			{
				pFirst = node;
			}
			else
			{
				pPrev->pNext = node;
			}
			pPrev = node;						// ��������� ��������� �� ����� ����, ���� �� ��� ���������
			now = now->pNext;					// ���������� �� ��������� ����
		}
	}
}


template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& s) 	// �������� ������������
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
bool TStack<T>::operator==(const TStack& s) const // �������� ���������
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
bool TStack<T>::operator!=(const TStack& s) const // �������� ���������
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
		T val = pFirst->data;				// ������ �������� ���� �����
		Node<T>* tmp = pFirst;				// ��������� ��
		pFirst = pFirst->pNext;				// ���������� ��������� �� ����.����
		delete tmp;							// ������� ������� ����
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
		throw "������: ������� ������� � ������� ������� �����";
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