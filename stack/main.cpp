// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <locale.h>
#include "stack.h"


using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    // Создание стека с размером 5
    TStack<int> stack(5);
    int k = 1;
    for (int i = 0; i < 5; i++)
    {
        stack.Push(k);
        k = k + 3;
    }

    cout << "Содержимое стека: ";
    cout << stack << endl;

    return 0;
}