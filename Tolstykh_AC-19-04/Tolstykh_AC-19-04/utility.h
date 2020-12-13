#pragma once
#include <iostream>
using namespace std;
template<typename T>
T proverka(T less, T more)
{
	T x;
	while ((cin >> x).fail() || x > more || x < less)
	{
		cout << "Пожалуйста введите корректные данные" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return x;
}