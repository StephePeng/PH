#pragma once
#include<vector>
#include"TLibCommon/TComDataCU.h"
#include<fstream>
//#include "TDecslice.h"
typedef std::vector<std::vector<UInt> > DATA;

class DecryptCtuSwap
{
public:
	vector<UInt> readKeyFromFile(UInt ctuNum, UInt poc);
	vector<TComDataCU*> decryptCtuSwapMain(vector<TComDataCU*> ctuData,vector<UInt> key);
};