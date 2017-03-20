#pragma once

#include "TLibDecoder/NALread.h"
#include <string>
#define CtuNum 80

typedef std::vector<unsigned char> BIN;
typedef std::vector<std::vector<int> > DATA;
typedef std::vector<std::vector<unsigned char> > BIN_2d;

class NaluOperation
{
public:
	
	//NaluOperation();
	InputNALUnit Encrypte(InputNALUnit nalu,int frameInGroupIdx,DATA data);
	void NaluPrint(InputNALUnit nalu);
	BIN CharToBin(BIN CtuData);
	InputNALUnit BinToChar(BIN Bin,BIN header,InputNALUnit nalu);
	void Permulation(BIN_2d &bin_2d,int dataIdx,DATA data);
	DATA ReadCtuBits(std::string url);
	//BIN_2d ExtractCtuFromBIN(BIN bin,int frameInGroupIdx,DATA data);
	BIN NaluOperation::ExtractHeader(InputNALUnit nalu);
	BIN NaluOperation::ExtractCtuData(InputNALUnit nalu);
	BIN_2d NaluOperation::Bin_1dToBin_2d(BIN bin, int frameInGroupIdx, DATA data);
	BIN NaluOperation::Bin_2dToBin_1d(BIN_2d bin_2d);
};