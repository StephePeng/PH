#include "SwapCu.h"
//
void SwapCu::swapCuMain(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	int maxDepth = getMaxDepth(pCtu);
	if (maxDepth >= 0)
	{
		//产生密钥
		/*vector<UInt> keyIdx;
		for (int i = 0; i < 4; i++)
			keyIdx.push_back(3-i);*/

		//random_shuffle(keyIdx.begin(), keyIdx.end());
		printf("keyIdx: ");
		for (int i = 0; i < keyIdx.size(); i++)
			printf("%d ", keyIdx[i]);
		printf("\n");
		swapWidth(pCtu, keyIdx);
		swapHeight(pCtu, keyIdx);
		swapDepth(pCtu, keyIdx);
		swapSkipFlag(pCtu, keyIdx);
		swapPartSize(pCtu, keyIdx);
		swapPredmode(pCtu, keyIdx);
		swapQP(pCtu, keyIdx);
		swapChromaQPAdj(pCtu, keyIdx);
		swapTransformSkip(pCtu, keyIdx);
		swapTransformIdx(pCtu, keyIdx);
		swapCbf(pCtu, keyIdx);
		swapTrCoeff(pCtu, keyIdx);
		swapArlCoeff(pCtu, keyIdx);
		swapMergeFlag(pCtu, keyIdx);
		swapMergeIdx(pCtu, keyIdx);
		swapIntraDir(pCtu, keyIdx);
		swapInterDir(pCtu, keyIdx);
		swapApiMVPIdx(pCtu, keyIdx);
		swapApiMVPNum(pCtu, keyIdx);
		swapIPCMFlag(pCtu, keyIdx);
		swapIPCMSample(pCtu, keyIdx);
		swapExplicitRdpcmMode(pCtu, keyIdx);
		swapCuMVField1(pCtu, keyIdx);
	}
}
//
void SwapCu::swapDepth(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> depthTemp1;
	vector<UChar> depthTemp2;
	vector<UChar> depthTemp3;
	vector<UChar> depthTemp4;

	int maxDepth = getMaxDepth(pCtu);
	if (maxDepth >= 2||true)
	{
		int numDepth = pCtu->getTotalNumPart();
		for (int i = 0; i < numDepth / 4; i++)
		{
			depthTemp1.push_back(pCtu->getDepth(i));
			depthTemp2.push_back(pCtu->getDepth(i + 64));
			depthTemp3.push_back(pCtu->getDepth(i + 128));
			depthTemp4.push_back(pCtu->getDepth(i + 192));
		}
		
		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setDepth(startIdx + j, depthTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setDepth(startIdx + j, depthTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setDepth(startIdx + j, depthTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setDepth(startIdx + j, depthTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
	int test = 1;
}

void SwapCu::swapSkipFlag(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Bool> temp1;
	vector<Bool> temp2;
	vector<Bool> temp3;
	vector<Bool> temp4;

	Bool *uiSkipFlag = pCtu->getSkipFlag();
	//printf("depth");
	/*for (int i = 0; i < pCtu->getNumPartitions(); i++)
	{
	printf("%d ", uiDepth[i]);
	}*/

	int maxDepth = getMaxDepth(pCtu);
	if (maxDepth >= 2 || true)
	{
		int numDepth = pCtu->getTotalNumPart();
		for (int i = 0; i < numDepth / 4; i++)
		{
			temp1.push_back(pCtu->getSkipFlag(i));
			temp2.push_back(pCtu->getSkipFlag(i + 64));
			temp3.push_back(pCtu->getSkipFlag(i + 128));
			temp4.push_back(pCtu->getSkipFlag(i + 192));
		}
		{
			//测试部分
			/*printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp1[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp2[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp3[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp4[i]);*/
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setSkipFlag(startIdx + j, temp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setSkipFlag(startIdx + j, temp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setSkipFlag(startIdx + j, temp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setSkipFlag(startIdx + j, temp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
		//测试部分
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getSkipFlag(i));
			}*/
		}
	}
}

void SwapCu::swapPartSize(TComDataCU *pCtu, vector<UInt> keyIdx)
{

	vector<SChar> temp1;
	vector<SChar> temp2;
	vector<SChar> temp3;
	vector<SChar> temp4;

	int maxDepth = getMaxDepth(pCtu);
	if (maxDepth >= 2 || true)
	{
		int numDepth = pCtu->getTotalNumPart();
		for (int i = 0; i < numDepth / 4; i++)
		{
			temp1.push_back(pCtu->getPartitionSize(i));
			temp2.push_back(pCtu->getPartitionSize(i + 64));
			temp3.push_back(pCtu->getPartitionSize(i + 128));
			temp4.push_back(pCtu->getPartitionSize(i + 192));
		}
		{
			//测试部分
			/*printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp1[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp2[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp3[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp4[i]);*/
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setPartitionSize(startIdx + j, static_cast<PartSize>(temp1[j]));
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setPartitionSize(startIdx + j, static_cast<PartSize>(temp2[j]));
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setPartitionSize(startIdx + j, static_cast<PartSize>(temp3[j]));
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setPartitionSize(startIdx + j, static_cast<PartSize>(temp4[j]));
				break;
			default:
				break;
			}
			startIdx += 64;
		}
		//测试部分
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getPartitionSize(i));
			}*/
		}
	}
	int test = 1;
}

void SwapCu::swapPredmode(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> temp1;
	vector<SChar> temp2;
	vector<SChar> temp3;
	vector<SChar> temp4;

	//printf("depth");
	/*for (int i = 0; i < pctu->getnumpartitions(); i++)
	{
	printf("%d ", uidepth[i]);
	}*/
	if (pCtu->getDepth(0) >= 2 || true)
	{
		int numdepth = pCtu->getTotalNumPart();
		for (int i = 0; i < numdepth / 4; i++)
		{
			temp1.push_back(pCtu->getPredictionMode(i));
			temp2.push_back(pCtu->getPredictionMode(i + 64));
			temp3.push_back(pCtu->getPredictionMode(i + 128));
			temp4.push_back(pCtu->getPredictionMode(i + 192));
		}
		{
			//测试部分
			/*printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp1[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp2[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp3[i]);
			printf("\n");
			for (int i = 0; i < temp1.size(); i++)
			printf("%d ", temp4[i]);*/
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp1[j]));
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp2[j]));
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp3[j]));
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp4[j]));
				break;
			default:
				break;
			}
			startIdx += 64;
		}
		//测试部分
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getPredictionMode(i));
			}*/
		}
	}
}

