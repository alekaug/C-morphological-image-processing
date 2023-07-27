/**
	@file bmp.h
	@brief Plik nag��wkowy zawieraj�cy wszelkie struktury, potrzebne do dzia�ania programu.
	@author Aleksander Augustyniak
*/

#include <inttypes.h>
#ifndef bmp_h
#define bmp_h

/** @brief  Pierwsza w kolejno�ci podstruktura struktury nag��wkowej pliku mapy bitowej. */
typedef struct BMPFILEHEADER
{
	uint8_t s1;								///< Pierwszy znak typu pliku w kodzie ASCII (powinien wskazywa� 'M').
	uint8_t s2;								///< Drugi znak typu pliku w kodzie ASCII (powinien wskazywa� 'M').
	uint32_t size;							///< Rozmiar pliku obrazu mapy bitowej (powinno by� 70 bajt�w).
	uint16_t r1;							///< Bajt zarezerwowany dla aplikacji.
	uint16_t r2;							///< Bajt zarezerwowany dla aplikacji.
	uint32_t offset;						///< Numer bajtu, kt�ry rozpoczyna macierz pikseli.
}BMPFILEHEADER;

/** @brief  Struktura przechowuj�ca nag��wek DIB. */
typedef struct BITMAPHEADER
{
	uint32_t size;							///< Warto�� ta wskazuje na ilo�� bajt�w, z kt�rych sk�ada si� drugi podnag��wek pliku mapy bitowej.
	uint32_t width;							///< Szeroko�� obrazu.
	uint32_t height;						///< Wysoko�� obrazu.
	uint16_t numBitPlanes;					///< Liczba u�ywanych przez obraz p�aszczyzn kolor�w.
	uint16_t numBitsPerPlane;				///< Ilo�� bit�w na piksel.
	uint32_t comp;							///< Parametr, wskazuj�cy na typ kompresji (w tym przypadku 0).
	uint32_t image_size;
	uint32_t Xres;							///< Rozdzielczo�� pozioma.
	uint32_t Yres;							///< Rozdzielczo�� pionowa.
	uint32_t colors_used;					///< Ilo�� kolor�w w palecie.
	uint16_t colors_importance_rotation;	///< Ilo�� wa�nych kolor�w w palecie (w tym przypadku 0; wszystkie kolory s� jednokowo wa�ne).
	uint16_t reserved; ///< Bajty zarezerwowane przez aplikacj�.
}BITMAPHEADER;

/** @brief  Struktura przechowuj�ca poszczeg�lne sk�adowe kolor�w pikseli. */
typedef struct PIXEL
{
	uint8_t blue;							///< Sk�adowa niebieska koloru piksela.
	uint8_t green;							///< Sk�adowa zielona koloru piksela.
	uint8_t red;							///< Sk�adowa czerwona koloru piksela.
}PIXEL;

typedef struct pixel_structure pixel_structure;

/** @brief  Struktura listy jednokierunkowej elementu strukturalnego.
			Sk�ada si� ona ze wska�nika na nast�pny element elementu strukturalnego, kt�ry zawiera znak.
			Ta struktura jest synchronizowana z siatk� pikselu obrazu za pomoc� odpowiednich funkcji.


*/
typedef struct pixel_structure
{
	pixel_structure* next;					///< Wska�nik na nast�pny element (znak) elementu strukturalnego.
	uint8_t type;							///< Znak, kt�ry zawiera dany element elementu strukturalnego.

}pixel_structure;

#endif

