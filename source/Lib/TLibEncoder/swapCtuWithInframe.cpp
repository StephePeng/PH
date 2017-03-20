#include "swapCtuWithInframe.h"

vector<TComDataCU*> SwapCtuWithInframe::swapCtuMain(vector<TComDataCU*> CtuData)
{
	/*int val1 = 14;
	int val2 = 15;
	int val3 = 26;
	int val4 = 43;
	int val5 = 45;*/
	vector<int> swap_Idx;
	vector<int> key_Idx;

	UInt boundingCtuTsAddr = CtuData[0]->getSlice()->getSliceSegmentCurEndCtuTsAddr();
	UInt startCtuTsAddr = CtuData[0]->getSlice()->getSliceSegmentCurStartCtuTsAddr();
	UInt CtuNumsInFrameWidth = CtuData[0]->getPic()->getPicSym()->getFrameWidthInCtus();
	UInt picWidth = CtuData[0]->getPic()->getPicYuvOrg()->getWidth(COMPONENT_Y);
	UInt ctuSize = picWidth / CtuNumsInFrameWidth;
	
	for (int i = startCtuTsAddr; i < boundingCtuTsAddr - CtuNumsInFrameWidth; i++)
	{
		swap_Idx.push_back(i);
		key_Idx.push_back(i);
	}

	random_shuffle(key_Idx.begin(), key_Idx.end());
	/*for (int i = 0; i < swap_Idx.size(); i++)
	{
		CtuData[i]->setTag(i);
	}
*/
	/*for (int i = 0; i < key_Idx.size(); i++)
	{
	printf("%d ", key_Idx[i]);
	}*/
	int i = 0;
	while (i<swap_Idx.size())
	{
		if (swap_Idx[i] != key_Idx[i])
		{
			swap(CtuData[swap_Idx[i]], CtuData[key_Idx[i]]);
		}
		i++;
	}
	/*printf("\n");
	for (int i = 0; i < swap_Idx.size(); i++)
	{
	printf("%d ", CtuData[i]->getTag());
	}*/
	////解密测试
	//for (int i = swap_Idx.size()-1; i >= 0; i--)
	//{
	//	swap(CtuData[swap_Idx[i]], CtuData[key_Idx[i]]);
	//}
	//for (int i = 0; i < swap_Idx.size(); i++)
	//{
	//	printf("%d ", CtuData[i]->getTag());
	//}

	//重置CtuAddr
	for (int i = 0; i < swap_Idx.size(); i++)
	{
		CtuData[swap_Idx[i]]->setCtuRsAddr(swap_Idx[i]);
		/*CtuData[swap_Idx[i]]->setCUpelX(CtuData[key_Idx[i]]->getCUPelX());
		CtuData[swap_Idx[i]]->setCUpelY(CtuData[key_Idx[i]]->getCUPelY());*/

	}
	for (int i = 0; i < swap_Idx.size(); i++)
	{
		int CUpelX = (i%CtuNumsInFrameWidth)*ctuSize;
		int CUpelY = (i / CtuNumsInFrameWidth)*ctuSize;
		CtuData[i]->setCUpelX(CUpelX);
		CtuData[i]->setCUpelY(CUpelY);
	}
	//重置CTU参考块
	for (int i = 0; i < swap_Idx.size(); i++)
	{
		//第一块，没有任何参考块
		if (i == 0)
		{
			CtuData[swap_Idx[i]]->setCtuLeft(NULL);
			CtuData[swap_Idx[i]]->setCtuAbove(NULL);
			CtuData[swap_Idx[i]]->setCtuAboveLeft(NULL);
			CtuData[swap_Idx[i]]->setCtuAboveRight(NULL);
		}
		//第一行的块（不包含第一块），只有左参考块
		else if (i<CtuNumsInFrameWidth)
		{
			CtuData[swap_Idx[i]]->setCtuLeft(CtuData[swap_Idx[i] - 1]);
			CtuData[swap_Idx[i]]->setCtuAbove(NULL);
			CtuData[swap_Idx[i]]->setCtuAboveLeft(NULL);
			CtuData[swap_Idx[i]]->setCtuAboveRight(NULL);
		}
		//第一列的块（不包含第一块），只有↑参考块和↗参考块
		else if (i%CtuNumsInFrameWidth == 0 && i != 0)
		{
			CtuData[swap_Idx[i]]->setCtuLeft(NULL);
			CtuData[swap_Idx[i]]->setCtuAbove(CtuData[swap_Idx[i] - CtuNumsInFrameWidth]);
			CtuData[swap_Idx[i]]->setCtuAboveLeft(NULL);
			CtuData[swap_Idx[i]]->setCtuAboveRight(CtuData[swap_Idx[i] - CtuNumsInFrameWidth + 1]);
		}
		//最后一列块（不包含第一行的最后一个块），只有↑、←和↖参考块
		else if (i%CtuNumsInFrameWidth == CtuNumsInFrameWidth - 1)
		{
			CtuData[swap_Idx[i]]->setCtuLeft(CtuData[swap_Idx[i] - 1]);
			CtuData[swap_Idx[i]]->setCtuAbove(CtuData[swap_Idx[i] - CtuNumsInFrameWidth]);
			CtuData[swap_Idx[i]]->setCtuAboveLeft(CtuData[swap_Idx[i] - CtuNumsInFrameWidth - 1]);
			CtuData[swap_Idx[i]]->setCtuAboveRight(NULL);
		}
		//其余的有四个参考块
		else
		{
			CtuData[swap_Idx[i]]->setCtuLeft(CtuData[swap_Idx[i] - 1]);
			CtuData[swap_Idx[i]]->setCtuAbove(CtuData[swap_Idx[i] - CtuNumsInFrameWidth]);
			CtuData[swap_Idx[i]]->setCtuAboveLeft(CtuData[swap_Idx[i] - CtuNumsInFrameWidth - 1]);
			CtuData[swap_Idx[i]]->setCtuAboveRight(CtuData[swap_Idx[i] - CtuNumsInFrameWidth + 1]);
		}

		if (i % CtuNumsInFrameWidth == 0)
		{
			CtuData[swap_Idx[i] + 1]->setCtuLeft(CtuData[swap_Idx[i]]);
			CtuData[swap_Idx[i] + CtuNumsInFrameWidth]->setCtuAbove(CtuData[swap_Idx[i]]);
			CtuData[swap_Idx[i] + CtuNumsInFrameWidth + 1]->setCtuAboveLeft(CtuData[swap_Idx[i]]);
			//CtuData[swap_Idx[i] + 9]->setCtuAboveRight(NULL);
		}
		else if (i%CtuNumsInFrameWidth == CtuNumsInFrameWidth - 1)
		{
			//CtuData[swap_Idx[i] + 1]->setCtuLeft(CtuData[swap_Idx[i]]);
			CtuData[swap_Idx[i] + CtuNumsInFrameWidth]->setCtuAbove(CtuData[swap_Idx[i]]);
			CtuData[swap_Idx[i] + CtuNumsInFrameWidth - 1]->setCtuAboveRight(CtuData[swap_Idx[i]]);
			//CtuData[swap_Idx[i] + 11]->setCtuAboveLeft(CtuData[swap_Idx[i]]);
		}
		else
		{
			CtuData[swap_Idx[i] + 1]->setCtuLeft(CtuData[swap_Idx[i]]);
			CtuData[swap_Idx[i] + CtuNumsInFrameWidth]->setCtuAbove(CtuData[swap_Idx[i]]);
			CtuData[swap_Idx[i] + CtuNumsInFrameWidth - 1]->setCtuAboveRight(CtuData[swap_Idx[i]]);
			CtuData[swap_Idx[i] + CtuNumsInFrameWidth + 1]->setCtuAboveLeft(CtuData[swap_Idx[i]]);
		}

	}
	//swap(CtuData[val1], CtuData[val2]);
	//swap(CtuData[val2], CtuData[val3]);

	//int ctuAddr1_temp = CtuData[val1]->getCtuRsAddr();
	//int ctuAddr2_temp = CtuData[val2]->getCtuRsAddr();
	//int ctuAddr3_temp = CtuData[val3]->getCtuRsAddr();
	//CtuData[val1]->setCtuRsAddr(ctuAddr3_temp);
	//CtuData[val2]->setCtuRsAddr(ctuAddr1_temp);
	//CtuData[val3]->setCtuRsAddr(ctuAddr2_temp);

	//int m_uiCUPelX1_temp = CtuData[val1]->getCUPelX();
	//int m_uiCUPelX2_temp = CtuData[val2]->getCUPelX();
	//int m_uiCUPelX3_temp = CtuData[val3]->getCUPelX();
	//CtuData[val1]->setCUpelX(m_uiCUPelX3_temp);
	//CtuData[val2]->setCUpelX(m_uiCUPelX1_temp);
	//CtuData[val3]->setCUpelX(m_uiCUPelX2_temp);
	//int m_uiCUPelY1_temp = CtuData[val1]->getCUPelY();
	//int m_uiCUPelY2_temp = CtuData[val2]->getCUPelY();
	//int m_uiCUPelY3_temp = CtuData[val3]->getCUPelY();
	//CtuData[val1]->setCUpelY(m_uiCUPelY3_temp);
	//CtuData[val2]->setCUpelY(m_uiCUPelY1_temp);
	//CtuData[val3]->setCUpelY(m_uiCUPelY2_temp);

	//CtuData[val1]->setCtuLeft(CtuData[val1 - 1]);
	//CtuData[val1]->setCtuAbove(CtuData[val1 - 10]);
	//CtuData[val1]->setCtuAboveLeft(CtuData[val1 - 11]);
	//CtuData[val1]->setCtuAboveRight(CtuData[val1 - 9]);

	////printf("%d\n",CtuData[11].size());
	//CtuData[val1 + 1]->setCtuLeft(CtuData[val1]);
	//CtuData[val1 + 10]->setCtuAbove(CtuData[val1]);
	//CtuData[val1 + 11]->setCtuAboveLeft(CtuData[val1]);
	//CtuData[val1 + 9]->setCtuAboveRight(CtuData[val1]);


	//CtuData[val2]->setCtuLeft(CtuData[val2 - 1]);
	//CtuData[val2]->setCtuAbove(CtuData[val2 - 10]);
	//CtuData[val2]->setCtuAboveLeft(CtuData[val2 - 11]);
	//CtuData[val2]->setCtuAboveRight(CtuData[val2 - 9]);

	////printf("%d\n",CtuData[11].size());
	//CtuData[val2 + 1]->setCtuLeft(CtuData[val2]);
	//CtuData[val2 + 10]->setCtuAbove(CtuData[val2]);
	//CtuData[val2 + 11]->setCtuAboveLeft(CtuData[val2]);
	//CtuData[val2 + 9]->setCtuAboveRight(CtuData[val2]);

	//CtuData[val3]->setCtuLeft(CtuData[val3 - 1]);
	//CtuData[val3]->setCtuAbove(CtuData[val3 - 10]);
	//CtuData[val3]->setCtuAboveLeft(CtuData[val3 - 11]);
	//CtuData[val3]->setCtuAboveRight(CtuData[val3 - 9]);

	////printf("%d\n",CtuData[11].size());
	//CtuData[val3 + 1]->setCtuLeft(CtuData[val3]);
	//CtuData[val3 + 10]->setCtuAbove(CtuData[val3]);
	//CtuData[val3 + 11]->setCtuAboveLeft(CtuData[val3]);
	//CtuData[val3 + 9]->setCtuAboveRight(CtuData[val3]);
	key_Idx.clear();
	swap_Idx.clear();
	return CtuData;
}

