#pragma once
#include <iostream>
#include <list>
using namespace std;
template<typename T>
T proverka(T less, T more)
{
	T x;
	while ((cin >> x).fail() || x > more || x < less)
	{
		cout << "���������� ������� ���������� ������" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return x;
}
template <class className>
void DeleteObject(std::unordered_map<int, className>& group)
{
	int id = getIntValue("������� id �������", 0u, group.size());
	if (group.find(id)!=group.end())
	{
		group.erase(id);
		cout << endl;
	}
	else
	{
		cout << "������ ������� ���. "<< endl;
	}
}
