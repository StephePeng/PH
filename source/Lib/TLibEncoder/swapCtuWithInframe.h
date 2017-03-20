#pragma once
#include<vector>
#include"TLibCommon/TComDataCU.h"
#include "TEncSlice.h"
#include "SwapCu.h"
#include<fstream>

typedef std::vector<std::vector<UInt> > DATA;

class SwapCtuWithInframe
{
public:
	vector<TComDataCU*> swapCtuMain(vector<TComDataCU*> ctuData);
	vector<TComDataCU*> swapCtuMainNew(vector<TComDataCU*> ctuData);
};