vector<TComDataCU*> SwapCtuWithInframe::swapCtuMainNew(vector<TComDataCU*> CtuData)
{
	vector<UInt> lockIdx;
	vector<UInt> keyIdx;
	vector<TComDataCU*> ctu;

	UInt boundingCtuTsAddr = CtuData[0]->getSlice()->getSliceSegmentCurEndCtuTsAddr();
	UInt startCtuTsAddr = CtuData[0]->getSlice()->getSliceSegmentCurStartCtuTsAddr();
	UInt CtuNumsInFrameWidth = CtuData[0]->getPic()->getPicSym()->getFrameWidthInCtus();
	UInt picWidth = CtuData[0]->getPic()->getPicYuvOrg()->getWidth(COMPONENT_Y);
	UInt ctuSize = picWidth / CtuNumsInFrameWidth;

	for (int i = 0; i < boundingCtuTsAddr - CtuNumsInFrameWidth; i++)
		lockIdx.push_back(boundingCtuTsAddr - CtuNumsInFrameWidth - i - 1);
	random_shuffle(lockIdx.begin(), lockIdx.end());

	//produce key
	SwapCu *swapCu;
	swapCu = new SwapCu();
	for (int i = 0; i < boundingCtuTsAddr - CtuNumsInFrameWidth; i++)
		keyIdx.push_back(boundingCtuTsAddr - CtuNumsInFrameWidth - i-1);
	keyIdx = swapCu->produceKeyIdx(lockIdx);

	//write key to file
	fstream f;
	f.open("CtuSwapKey.txt", ios::app);

	for (int i = 0; i < keyIdx.size(); i++)
	{
		f << keyIdx[i] << " ";
	}
	f << "\n";
	f.close();

	for (int i = 0; i < lockIdx.size(); i++)
	{
		ctu.push_back(CtuData[lockIdx[i]]);
	}
	for (int i = 0; i < CtuNumsInFrameWidth; i++)
		ctu.push_back(CtuData[lockIdx.size() + i]);
	//reset Addr
	for (int i = 0; i < lockIdx.size(); i++)
		ctu[i]->setCtuRsAddr(i);

	//reset CUcolocate
	for (int i = 0; i < lockIdx.size(); i++)
		ctu[i]->setCUColocated(REF_PIC_LIST_0,ctu[keyIdx[i]]->getCUColocated(REF_PIC_LIST_0));

	//reset CUpel
	for (int i = 0; i < lockIdx.size(); i++)
	{
		int CUpelX = (i%CtuNumsInFrameWidth)*ctuSize;
		int CUpelY = (i / CtuNumsInFrameWidth)*ctuSize;
		ctu[i]->setCUpelX(CUpelX);
		ctu[i]->setCUpelY(CUpelY);
	}

	//reset CTUref
	for (int i = 0; i < lockIdx.size(); i++)
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
	lockIdx.clear();
	return ctu;
}