void SwapCu::swapCrossComponentPredictionAlpha(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> tempY1;
	vector<SChar> tempY2;
	vector<SChar> tempY3;
	vector<SChar> tempY4;

	vector<SChar> tempCb1;
	vector<SChar> tempCb2;
	vector<SChar> tempCb3;
	vector<SChar> tempCb4;

	vector<SChar> tempCr1;
	vector<SChar> tempCr2;
	vector<SChar> tempCr3;
	vector<SChar> tempCr4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			tempY1.push_back(pCtu->getCrossComponentPredictionAlpha(i, COMPONENT_Y));
			tempY2.push_back(pCtu->getCrossComponentPredictionAlpha(i + 64, COMPONENT_Y));
			tempY3.push_back(pCtu->getCrossComponentPredictionAlpha(i + 128, COMPONENT_Y));
			tempY4.push_back(pCtu->getCrossComponentPredictionAlpha(i + 192, COMPONENT_Y));

			tempCb1.push_back(pCtu->getCrossComponentPredictionAlpha(i, COMPONENT_Cb));
			tempCb2.push_back(pCtu->getCrossComponentPredictionAlpha(i + 64, COMPONENT_Cb));
			tempCb3.push_back(pCtu->getCrossComponentPredictionAlpha(i + 128, COMPONENT_Cb));
			tempCb4.push_back(pCtu->getCrossComponentPredictionAlpha(i + 192, COMPONENT_Cb));

			tempCr1.push_back(pCtu->getCrossComponentPredictionAlpha(i, COMPONENT_Cr));
			tempCr2.push_back(pCtu->getCrossComponentPredictionAlpha(i + 64, COMPONENT_Cr));
			tempCr3.push_back(pCtu->getCrossComponentPredictionAlpha(i + 128, COMPONENT_Cr));
			tempCr4.push_back(pCtu->getCrossComponentPredictionAlpha(i + 192, COMPONENT_Cr));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY1[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb1[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr1[j]);
				}
			case 1:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY2[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb2[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr2[j]);
				}
			case 2:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY3[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb3[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr3[j]);
				}
			case 3:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY4[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb4[j]);
					pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr4[j]);
				}
			default:
				break;
			}
		}
	}
}

void SwapCu::swapCUTransquantBypass(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Bool> temp1;
	vector<Bool> temp2;
	vector<Bool> temp3;
	vector<Bool> temp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			temp1.push_back(pCtu->getCUTransquantBypass(i));
			temp2.push_back(pCtu->getCUTransquantBypass(i + 64));
			temp3.push_back(pCtu->getCUTransquantBypass(i + 128));
			temp4.push_back(pCtu->getCUTransquantBypass(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setCUTransquantBypass(j + startIdx, temp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setCUTransquantBypass(j + startIdx, temp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setCUTransquantBypass(j + startIdx, temp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setCUTransquantBypass(j + startIdx, temp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapTransformIdx(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> transformIdxTemp1;
	vector<UChar> transformIdxTemp2;
	vector<UChar> transformIdxTemp3;
	vector<UChar> transformIdxTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			transformIdxTemp1.push_back(pCtu->getTransformIdx(i));
			transformIdxTemp2.push_back(pCtu->getTransformIdx(i + 64));
			transformIdxTemp3.push_back(pCtu->getTransformIdx(i + 128));
			transformIdxTemp4.push_back(pCtu->getTransformIdx(i + 192));
		}
		//测试vector向量
		{
			/*for (int i = 0; i < transformIdxTemp1.size(); i++)
			printf("%d ", transformIdxTemp1[i]);
			printf("\n");
			for (int i = 0; i < transformIdxTemp2.size(); i++)
			printf("%d ", transformIdxTemp2[i]);
			printf("\n");
			for (int i = 0; i < transformIdxTemp2.size(); i++)
			printf("%d ", transformIdxTemp3[i]);
			printf("\n");
			for (int i = 0; i < transformIdxTemp2.size(); i++)
			printf("%d ", transformIdxTemp4[i]);
			printf("\n\n");*/
		}
		//根据keyIdx扰乱
		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setTransformIdx(startIdx + j, transformIdxTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setTransformIdx(startIdx + j, transformIdxTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setTransformIdx(startIdx + j, transformIdxTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setTransformIdx(startIdx + j, transformIdxTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
		//测试交换后
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getTransformIdx(i));
			}
			printf("\n\n");*/
		}
		int test = 0;
	}
}

void SwapCu::swapTransformSkip(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> transformSkipYTemp1;
	vector<UChar> transformSkipYTemp2;
	vector<UChar> transformSkipYTemp3;
	vector<UChar> transformSkipYTemp4;

	vector<UChar> transformSkipCbTemp1;
	vector<UChar> transformSkipCbTemp2;
	vector<UChar> transformSkipCbTemp3;
	vector<UChar> transformSkipCbTemp4;

	vector<UChar> transformSkipCrTemp1;
	vector<UChar> transformSkipCrTemp2;
	vector<UChar> transformSkipCrTemp3;
	vector<UChar> transformSkipCrTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			transformSkipYTemp1.push_back(pCtu->getTransformSkip(i, COMPONENT_Y));
			transformSkipYTemp2.push_back(pCtu->getTransformSkip(i + 64, COMPONENT_Y));
			transformSkipYTemp3.push_back(pCtu->getTransformSkip(i + 128, COMPONENT_Y));
			transformSkipYTemp4.push_back(pCtu->getTransformSkip(i + 192, COMPONENT_Y));

			transformSkipCbTemp1.push_back(pCtu->getTransformSkip(i, COMPONENT_Cb));
			transformSkipCbTemp2.push_back(pCtu->getTransformSkip(i + 64, COMPONENT_Cb));
			transformSkipCbTemp3.push_back(pCtu->getTransformSkip(i + 128, COMPONENT_Cb));
			transformSkipCbTemp4.push_back(pCtu->getTransformSkip(i + 192, COMPONENT_Cb));

			transformSkipCrTemp1.push_back(pCtu->getTransformSkip(i, COMPONENT_Cr));
			transformSkipCrTemp2.push_back(pCtu->getTransformSkip(i + 64, COMPONENT_Cr));
			transformSkipCrTemp3.push_back(pCtu->getTransformSkip(i + 128, COMPONENT_Cr));
			transformSkipCrTemp4.push_back(pCtu->getTransformSkip(i + 192, COMPONENT_Cr));
		}
		//测试vector向量
		{
			/*for (int i = 0; i < transformSkipTemp1.size(); i++)
			printf("%d ", transformSkipTemp1[i]);
			printf("\n");
			for (int i = 0; i < transformSkipTemp2.size(); i++)
			printf("%d ", transformSkipTemp2[i]);
			printf("\n");
			for (int i = 0; i < transformSkipTemp3.size(); i++)
			printf("%d ", transformSkipTemp3[i]);
			printf("\n");
			for (int i = 0; i < transformSkipTemp4.size(); i++)
			printf("%d ", transformSkipTemp4[i]);
			printf("\n\n");*/
		}
		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setTransformSkip(startIdx + j, transformSkipYTemp1[j], COMPONENT_Y);
					pCtu->setTransformSkip(startIdx + j, transformSkipCbTemp1[j], COMPONENT_Cb);
					pCtu->setTransformSkip(startIdx + j, transformSkipCrTemp1[j], COMPONENT_Cr);
				}
				break;
			case 1:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setTransformSkip(startIdx + j, transformSkipYTemp2[j], COMPONENT_Y);
					pCtu->setTransformSkip(startIdx + j, transformSkipCbTemp2[j], COMPONENT_Cb);
					pCtu->setTransformSkip(startIdx + j, transformSkipCrTemp2[j], COMPONENT_Cr);
				}
				break;
			case 2:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setTransformSkip(startIdx + j, transformSkipYTemp3[j], COMPONENT_Y);
					pCtu->setTransformSkip(startIdx + j, transformSkipCbTemp3[j], COMPONENT_Cb);
					pCtu->setTransformSkip(startIdx + j, transformSkipCrTemp3[j], COMPONENT_Cr);
				}
				break;
			case 3:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setTransformSkip(startIdx + j, transformSkipYTemp4[j], COMPONENT_Y);
					pCtu->setTransformSkip(startIdx + j, transformSkipCbTemp4[j], COMPONENT_Cb);
					pCtu->setTransformSkip(startIdx + j, transformSkipCrTemp4[j], COMPONENT_Cr);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}

		//测试交换后的transformSkip
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getTransformSkip(i, COMPONENT_Y));
			}
			printf("\n");*/
		}
		int test = 0;
	}
}

