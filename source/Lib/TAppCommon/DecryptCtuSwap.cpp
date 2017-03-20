#include "DecryptCtuSwap.h"

vector<UInt> DecryptCtuSwap::readKeyFromFile(UInt ctuNum, UInt poc)
{
	DATA data;
	std::ifstream inputFile;
	inputFile.open("CtuSwapKey.txt");

	int tmp;
	int i = 0;
	std::vector<UInt> v;
	std::vector<UInt> n;
	while (!inputFile.eof())
	{
		inputFile >> tmp;
		v.push_back(tmp);
	}
	v.pop_back();
	inputFile.close();
	//printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i = i + ctuNum)
	{
		for (int j = 0; j < ctuNum; j++)
		{
			n.push_back(v[i + j]);
		}
		data.push_back(n);
		n.clear();
	}
	v.clear();
	return data[poc];
}

vector<TComDataCU*> DecryptCtuSwap::decryptCtuSwapMain(vector<TComDataCU*> CtuData,vector<UInt> key)
{
	vector<TComDataCU*> ctu;
	UInt boundingCtuTsAddr = CtuData[0]->getSlice()->getSliceSegmentCurEndCtuTsAddr();
	UInt startCtuTsAddr = CtuData[0]->getSlice()->getSliceSegmentCurStartCtuTsAddr();
	//UInt CtuNumsInFrameWidth = CtuData[0]->getPic()->getPicSym()->getFrameWidthInCtus();
	UInt CtuNumsInFrameWidth = 10;
	//UInt picWidth = CtuData[0]->getPic()->getPicYuvOrg()->getWidth(COMPONENT_Y);
	UInt picWidth = 640;
	UInt ctuSize = picWidth / CtuNumsInFrameWidth;

	for (int i = 0; i < key.size(); i++)
	{
		ctu.push_back(CtuData[key[i]]);
	}
	for (int i = 0; i < CtuNumsInFrameWidth; i++)
		ctu.push_back(CtuData[key.size() + i]);
	//reset Addr
	for (int i = 0; i < key.size(); i++)
		ctu[i]->setCtuRsAddr(i);

	//reset CUpel
	for (int i = 0; i < key.size(); i++)
	{
		int CUpelX = (i%CtuNumsInFrameWidth)*ctuSize;
		int CUpelY = (i / CtuNumsInFrameWidth)*ctuSize;
		ctu[i]->setCUpelX(CUpelX);
		ctu[i]->setCUpelY(CUpelY);
	}
	for (int i = 0; i < key.size(); i++)
	{
		//第一块，没有任何参考块
		if (i == 0)
		{
			ctu[i]->setCtuLeft(NULL);
			ctu[i]->setCtuAbove(NULL);
			ctu[i]->setCtuAboveLeft(NULL);
			ctu[i]->setCtuAboveRight(NULL);
		}
		//第一行的块（不包含第一块），只有左参考块
		else if (i<CtuNumsInFrameWidth)
		{
			ctu[i]->setCtuLeft(ctu[i - 1]);
			ctu[i]->setCtuAbove(NULL);
			ctu[i]->setCtuAboveLeft(NULL);
			ctu[i]->setCtuAboveRight(NULL);
		}
		//第一列的块（不包含第一块），只有↑参考块和↗参考块
		else if (i%CtuNumsInFrameWidth == 0 && i != 0)
		{
			ctu[i]->setCtuLeft(NULL);
			ctu[i]->setCtuAbove(ctu[i - CtuNumsInFrameWidth]);
			ctu[i]->setCtuAboveLeft(NULL);
			ctu[i]->setCtuAboveRight(ctu[i - CtuNumsInFrameWidth + 1]);
		}
		//最后一列块（不包含第一行的最后一个块），只有↑、←和↖参考块
		else if (i%CtuNumsInFrameWidth == CtuNumsInFrameWidth - 1)
		{
			ctu[i]->setCtuLeft(ctu[i - 1]);
			ctu[i]->setCtuAbove(ctu[i - CtuNumsInFrameWidth]);
			ctu[i]->setCtuAboveLeft(ctu[i - CtuNumsInFrameWidth - 1]);
			ctu[i]->setCtuAboveRight(NULL);
		}
		//其余的有四个参考块
		else
		{
			ctu[i]->setCtuLeft(ctu[i - 1]);
			ctu[i]->setCtuAbove(ctu[i - CtuNumsInFrameWidth]);
			ctu[i]->setCtuAboveLeft(ctu[i - CtuNumsInFrameWidth - 1]);
			ctu[i]->setCtuAboveRight(ctu[i - CtuNumsInFrameWidth + 1]);
		}

		if (i % CtuNumsInFrameWidth == 0)
		{
			ctu[i + 1]->setCtuLeft(ctu[i]);
			ctu[i + CtuNumsInFrameWidth]->setCtuAbove(ctu[i]);
			ctu[i + CtuNumsInFrameWidth + 1]->setCtuAboveLeft(ctu[i]);
			//CtuData[swap_Idx[i] + 9]->setCtuAboveRight(NULL);
		}
		else if (i%CtuNumsInFrameWidth == CtuNumsInFrameWidth - 1)
		{
			//CtuData[swap_Idx[i] + 1]->setCtuLeft(CtuData[swap_Idx[i]]);
			ctu[i + CtuNumsInFrameWidth]->setCtuAbove(ctu[i]);
			ctu[i + CtuNumsInFrameWidth - 1]->setCtuAboveRight(ctu[i]);
			//CtuData[swap_Idx[i] + 11]->setCtuAboveLeft(CtuData[swap_Idx[i]]);
		}
		else
		{
			ctu[i + 1]->setCtuLeft(ctu[i]);
			ctu[i + CtuNumsInFrameWidth]->setCtuAbove(ctu[i]);
			ctu[i + CtuNumsInFrameWidth - 1]->setCtuAboveRight(ctu[i]);
			ctu[i + CtuNumsInFrameWidth + 1]->setCtuAboveLeft(ctu[i]);
		}

	}
	key.clear();
	return ctu;
}