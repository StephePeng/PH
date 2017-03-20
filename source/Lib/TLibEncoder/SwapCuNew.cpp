#include "SwapCuNew.h"

void SwapCuNew::swapCuMainNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	swapWidthNew(pCtu, keyIdx);
	swapHeightNew(pCtu, keyIdx);
	swapDepthNew(pCtu, keyIdx);
	swapSkipFlagNew(pCtu, keyIdx);
	swapPartSizeNew(pCtu, keyIdx);
	swapPredmodeNew(pCtu, keyIdx);
	swapCrossComponentPredictionAlphaNew(pCtu, keyIdx);
	swapCUTransquantBypassNew(pCtu, keyIdx);
	swapQPNew(pCtu, keyIdx);
	swapChromaQPAdjNew(pCtu, keyIdx);
	swapTransformIdxNew(pCtu, keyIdx);
	swapTransformSkipNew(pCtu, keyIdx);
	swapCbfNew(pCtu, keyIdx);
	swapTrCoeffNew(pCtu, keyIdx);
	swapArlCoeffNew(pCtu, keyIdx);
	swapMergeFlagNew(pCtu, keyIdx);
	swapMergeIdxNew(pCtu, keyIdx);
	swapIntraDirNew(pCtu, keyIdx);
	swapInterDirNew(pCtu, keyIdx);
	swapApiMVPIdxNew(pCtu, keyIdx);
	swapApiMVPNumNew(pCtu, keyIdx);
	swapIPCMFlagNew(pCtu, keyIdx);
	swapIPCMSampleNew(pCtu, keyIdx);
	swapCuMVFieldNew(pCtu, keyIdx);
	swapExplicitRdpcmModeNew(pCtu, keyIdx);
}

