#pragma once
#include <string.h>

template<class T>
class TStack
{
	T* pMem;
	int MaxSize, Num;

public:
	TStack operator=(const TStack<T>& s);








	bool Check(string stz)
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
	}


};


