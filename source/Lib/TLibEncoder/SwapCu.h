#pragma once
#pragma once
#include"TLibCommon/TComDataCU.h"
#include "vector"

class SwapCu
{
public:

	void swapCuMain(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapWidth(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapHeight(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapDepth(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapSkipFlag(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapPartSize(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapPredmode(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCrossComponentPredictionAlpha(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCUTransquantBypass(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapQP(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapChromaQPAdj(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapTransformIdx(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapTransformSkip(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCbf(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapTrCoeff(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapArlCoeff(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapMergeFlag(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapMergeIdx(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapIntraDir(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapInterDir(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapApiMVPIdx(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapApiMVPNum(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapIPCMFlag(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapExplicitRdpcmMode(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCuMVField1(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCuMVField2(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapIPCMSample(TComDataCU *pCtu, vector<UInt> keyIdx);
	int getMaxDepth(TComDataCU *pCtu);

	vector<UInt> produceKeyIdx( vector<UInt> lockIdx );

	void swapTotalCu(TComDataCU *pCtu);

private:

};

