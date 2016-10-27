
//@Author zhaossbnu

#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<Windows.h>
using namespace std;

struct RGB{
	BYTE B;
	BYTE G;
	BYTE R;
};

int main(void)
{
	//ifstream fin("filein,bmp", std::ios::binary);
	//ofstream fout("fileout.bmp", std::ios::binary | std::ios::app);
	FILE* fin = fopen("filein.bmp", "rb");
	FILE* fout = fopen("fileout.bmp", "wb");

	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;

	//fin.read((char *)&BmpFileHeader, sizeof(BITMAPFILEHEADER));
	//fin.read((char *)&BmpInfoHeader, sizeof(BITMAPINFOHEADER));
	fread(&BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fin);
	fread(&BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fin);
	if(BmpInfoHeader.biBitCount == 24)
	{
		int m = BmpInfoHeader.biWidth;
		int n = BmpInfoHeader.biHeight;
		RGB* *byteimg = new RGB* [n];
		for(int i = 0; i < n; i ++)
		{
			byteimg[i] = new RGB[m];
		}
		for(int i = 0; i <n; i ++)
		{
			for(int j = 0; j < m; j++)
			{
				byteimg[i][j].B = '\0';
				byteimg[i][j].G = '\0';
				byteimg[i][j].R = '\0';
			}
		}
		
		
		//欢脱的将像素信息输入
		int rowSize = 4*(int)ceil(((double)(24*m))/32);
		char ch;
		int count_byte = -1, count_use_byte = -1;
		while((fscanf(fin, "%c", &ch))!=EOF)
		//while(!fin.eof())
		{
			//fin.read(&ch , sizeof(char));
			count_byte ++;
			if(count_byte%rowSize == rowSize - 1 ||count_byte%rowSize == rowSize - 2)
			{
				continue;
			}
			count_use_byte ++;
			if(count_use_byte%3==0)
				byteimg[(count_use_byte/3)/m][(count_use_byte/3)%m].B = ch;
			else if(count_use_byte%3 ==1)
				byteimg[(count_use_byte/3)/m][(count_use_byte/3)%m].G = ch;
			else
				byteimg[(count_use_byte/3)/m][(count_use_byte/3)%m].R = ch;
		}

		//欢快的加入学号  4
		for(int i = 100; i < 150; i ++ )
			for(int j = 100 ; j < 110; j++)
			{
				byteimg[i][j].B = byteimg[i][j].G = byteimg[i][j].R = 0;
			}
		for(int i = 100; i < 110; i ++)
			for(int j = 110; j <140; j ++)
			{
				byteimg[i][j].B = byteimg[i][j].G = byteimg[i][j].R = 0;
			}
		for(int i = 50; i < 150; i ++)
			for(int j = 140; j < 150; j ++)
			{
				byteimg[i][j].B = byteimg[i][j].G = byteimg[i][j].R = 0;
			}

		//愉快的输出文件
		BmpInfoHeader.biBitCount = 8;
		BmpInfoHeader.biSizeImage = n * (m + 2);
		BmpFileHeader.bfOffBits += 4 * 256;
		BmpFileHeader.bfSize = BmpFileHeader.bfOffBits + BmpInfoHeader.biSizeImage;
		//cout<<"bfSize:"<<BmpFileHeader.bfSize<<endl;
		//cout<<"bfOffBits:"<<BmpFileHeader.bfOffBits<<endl;
		//cout<<"biSizeImage:"<<BmpInfoHeader.biSizeImage<<endl;
		//cout<<"bfSize = bfOffBits + biSizeImage"<<endl;
		fwrite(&BmpFileHeader, sizeof(BmpFileHeader), 1, fout);
		fwrite(&BmpInfoHeader, sizeof(BmpInfoHeader), 1, fout);
		//fout.write((char*)&BmpFileHeader, sizeof(BmpFileHeader));
		//fout.write((char*)&BmpInfoHeader,sizeof(BmpInfoHeader));
		for(int i = 0; i < 256; i ++)
		{
			fprintf(fout, "%c%c%c%c", i,i,i,'\0');
			//fout.write((char*)&i, 3*sizeof(char));
			//fout.write("\0", sizeof(char));
		}
		for(int i = 0; i < n; i ++)
		{
			for(int j = 0; j < m; j++)
			{
				//fout.write((char*)(int)(0.299 * byteimg[i][j].R + 0.587 * byteimg[i][j].G + 0.114 * byteimg[i][j].B), sizeof(char));
				fprintf(fout, "%c", (int)(0.299 * byteimg[i][j].R + 0.587 * byteimg[i][j].G + 0.114 * byteimg[i][j].B));
			}
			//fout.write("\0\0", 2*sizeof(char));
			fprintf(fout, "%c%c", '\0', '\0');
		}
		//fin.close();
		//fout.close();
		fclose(fin);
		fclose(fout);

	}

	return 0;
}