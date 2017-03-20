#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include "NaluOperation.h"
#define CtuNum 80
#define HeaderLength 7
typedef std::vector<unsigned char> BIN;
typedef std::vector<std::vector<unsigned char> > BIN_2d;
typedef std::vector<std::vector<int> > DATA;

InputNALUnit NaluOperation::Encrypte(InputNALUnit nalu,int frameInGroupIdx,DATA data)
{
	NaluOperation naluOperation;
	//naluOperation.NaluPrint(nalu);

	//��ȡnalu��slice��ͷ����Ϣ
	BIN header;
	header = naluOperation.ExtractHeader(nalu);

	//��ȡCTU������Ϣ
	BIN CtuData;
	CtuData = naluOperation.ExtractCtuData(nalu);

	//��CtuDataת��Ϊ�����ƴ�����ʽ
	BIN bin;
	bin = naluOperation.CharToBin(CtuData);

	//һά�����ƴ�ת��Ϊ��ά
	BIN_2d bin_2d;
	bin_2d = naluOperation.Bin_1dToBin_2d(bin, frameInGroupIdx, data);

	//����CTU��
	naluOperation.Permulation(bin_2d, frameInGroupIdx, data);

	//��ά�����ƴ�ת��Ϊһά
	BIN binAfterPermulation;
	binAfterPermulation = naluOperation.Bin_2dToBin_1d(bin_2d);
	
	//�����Һ�Ķ����ƴ�д�ᵽnalu��
	nalu = naluOperation.BinToChar(binAfterPermulation,header,nalu);
	//naluOperation.NaluPrint(nalu);

	return nalu;
}

//��ӡ��nalu����
void NaluOperation::NaluPrint(InputNALUnit nalu)
{
	for (int i = 0; i < nalu.getBitstream().getFifo().size(); i++)
	{
		unsigned char c = nalu.getBitstream().getFifo()[i];
		printf("%d\n", c);
		//printf("%d\n", nalu.getBitstream().getFifo()[i]);
	}
}


//��nalu�е�unsigned char������ȡ����ת��Ϊ�ַ�����ʽ���ڲ���
BIN  NaluOperation::CharToBin(BIN CtuData)
{
	std::vector<unsigned char> Bin;
	for (int i = 0; i < CtuData.size(); i++)
	{
		unsigned char c = CtuData[i];

		for (int j = 0; j < 8; j++)
		{
			unsigned char temp = 1;
			if (c&temp << j)
				Bin.push_back('1');
			else
				Bin.push_back('0');
		}
	}
	//std::reverse(Bin.begin(), Bin.end());
	for (int i = 0; i < Bin.size() / 8; i++)
	{
		std::reverse(Bin.begin() + i * 8, Bin.begin() + i * 8 + 8);
	}
	for (int i = 0; i < CtuData.size()*8; i++)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("%c", Bin[i]);
	}
	return Bin;
}

//���������ַ���д�ᵽnalu��
InputNALUnit NaluOperation::BinToChar(BIN Bin,BIN header,InputNALUnit nalu)
{
	/*printf("\n%d\n", nalu.getBitstream().getFifo().size());
	printf("\n%d\n", Bin.size());
	for (int i = 0; i < Bin.size(); i++)
		printf("%c", Bin[i]);*/
	for (int i = 0; i < Bin.size()/8; i++)
	{
		std::reverse(Bin.begin() + i * 8, Bin.begin() + i * 8 + 8);
	}

	for (int i = 0; i < header.size(); i++)
	{
		nalu.getBitstream().getFifo()[i] = header[i];
	}
	for (int i = 0; i < Bin.size()/8; i++)
	{
		int temp = 1;
		int c = 0;
		for (int j = 0; j < 8; j++)
		{
			c += (Bin[i*8+j]-48) * temp;
			temp *= 2;
		}
		nalu.getBitstream().getFifo()[i+header.size()] = c;
	}

	return nalu;
}

