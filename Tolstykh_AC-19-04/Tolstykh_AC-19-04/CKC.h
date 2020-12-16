#pragma once
#include "lib.h"
class CKC
{
public:

	int identificator;
	std::string name = " ";
	int kolvo_tsehov =0;
	int kolvo_tsehov_v_rabote=0;
	float effektivnost=0;
public:
	static int CountKC;
	static std::unordered_map<int, CKC>
EditAllKC(std::unordered_map<int, CKC>& cs);
	static std::unordered_map<int, CKC> 
	EditOneKC(std::unordered_map<int, CKC>& cs);
	void send();
	CKC();
};

