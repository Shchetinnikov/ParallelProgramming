#pragma once

#pragma pack(1)				// выравнивание в один байт
typedef struct BMPHeader {
	unsigned char ID[2];	// ID
	unsigned int file_size;	// размер BMP-файла
	unsigned char unused[4];
	unsigned int pixel_offset;	// смещение, по которому хранится массив пикселей
} BMPHeader;

typedef struct DIBHeader {
	unsigned int header_size;	// кол-во байт в DIBHeader
	unsigned int width;		// 	размер изображения
	unsigned int height;
	unsigned short color_planes;	// кол-во цветовых плоскостей
	unsigned short bits_per_pixel;  // кол-во бит на пиксель
	unsigned int comp;			// признак наличия сжатия
	unsigned int data_size;	// размер информации о пикселях (включая отступы)
	unsigned int pwidth;	// разрешение для печати
	unsigned int pheight;
	unsigned int colors_count;		// кол-во цветов в палитре
	unsigned int imp_colors_count;	// кол-во важных цветов
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