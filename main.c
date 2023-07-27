/** 
	@file main.c
	@brief Plik źródłowy.
	@author Aleksander Augustyniak
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <inttypes.h>
#include <ctype.h>
#include "bmp.h"
#include "functions.h"
		#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	// komunikat – za mało argumentów
	if (argc < 5)
	{
		printf("%s","\nSomething went wrong.\nThe proper use of the program: input_file.bmp output_file.bmp sieve_file.txt operation_type: e(rosion) / d(ilatation) / o(pening) / c(losing).\n ");
		exit(98);;
	}

	// otwarcie pliku BMP
	FILE* input_file = fopen(argv[1], "rb");
	if (!input_file)
		exit(101);

	// rezerwacja pamięci dla struktur
	const BMPFILEHEADER* FileHeader = (BMPFILEHEADER*)malloc(sizeof(BMPFILEHEADER));
	if (!FileHeader)
		exit(102);
	const BITMAPHEADER* Header = (BITMAPHEADER*)malloc(sizeof(BITMAPHEADER));
	if (!Header)
		exit(103);

	// załadowanie do struktury danych pliku mapy bitowej
	ReadToStructure(FileHeader, Header, input_file);

	// sprawdzenie, czy wejsciowy plik jest plikiem mapy bitowej
	if (!(FileHeader->s1 == 'B' && FileHeader->s2 == 'M'))
	{
		printf("\nInput is not a bitmap file.\n");
		exit(99);
	}

	// otwarcie pliku elementu strukturalnego
	FILE* sieve_file = fopen(argv[3], "r");
	if (sieve_file == 100)
		exit("\nProgram was unable to load a sieve file.\n");

	// wczytanie sita do struktury sita
	pixel_structure* sieve = load_sieve(sieve_file);
	if (!sieve)
		exit(104); // "sieve not found"

	fclose(sieve_file);
	sieve_file = (FILE*)0;

	// wyczytanie koordynatów punktu modyfikowanego
	uint32_t* coordinates = main_point(sieve);
	if (!coordinates)
		exit(105);
	
	// alokacja potrzebnej pamięci dla obrazu wejściowego (tymczasowy schowek)
	uint8_t*** image_in = AllocateInputMemory(&Header->height, &Header->width);
	if (!image_in)
		exit(106);
	ReadPixels(image_in, &Header->height, &Header->width, input_file, &FileHeader->offset);
	// zajmowanie pamięci dla obrazu wyjściowego
	uint8_t*** image_out = AllocateOutputMemory(image_in, &Header->height, &Header->width);
	if (!image_out)
		exit(107);

	// odczytaj znak typu operacji:
	*argv[4] = tolower(*argv[4]);
	if (*argv[4] == 'e')
		operation('e', image_in, image_out, Header->width, Header->height, sieve, coordinates);
	else if (*argv[4] == 'd')
		operation('d', image_in, image_out, Header->width, Header->height, sieve, coordinates);
	else if (*argv[4] == 'c')
		closing(image_in, image_out, Header->width, Header->height, sieve, coordinates);
	else if (*argv[4] == 'o')
		opening(image_in, image_out, Header->width, Header->height, sieve, coordinates);
	else
		printf("Obraz zostanie powielony (nieodpowiedni znak typu operacji)");

	// dealokacja sita po wykonaniu operacji morfologicznej
	deallocate_sieve(sieve);
	sieve = (pixel_structure*)0;

	// utworzenie (modyfikacja) pliku w lokalizacji podanej przez użytkownika
	FILE* output_file = fopen(argv[2], "wb");
	if (output_file == NULL)
		exit(108);

	// wypisanie ze struktury informacji z pliku przed modyfikacją
	WriteFromStructure(FileHeader, Header, output_file);

	// zapisanie wartości do pliku binarnego
	SaveBMPFile(&Header->height, &Header->width, image_out, output_file);

	// zwolnienie pamięci przydzielonej situ i współrzędnych piksela modyfikowanego
	free(coordinates);
	coordinates = (uint32_t*)0;
	
	// Zwolnienie ze sterty zaalokowanej pamięci obrazu wynikowego:
	image_in = DeallocateInputMemory(image_in, &Header->height, &Header->width);

	// Zwolnienie dodatkowej pamięci, zajętej na stercie dla obrazu wynikowego
	image_out = DeallocateOutputMemory(image_out, &Header->height, &Header->width);

	free(FileHeader);
	FileHeader = (BMPFILEHEADER*)0;
	free(Header);
	Header = (BITMAPHEADER*)0;
 	return 0;
} 