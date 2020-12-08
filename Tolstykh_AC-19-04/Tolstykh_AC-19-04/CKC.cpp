#include "CKC.h"
using namespace std;

int CKC::CountKC = 0;

CKC::CKC()
{
	identificator = CountKC;
	CountKC++;
}