void SwapCu::swapCbf(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> CbfYTemp1;
	vector<UChar> CbfYTemp2;
	vector<UChar> CbfYTemp3;
	vector<UChar> CbfYTemp4;

	vector<UChar> CbfCbTemp1;
	vector<UChar> CbfCbTemp2;
	vector<UChar> CbfCbTemp3;
	vector<UChar> CbfCbTemp4;

	vector<UChar> CbfCrTemp1;
	vector<UChar> CbfCrTemp2;
	vector<UChar> CbfCrTemp3;
	vector<UChar> CbfCrTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			CbfYTemp1.push_back(pCtu->getCbf(i, COMPONENT_Y));
			CbfYTemp2.push_back(pCtu->getCbf(i + 64, COMPONENT_Y));
			CbfYTemp3.push_back(pCtu->getCbf(i + 128, COMPONENT_Y));
			CbfYTemp4.push_back(pCtu->getCbf(i + 192, COMPONENT_Y));

			CbfCbTemp1.push_back(pCtu->getCbf(i, COMPONENT_Cb));
			CbfCbTemp2.push_back(pCtu->getCbf(i + 64, COMPONENT_Cb));
			CbfCbTemp3.push_back(pCtu->getCbf(i + 128, COMPONENT_Cb));
			CbfCbTemp4.push_back(pCtu->getCbf(i + 192, COMPONENT_Cb));

			CbfCrTemp1.push_back(pCtu->getCbf(i, COMPONENT_Cr));
			CbfCrTemp2.push_back(pCtu->getCbf(i + 64, COMPONENT_Cr));
			CbfCrTemp3.push_back(pCtu->getCbf(i + 128, COMPONENT_Cr));
			CbfCrTemp4.push_back(pCtu->getCbf(i + 192, COMPONENT_Cr));
		}
		//测试vector向量
		{
			/*for (int i = 0; i < CbfTemp1.size(); i++)
			printf("%d ", CbfTemp1[i]);
			printf("\n");
			for (int i = 0; i < CbfTemp2.size(); i++)
			printf("%d ", CbfTemp2[i]);
			printf("\n");
			for (int i = 0; i < CbfTemp3.size(); i++)
			printf("%d ", CbfTemp3[i]);
			printf("\n");
			for (int i = 0; i < CbfTemp4.size(); i++)
			printf("%d ", CbfTemp4[i]);
			printf("\n\n");*/
		}
		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCbf(startIdx + j, COMPONENT_Y, CbfYTemp1[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cb, CbfCbTemp1[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cr, CbfCrTemp1[j]);
				}
				break;
			case 1:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCbf(startIdx + j, COMPONENT_Y, CbfYTemp2[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cb, CbfCbTemp2[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cr, CbfCrTemp2[j]);
				}
				break;
			case 2:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCbf(startIdx + j, COMPONENT_Y, CbfYTemp3[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cb, CbfCbTemp3[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cr, CbfCrTemp3[j]);
				}
				break;
			case 3:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setCbf(startIdx + j, COMPONENT_Y, CbfYTemp4[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cb, CbfCbTemp4[j]);
					pCtu->setCbf(startIdx + j, COMPONENT_Cr, CbfCrTemp4[j]);
				}
				break;
			default:
				break;
			}
			startIdx += pCtu->getTotalNumPart() / 4;
		}

		//测试交换后的transformSkip
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getCbf(i, COMPONENT_Y));
			}
			printf("\n");*/
		}
		int test = 0;
	}
}

