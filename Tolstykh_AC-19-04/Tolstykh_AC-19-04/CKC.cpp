#include "CKC.h"
#include "utility.h"

using namespace std;

int CKC::CountKC = 0;

CKC::CKC()
{
	identificator = CountKC;
	CountKC++;
	cout << "ID для данной КС = " << identificator << endl;
}
