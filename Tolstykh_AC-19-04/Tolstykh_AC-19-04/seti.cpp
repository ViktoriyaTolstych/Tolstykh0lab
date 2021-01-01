//#include "seti.h"
//#include<set>
//#include <unordered_map>
//#include<vector>
//#include"CKC.h"
//#include<map>
//
//using std::unordered_map;
//using std::vector;
//using namespace std;
//
//void seti::editnetwork(unordered_map<int, Cpipe>& pv)
//	{
//		while (true)
//		{
//			cout << "1 - Соединить KC\n";
//			cout << "0 - Выход\n";
//			int i = Utility::proverka(0, 1);
//			switch (i)
//			{
//			case 1:
//			{cout <<  "Введите ID КС";
//			unsigned int ks = Utility::proverka(1, CKC::GetCountKC());
//			idks.insert(ks);
//			unsigned int t;
//			while (true)
//			{
//				cout << "Введите ID трубы ";
//				t = Utility::proverka(1, Cpipe::GetCountP());//pipeconnect
//				if (pv[t].getinputks() == 0 && pv[t].getoutputks() == 0)
//					break;
//				else
//					cout << "Эта труба уже используется\n";
//			}
//			idt.insert(t);
//			pv[t].setinputks(ks);
//			unsigned int ks1;
//			while (true)
//			{
//				cout << "Введите KC ID";
//				ks1 = Utility::proverka(1, CKC::GetCountKC());//2 KC
//				if (ks1 != ks)
//					break;
//				else
//					cout << "Ошибка\n";
//			}
//			idks.insert(ks1);
//			pv[t].setoutputks(ks1);
//			break;
//			}
//			case 0:
//			{
//				return;
//			}
//			default:
//			{
//				cout << "Ошибка\n";
//			}
//			}
//		}
//	}
//
//	void seti::savefilenetwork(std::ofstream& fout)
//	{
//		if (idks.size() > 0)
//		{
//			for (auto& n : idks)
//			{
//				fout << n << endl;
//			}
//		}
//		if (idks.size() > 0)
//		{
//			for (auto& n : idt)
//			{
//				fout << n << endl;
//			}
//		}
//	}
//
//	int seti::inputfilenetwork(std::ifstream& fin)
//	{
//		int n;
//		fin >> n;
//		return n; 
//	}
//
//	int** seti::creatematrix(int n)
//	{
//		matrix = new int* [n]();
//		for (int i = 0; i < n; i++)
//		{
//			matrix[i] = new int[n]();
//		}
//		return matrix; 
//	}
//
//	void seti::deletematrix(int n)
//	{
//		for (int i = 0; i < n; i++)
//		{
//			delete[] matrix[i];
//		}
//		delete[] matrix;
//	}
//
//	void seti::editmatrix(unordered_map<int, Cpipe>& pv)
//	{
//		vector<unsigned int> sortedidks;
//		for (auto& v : idks)
//		{
//			sortedidks.push_back(v);
//		}
//		int n = idks.size();
//		for (auto& infotruba : pv)
//		{
//			int first = -1;
//			int second = -1;
//			for (int i = 0; i < n; i++)
//			{
//				if (infotruba.second.getinputks() == sortedidks[i])
//					first = i;
//			}
//			for (int i = 0; i < n; i++)
//			{
//				if (infotruba.second.getoutputks() == sortedidks[i])
//					second = i;
//			}
//			if (first > -1 && second > -1)
//				matrix[first][second] = 1;
//		}
//	}
//
//	vector<unsigned int> seti::tgtssort(unordered_map<int, Cpipe>& pv)
//	{
//		vector<unsigned int> sorted;
//		vector<unsigned int> vks;
//		for (auto& v : idks)
//		{
//			vks.push_back(v);
//		}
//		int n = idks.size();
//		matrix = creatematrix(n);
//		editmatrix(pv);
//		for (int k = 0; k < n; k++)
//		{
//			for (int i = 0; i < n; i++)
//			{
//				int sum = 0;
//				for (int j = 0; j < n; j++)
//				{
//					sum += matrix[i][j];
//				}
//				if (sum == 0)
//				{
//					sorted.push_back(vks[i]);
//					for (int j = 0; j < n; j++)
//					{
//						matrix[j][i] = 0;
//					}
//					matrix[i][i] = 1;
//				}
//			}
//		}
//		for (int i = 0; i < n; i++)
//		{
//			for (int j = 0; j < n; j++)
//			{
//				cout << matrix[i][j];
//
//			}
//			cout << endl;
//		}
//		deletematrix(n);
//		reverse(sorted.begin(), sorted.end());
//		return sorted; 
//	}
//
//	void seti::deleteidks(int value)
//	{
//		idks.erase(idks.find(value));
//	}
//
//	set<int> seti::getidks()
//	{
//		return idks; 
//	}
//
//	set<int> seti::getidt()
//	{
//		return idt;
//	}
//
//	void seti::setidks(int value)
//	{
//		idks.insert(value);
//	}
//
//	void seti::setidt(int value)
//	{
//		idt.insert(value);
//	}