void SwapCu::swapTrCoeff(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<TCoeff> TrCoeffYTemp1;
	vector<TCoeff> TrCoeffYTemp2;
	vector<TCoeff> TrCoeffYTemp3;
	vector<TCoeff> TrCoeffYTemp4;

	vector<TCoeff> TrCoeffCbTemp1;
	vector<TCoeff> TrCoeffCbTemp2;
	vector<TCoeff> TrCoeffCbTemp3;
	vector<TCoeff> TrCoeffCbTemp4;

	vector<TCoeff> TrCoeffCrTemp1;
	vector<TCoeff> TrCoeffCrTemp2;
	vector<TCoeff> TrCoeffCrTemp3;
	vector<TCoeff> TrCoeffCrTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() * 4; i++)
		{
			TrCoeffYTemp1.push_back(pCtu->getCoeff(i, COMPONENT_Y));
			TrCoeffYTemp2.push_back(pCtu->getCoeff(i + 1024, COMPONENT_Y));
			TrCoeffYTemp3.push_back(pCtu->getCoeff(i + 2048, COMPONENT_Y));
			TrCoeffYTemp4.push_back(pCtu->getCoeff(i + 3072, COMPONENT_Y));
		}

		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			TrCoeffCbTemp1.push_back(pCtu->getCoeff(i, COMPONENT_Cb));
			TrCoeffCbTemp2.push_back(pCtu->getCoeff(i + 256, COMPONENT_Cb));
			TrCoeffCbTemp3.push_back(pCtu->getCoeff(i + 512, COMPONENT_Cb));
			TrCoeffCbTemp4.push_back(pCtu->getCoeff(i + 768, COMPONENT_Cb));

			TrCoeffCrTemp1.push_back(pCtu->getCoeff(i, COMPONENT_Cr));
			TrCoeffCrTemp2.push_back(pCtu->getCoeff(i + 256, COMPONENT_Cr));
			TrCoeffCrTemp3.push_back(pCtu->getCoeff(i + 512, COMPONENT_Cr));
			TrCoeffCrTemp4.push_back(pCtu->getCoeff(i + 768, COMPONENT_Cr));
		}

		//测试vector向量
		{
			/*for (int i = 0; i < TrCoeffTemp1.size(); i++)
			printf("%d ", TrCoeffTemp1[i]);
			printf("\n");
			for (int i = 0; i < TrCoeffTemp2.size(); i++)
			printf("%d ", TrCoeffTemp2[i]);
			printf("\n");
			for (int i = 0; i < TrCoeffTemp3.size(); i++)
			printf("%d ", TrCoeffTemp3[i]);
			printf("\n");
			for (int i = 0; i < TrCoeffTemp4.size(); i++)
			printf("%d ", TrCoeffTemp4[i]);
			printf("\n\n");*/
		}
		int startIdx1 = 0;
		int startIdx2 = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 1024; j++)
				{
					pCtu->setCoeff(startIdx1 + j, TrCoeffYTemp1[j], COMPONENT_Y);
				}
				for (int j = 0; j < 256; j++)
				{
					pCtu->setCoeff(startIdx2 + j, TrCoeffCbTemp1[j], COMPONENT_Cb);
					pCtu->setCoeff(startIdx2 + j, TrCoeffCrTemp1[j], COMPONENT_Cr);
				}
				break;
			case 1:
				for (int j = 0; j < 1024; j++)
				{
					pCtu->setCoeff(startIdx1 + j, TrCoeffYTemp2[j], COMPONENT_Y);
				}
				for (int j = 0; j < 256; j++)
				{
					pCtu->setCoeff(startIdx2 + j, TrCoeffCbTemp2[j], COMPONENT_Cb);
					pCtu->setCoeff(startIdx2 + j, TrCoeffCrTemp2[j], COMPONENT_Cr);
				}
				break;
			case 2:
				for (int j = 0; j < 1024; j++)
				{
					pCtu->setCoeff(startIdx1 + j, TrCoeffYTemp3[j], COMPONENT_Y);
				}
				for (int j = 0; j < 256; j++)
				{
					pCtu->setCoeff(startIdx2 + j, TrCoeffCbTemp3[j], COMPONENT_Cb);
					pCtu->setCoeff(startIdx2 + j, TrCoeffCrTemp3[j], COMPONENT_Cr);
				}
				break;
			case 3:
				for (int j = 0; j < 1024; j++)
				{
					pCtu->setCoeff(startIdx1 + j, TrCoeffYTemp4[j], COMPONENT_Y);
				}
				for (int j = 0; j < 256; j++)
				{
					pCtu->setCoeff(startIdx2 + j, TrCoeffCbTemp4[j], COMPONENT_Cb);
					pCtu->setCoeff(startIdx2 + j, TrCoeffCrTemp4[j], COMPONENT_Cr);
				}
				break;
			default:
				break;
			}
			startIdx1 += 1024;
			startIdx2 += 256;
		}

		//测试交换后的transformSkip
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getCoeff(i, COMPONENT_Y));
			}
			printf("\n");*/
		}
		int test = 0;
	}
}

void SwapCu::swapArlCoeff(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<TCoeff> ArlCoeffYTemp1;
	vector<TCoeff> ArlCoeffYTemp2;
	vector<TCoeff> ArlCoeffYTemp3;
	vector<TCoeff> ArlCoeffYTemp4;

	vector<TCoeff> ArlCoeffCbTemp1;
	vector<TCoeff> ArlCoeffCbTemp2;
	vector<TCoeff> ArlCoeffCbTemp3;
	vector<TCoeff> ArlCoeffCbTemp4;

	vector<TCoeff> ArlCoeffCrTemp1;
	vector<TCoeff> ArlCoeffCrTemp2;
	vector<TCoeff> ArlCoeffCrTemp3;
	vector<TCoeff> ArlCoeffCrTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			ArlCoeffYTemp1.push_back(pCtu->getArlCoeff(i, COMPONENT_Y));
			ArlCoeffYTemp2.push_back(pCtu->getArlCoeff(i + 64, COMPONENT_Y));
			ArlCoeffYTemp3.push_back(pCtu->getArlCoeff(i + 128, COMPONENT_Y));
			ArlCoeffYTemp4.push_back(pCtu->getArlCoeff(i + 192, COMPONENT_Y));

			ArlCoeffCbTemp1.push_back(pCtu->getArlCoeff(i, COMPONENT_Cb));
			ArlCoeffCbTemp2.push_back(pCtu->getArlCoeff(i + 64, COMPONENT_Cb));
			ArlCoeffCbTemp3.push_back(pCtu->getArlCoeff(i + 128, COMPONENT_Cb));
			ArlCoeffCbTemp4.push_back(pCtu->getArlCoeff(i + 192, COMPONENT_Cb));

			ArlCoeffCrTemp1.push_back(pCtu->getArlCoeff(i, COMPONENT_Cr));
			ArlCoeffCrTemp2.push_back(pCtu->getArlCoeff(i + 64, COMPONENT_Cr));
			ArlCoeffCrTemp3.push_back(pCtu->getArlCoeff(i + 128, COMPONENT_Cr));
			ArlCoeffCrTemp4.push_back(pCtu->getArlCoeff(i + 192, COMPONENT_Cr));
		}

		//测试vector向量
		{/*
		 for (int i = 0; i < ArlCoeffTemp1.size(); i++)
		 printf("%d ", ArlCoeffTemp1[i]);
		 printf("\n");
		 for (int i = 0; i < ArlCoeffTemp2.size(); i++)
		 printf("%d ", ArlCoeffTemp2[i]);
		 printf("\n");
		 for (int i = 0; i < ArlCoeffTemp3.size(); i++)
		 printf("%d ", ArlCoeffTemp3[i]);
		 printf("\n");
		 for (int i = 0; i < ArlCoeffTemp4.size(); i++)
		 printf("%d ", ArlCoeffTemp4[i]);
		 printf("\n\n");*/
		}
		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setArlCoeff(startIdx + j, ArlCoeffYTemp1[j], COMPONENT_Y);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCbTemp1[j], COMPONENT_Cb);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCrTemp1[j], COMPONENT_Cr);
				}
				break;
			case 1:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setArlCoeff(startIdx + j, ArlCoeffYTemp2[j], COMPONENT_Y);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCbTemp2[j], COMPONENT_Cb);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCrTemp2[j], COMPONENT_Cr);
				}
				break;
			case 2:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setArlCoeff(startIdx + j, ArlCoeffYTemp3[j], COMPONENT_Y);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCbTemp3[j], COMPONENT_Cb);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCrTemp3[j], COMPONENT_Cr);
				}
				break;
			case 3:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setArlCoeff(startIdx + j, ArlCoeffYTemp4[j], COMPONENT_Y);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCbTemp4[j], COMPONENT_Cb);
					pCtu->setArlCoeff(startIdx + j, ArlCoeffCrTemp4[j], COMPONENT_Cr);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}

		//测试交换后的transformSkip
		{
			/*for (int i = 0; i < pCtu->getTotalNumPart(); i++)
			{
			if (i % 16 == 0)
			printf("\n");
			printf("%d ", pCtu->getArlCoeff(i, COMPONENT_Y));
			}
			printf("\n");*/
		}
		int test = 0;
	}
}

