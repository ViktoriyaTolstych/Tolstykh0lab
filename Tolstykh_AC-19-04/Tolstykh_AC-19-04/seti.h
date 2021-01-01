#pragma once
#include "Cpipe.h"
#include "CKC.h"
#include"utility.h"
#include <set>
#include <iostream>
#include <fstream>

#pragma once

class seti
{
private:
	int** matrix;
	set<int> idks;
	set<int> idt;
public:
	void editnetwork(unordered_map<int, Cpipe>& pv);
	void savefilenetwork(std::ofstream& fout);
	int inputfilenetwork(std::ifstream& fin);
	int** creatematrix(int n);
	void deletematrix(int n);
	void editmatrix(unordered_map<int, Cpipe>& Truboprovod);
	vector<unsigned int> tgtssort(unordered_map<int, Cpipe>& Truboprovod);
	void deleteidks(int value);
	set<int> getidks();
	set<int> getidt();
	void setidks(int value);
	void setidt(int value);

};