//����CTU���λ��
void NaluOperation::Permulation(BIN_2d &bin_2d,int frameInGroupIdx,DATA data)
{
	//BIN_2d bin_2d;
	//std::vector<unsigned char> temp;
	/*printf("\n%d\n", Bin.size());
	int sum = 0;
	for (int i = 0; i < CtuNum; i++)
		sum += data[frameInGroupIdx][i];
	printf("%d\n", sum);*/

	//bin_2d = ExtractCtuFromBIN(Bin, frameInGroupIdx, data); 
	std::vector<unsigned char> v,n;
	
	while (!bin_2d[0].empty())
	{
		n.push_back(bin_2d[0][0]);
		bin_2d[0].erase(bin_2d[0].begin());
	}
	while (!bin_2d[1].empty())
	{
		v.push_back(bin_2d[1][0]);
		bin_2d[1].erase(bin_2d[1].begin());
	}
	for (int i = 0; i < n.size(); i++)
	{
		bin_2d[1].push_back(n[i]);
		//bin_2d[0].erase(bin_2d[1].begin());
	}
	for (int i = 0; i < v.size(); i++)
	{
		bin_2d[0].push_back(v[i]);
		//bin_2d[0].erase(bin_2d[1].begin());
	}
	n.clear();
	v.clear();
	printf("\n");
	for (int i = 0; i < CtuNum; i++)
	{
		for (int j = 0; j < bin_2d[i].size(); j++)
		{
			printf("%c", bin_2d[i][j]);
		}
		printf("\n");
	}
}

//��txt�ļ���ȡCTU������
DATA NaluOperation::ReadCtuBits(std::string url)
{
	DATA data;
	std::ifstream inputFile;
	inputFile.open(url);

	int tmp;
	int i = 0;
	std::vector<int> v;
	std::vector<int> n;
	while (!inputFile.eof())
	{
		inputFile >> tmp;
		v.push_back(tmp);
	}
	v.pop_back();
	inputFile.close();
	//printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i = i + CtuNum)
	{
		for (int j = 0; j < CtuNum; j++)
		{
			n.push_back(v[i+j]);
		}
		data.push_back(n);
		n.clear();
	}
	v.clear();
	return data;
}


BIN NaluOperation::ExtractHeader(InputNALUnit nalu)
{
	BIN header;
	for (int i = 0; i < HeaderLength; i++)
	{
		header.push_back(nalu.getBitstream().getFifo()[i]);
	}
	return header;
}

BIN NaluOperation::ExtractCtuData(InputNALUnit nalu)
{
	BIN CtuData;
	for (int i = 0; i < nalu.getBitstream().getFifo().size()-HeaderLength; i++)
	{
		CtuData.push_back(nalu.getBitstream().getFifo()[i + HeaderLength]);
	}
	return CtuData;
}

//��һά����������ת��Ϊ��ά
BIN_2d NaluOperation::Bin_1dToBin_2d(BIN bin, int frameInGroupIdx, DATA data)
{
	BIN_2d bin2d;
	BIN temp;
	
	for (int i = 0; i < CtuNum; i++)
	{
		for (int j = 0; j < data[frameInGroupIdx][i]; j++)
		{
			temp.push_back(bin[j]);
		}
		for (int k = 0; k < data[frameInGroupIdx][i]; k++)
		{
			bin.erase(bin.begin());
		}
		bin2d.push_back(temp);
		temp.clear();
	}

	printf("\n\n");
	for (int i = 0; i < CtuNum; i++)
	{
		for (int j = 0; j < bin2d[i].size(); j++)
		{
			printf("%c", bin2d[i][j]);
		}
		printf("\n");
	}
	return bin2d;
}

BIN NaluOperation::Bin_2dToBin_1d(BIN_2d bin_2d)
{
	BIN bin_1d;
	for (int i = 0; i < CtuNum; i++)
	{
		for (int j = 0; j < bin_2d[i].size(); j++)
		{
			bin_1d.push_back(bin_2d[i][j]);
		}
	}
	bin_2d.clear();
	return bin_1d;
}