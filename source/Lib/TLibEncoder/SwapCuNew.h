#pragma once
#pragma once
#pragma once
#include"TLibCommon/TComDataCU.h"
#include "vector"

class SwapCuNew
{
public:

	void swapCuMainNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapWidthNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapHeightNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapDepthNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapSkipFlagNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapPartSizeNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapPredmodeNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCrossComponentPredictionAlphaNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCUTransquantBypassNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapQPNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapChromaQPAdjNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapTransformIdxNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapTransformSkipNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCbfNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapTrCoeffNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapArlCoeffNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapMergeFlagNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapMergeIdxNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapIntraDirNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapInterDirNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapApiMVPIdxNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapApiMVPNumNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapIPCMFlagNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapExplicitRdpcmModeNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapCuMVFieldNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	void swapIPCMSampleNew(TComDataCU *pCtu, vector<UInt> keyIdx);
	int getMaxDepth(TComDataCU *pCtu);

	vector<UInt> produceKeyIdx(vector<UInt> lockIdx);

private:

};

