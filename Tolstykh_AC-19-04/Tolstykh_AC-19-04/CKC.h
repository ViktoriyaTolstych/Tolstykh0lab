#pragma once
#include <iostream>
#include <string>
#include <list>
class CKC
{
	int identificator;
	std::string name = " ";
	int kolvo_tsehov =0;
	int kolvo_tsehov_v_rabote=0;
	float effektivnost=0;
public:
	static int CountKC;
	
	int kolvo_tsehov
	std::istream& operator>>(std::istream& in, CKC& cs);
	CKC();
};

