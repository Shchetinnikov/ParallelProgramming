#include <iostream>
#include <stdio.h>

#include "bmp_reader.h"

using namespace std;

void printBMPHeaders(BMPFile* bmpf) {
	cout << "ID\[2\] = " << bmpf->bhdr.ID[0] << bmpf->bhdr.ID[1] << endl
		<< "file_size = " << bmpf->bhdr.file_size << endl
		<< "pixel_offset = " << bmpf->bhdr.pixel_offset << endl << endl;
	cout << "header_size = " << bmpf->dhdr.header_size << endl
		<< "width = " << bmpf->dhdr.width << endl
		<< "height = " << bmpf->dhdr.height << endl
		<< "color_planes = " << bmpf->dhdr.color_planes << endl
		<< "bits_per_pixel = " << bmpf->dhdr.bits_per_pixel << endl
		<< "comp = " << bmpf->dhdr.comp << endl
		<< "data_size = " << bmpf->dhdr.data_size << endl
		<< "pwidth = " << bmpf->dhdr.pwidth << endl
		<< "pheight = " << bmpf->dhdr.pheight << endl
		<< "colors_count = " << bmpf->dhdr.colors_count << endl
		<< "imp_colors_count = " << bmpf->dhdr.imp_colors_count << endl << endl;
}


void printBMPPixels(BMPFile* bmpf) {
	int data_size = bmpf->dhdr.width * bmpf->dhdr.height * bmpf->dhdr.bits_per_pixel / 8;
	for (int i = 0; i < data_size; i++) {
		if (i % 16 == 0)
			printf("\n%04x: ", i);
		printf("%02x ", bmpf->data[i]);
	}
	cout << endl << endl;
}


void readBMPRowByRow(FILE* fp, BMPFile* bmpf) {
	int bytes_per_pixel = bmpf->dhdr.bits_per_pixel / 8;
	int row_size = bytes_per_pixel * bmpf->dhdr.width;
	int row_padding = (4 - (row_size % 4)) % 4;		// кол-во байт выравнивания
	int rows_written = 0;							// кол-во записанных в память строк

	unsigned char* row = (unsigned char*)malloc(row_size + row_padding);
	unsigned char* p = &bmpf->data[(bmpf->dhdr.height - 1) * row_size];
	
	fseek(fp, bmpf->bhdr.pixel_offset, SEEK_SET);

	while (rows_written < bmpf->dhdr.height) {
		fread(row, row_size + row_padding, 1, fp);
		if (bytes_per_pixel == 3) {
			for (int i = 0; i < row_size; i += bytes_per_pixel) {
				*p = row[i + 2]; p++;
				*p = row[i + 1]; p++;
				*p = row[i]; p++;
			}
		}
		else if (bytes_per_pixel == 4) {
			for (int i = 0; i < row_size; i += bytes_per_pixel) {
				*p = row[i + 3]; p++;
				*p = row[i + 2]; p++;
				*p = row[i + 1]; p++;
				*p = row[i]; p++;
			}
		}
		else {
			cout << "Error: don't work with bytes_per_pixel = " << bytes_per_pixel;
			exit(0);
		}
		rows_written++;
		p = p - 2 * row_size;
	}
	free(row);
}


BMPFile* loadBMPFile(char* fname) {
	FILE* fp = fopen(fname, "r");
	if (!fp) {
		cout << "Can't load file " << fname;
		exit(0);
	}

	BMPFile* bmp_file = (BMPFile*)malloc(sizeof(BMPFile));
	fread(&bmp_file->bhdr, sizeof(BMPHeader), 1, fp);
	fread(&bmp_file->dhdr, sizeof(DIBHeader), 1, fp);

	int data_size = bmp_file->dhdr.width * bmp_file->dhdr.height * bmp_file->dhdr.bits_per_pixel / 8;

	bmp_file->data = (unsigned char*)malloc(data_size);
	readBMPRowByRow(fp, bmp_file);

	fclose(fp);
	return bmp_file;
}

void freeBMPFile(BMPFile* bmp_file) {
	if (bmp_file) {
		free(bmp_file);
	}
}
