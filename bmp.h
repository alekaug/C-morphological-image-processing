/**
	@file bmp.h
	@brief Plik nag³ówkowy zawieraj¹cy wszelkie struktury, potrzebne do dzia³ania programu.
	@author Aleksander Augustyniak
*/

#include <inttypes.h>
#ifndef bmp_h
#define bmp_h

/** @brief  Pierwsza w kolejnoœci podstruktura struktury nag³ówkowej pliku mapy bitowej. */
typedef struct BMPFILEHEADER
{
	uint8_t s1;								///< Pierwszy znak typu pliku w kodzie ASCII (powinien wskazywaæ 'M').
	uint8_t s2;								///< Drugi znak typu pliku w kodzie ASCII (powinien wskazywaæ 'M').
	uint32_t size;							///< Rozmiar pliku obrazu mapy bitowej (powinno byæ 70 bajtów).
	uint16_t r1;							///< Bajt zarezerwowany dla aplikacji.
	uint16_t r2;							///< Bajt zarezerwowany dla aplikacji.
	uint32_t offset;						///< Numer bajtu, który rozpoczyna macierz pikseli.
}BMPFILEHEADER;

/** @brief  Struktura przechowuj¹ca nag³ówek DIB. */
typedef struct BITMAPHEADER
{
	uint32_t size;							///< Wartoœæ ta wskazuje na iloœæ bajtów, z których sk³ada siê drugi podnag³ówek pliku mapy bitowej.
	uint32_t width;							///< Szerokoœæ obrazu.
	uint32_t height;						///< Wysokoœæ obrazu.
	uint16_t numBitPlanes;					///< Liczba u¿ywanych przez obraz p³aszczyzn kolorów.
	uint16_t numBitsPerPlane;				///< Iloœæ bitów na piksel.
	uint32_t comp;							///< Parametr, wskazuj¹cy na typ kompresji (w tym przypadku 0).
	uint32_t image_size;
	uint32_t Xres;							///< Rozdzielczoœæ pozioma.
	uint32_t Yres;							///< Rozdzielczoœæ pionowa.
	uint32_t colors_used;					///< Iloœæ kolorów w palecie.
	uint16_t colors_importance_rotation;	///< Iloœæ wa¿nych kolorów w palecie (w tym przypadku 0; wszystkie kolory s¹ jednokowo wa¿ne).
	uint16_t reserved; ///< Bajty zarezerwowane przez aplikacjê.
}BITMAPHEADER;

/** @brief  Struktura przechowuj¹ca poszczególne sk³adowe kolorów pikseli. */
typedef struct PIXEL
{
	uint8_t blue;							///< Sk³adowa niebieska koloru piksela.
	uint8_t green;							///< Sk³adowa zielona koloru piksela.
	uint8_t red;							///< Sk³adowa czerwona koloru piksela.
}PIXEL;

typedef struct pixel_structure pixel_structure;

/** @brief  Struktura listy jednokierunkowej elementu strukturalnego.
			Sk³ada siê ona ze wskaŸnika na nastêpny element elementu strukturalnego, który zawiera znak.
			Ta struktura jest synchronizowana z siatk¹ pikselu obrazu za pomoc¹ odpowiednich funkcji.


*/
typedef struct pixel_structure
{
	pixel_structure* next;					///< WskaŸnik na nastêpny element (znak) elementu strukturalnego.
	uint8_t type;							///< Znak, który zawiera dany element elementu strukturalnego.

}pixel_structure;

#endif

