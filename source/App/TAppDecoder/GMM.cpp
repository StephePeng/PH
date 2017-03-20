#include "GMM.h"
using namespace std;

void GMM::myRead(Int picNum, std::string fileName, Int picHeight, Int picWidth)
{
	Int tag[4][5][3] = { 0 };
	tag[2][3][1] = tag[3][4][2] = 1;
	Int ctuSize = 64;
	string output_fileName = "output.yuv";
	std::ofstream	handle;
	handle.open(output_fileName, ios::binary | ios::out);

	ifstream inputFile;
	inputFile.open(fileName, ios::binary | ios::in);
	Int readStride = (picNum - 1)*(picHeight*picWidth * 3 / 2);
	inputFile.seekg(readStride, ios::beg);
	Int H = (picHeight%ctuSize) == 0 ? picHeight / ctuSize : picHeight / ctuSize + 1;
	Int W = (picWidth%ctuSize) == 0 ? picWidth / ctuSize : picWidth / ctuSize + 1;

	//Y分量缓存
	unsigned char **buf1 = new unsigned char *[picHeight / 2];
	for (Int i = 0; i < H*ctuSize; i++)
	{
		buf1[i] = new unsigned char[W*ctuSize]();
	}
	for (Int i = 0; i < H*ctuSize; i++)
	{
		inputFile.read(reinterpret_cast<char*>(buf1[i]), W*ctuSize);
		handle.write(reinterpret_cast<char*>(buf1[i]), W*ctuSize);
	}

	//定义U分量缓存
	unsigned char **buf2 = new unsigned char *[H*ctuSize / 2];
	for (Int i = 0; i < H*ctuSize / 2;i++)
	{
		buf2[i] = new unsigned char[W*ctuSize / 2]();
	}

	//定义V分量缓存
	unsigned char **buf3 = new unsigned char *[H*ctuSize / 2];
	for (Int i = 0; i < H*ctuSize / 2;i++)
	{
		buf3[i] = new unsigned char[W*ctuSize / 2]();
	}

	//读取UV分量到缓存buf2和buf3
	for (UInt i = 0; i < picHeight/2; i++)
	{
		inputFile.read(reinterpret_cast<char*>(buf2[i]), W*ctuSize / 2);
	}

	for (UInt i = 0; i < picHeight / 2; i++)
	{
		inputFile.read(reinterpret_cast<char*>(buf3[i]), W*ctuSize / 2);
	}

	for (int i = 1; i <= H; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			if (tag[i][j][picNum] == 1)
				for (int x = i*ctuSize; x < (i + 1)*ctuSize; x++)
					for (int y = j*ctuSize; y < (j + 1)*ctuSize; y++)
					{
						buf2[x / 2][y / 2] = 128;
						buf3[x / 2][y / 2] = 128;
					}
		}
	    handle.write(reinterpret_cast<char*>(buf2), picWidth/2);
		handle.write(reinterpret_cast<char*>(buf3), picWidth / 2);
	}

	inputFile.close();

}