void SwapCu::swapWidth(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> widthTemp1;
	vector<UChar> widthTemp2;
	vector<UChar> widthTemp3;
	vector<UChar> widthTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			widthTemp1.push_back(pCtu->getWidth(i));
			widthTemp2.push_back(pCtu->getWidth(i + 64));
			widthTemp3.push_back(pCtu->getWidth(i + 128));
			widthTemp4.push_back(pCtu->getWidth(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setWidth(startIdx + j, widthTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setWidth(startIdx + j, widthTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setWidth(startIdx + j, widthTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setWidth(startIdx + j, widthTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapHeight(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> heightTemp1;
	vector<UChar> heightTemp2;
	vector<UChar> heightTemp3;
	vector<UChar> heightTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			heightTemp1.push_back(pCtu->getHeight(i));
			heightTemp2.push_back(pCtu->getHeight(i + 64));
			heightTemp3.push_back(pCtu->getHeight(i + 128));
			heightTemp4.push_back(pCtu->getHeight(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setHeight(startIdx + j, heightTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setHeight(startIdx + j, heightTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setHeight(startIdx + j, heightTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setHeight(startIdx + j, heightTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapMergeFlag(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> mergeFlagTemp1;
	vector<UChar> mergeFlagTemp2;
	vector<UChar> mergeFlagTemp3;
	vector<UChar> mergeFlagTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			mergeFlagTemp1.push_back(pCtu->getMergeFlag(i));
			mergeFlagTemp2.push_back(pCtu->getMergeFlag(i + 64));
			mergeFlagTemp3.push_back(pCtu->getMergeFlag(i + 128));
			mergeFlagTemp4.push_back(pCtu->getMergeFlag(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeFlag(startIdx + j, mergeFlagTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeFlag(startIdx + j, mergeFlagTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeFlag(startIdx + j, mergeFlagTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeFlag(startIdx + j, mergeFlagTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapMergeIdx(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> mergeIdxTemp1;
	vector<UChar> mergeIdxTemp2;
	vector<UChar> mergeIdxTemp3;
	vector<UChar> mergeIdxTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			mergeIdxTemp1.push_back(pCtu->getMergeIndex(i));
			mergeIdxTemp2.push_back(pCtu->getMergeIndex(i + 64));
			mergeIdxTemp3.push_back(pCtu->getMergeIndex(i + 128));
			mergeIdxTemp4.push_back(pCtu->getMergeIndex(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeIndex(startIdx + j, mergeIdxTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeIndex(startIdx + j, mergeIdxTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeIndex(startIdx + j, mergeIdxTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setMergeIndex(startIdx + j, mergeIdxTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapIntraDir(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> intraDirLUMATemp1;
	vector<UChar> intraDirLUMATemp2;
	vector<UChar> intraDirLUMATemp3;
	vector<UChar> intraDirLUMATemp4;

	vector<UChar> intraDirCHROMATemp1;
	vector<UChar> intraDirCHROMATemp2;
	vector<UChar> intraDirCHROMATemp3;
	vector<UChar> intraDirCHROMATemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			intraDirLUMATemp1.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, i));
			intraDirCHROMATemp1.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, i));
			intraDirLUMATemp2.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, i + 64));
			intraDirCHROMATemp2.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, i + 64));
			intraDirLUMATemp3.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, i + 128));
			intraDirCHROMATemp3.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, i + 128));
			intraDirLUMATemp4.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, i + 192));
			intraDirCHROMATemp4.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setIntraDir(startIdx + j, intraDirLUMATemp1[j], CHANNEL_TYPE_LUMA);
					pCtu->setIntraDir(startIdx + j, intraDirCHROMATemp1[j], CHANNEL_TYPE_CHROMA);
				}
				break;
			case 1:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setIntraDir(startIdx + j, intraDirLUMATemp2[j], CHANNEL_TYPE_LUMA);
					pCtu->setIntraDir(startIdx + j, intraDirCHROMATemp2[j], CHANNEL_TYPE_CHROMA);
				}
				break;
			case 2:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setIntraDir(startIdx + j, intraDirLUMATemp3[j], CHANNEL_TYPE_LUMA);
					pCtu->setIntraDir(startIdx + j, intraDirCHROMATemp3[j], CHANNEL_TYPE_CHROMA);
				}
				break;
			case 3:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setIntraDir(startIdx + j, intraDirLUMATemp4[j], CHANNEL_TYPE_LUMA);
					pCtu->setIntraDir(startIdx + j, intraDirCHROMATemp4[j], CHANNEL_TYPE_CHROMA);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapInterDir(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> interDirTemp1;
	vector<UChar> interDirTemp2;
	vector<UChar> interDirTemp3;
	vector<UChar> interDirTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			interDirTemp1.push_back(pCtu->getInterDir(i));
			interDirTemp2.push_back(pCtu->getInterDir(i + 64));
			interDirTemp3.push_back(pCtu->getInterDir(i + 128));
			interDirTemp4.push_back(pCtu->getInterDir(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setInterDir(startIdx + j, interDirTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setInterDir(startIdx + j, interDirTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setInterDir(startIdx + j, interDirTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setInterDir(startIdx + j, interDirTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapApiMVPIdx(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Int> apiMVPRef0IdxTemp1;
	vector<Int> apiMVPRef0IdxTemp2;
	vector<Int> apiMVPRef0IdxTemp3;
	vector<Int> apiMVPRef0IdxTemp4;

	vector<Int> apiMVPRef1IdxTemp1;
	vector<Int> apiMVPRef1IdxTemp2;
	vector<Int> apiMVPRef1IdxTemp3;
	vector<Int> apiMVPRef1IdxTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			apiMVPRef0IdxTemp1.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, i));
			apiMVPRef0IdxTemp2.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, i + 64));
			apiMVPRef0IdxTemp3.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, i + 128));
			apiMVPRef0IdxTemp4.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, i + 192));

			apiMVPRef1IdxTemp1.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, i));
			apiMVPRef1IdxTemp2.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, i + 64));
			apiMVPRef1IdxTemp3.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, i + 128));
			apiMVPRef1IdxTemp4.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, apiMVPRef0IdxTemp1[j]);
					pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, apiMVPRef1IdxTemp1[j]);
				}
				break;
			case 1:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, apiMVPRef0IdxTemp2[j]);
					pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, apiMVPRef1IdxTemp2[j]);
				}
				break;
			case 2:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, apiMVPRef0IdxTemp3[j]);
					pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, apiMVPRef1IdxTemp3[j]);
				}
				break;
			case 3:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, apiMVPRef0IdxTemp4[j]);
					pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, apiMVPRef1IdxTemp4[j]);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapApiMVPNum(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Int> apiMVPRef0NumTemp1;
	vector<Int> apiMVPRef0NumTemp2;
	vector<Int> apiMVPRef0NumTemp3;
	vector<Int> apiMVPRef0NumTemp4;

	vector<Int> apiMVPRef1NumTemp1;
	vector<Int> apiMVPRef1NumTemp2;
	vector<Int> apiMVPRef1NumTemp3;
	vector<Int> apiMVPRef1NumTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			apiMVPRef0NumTemp1.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, i));
			apiMVPRef0NumTemp2.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, i + 64));
			apiMVPRef0NumTemp3.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, i + 128));
			apiMVPRef0NumTemp4.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, i + 192));

			apiMVPRef1NumTemp1.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, i));
			apiMVPRef1NumTemp2.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, i + 64));
			apiMVPRef1NumTemp3.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, i + 128));
			apiMVPRef1NumTemp4.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, apiMVPRef0NumTemp1[j]);
					pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, apiMVPRef1NumTemp1[j]);
				}
				break;
			case 1:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, apiMVPRef0NumTemp2[j]);
					pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, apiMVPRef1NumTemp2[j]);
				}
				break;
			case 2:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, apiMVPRef0NumTemp3[j]);
					pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, apiMVPRef1NumTemp3[j]);
				}
				break;
			case 3:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, apiMVPRef0NumTemp4[j]);
					pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, apiMVPRef1NumTemp4[j]);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapIPCMFlag(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Bool> iPCMFlagTemp1;
	vector<Bool> iPCMFlagTemp2;
	vector<Bool> iPCMFlagTemp3;
	vector<Bool> iPCMFlagTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			iPCMFlagTemp1.push_back(pCtu->getIPCMFlag(i));
			iPCMFlagTemp2.push_back(pCtu->getIPCMFlag(i + 64));
			iPCMFlagTemp3.push_back(pCtu->getIPCMFlag(i + 128));
			iPCMFlagTemp4.push_back(pCtu->getIPCMFlag(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setIPCMFlag(startIdx + j, iPCMFlagTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setIPCMFlag(startIdx + j, iPCMFlagTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setIPCMFlag(startIdx + j, iPCMFlagTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setIPCMFlag(startIdx + j, iPCMFlagTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}

}

void SwapCu::swapExplicitRdpcmMode(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> explicitRdpcmModeYTemp1;
	vector<UChar> explicitRdpcmModeYTemp2;
	vector<UChar> explicitRdpcmModeYTemp3;
	vector<UChar> explicitRdpcmModeYTemp4;

	vector<UChar> explicitRdpcmModeCbTemp1;
	vector<UChar> explicitRdpcmModeCbTemp2;
	vector<UChar> explicitRdpcmModeCbTemp3;
	vector<UChar> explicitRdpcmModeCbTemp4;

	vector<UChar> explicitRdpcmModeCrTemp1;
	vector<UChar> explicitRdpcmModeCrTemp2;
	vector<UChar> explicitRdpcmModeCrTemp3;
	vector<UChar> explicitRdpcmModeCrTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			explicitRdpcmModeYTemp1.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, i));
			explicitRdpcmModeYTemp2.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, i + 64));
			explicitRdpcmModeYTemp3.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, i + 128));
			explicitRdpcmModeYTemp4.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, i + 192));

			explicitRdpcmModeCbTemp1.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, i));
			explicitRdpcmModeCbTemp2.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, i + 64));
			explicitRdpcmModeCbTemp3.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, i + 128));
			explicitRdpcmModeCbTemp4.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, i + 192));

			explicitRdpcmModeCrTemp1.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, i));
			explicitRdpcmModeCrTemp2.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, i + 64));
			explicitRdpcmModeCrTemp3.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, i + 128));
			explicitRdpcmModeCrTemp4.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, explicitRdpcmModeYTemp1[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, explicitRdpcmModeCbTemp1[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, explicitRdpcmModeCrTemp1[j]);
				}
				break;
			case 1:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, explicitRdpcmModeYTemp2[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, explicitRdpcmModeCbTemp2[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, explicitRdpcmModeCrTemp2[j]);
				}
				break;
			case 2:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, explicitRdpcmModeYTemp3[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, explicitRdpcmModeCbTemp3[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, explicitRdpcmModeCrTemp3[j]);
				}
				break;
			case 3:
				for (int j = 0; j < 64; j++)
				{
					pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, explicitRdpcmModeYTemp4[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, explicitRdpcmModeCbTemp4[j]);
					pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, explicitRdpcmModeCrTemp4[j]);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapQP(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> QPTemp1;
	vector<SChar> QPTemp2;
	vector<SChar> QPTemp3;
	vector<SChar> QPTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			QPTemp1.push_back(pCtu->getQP(i));
			QPTemp2.push_back(pCtu->getQP(i + 64));
			QPTemp3.push_back(pCtu->getQP(i + 128));
			QPTemp4.push_back(pCtu->getQP(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setQP(startIdx + j, QPTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setQP(startIdx + j, QPTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setQP(startIdx + j, QPTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setQP(startIdx + j, QPTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}

	}
}

void SwapCu::swapChromaQPAdj(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> chromaQPAdjTemp1;
	vector<UChar> chromaQPAdjTemp2;
	vector<UChar> chromaQPAdjTemp3;
	vector<UChar> chromaQPAdjTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			chromaQPAdjTemp1.push_back(pCtu->getChromaQpAdj(i));
			chromaQPAdjTemp2.push_back(pCtu->getChromaQpAdj(i + 64));
			chromaQPAdjTemp3.push_back(pCtu->getChromaQpAdj(i + 128));
			chromaQPAdjTemp4.push_back(pCtu->getChromaQpAdj(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
					pCtu->setChromaQpAdj(startIdx + j, chromaQPAdjTemp1[j]);
				break;
			case 1:
				for (int j = 0; j < 64; j++)
					pCtu->setChromaQpAdj(startIdx + j, chromaQPAdjTemp2[j]);
				break;
			case 2:
				for (int j = 0; j < 64; j++)
					pCtu->setChromaQpAdj(startIdx + j, chromaQPAdjTemp3[j]);
				break;
			case 3:
				for (int j = 0; j < 64; j++)
					pCtu->setChromaQpAdj(startIdx + j, chromaQPAdjTemp4[j]);
				break;
			default:
				break;
			}
			startIdx += 64;
		}

	}
}

void SwapCu::swapCuMVField1(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<TComMv> MvRef0Temp1;
	vector<TComMv> MvRef0Temp2;
	vector<TComMv> MvRef0Temp3;
	vector<TComMv> MvRef0Temp4;

	vector<TComMv> MvRef1Temp1;
	vector<TComMv> MvRef1Temp2;
	vector<TComMv> MvRef1Temp3;
	vector<TComMv> MvRef1Temp4;

	vector<TComMv> MvdRef0Temp1;
	vector<TComMv> MvdRef0Temp2;
	vector<TComMv> MvdRef0Temp3;
	vector<TComMv> MvdRef0Temp4;

	vector<TComMv> MvdRef1Temp1;
	vector<TComMv> MvdRef1Temp2;
	vector<TComMv> MvdRef1Temp3;
	vector<TComMv> MvdRef1Temp4;

	vector<UChar> refIdxRef0Temp1;
	vector<UChar> refIdxRef0Temp2;
	vector<UChar> refIdxRef0Temp3;
	vector<UChar> refIdxRef0Temp4;

	vector<UChar> refIdxRef1Temp1;
	vector<UChar> refIdxRef1Temp2;
	vector<UChar> refIdxRef1Temp3;
	vector<UChar> refIdxRef1Temp4;

	int maxDepth = getMaxDepth(pCtu);
	if (maxDepth >= 2 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			MvRef0Temp1.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i));
			MvRef0Temp2.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 64));
			MvRef0Temp3.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 128));
			MvRef0Temp4.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 192));

			MvRef1Temp1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i));
			MvRef1Temp2.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i + 64));
			MvRef1Temp3.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i + 128));
			MvRef1Temp4.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i + 192));

			MvdRef0Temp1.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i));
			MvdRef0Temp2.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 64));
			MvdRef0Temp3.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 128));
			MvdRef0Temp4.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 192));

			MvdRef1Temp1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i));
			MvdRef1Temp2.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i + 64));
			MvdRef1Temp3.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i + 128));
			MvdRef1Temp4.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i + 192));

			refIdxRef0Temp1.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));
			refIdxRef0Temp2.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i + 64));
			refIdxRef0Temp3.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i + 128));
			refIdxRef0Temp4.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i + 192));

			refIdxRef1Temp1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i));
			refIdxRef1Temp2.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i + 64));
			refIdxRef1Temp3.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i + 128));
			refIdxRef1Temp4.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i + 192));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < 64; j++)
				{
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0Temp1[j]);
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0Temp1[j]);
				    pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0Temp1[j]);

					pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1Temp1[j]);
					pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1Temp1[j]);
					pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1Temp1[j]);
				}
				break;
			case 1:
				for (int j = 0; j < 64; j++)
				{
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0Temp2[j]);
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0Temp2[j]);
				    pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0Temp2[j]);

					pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1Temp2[j]);
					pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1Temp2[j]);
					pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1Temp2[j]);
				}
				break;
			case 2:
				for (int j = 0; j < 64; j++)
				{
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0Temp3[j]);
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0Temp3[j]);
					pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0Temp3[j]);

					pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1Temp3[j]);
					pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1Temp3[j]);
					pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1Temp3[j]);
				}
				break;
			case 3:
				for (int j = 0; j < 64; j++)
				{
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0Temp4[j]);
					pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0Temp4[j]);
					pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0Temp4[j]);

					pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1Temp4[j]);
					pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1Temp4[j]);
				    pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1Temp4[j]);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

