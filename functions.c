/**
	@file functions.c
	@brief Plik nag³ówkowy zawieraj¹cy definicje funkcji.
	@author Aleksander Augustyniak
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "bmp.h"
#include "functions.h"

uint8_t*** AllocateInputMemory(const uint32_t* imgHeight, const uint32_t* imgWidth)
{
	uint8_t*** image_in = (uint8_t***)malloc(*imgHeight * sizeof(uint8_t**));
	if (!image_in)
		return (uint8_t***)0;
	for (int i = 0; i < *imgHeight; i++)
	{
		image_in[i] = (uint8_t**)malloc(*imgWidth * sizeof(uint8_t*));
		image_in[i] == (uint8_t**)0 ? exit(__LINE__) : 0;

		for (int j = 0; j < *imgWidth; j++)
		{
			image_in[i][j] = (uint8_t*)malloc(3 * sizeof(uint8_t));
			image_in == (uint8_t*)0 ? exit(__LINE__) : 0;
		}
	}
	return image_in;
}
uint8_t*** DeallocateInputMemory(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth)
{
	for (int y = 0; y < *imgHeight; y++)
	{
		for (int x = 0; x < *imgWidth; x++)
			free(image_in[y][x]);
		free(image_in[y]);
	}
	free(image_in);
	return (uint8_t***)0;
}
void ReadPixels(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth, const FILE* input_file, const uint32_t* offset_byte)
{
	fseek(input_file, *offset_byte, SEEK_SET);
	PIXEL actual;
	for (int y = 0; y < *imgHeight; y++)
	{
		for (int x = 0; x < *imgWidth; x++)
		{
			// konwencja: zapisywanie wartoœci kolorów w kolejnoœci Blue, Green, Red.
			fread(&actual, sizeof(actual), 1, input_file);

			// warunek: je¿eli 
			if (actual.blue != 0 || actual.green != 0 || actual.red != 0)
				actual.green = actual.blue = actual.red = 255;

			image_in[y][x][0] = actual.blue;
			image_in[y][x][1] = actual.green;
			image_in[y][x][2] = actual.red;
		}
		fseek(input_file, *imgWidth % 4, SEEK_CUR);
	}
	fclose(input_file);
	input_file = (FILE*)0;
}
uint8_t*** AllocateOutputMemory(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth)
{
	uint8_t*** image_out = (uint8_t***)malloc(*imgHeight * sizeof(uint8_t**));
	if (!image_out)
		return (uint8_t***)0;
	for (int i = 0; i < *imgHeight; i++)
	{
		image_out[i] = (uint8_t**)malloc(*imgWidth * sizeof(uint8_t*));
		image_out == (void*)0 ? exit(__LINE__) : 0;


		for (int j = 0; j < *imgWidth; j++)
		{
			image_out[i][j] = (uint8_t*)malloc(3 * sizeof(uint8_t));
			image_out == (void*)0 ? exit(__LINE__) : 0;
			image_out[i][j][0] = image_in[i][j][0];
			image_out[i][j][1] = image_in[i][j][1];
			image_out[i][j][2] = image_in[i][j][2];
		}
	}
	return image_out;
}
uint8_t*** DeallocateOutputMemory(uint8_t*** image_out, const uint8_t* imgHeight, const uint8_t* imgWidth)
{
	for (int y = 0; y < *imgHeight; y++)
	{
		for (int x = 0; x < *imgWidth; x++)
			free(image_out[y][x]);
		free(image_out[y]);
	}
	free(image_out);
	return (uint8_t***)0;
}
void SaveBMPFile(const uint32_t* imgHeight, const uint32_t* imgWidth, const uint8_t*** image_out, const FILE* output_file)
{
	uint8_t nothing = 0;
	for (int y = 0; y < *imgHeight; y++)
	{
		for (int x = 0; x < *imgWidth; x++)
		{
			// konwencja: zapisywanie wartoœci kolorów w kolejnoœci Blue, Green, Red.
			fwrite(&image_out[y][x][0], sizeof(uint8_t), 1, output_file);
			fwrite(&image_out[y][x][1], sizeof(uint8_t), 1, output_file);
			fwrite(&image_out[y][x][2], sizeof(uint8_t), 1, output_file);
		}
		fwrite(&nothing, sizeof(uint8_t), *imgWidth % 4, output_file);
	}
	fclose(output_file);
	output_file = (FILE*)0;
}
void ReadToStructure(const BMPFILEHEADER* FileHeader, const BITMAPHEADER* Header, const FILE* input_file)
{
	// BMP FILE HEADER
	fseek(input_file, 0, SEEK_SET);
	fread(&FileHeader->s1, sizeof(FileHeader->s1), 1, input_file);
	fread(&FileHeader->s2, sizeof(FileHeader->s2), 1, input_file);
	fread(&FileHeader->size, sizeof(FileHeader->size), 1, input_file);
	fread(&FileHeader->r1, sizeof(FileHeader->r1), 1, input_file);
	fread(&FileHeader->r2, sizeof(FileHeader->r2), 1, input_file);
	fread(&FileHeader->offset, sizeof(FileHeader->offset), 1, input_file);
	// DIB HEADER
	fread(&Header->size, sizeof(Header->size), 1, input_file);
	fread(&Header->width, sizeof(Header->width), 1, input_file);
	fread(&Header->height, sizeof(Header->height), 1, input_file);
	fread(&Header->numBitPlanes, sizeof(Header->numBitPlanes), 1, input_file);
	fread(&Header->numBitsPerPlane, sizeof(Header->numBitsPerPlane), 1, input_file);
	fread(&Header->comp, sizeof(Header->comp), 1, input_file);
	fread(&Header->image_size, sizeof(Header->image_size), 1, input_file);
	fread(&Header->Xres, sizeof(Header->Xres), 1, input_file);
	fread(&Header->Yres, sizeof(Header->Yres), 1, input_file);
	fread(&Header->colors_used, sizeof(Header->colors_used), 1, input_file);
	fread(&Header->colors_importance_rotation, sizeof(Header->colors_importance_rotation), 1, input_file);
	fread(&Header->reserved, sizeof(Header->reserved), 1, input_file);
}
void WriteFromStructure(const BMPFILEHEADER* FileHeader, const BITMAPHEADER* Header, const FILE* output_file)
{
	// BMP FILE HEADER
	fwrite(&FileHeader->s1, sizeof(FileHeader->s1), 1, output_file);
	fwrite(&FileHeader->s2, sizeof(FileHeader->s2), 1, output_file);
	fwrite(&FileHeader->size, sizeof(FileHeader->size), 1, output_file);
	fwrite(&FileHeader->r1, sizeof(FileHeader->r1), 1, output_file);
	fwrite(&FileHeader->r2, sizeof(FileHeader->r2), 1, output_file);
	fwrite(&FileHeader->offset, sizeof(FileHeader->offset), 1, output_file);
	
	// DIB HEADER
	fwrite(&Header->size, sizeof(Header->size), 1, output_file);
	fwrite(&Header->width, sizeof(Header->width), 1, output_file);
	fwrite(&Header->height, sizeof(Header->height), 1, output_file);
	fwrite(&Header->numBitPlanes, sizeof(Header->numBitPlanes), 1, output_file);
	fwrite(&Header->numBitsPerPlane, sizeof(Header->numBitsPerPlane), 1, output_file);
	fwrite(&Header->comp, sizeof(Header->comp), 1, output_file);
	fwrite(&Header->image_size, sizeof(Header->image_size), 1, output_file);
	fwrite(&Header->Xres, sizeof(Header->Xres), 1, output_file);
	fwrite(&Header->Yres, sizeof(Header->Yres), 1, output_file);
	fwrite(&Header->colors_used, sizeof(Header->colors_used), 1, output_file);
	fwrite(&Header->colors_importance_rotation, sizeof(Header->colors_importance_rotation), 1, output_file);
	fwrite(&Header->reserved, sizeof(Header->reserved), 1, output_file);
}
uint8_t* change_pixel_color(uint8_t* pixel, uint8_t color)
{
	if (color == 1)
		*pixel = *(pixel + 1) = *(pixel + 2) = 255;
	else
		*pixel = *(pixel + 1) = *(pixel + 2) = 0;
	return pixel;
}
uint8_t check_pixel_color(uint8_t* pixel)
{
	return pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0 ?  0 :  1;
}
void operation(const uint8_t type, uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates)
{
	for (int32_t y = 0; y < height; y++)
	{
		for (int32_t x = 0; x < width; x++)
		{
			int32_t pX = x - coordinates[0];
			int32_t pY = y + coordinates[1];
			pixel_structure* ptr = sieve;
			while (ptr->type != 'E')
			{
				//punkt sprawdzany nie odpowiada zakresowi
				if (!(pY >= 0 && pY < height && pX >= 0 && pX < width))
				{
					if (ptr->type != '\n')
						pX++;
					else
					{
						pX = x - coordinates[0];
						pY--;
					}
				}
				else
				{
					if (ptr->type == ' ')
					{
						pX++;
					}
					else if (ptr->type == '-')
					{
						if (check_pixel_color(image_in[pY][pX]) == 1 && type == 'e')
							change_pixel_color(image_out[y][x], 1);
						else if (check_pixel_color(image_in[pY][pX]) == 0 && type == 'd')
							change_pixel_color(image_out[y][x], 0);
						pX++;
					}
					else if (ptr->type == '\n')
					{
						pX = x - coordinates[0];
						pY--;
					}
					else
					{
						pX++;
					}
				}
				ptr = ptr->next;
			}
		}
	}
	for (int32_t y = 0; y < height; y++)
	{
		for (int32_t x = 0; x < width; x++)
		{
			image_in[y][x][0] = image_out[y][x][0];
			image_in[y][x][1] = image_out[y][x][1];
			image_in[y][x][2] = image_out[y][x][2];
		}
	}
}
void opening(uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates)
{
	operation('e', image_in, image_out, width, height, sieve, coordinates);
	operation('d', image_in, image_out, width, height, sieve, coordinates);
}
void closing(uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates)
{
	operation('d', image_in, image_out, width, height, sieve, coordinates);
	operation('e', image_in, image_out, width, height, sieve, coordinates);
}
pixel_structure* load_sieve(FILE* stream)
{
	pixel_structure* sieve_array = (pixel_structure*)calloc(1, sizeof(pixel_structure));
	pixel_structure* sieve_ptr = sieve_array;
	unsigned char isMainPoint = 0;
	unsigned char isNeighbor = 0;
	char sign = 0;
	while ((sign = getc(stream)) != EOF)
	{
		if (sign == '-' && isNeighbor == 0)
			isNeighbor = 1;
		if (sign == 'o')
		{
			if (isMainPoint == 0)
				isMainPoint = 1;
			else if (sign == 'o' && isMainPoint == 1)
				isMainPoint = 2;
			if (sign == 'o' && isMainPoint == 2)
			{
				sign = '-';
				if (!isNeighbor)
					isNeighbor = 1;
			}
		}
		if (sign != 'o' && sign != '-' && sign != ' ' && sign != '\n')
			sign = ' ';
		sieve_ptr->type = sign;
		sieve_ptr->next = (pixel_structure*)malloc(sizeof(pixel_structure));
		sieve_ptr = sieve_ptr->next;
		sieve_ptr->next = (pixel_structure*)0;
	}

	if (!isMainPoint || !isNeighbor)
	{
		while (sieve_array->next)
		{
			sieve_ptr = sieve_array->next;
			free(sieve_array);
			sieve_array = sieve_ptr;
		}
		free(sieve_array);
		return (pixel_structure*)0;
	}

	sieve_ptr->type = 'E';

	pixel_structure* ptr = sieve_array;
	while (ptr)
	{
		if (ptr->type == 'E')
			return sieve_array;
		sign = ptr->type;
		printf("%c ", sign);
		ptr = ptr->next;
	}

}
uint32_t* main_point(pixel_structure* sieve)
{
	pixel_structure* ptr = sieve;
  	uint32_t* coordinates = (uint32_t*)calloc(2, sizeof(uint32_t));
	uint32_t x = 0, y = 0;
	while (ptr)
	{

		if (ptr->type == 'o')
		{
			coordinates[0] = x;
			coordinates[1] = y;
			return coordinates;
		}
		else if (ptr->type == '\n')
		{
			y++;
			x = 0;
		}
		else
		{
			x++;
		}
		ptr = ptr->next;
	}
	free(coordinates);
	return (uint32_t*)0;
}
void deallocate_sieve(pixel_structure* sieve)
{
	pixel_structure* ptr = sieve;
	if (!ptr)
		return;
	while (ptr)
	{
		sieve = ptr->next;
		free(ptr);
		ptr = sieve;
	}
	sieve = (pixel_structure*)0;
}