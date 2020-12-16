#pragma once
#include "lib.h"
#include <unordered_map>
class Utility
{
public:
	template<typename T>
	static T proverka(T less, T more);
	template <class className>
	static void DeleteObject(std::unordered_map<int, className>& group);

};
template<typename T>
T Utility:: proverka(T less, T more)
{
	T x;
	while ((std::cin >> x).fail() || x > more || x < less)
	{
		std::cout << "Пожалуйста введите корректные данные" << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
	return x;
}
template <class className>
void Utility::DeleteObject(std::unordered_map<int, className>& group)
{
	std::cout<<"Введите id объекта"<<std::endl;
	int id;
	std::cin >> id;
	if (group.find(id)!=group.end())
	{
		group.erase(id);
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Такого объекта нет. "<< std::endl;
	}
}