void SwapCu::swapIPCMSample(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Pel> PCMSampleYTemp1;
	vector<Pel> PCMSampleYTemp2;
	vector<Pel> PCMSampleYTemp3;
	vector<Pel> PCMSampleYTemp4;

	vector<Pel> PCMSampleCbTemp1;
	vector<Pel> PCMSampleCbTemp2;
	vector<Pel> PCMSampleCbTemp3;
	vector<Pel> PCMSampleCbTemp4;

	vector<Pel> PCMSampleCrTemp1;
	vector<Pel> PCMSampleCrTemp2;
	vector<Pel> PCMSampleCrTemp3;
	vector<Pel> PCMSampleCrTemp4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth != 0 || true)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			PCMSampleYTemp1.push_back(pCtu->getPCMSample(i, COMPONENT_Y));
			PCMSampleYTemp2.push_back(pCtu->getPCMSample(i + 64, COMPONENT_Y));
			PCMSampleYTemp3.push_back(pCtu->getPCMSample(i + 128, COMPONENT_Y));
			PCMSampleYTemp4.push_back(pCtu->getPCMSample(i + 192, COMPONENT_Y));

			PCMSampleCbTemp1.push_back(pCtu->getPCMSample(i, COMPONENT_Cb));
			PCMSampleCbTemp2.push_back(pCtu->getPCMSample(i + 64, COMPONENT_Cb));
			PCMSampleCbTemp3.push_back(pCtu->getPCMSample(i + 128, COMPONENT_Cb));
			PCMSampleCbTemp4.push_back(pCtu->getPCMSample(i + 192, COMPONENT_Cb));

			PCMSampleCrTemp1.push_back(pCtu->getPCMSample(i, COMPONENT_Cr));
			PCMSampleCrTemp2.push_back(pCtu->getPCMSample(i + 64, COMPONENT_Cr));
			PCMSampleCrTemp3.push_back(pCtu->getPCMSample(i + 128, COMPONENT_Cr));
			PCMSampleCrTemp4.push_back(pCtu->getPCMSample(i + 192, COMPONENT_Cr));
		}

		int startIdx = 0;
		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setPCMSample(startIdx + j, PCMSampleYTemp1[j], COMPONENT_Y);
					pCtu->setPCMSample(startIdx + j, PCMSampleCbTemp1[j], COMPONENT_Cb);
					pCtu->setPCMSample(startIdx + j, PCMSampleCrTemp1[j], COMPONENT_Cr);
				}
				break;
			case 1:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setPCMSample(startIdx + j, PCMSampleYTemp2[j], COMPONENT_Y);
					pCtu->setPCMSample(startIdx + j, PCMSampleCbTemp2[j], COMPONENT_Cb);
					pCtu->setPCMSample(startIdx + j, PCMSampleCrTemp2[j], COMPONENT_Cr);
				}
				break;
			case 2:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setPCMSample(startIdx + j, PCMSampleYTemp3[j], COMPONENT_Y);
					pCtu->setPCMSample(startIdx + j, PCMSampleCbTemp3[j], COMPONENT_Cb);
					pCtu->setPCMSample(startIdx + j, PCMSampleCrTemp3[j], COMPONENT_Cr);
				}
				break;
			case 3:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					pCtu->setPCMSample(startIdx + j, PCMSampleYTemp4[j], COMPONENT_Y);
					pCtu->setPCMSample(startIdx + j, PCMSampleCbTemp4[j], COMPONENT_Cb);
					pCtu->setPCMSample(startIdx + j, PCMSampleCrTemp4[j], COMPONENT_Cr);
				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}


	}


}

