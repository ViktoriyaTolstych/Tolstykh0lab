#pragma once
#include <iostream>
#include <string>
class CKC
{
public:
	int identificator;
	std::string name = " ";
	int kolvo_tsehov =0;
	int kolvo_tsehov_v_rabote=0;
	float effektivnost=0;
	static int CountKC;
	CKC();
};