void SwapCuNew::swapWidthNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	for (int i = 0; i < pCtu->getTotalNumPart(); i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%d ", pCtu->getWidth(i));
		int debug = 0;
	}
	printf("\n");
	vector<UChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1;
		vector<UChar> X2;
		vector<UChar> X3;
		vector<UChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getWidth(startIdx + j));
			X2.push_back(pCtu->getWidth(startIdx + j + 16));
			X3.push_back(pCtu->getWidth(startIdx + j + 32));
			X4.push_back(pCtu->getWidth(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setWidth(startIdx+j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setWidth(startIdx+j, temp[j+64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setWidth(startIdx+j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setWidth(startIdx+j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

	for (int i = 0; i < pCtu->getTotalNumPart(); i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%d ", pCtu->getWidth(i));
	}
 }
void SwapCuNew::swapHeightNew(TComDataCU *pCtu, vector<UInt> keyIdx)
 {
	 vector<UChar> temp;
	 int startIdx;
	 startIdx = 0;

	 for (int i = 0; i < 4; i++)
	 {
		 vector<UChar> X1;
		 vector<UChar> X2;
		 vector<UChar> X3;
		 vector<UChar> X4;

		 for (int j = 0; j < 16; j++)
		 {
			 X1.push_back(pCtu->getHeight(startIdx + j));
			 X2.push_back(pCtu->getHeight(startIdx + j + 16));
			 X3.push_back(pCtu->getHeight(startIdx + j + 32));
			 X4.push_back(pCtu->getHeight(startIdx + j + 48));
		 }

		 for (int k = 0; k < keyIdx.size(); k++)
		 {
			 switch (keyIdx[k])
			 {
			 case 0:
				 for (int kk = 0; kk < 16; kk++)
				 {
					 temp.push_back(X1[kk]);
				 }
				 break;
			 case 1:
				 for (int kk = 0; kk < 16; kk++)
				 {
					 temp.push_back(X2[kk]);
				 }
				 break;
			 case 2:
				 for (int kk = 0; kk < 16; kk++)
				 {
					 temp.push_back(X3[kk]);
				 }
				 break;
			 case 3:
				 for (int kk = 0; kk < 16; kk++)
				 {
					 temp.push_back(X4[kk]);
				 }
				 break;
			 default:
				 break;
			 }
		 }
		 startIdx += 64;
	 }

	 startIdx = 0;
	 for (int i = 0; i < 4; i++)
	 {
		 switch (keyIdx[i])
		 {
		 case 0:
			 for (int j = 0; j < 64; j++)
			 {
				 pCtu->setHeight(startIdx + j, temp[j]);
			 }
			 break;
		 case 1:
			 for (int j = 0; j < 64; j++)
			 {
				 pCtu->setHeight(startIdx + j, temp[j + 64]);
			 }
			 break;
		 case 2:
			 for (int j = 0; j < 64; j++)
			 {
				 pCtu->setHeight(startIdx + j, temp[j + 128]);
			 }
			 break;
		 case 3:
			 for (int j = 0; j < 64; j++)
			 {
				 pCtu->setHeight(startIdx + j, temp[j + 192]);
			 }
			 break;
		 default:
			 break;
		 }
		 startIdx += 64;
	 }

 }
void SwapCuNew::swapDepthNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1;
		vector<UChar> X2;
		vector<UChar> X3;
		vector<UChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getDepth(startIdx + j));
			X2.push_back(pCtu->getDepth(startIdx + j + 16));
			X3.push_back(pCtu->getDepth(startIdx + j + 32));
			X4.push_back(pCtu->getDepth(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapSkipFlagNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Bool> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<Bool> X1;
		vector<Bool> X2;
		vector<Bool> X3;
		vector<Bool> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getSkipFlag(startIdx + j));
			X2.push_back(pCtu->getSkipFlag(startIdx + j + 16));
			X3.push_back(pCtu->getSkipFlag(startIdx + j + 32));
			X4.push_back(pCtu->getSkipFlag(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setSkipFlag(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setSkipFlag(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setSkipFlag(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setSkipFlag(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapPartSizeNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<SChar> X1;
		vector<SChar> X2;
		vector<SChar> X3;
		vector<SChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getPartitionSize(startIdx + j));
			X2.push_back(pCtu->getPartitionSize(startIdx + j + 16));
			X3.push_back(pCtu->getPartitionSize(startIdx + j + 32));
			X4.push_back(pCtu->getPartitionSize(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, static_cast<PartSize>(temp[j]));
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, static_cast<PartSize>(temp[j + 64]));
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, static_cast<PartSize>(temp[j + 128]));
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setDepth(startIdx + j, static_cast<PartSize>(temp[j + 192]));
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapPredmodeNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<SChar> X1;
		vector<SChar> X2;
		vector<SChar> X3;
		vector<SChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getPredictionMode(startIdx + j));
			X2.push_back(pCtu->getPredictionMode(startIdx + j + 16));
			X3.push_back(pCtu->getPredictionMode(startIdx + j + 32));
			X4.push_back(pCtu->getPredictionMode(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp[j]));
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp[j + 64]));
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp[j + 128]));
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPredictionMode(startIdx + j, static_cast<PredMode>(temp[j + 192]));
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapCrossComponentPredictionAlphaNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> tempY;
	vector<UChar> tempCb;
	vector<UChar> tempCr;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1Y;
		vector<UChar> X1Cb;
		vector<UChar> X1Cr;

		vector<UChar> X2Y;
		vector<UChar> X2Cb;
		vector<UChar> X2Cr;

		vector<UChar> X3Y;
		vector<UChar> X3Cb;
		vector<UChar> X3Cr;

		vector<UChar> X4Y;
		vector<UChar> X4Cb;
		vector<UChar> X4Cr;

		for (int j = 0; j < 16; j++)
		{
			X1Y.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j,COMPONENT_Y));
			X1Cb.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb));
			X1Cr.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr));

			X2Y.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 16,COMPONENT_Y));
			X2Cb.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 16,COMPONENT_Cb));
			X2Cr.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 16,COMPONENT_Cr));

			X3Y.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 32,COMPONENT_Y));
			X3Cb.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 32,COMPONENT_Cb));
			X3Cr.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 32,COMPONENT_Cr));

			X4Y.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 48,COMPONENT_Y));
			X4Cb.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 48, COMPONENT_Cb));
			X4Cr.push_back(pCtu->getCrossComponentPredictionAlpha(startIdx + j + 48, COMPONENT_Cr));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X1Y[kk]);
					tempCb.push_back(X1Cb[kk]);
					tempCr.push_back(X1Cr[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X2Y[kk]);
					tempCb.push_back(X2Cb[kk]);
					tempCr.push_back(X2Cr[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X3Y[kk]);
					tempCb.push_back(X3Cb[kk]);
					tempCr.push_back(X3Cr[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X4Y[kk]);
					tempCb.push_back(X4Cb[kk]);
					tempCr.push_back(X4Cr[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY[j]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb[j]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY[j + 64]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb[j + 64]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY[j + 128]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb[j + 128]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Y, tempY[j + 192]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cb, tempCb[j + 192]);
				pCtu->setCrossComponentPredictionAlpha(startIdx + j, COMPONENT_Cr, tempCr[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapCUTransquantBypassNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Bool> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<Bool> X1;
		vector<Bool> X2;
		vector<Bool> X3;
		vector<Bool> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getCUTransquantBypass(startIdx + j));
			X2.push_back(pCtu->getCUTransquantBypass(startIdx + j + 16));
			X3.push_back(pCtu->getCUTransquantBypass(startIdx + j + 32));
			X4.push_back(pCtu->getCUTransquantBypass(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCUTransquantBypass(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCUTransquantBypass(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCUTransquantBypass(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCUTransquantBypass(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapQPNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<SChar> X1;
		vector<SChar> X2;
		vector<SChar> X3;
		vector<SChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getQP(startIdx + j));
			X2.push_back(pCtu->getQP(startIdx + j + 16));
			X3.push_back(pCtu->getQP(startIdx + j + 32));
			X4.push_back(pCtu->getQP(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setQP(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setQP(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setQP(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setQP(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}
}
void SwapCuNew::swapChromaQPAdjNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1;
		vector<UChar> X2;
		vector<UChar> X3;
		vector<UChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getChromaQpAdj(startIdx + j));
			X2.push_back(pCtu->getChromaQpAdj(startIdx + j + 16));
			X3.push_back(pCtu->getChromaQpAdj(startIdx + j + 32));
			X4.push_back(pCtu->getChromaQpAdj(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setChromaQpAdj(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setChromaQpAdj(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setChromaQpAdj(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setChromaQpAdj(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapTransformIdxNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1;
		vector<UChar> X2;
		vector<UChar> X3;
		vector<UChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getTransformIdx(startIdx + j));
			X2.push_back(pCtu->getTransformIdx(startIdx + j + 16));
			X3.push_back(pCtu->getTransformIdx(startIdx + j + 32));
			X4.push_back(pCtu->getTransformIdx(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformIdx(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformIdx(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformIdx(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformIdx(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapTransformSkipNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> tempY;
	vector<UChar> tempCb;
	vector<UChar> tempCr;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1Y;
		vector<UChar> X1Cb;
		vector<UChar> X1Cr;

		vector<UChar> X2Y;
		vector<UChar> X2Cb;
		vector<UChar> X2Cr;

		vector<UChar> X3Y;
		vector<UChar> X3Cb;
		vector<UChar> X3Cr;

		vector<UChar> X4Y;
		vector<UChar> X4Cb;
		vector<UChar> X4Cr;

		for (int j = 0; j < 16; j++)
		{
			X1Y.push_back(pCtu->getTransformSkip(startIdx + j, COMPONENT_Y));
			X1Cb.push_back(pCtu->getTransformSkip(startIdx + j, COMPONENT_Cb));
			X1Cr.push_back(pCtu->getTransformSkip(startIdx + j, COMPONENT_Cr));

			X2Y.push_back(pCtu->getTransformSkip(startIdx + j + 16, COMPONENT_Y));
			X2Cb.push_back(pCtu->getTransformSkip(startIdx + j + 16, COMPONENT_Cb));
			X2Cr.push_back(pCtu->getTransformSkip(startIdx + j + 16, COMPONENT_Cr));

			X3Y.push_back(pCtu->getTransformSkip(startIdx + j + 32, COMPONENT_Y));
			X3Cb.push_back(pCtu->getTransformSkip(startIdx + j + 32, COMPONENT_Cb));
			X3Cr.push_back(pCtu->getTransformSkip(startIdx + j + 32, COMPONENT_Cr));

			X4Y.push_back(pCtu->getTransformSkip(startIdx + j + 48, COMPONENT_Y));
			X4Cb.push_back(pCtu->getTransformSkip(startIdx + j + 48, COMPONENT_Cb));
			X4Cr.push_back(pCtu->getTransformSkip(startIdx + j + 48, COMPONENT_Cr));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X1Y[kk]);
					tempCb.push_back(X1Cb[kk]);
					tempCr.push_back(X1Cr[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X2Y[kk]);
					tempCb.push_back(X2Cb[kk]);
					tempCr.push_back(X2Cr[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X3Y[kk]);
					tempCb.push_back(X3Cb[kk]);
					tempCr.push_back(X3Cr[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X4Y[kk]);
					tempCb.push_back(X4Cb[kk]);
					tempCr.push_back(X4Cr[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformSkip(startIdx + j, tempY[j], COMPONENT_Y);
				pCtu->setTransformSkip(startIdx + j, tempCb[j], COMPONENT_Cb);
				pCtu->setTransformSkip(startIdx + j, tempCr[j], COMPONENT_Cr);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformSkip(startIdx + j, tempY[j + 64], COMPONENT_Y);
				pCtu->setTransformSkip(startIdx + j, tempCb[j + 64], COMPONENT_Cb);
				pCtu->setTransformSkip(startIdx + j, tempCr[j + 64], COMPONENT_Cr);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformSkip(startIdx + j, tempY[j + 128], COMPONENT_Y);
				pCtu->setTransformSkip(startIdx + j, tempCb[j + 128], COMPONENT_Cb);
				pCtu->setTransformSkip(startIdx + j, tempCr[j + 128], COMPONENT_Cr);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setTransformSkip(startIdx + j, tempY[j + 192], COMPONENT_Y);
				pCtu->setTransformSkip(startIdx + j, tempCb[j + 192], COMPONENT_Cb);
				pCtu->setTransformSkip(startIdx + j, tempCr[j + 192], COMPONENT_Cr);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapCbfNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> tempY;
	vector<UChar> tempCb;
	vector<UChar> tempCr;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1Y;
		vector<UChar> X1Cb;
		vector<UChar> X1Cr;

		vector<UChar> X2Y;
		vector<UChar> X2Cb;
		vector<UChar> X2Cr;

		vector<UChar> X3Y;
		vector<UChar> X3Cb;
		vector<UChar> X3Cr;

		vector<UChar> X4Y;
		vector<UChar> X4Cb;
		vector<UChar> X4Cr;

		for (int j = 0; j < 16; j++)
		{
			X1Y.push_back(pCtu->getCbf(startIdx + j, COMPONENT_Y));
			X1Cb.push_back(pCtu->getCbf(startIdx + j, COMPONENT_Cb));
			X1Cr.push_back(pCtu->getCbf(startIdx + j, COMPONENT_Cr));

			X2Y.push_back(pCtu->getCbf(startIdx + j + 16, COMPONENT_Y));
			X2Cb.push_back(pCtu->getCbf(startIdx + j + 16, COMPONENT_Cb));
			X2Cr.push_back(pCtu->getCbf(startIdx + j + 16, COMPONENT_Cr));

			X3Y.push_back(pCtu->getCbf(startIdx + j + 32, COMPONENT_Y));
			X3Cb.push_back(pCtu->getCbf(startIdx + j + 32, COMPONENT_Cb));
			X3Cr.push_back(pCtu->getCbf(startIdx + j + 32, COMPONENT_Cr));

			X4Y.push_back(pCtu->getCbf(startIdx + j + 48, COMPONENT_Y));
			X4Cb.push_back(pCtu->getCbf(startIdx + j + 48, COMPONENT_Cb));
			X4Cr.push_back(pCtu->getCbf(startIdx + j + 48, COMPONENT_Cr));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X1Y[kk]);
					tempCb.push_back(X1Cb[kk]);
					tempCr.push_back(X1Cr[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X2Y[kk]);
					tempCb.push_back(X2Cb[kk]);
					tempCr.push_back(X2Cr[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X3Y[kk]);
					tempCb.push_back(X3Cb[kk]);
					tempCr.push_back(X3Cr[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X4Y[kk]);
					tempCb.push_back(X4Cb[kk]);
					tempCr.push_back(X4Cr[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCbf(startIdx + j, COMPONENT_Y, tempY[j]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cb, tempCb[j]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cr, tempCr[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCbf(startIdx + j, COMPONENT_Y, tempY[j + 64]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cb, tempCb[j + 64]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cr, tempCr[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCbf(startIdx + j, COMPONENT_Y, tempY[j + 128]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cb, tempCb[j + 128]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cr, tempCr[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setCbf(startIdx + j, COMPONENT_Y, tempY[j + 192]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cb, tempCb[j + 192]);
				pCtu->setCbf(startIdx + j, COMPONENT_Cr, tempCr[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapTrCoeffNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<TCoeff> tempY;
	vector<TCoeff> tempCb;
	vector<TCoeff> tempCr;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<TCoeff> X1Y;
		vector<TCoeff> X1Cb;
		vector<TCoeff> X1Cr;

		vector<TCoeff> X2Y;
		vector<TCoeff> X2Cb;
		vector<TCoeff> X2Cr;

		vector<TCoeff> X3Y;
		vector<TCoeff> X3Cb;
		vector<TCoeff> X3Cr;

		vector<TCoeff> X4Y;
		vector<TCoeff> X4Cb;
		vector<TCoeff> X4Cr;

		for (int j = 0; j < 256; j++)
		{
			X1Y.push_back(pCtu->getCoeff(startIdx + j, COMPONENT_Y));

			X2Y.push_back(pCtu->getCoeff(startIdx + j + 256, COMPONENT_Y));

			X3Y.push_back(pCtu->getCoeff(startIdx + j + 512, COMPONENT_Y));
			
			X4Y.push_back(pCtu->getCoeff(startIdx + j + 768, COMPONENT_Y));
			
		}
		for (int j = 0; j < 64; j++)
		{
		
			X1Cb.push_back(pCtu->getCoeff(startIdx + j, COMPONENT_Cb));
			X1Cr.push_back(pCtu->getCoeff(startIdx + j, COMPONENT_Cr));

			X2Cb.push_back(pCtu->getCoeff(startIdx + j + 64, COMPONENT_Cb));
			X2Cr.push_back(pCtu->getCoeff(startIdx + j + 64, COMPONENT_Cr));

			X3Cb.push_back(pCtu->getCoeff(startIdx + j + 128, COMPONENT_Cb));
			X3Cr.push_back(pCtu->getCoeff(startIdx + j + 128, COMPONENT_Cr));

			X4Cb.push_back(pCtu->getCoeff(startIdx + j + 192, COMPONENT_Cb));
			X4Cr.push_back(pCtu->getCoeff(startIdx + j + 192, COMPONENT_Cr));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 256; kk++)
				{
					tempY.push_back(X1Y[kk]);
				}
				for (int kk = 0; kk < 64; kk++)
				{
					tempCb.push_back(X1Cb[kk]);
					tempCr.push_back(X1Cr[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 256; kk++)
				{
					tempY.push_back(X2Y[kk]);
				}
				for (int kk = 0; kk < 64; kk++)
				{
					tempCb.push_back(X2Cb[kk]);
					tempCr.push_back(X2Cr[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 256; kk++)
				{
					tempY.push_back(X3Y[kk]);
				}
				for (int kk = 0; kk < 64; kk++)
				{
					tempCb.push_back(X3Cb[kk]);
					tempCr.push_back(X3Cr[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 256; kk++)
				{
					tempY.push_back(X4Y[kk]);
				}
				for (int kk = 0; kk < 64; kk++)
				{
					tempCb.push_back(X4Cb[kk]);
					tempCr.push_back(X4Cr[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	int startIdx1 = 0;
	int startIdx2 = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 1024; j++)
			{
				pCtu->setCoeff(startIdx1 + j, tempY[j], COMPONENT_Y);
			}
			for (int j = 0; j < 256; j++)
			{
				pCtu->setCoeff(startIdx2 + j, tempCb[j], COMPONENT_Cb);
				pCtu->setCoeff(startIdx2 + j, tempCr[j], COMPONENT_Cr);
			}
			break;
		case 1:
			for (int j = 0; j < 1024; j++)
			{
				pCtu->setCoeff(startIdx1 + j, tempY[j+1024], COMPONENT_Y);
			}
			for (int j = 0; j < 256; j++)
			{
				pCtu->setCoeff(startIdx2 + j, tempCb[j+256], COMPONENT_Cb);
				pCtu->setCoeff(startIdx2 + j, tempCr[j+256], COMPONENT_Cr);
			}
			break;
		case 2:
			for (int j = 0; j < 1024; j++)
			{
				pCtu->setCoeff(startIdx1 + j, tempY[j+2048], COMPONENT_Y);
			}
			for (int j = 0; j < 256; j++)
			{
				pCtu->setCoeff(startIdx2 + j, tempCb[j+512], COMPONENT_Cb);
				pCtu->setCoeff(startIdx2 + j, tempCr[j+512], COMPONENT_Cr);
			}
			break;
		case 3:
			for (int j = 0; j < 1024; j++)
			{
				pCtu->setCoeff(startIdx1 + j, tempY[j+3072], COMPONENT_Y);
			}
			for (int j = 0; j < 256; j++)
			{
				pCtu->setCoeff(startIdx2 + j, tempCb[j+768], COMPONENT_Cb);
				pCtu->setCoeff(startIdx2 + j, tempCr[j+768], COMPONENT_Cr);
			}
			break;
		default:
			break;
		}
		startIdx1 += 1024;
		startIdx2 += 256;
	}

}
void SwapCuNew::swapArlCoeffNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> tempY;
	vector<UChar> tempCb;
	vector<UChar> tempCr;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1Y;
		vector<UChar> X1Cb;
		vector<UChar> X1Cr;

		vector<UChar> X2Y;
		vector<UChar> X2Cb;
		vector<UChar> X2Cr;

		vector<UChar> X3Y;
		vector<UChar> X3Cb;
		vector<UChar> X3Cr;

		vector<UChar> X4Y;
		vector<UChar> X4Cb;
		vector<UChar> X4Cr;

		for (int j = 0; j < 16; j++)
		{
			X1Y.push_back(pCtu->getArlCoeff(startIdx + j, COMPONENT_Y));
			X1Cb.push_back(pCtu->getArlCoeff(startIdx + j, COMPONENT_Cb));
			X1Cr.push_back(pCtu->getArlCoeff(startIdx + j, COMPONENT_Cr));

			X2Y.push_back(pCtu->getArlCoeff(startIdx + j + 16, COMPONENT_Y));
			X2Cb.push_back(pCtu->getArlCoeff(startIdx + j + 16, COMPONENT_Cb));
			X2Cr.push_back(pCtu->getArlCoeff(startIdx + j + 16, COMPONENT_Cr));

			X3Y.push_back(pCtu->getArlCoeff(startIdx + j + 32, COMPONENT_Y));
			X3Cb.push_back(pCtu->getArlCoeff(startIdx + j + 32, COMPONENT_Cb));
			X3Cr.push_back(pCtu->getArlCoeff(startIdx + j + 32, COMPONENT_Cr));

			X4Y.push_back(pCtu->getArlCoeff(startIdx + j + 48, COMPONENT_Y));
			X4Cb.push_back(pCtu->getArlCoeff(startIdx + j + 48, COMPONENT_Cb));
			X4Cr.push_back(pCtu->getArlCoeff(startIdx + j + 48, COMPONENT_Cr));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X1Y[kk]);
					tempCb.push_back(X1Cb[kk]);
					tempCr.push_back(X1Cr[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X2Y[kk]);
					tempCb.push_back(X2Cb[kk]);
					tempCr.push_back(X2Cr[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X3Y[kk]);
					tempCb.push_back(X3Cb[kk]);
					tempCr.push_back(X3Cr[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X4Y[kk]);
					tempCb.push_back(X4Cb[kk]);
					tempCr.push_back(X4Cr[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setArlCoeff(startIdx + j, tempY[j], COMPONENT_Y);
				pCtu->setArlCoeff(startIdx + j, tempCb[j], COMPONENT_Cb);
				pCtu->setArlCoeff(startIdx + j, tempCr[j], COMPONENT_Cr);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setArlCoeff(startIdx + j, tempY[j + 64], COMPONENT_Y);
				pCtu->setArlCoeff(startIdx + j, tempCb[j + 64], COMPONENT_Cb);
				pCtu->setArlCoeff(startIdx + j, tempCr[j + 64], COMPONENT_Cr);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setArlCoeff(startIdx + j, tempY[j + 128], COMPONENT_Y);
				pCtu->setArlCoeff(startIdx + j, tempCb[j + 128], COMPONENT_Cb);
				pCtu->setArlCoeff(startIdx + j, tempCr[j + 128], COMPONENT_Cr);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setArlCoeff(startIdx + j, tempY[j + 192], COMPONENT_Y);
				pCtu->setArlCoeff(startIdx + j, tempCb[j + 192], COMPONENT_Cb);
				pCtu->setArlCoeff(startIdx + j, tempCr[j + 192], COMPONENT_Cr);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapMergeFlagNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1;
		vector<UChar> X2;
		vector<UChar> X3;
		vector<UChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getMergeFlag(startIdx + j));
			X2.push_back(pCtu->getMergeFlag(startIdx + j + 16));
			X3.push_back(pCtu->getMergeFlag(startIdx + j + 32));
			X4.push_back(pCtu->getMergeFlag(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeFlag(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeFlag(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeFlag(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeFlag(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapMergeIdxNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1;
		vector<UChar> X2;
		vector<UChar> X3;
		vector<UChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getMergeIndex(startIdx + j));
			X2.push_back(pCtu->getMergeIndex(startIdx + j + 16));
			X3.push_back(pCtu->getMergeIndex(startIdx + j + 32));
			X4.push_back(pCtu->getMergeIndex(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeIndex(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeIndex(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeIndex(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMergeIndex(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapIntraDirNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> tempLuma;
	vector<UChar> tempChroma;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1Luma;
		vector<UChar> X2Luma;
		vector<UChar> X3Luma;
		vector<UChar> X4Luma;

		vector<UChar> X1Chroma;
		vector<UChar> X2Chroma;
		vector<UChar> X3Chroma;
		vector<UChar> X4Chroma;

		for (int j = 0; j < 16; j++)
		{
			X1Luma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, startIdx + j));
			X2Luma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, startIdx + j + 16));
			X3Luma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, startIdx + j + 32));
			X4Luma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_LUMA, startIdx + j + 48));

			X1Chroma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, startIdx + j));
			X2Chroma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, startIdx + j + 16));
			X3Chroma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, startIdx + j + 32));
			X4Chroma.push_back(pCtu->getIntraDir(CHANNEL_TYPE_CHROMA, startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempLuma.push_back(X1Luma[kk]);
					tempChroma.push_back(X1Chroma[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempLuma.push_back(X2Luma[kk]);
					tempChroma.push_back(X2Chroma[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempLuma.push_back(X3Luma[kk]);
					tempChroma.push_back(X3Chroma[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempLuma.push_back(X4Luma[kk]);
					tempChroma.push_back(X4Chroma[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIntraDir(startIdx + j, tempLuma[j],CHANNEL_TYPE_LUMA);
				pCtu->setIntraDir(startIdx + j, tempChroma[j], CHANNEL_TYPE_CHROMA);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIntraDir(startIdx + j, tempLuma[j+64], CHANNEL_TYPE_LUMA);
				pCtu->setIntraDir(startIdx + j, tempChroma[j+64], CHANNEL_TYPE_CHROMA);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIntraDir(startIdx + j, tempLuma[j+128], CHANNEL_TYPE_LUMA);
				pCtu->setIntraDir(startIdx + j, tempChroma[j+128], CHANNEL_TYPE_CHROMA);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIntraDir(startIdx + j, tempLuma[j+192], CHANNEL_TYPE_LUMA);
				pCtu->setIntraDir(startIdx + j, tempChroma[j+192], CHANNEL_TYPE_CHROMA);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapInterDirNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1;
		vector<UChar> X2;
		vector<UChar> X3;
		vector<UChar> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getInterDir(startIdx + j));
			X2.push_back(pCtu->getInterDir(startIdx + j + 16));
			X3.push_back(pCtu->getInterDir(startIdx + j + 32));
			X4.push_back(pCtu->getInterDir(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setInterDir(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setInterDir(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setInterDir(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setInterDir(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapApiMVPIdxNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> tempRef0;
	vector<SChar> tempRef1;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<SChar> X1Ref0;
		vector<SChar> X2Ref0;
		vector<SChar> X3Ref0;
		vector<SChar> X4Ref0;

		vector<SChar> X1Ref1;
		vector<SChar> X2Ref1;
		vector<SChar> X3Ref1;
		vector<SChar> X4Ref1;

		for (int j = 0; j < 16; j++)
		{
			X1Ref0.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, startIdx + j));
			X2Ref0.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, startIdx + j + 16));
			X3Ref0.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, startIdx + j + 32));
			X4Ref0.push_back(pCtu->getMVPIdx(REF_PIC_LIST_0, startIdx + j + 48));

			X1Ref1.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, startIdx + j));
			X2Ref1.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, startIdx + j + 16));
			X3Ref1.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, startIdx + j + 32));
			X4Ref1.push_back(pCtu->getMVPIdx(REF_PIC_LIST_1, startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X1Ref0[kk]);
					tempRef1.push_back(X1Ref1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X2Ref0[kk]);
					tempRef1.push_back(X2Ref1[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X3Ref0[kk]);
					tempRef1.push_back(X3Ref1[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X4Ref0[kk]);
					tempRef1.push_back(X4Ref1[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, tempRef0[j]);
				pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, tempRef1[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, tempRef0[j + 64]);
				pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, tempRef1[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, tempRef0[j + 128]);
				pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, tempRef1[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPIdx(REF_PIC_LIST_0, startIdx + j, tempRef0[j + 192]);
				pCtu->setMVPIdx(REF_PIC_LIST_1, startIdx + j, tempRef1[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapApiMVPNumNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<SChar> tempRef0;
	vector<SChar> tempRef1;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<SChar> X1Ref0;
		vector<SChar> X2Ref0;
		vector<SChar> X3Ref0;
		vector<SChar> X4Ref0;

		vector<SChar> X1Ref1;
		vector<SChar> X2Ref1;
		vector<SChar> X3Ref1;
		vector<SChar> X4Ref1;

		for (int j = 0; j < 16; j++)
		{
			X1Ref0.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, startIdx + j));
			X2Ref0.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, startIdx + j + 16));
			X3Ref0.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, startIdx + j + 32));
			X4Ref0.push_back(pCtu->getMVPNum(REF_PIC_LIST_0, startIdx + j + 48));

			X1Ref1.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, startIdx + j));
			X2Ref1.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, startIdx + j + 16));
			X3Ref1.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, startIdx + j + 32));
			X4Ref1.push_back(pCtu->getMVPNum(REF_PIC_LIST_1, startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X1Ref0[kk]);
					tempRef1.push_back(X1Ref1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X2Ref0[kk]);
					tempRef1.push_back(X2Ref1[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X3Ref0[kk]);
					tempRef1.push_back(X3Ref1[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempRef0.push_back(X4Ref0[kk]);
					tempRef1.push_back(X4Ref1[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, tempRef0[j]);
				pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, tempRef1[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, tempRef0[j + 64]);
				pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, tempRef1[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, tempRef0[j + 128]);
				pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, tempRef1[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setMVPNum(REF_PIC_LIST_0, startIdx + j, tempRef0[j + 192]);
				pCtu->setMVPNum(REF_PIC_LIST_1, startIdx + j, tempRef1[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapIPCMFlagNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Bool> temp;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<Bool> X1;
		vector<Bool> X2;
		vector<Bool> X3;
		vector<Bool> X4;

		for (int j = 0; j < 16; j++)
		{
			X1.push_back(pCtu->getIPCMFlag(startIdx + j));
			X2.push_back(pCtu->getIPCMFlag(startIdx + j + 16));
			X3.push_back(pCtu->getIPCMFlag(startIdx + j + 32));
			X4.push_back(pCtu->getIPCMFlag(startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X1[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X2[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X3[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					temp.push_back(X4[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIPCMFlag(startIdx + j, temp[j]);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIPCMFlag(startIdx + j, temp[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIPCMFlag(startIdx + j, temp[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setIPCMFlag(startIdx + j, temp[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapExplicitRdpcmModeNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<UChar> tempY;
	vector<UChar> tempCb;
	vector<UChar> tempCr;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<UChar> X1Y;
		vector<UChar> X1Cb;
		vector<UChar> X1Cr;

		vector<UChar> X2Y;
		vector<UChar> X2Cb;
		vector<UChar> X2Cr;

		vector<UChar> X3Y;
		vector<UChar> X3Cb;
		vector<UChar> X3Cr;

		vector<UChar> X4Y;
		vector<UChar> X4Cb;
		vector<UChar> X4Cr;

		for (int j = 0; j < 16; j++)
		{
			X1Y.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, startIdx + j));
			X1Cb.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, startIdx + j));
			X1Cr.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, startIdx + j));

			X2Y.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, startIdx + j + 16));
			X2Cb.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, startIdx + j + 16));
			X2Cr.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, startIdx + j + 16));

			X3Y.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, startIdx + j + 32));
			X3Cb.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, startIdx + j + 32));
			X3Cr.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, startIdx + j + 32));

			X4Y.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Y, startIdx + j + 48));
			X4Cb.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cb, startIdx + j + 48));
			X4Cr.push_back(pCtu->getExplicitRdpcmMode(COMPONENT_Cr, startIdx + j + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X1Y[kk]);
					tempCb.push_back(X1Cb[kk]);
					tempCr.push_back(X1Cr[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X2Y[kk]);
					tempCb.push_back(X2Cb[kk]);
					tempCr.push_back(X2Cr[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X3Y[kk]);
					tempCb.push_back(X3Cb[kk]);
					tempCr.push_back(X3Cr[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X4Y[kk]);
					tempCb.push_back(X4Cb[kk]);
					tempCr.push_back(X4Cr[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, tempY[j]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, tempCb[j]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, tempCr[j]);
			}
			break; 
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, tempY[j + 64]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, tempCb[j + 64]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, tempCr[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, tempY[j + 128]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, tempCb[j + 128]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, tempCr[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setExplicitRdpcmMode(COMPONENT_Y, startIdx + j, tempY[j + 192]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cb, startIdx + j, tempCb[j + 192]);
				pCtu->setExplicitRdpcmMode(COMPONENT_Cr, startIdx + j, tempCr[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapIPCMSampleNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<Pel> tempY;
	vector<Pel> tempCb;
	vector<Pel> tempCr;
	int startIdx;
	startIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		vector<Pel> X1Y;
		vector<Pel> X1Cb;
		vector<Pel> X1Cr;

		vector<Pel> X2Y;
		vector<Pel> X2Cb;
		vector<Pel> X2Cr;

		vector<Pel> X3Y;
		vector<Pel> X3Cb;
		vector<Pel> X3Cr;

		vector<Pel> X4Y;
		vector<Pel> X4Cb;
		vector<Pel> X4Cr;

		for (int j = 0; j < 16; j++)
		{
			X1Y.push_back(pCtu->getPCMSample(startIdx + j, COMPONENT_Y));
			X1Cb.push_back(pCtu->getPCMSample(startIdx + j, COMPONENT_Cb));
			X1Cr.push_back(pCtu->getPCMSample(startIdx + j, COMPONENT_Cr));

			X2Y.push_back(pCtu->getPCMSample(startIdx + j + 16, COMPONENT_Y));
			X2Cb.push_back(pCtu->getPCMSample(startIdx + j + 16, COMPONENT_Cb));
			X2Cr.push_back(pCtu->getPCMSample(startIdx + j + 16, COMPONENT_Cr));

			X3Y.push_back(pCtu->getPCMSample(startIdx + j + 32, COMPONENT_Y));
			X3Cb.push_back(pCtu->getPCMSample(startIdx + j + 32, COMPONENT_Cb));
			X3Cr.push_back(pCtu->getPCMSample(startIdx + j + 32, COMPONENT_Cr));

			X4Y.push_back(pCtu->getPCMSample(startIdx + j + 48, COMPONENT_Y));
			X4Cb.push_back(pCtu->getPCMSample(startIdx + j + 48, COMPONENT_Cb));
			X4Cr.push_back(pCtu->getPCMSample(startIdx + j + 48, COMPONENT_Cr));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X1Y[kk]);
					tempCb.push_back(X1Cb[kk]);
					tempCr.push_back(X1Cr[kk]);
				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X2Y[kk]);
					tempCb.push_back(X2Cb[kk]);
					tempCr.push_back(X2Cr[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X3Y[kk]);
					tempCb.push_back(X3Cb[kk]);
					tempCr.push_back(X3Cr[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					tempY.push_back(X4Y[kk]);
					tempCb.push_back(X4Cb[kk]);
					tempCr.push_back(X4Cr[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPCMSample(startIdx + j, tempY[j], COMPONENT_Y);
				pCtu->setPCMSample(startIdx + j, tempCb[j], COMPONENT_Cb);
				pCtu->setPCMSample(startIdx + j, tempCr[j], COMPONENT_Cr);
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPCMSample(startIdx + j, tempY[j + 64], COMPONENT_Y);
				pCtu->setPCMSample(startIdx + j, tempCb[j + 64], COMPONENT_Cb);
				pCtu->setPCMSample(startIdx + j, tempCr[j + 64], COMPONENT_Cr);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPCMSample(startIdx + j, tempY[j + 128], COMPONENT_Y);
				pCtu->setPCMSample(startIdx + j, tempCb[j + 128], COMPONENT_Cb);
				pCtu->setPCMSample(startIdx + j, tempCr[j + 128], COMPONENT_Cr);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->setPCMSample(startIdx + j, tempY[j + 192], COMPONENT_Y);
				pCtu->setPCMSample(startIdx + j, tempCb[j + 192], COMPONENT_Cb);
				pCtu->setPCMSample(startIdx + j, tempCr[j + 192], COMPONENT_Cr);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}

}
void SwapCuNew::swapCuMVFieldNew(TComDataCU *pCtu, vector<UInt> keyIdx)
{
	vector<TComMv> MvRef0;
	vector<TComMv> MvRef1;

	vector<TComMv> MvdRef0;
	vector<TComMv> MvdRef1;

	vector<UChar> refIdxRef0;
	vector<UChar> refIdxRef1;

	int startIdx;
	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		vector<TComMv> X1_Mv_Ref0;
		vector<TComMv> X1_Mv_Ref1;

		vector<TComMv> X1_Mvd_Ref0;
		vector<TComMv> X1_Mvd_Ref1;

		vector<UChar> X1_RefIdx_Ref0;
		vector<UChar> X1_RefIdx_Ref1;

		vector<TComMv> X2_Mv_Ref0;
		vector<TComMv> X2_Mv_Ref1;

		vector<TComMv> X2_Mvd_Ref0;
		vector<TComMv> X2_Mvd_Ref1;

		vector<UChar> X2_RefIdx_Ref0;
		vector<UChar> X2_RefIdx_Ref1;

		vector<TComMv> X3_Mv_Ref0;
		vector<TComMv> X3_Mv_Ref1;

		vector<TComMv> X3_Mvd_Ref0;
		vector<TComMv> X3_Mvd_Ref1;

		vector<UChar> X3_RefIdx_Ref0;
		vector<UChar> X3_RefIdx_Ref1;
		
		vector<TComMv> X4_Mv_Ref0;
		vector<TComMv> X4_Mv_Ref1;

		vector<TComMv> X4_Mvd_Ref0;
		vector<TComMv> X4_Mvd_Ref1;

		vector<UChar> X4_RefIdx_Ref0;
		vector<UChar> X4_RefIdx_Ref1;

		for (int j = 0; j < 16; j++)
		{
			X1_Mv_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i));
			X1_Mv_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i));
			X1_Mvd_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i));
			X1_Mvd_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i));
			X1_RefIdx_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));
			X1_RefIdx_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i));

			X2_Mv_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 16));
			X2_Mv_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i + 16));
			X2_Mvd_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 16));
			X2_Mvd_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i + 16));
			X2_RefIdx_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i + 16));
			X2_RefIdx_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i + 16));

			X3_Mv_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 32));
			X3_Mv_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i + 32));
			X3_Mvd_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 32));
			X3_Mvd_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i + 32));
			X3_RefIdx_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i + 32));
			X3_RefIdx_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i + 32));

			X4_Mv_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i + 48));
			X4_Mv_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMv(i + 48));
			X4_Mvd_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i + 48));
			X4_Mvd_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getMvd(i + 48));
			X4_RefIdx_Ref0.push_back(pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i + 48));
			X4_RefIdx_Ref1.push_back(pCtu->getCUMvField(REF_PIC_LIST_1)->getRefIdx(i + 48));
		}

		for (int k = 0; k < keyIdx.size(); k++)
		{
			switch (keyIdx[k])
			{
			case 0:
				for (int kk = 0; kk < 16; kk++)
				{
					MvRef0.push_back(X1_Mv_Ref0[kk]);
					MvRef1.push_back(X1_Mv_Ref1[kk]);

					MvdRef0.push_back(X1_Mvd_Ref0[kk]);
					MvdRef1.push_back(X1_Mvd_Ref1[kk]);

					refIdxRef0.push_back(X1_RefIdx_Ref0[kk]);
					refIdxRef1.push_back(X1_RefIdx_Ref1[kk]);

				}
				break;
			case 1:
				for (int kk = 0; kk < 16; kk++)
				{
					MvRef0.push_back(X2_Mv_Ref0[kk]);
					MvRef1.push_back(X2_Mv_Ref1[kk]);

					MvdRef0.push_back(X2_Mvd_Ref0[kk]);
					MvdRef1.push_back(X2_Mvd_Ref1[kk]);

					refIdxRef0.push_back(X2_RefIdx_Ref0[kk]);
					refIdxRef1.push_back(X2_RefIdx_Ref1[kk]);
				}
				break;
			case 2:
				for (int kk = 0; kk < 16; kk++)
				{
					MvRef0.push_back(X3_Mv_Ref0[kk]);
					MvRef1.push_back(X3_Mv_Ref1[kk]);

					MvdRef0.push_back(X3_Mvd_Ref0[kk]);
					MvdRef1.push_back(X3_Mvd_Ref1[kk]);

					refIdxRef0.push_back(X3_RefIdx_Ref0[kk]);
					refIdxRef1.push_back(X3_RefIdx_Ref1[kk]);
				}
				break;
			case 3:
				for (int kk = 0; kk < 16; kk++)
				{
					MvRef0.push_back(X4_Mv_Ref0[kk]);
					MvRef1.push_back(X4_Mv_Ref1[kk]);

					MvdRef0.push_back(X4_Mvd_Ref0[kk]);
					MvdRef1.push_back(X4_Mvd_Ref1[kk]);

					refIdxRef0.push_back(X4_RefIdx_Ref0[kk]);
					refIdxRef1.push_back(X4_RefIdx_Ref1[kk]);
				}
				break;
			default:
				break;
			}
		}
		startIdx += 64;
	}

	startIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (keyIdx[i])
		{
		case 0:
			for (int j = 0; j < 64; j++)
			{
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0[j]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1[j]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0[j]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1[j]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0[j]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1[j]);
				
			}
			break;
		case 1:
			for (int j = 0; j < 64; j++)
			{
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0[j + 64]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1[j + 64]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0[j + 64]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1[j + 64]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0[j + 64]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1[j + 64]);
			}
			break;
		case 2:
			for (int j = 0; j < 64; j++)
			{
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0[j + 128]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1[j + 128]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0[j + 128]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1[j + 128]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0[j + 128]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1[j + 128]);
			}
			break;
		case 3:
			for (int j = 0; j < 64; j++)
			{
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMv(startIdx + j, MvRef0[j + 192]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMv(startIdx + j, MvRef1[j + 192]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setMvd(startIdx + j, MvdRef0[j + 192]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setMvd(startIdx + j, MvdRef1[j + 192]);
				pCtu->getCUMvField(REF_PIC_LIST_0)->setRefIdx(startIdx + j, refIdxRef0[j + 192]);
				pCtu->getCUMvField(REF_PIC_LIST_1)->setRefIdx(startIdx + j, refIdxRef1[j + 192]);
			}
			break;
		default:
			break;
		}
		startIdx += 64;
	}
}

vector<UInt> SwapCuNew::produceKeyIdx(vector<UInt> lockIdx)
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