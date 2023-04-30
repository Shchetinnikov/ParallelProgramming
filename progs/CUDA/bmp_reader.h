#pragma once

#pragma pack(1)				// ������������ � ���� ����
typedef struct BMPHeader {
	unsigned char ID[2];	// ID
	unsigned int file_size;	// ������ BMP-�����
	unsigned char unused[4];
	unsigned int pixel_offset;	// ��������, �� �������� �������� ������ ��������
} BMPHeader;

typedef struct DIBHeader {
	unsigned int header_size;	// ���-�� ���� � DIBHeader
	unsigned int width;		// 	������ �����������
	unsigned int height;
	unsigned short color_planes;	// ���-�� �������� ����������
	unsigned short bits_per_pixel;  // ���-�� ��� �� �������
	unsigned int comp;			// ������� ������� ������
	unsigned int data_size;	// ������ ���������� � �������� (������� �������)
	unsigned int pwidth;	// ���������� ��� ������
	unsigned int pheight;
	unsigned int colors_count;		// ���-�� ������ � �������
	unsigned int imp_colors_count;	// ���-�� ������ ������
} DIBHeader;

typedef struct BMPFile {
	BMPHeader bhdr;
	DIBHeader dhdr;
	unsigned char* data;
} BMPFile;
#pragma pop

void printBMPHeaders(BMPFile* bmpf);
void printBMPPixels(BMPFile* bmpf);
BMPFile* loadBMPFile(char* fname);
void freeBMPFile(BMPFile* bmp_file);