int SwapCu::getMaxDepth(TComDataCU *pCtu)
{
	int maxDepth = -1;
	for (int i = 0; i < pCtu->getTotalNumPart(); i++)
	{
		if (pCtu->getDepth(i) > maxDepth)
		{
			maxDepth = pCtu->getDepth(i);
		}
	}
	return maxDepth;
}

void SwapCu::swapTotalCu(TComDataCU *pCtu)
{
	vector<SChar> QP;

	int maxDepth = getMaxDepth(pCtu);

	for (int i = 0; i < pCtu->getTotalNumPart(); i++)
	{
		QP.push_back(pCtu->getQP(i));
	}
	for (int i = 0; i < maxDepth; i++)
	{
		vector<SChar> QPTemp1;
		vector<SChar> QPTemp2;
		vector<SChar> QPTemp3;
		vector<SChar> QPTemp4;


	}
}

void SwapCu::swapCuMVField2(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<short> MvHor1;
	vector<short> MvHor2;
	vector<short> MvHor3;
	vector<short> MvHor4;

	vector<short> MvVer1;
	vector<short> MvVer2;
	vector<short> MvVer3;
	vector<short> MvVer4;


	vector<short> MvdHor1;
	vector<short> MvdHor2;
	vector<short> MvdHor3;
	vector<short> MvdHor4;

	vector<short> MvdVer1;
	vector<short> MvdVer2;
	vector<short> MvdVer3;
	vector<short> MvdVer4;

	int maxDepth = getMaxDepth(pCtu);

	if (maxDepth != 0)
	{
		for (int i = 0; i < pCtu->getTotalNumPart() / 4; i++)
		{
			MvHor1.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor());
			MvHor2.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 64).getHor());
			MvHor3.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 128).getHor());
			MvHor4.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 192).getHor());

			MvVer1.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer());
			MvVer2.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 64).getVer());
			MvVer3.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 128).getVer());
			MvVer4.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 192).getVer());

			MvdHor1.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getHor());
			MvdHor2.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 64).getHor());
			MvdHor3.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 128).getHor());
			MvdHor4.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 192).getHor());

			MvdVer1.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getVer());
			MvdVer2.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 64).getVer());
			MvdVer3.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 128).getVer());
			MvdVer4.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 192).getVer());
		}

		int startIdx = 0;

		for (int i = 0; i < keyIdx.size(); i++)
		{
			switch (keyIdx[i])
			{
			case 0:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					TComMv Mv = pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(startIdx + j);
					Mv.setHor(MvHor1[j]);
					Mv.setVer(MvVer1[j]);

					TComMv Mvd = pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(startIdx + j);
					Mvd.setHor(MvdHor1[j]);
					Mvd.setVer(MvdVer1[j]);

				}
				break;
			case 1:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					TComMv Mv = pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(startIdx + j);
					Mv.setHor(MvHor2[j]);
					Mv.setVer(MvVer2[j]);

					TComMv Mvd = pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(startIdx + j);
					Mvd.setHor(MvdHor2[j]);
					Mvd.setVer(MvdVer2[j]);

				}
				break;
			case 2:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					TComMv Mv = pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(startIdx + j);
					Mv.setHor(MvHor3[j]);
					Mv.setVer(MvVer3[j]);

					TComMv Mvd = pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(startIdx + j);
					Mvd.setHor(MvdHor3[j]);
					Mvd.setVer(MvdVer3[j]);

				}
				break;
			case 3:
				for (int j = 0; j < pCtu->getTotalNumPart() / 4; j++)
				{
					TComMv Mv = pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(startIdx + j);
					Mv.setHor(MvHor4[j]);
					Mv.setVer(MvVer4[j]);

					TComMv Mvd = pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(startIdx + j);
					Mvd.setHor(MvdHor4[j]);
					Mvd.setVer(MvdVer4[j]);

				}
				break;
			default:
				break;
			}
			startIdx += 64;
		}
	}
}

vector<UInt> SwapCu::produceKeyIdx(vector<UInt> lockIdx)
{
	vector<UInt> keyIdx;
	for (int i = 0; i < lockIdx.size(); i++)
	{
		for (int j = 0; j < lockIdx.size(); j++)
		{
			if (lockIdx[j] == i)
				keyIdx.push_back(j);
		}
	}
	return keyIdx;
}