/**
	@file functions.h
	@brief Plik nag��wkowy zawieraj�cy deklaracje funkcji.
	@author Aleksander Augustyniak
*/

#ifndef functions_h
#define functions_h


/** \brief  Funkcja alokuj�ca tyle pami�ci, by pomie�ci� ca�y zakres kolor�w (wysoko�� x szeroko�� x 3 sk�adowe).
@param imgHeight wska�nik na wysoko�� obrazu.
@param imgWidth wska�nik na szeroko�� obrazu.
@return wska�nik do adresu schowka na dane wej�ciowe lub NULL.
*/
uint8_t*** AllocateInputMemory(const uint32_t* imgHeight, const uint32_t* imgWidth);

/** \brief  Funkcja dealokuj�ca ca�� pami�� zaj�t� przez funkcj� AllocateInputMemory. 
@param image_in wska�nik do pocz�tku tablicy na dane wej�ciowe.
@param imgHeight wska�nik na wysoko�� obrazu.
@param imgWidth wska�nik na szeroko�� obrazu.
@return NULL.
*/
uint8_t*** DeallocateInputMemory(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth);

/** \brief  Funkcja sczytuj�ca do struktury poszczeg�lne sk�adowe ka�dego piksela obrazu wej�ciowego.
*			Je�eli kt�rykolwiek ze sk�adowych koloru piksela ma warto�� wi�ksz� od 0 � wszystkie sk�adowe s� maksymalizowane.
@param image_in wska�nik do pocz�tku tablicy na dane wej�ciowe.
@param imgHeight wska�nik na wysoko�� obrazu.
@param imgWidth wska�nik na szeroko�� obrazu.
@param input_file wska�nik na plik wej�ciowy.
@param offset_byte numer bajtu, od kt�rego zaczynaj� si� dane zwi�zane z zawarto�ci� poszczeg�lnych sk�adowych pikseli.
*/
void ReadPixels(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth, const FILE* input_file, uint32_t* offset_byte);

/** \brief  Funkcja alokuj�ca tyle pami�ci, by pomie�ci� ca�y zakres kolor�w dla pliku wyj�ciowego.
@param image_in wska�nik do pocz�tku tablicy na dane wej�ciowe.
@param imgHeight wska�nik na wysoko�� obrazu.
@param imgWidth wska�nik na szeroko�� obrazu.
@return wska�nik do adresu schowka na dane wyj�ciowe lub NULL.
*/
uint8_t*** AllocateOutputMemory(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth);

/** \brief  Funkcja dealokuj�ca ca�� pami�� zaj�t� przez funkcj� AllocateOutputMemory.
@param image_out wska�nik do pocz�tku tablicy na dane wej�ciowe.
@param imgHeight wska�nik na wysoko�� obrazu.
@param imgWidth wska�nik na szeroko�� obrazu.
@return NULL.
*/
uint8_t*** DeallocateOutputMemory(uint8_t*** image_out, const uint8_t* imgHeight, const uint8_t* imgWidth);

/** \brief  Funkcja zapisuj�ca bajty sk�adowych kolor�w pikseli do pliku wyj�ciowego.
@param imgHeight wska�nik na wysoko�� obrazu.
@param imgWidth wska�nik na szeroko�� obrazu.
@param image_out wska�nik do pocz�tku tablicy na dane wyj�ciowe.
@param output_file wska�nik na plik wyj�ciowy.
*/
void SaveBMPFile(const uint32_t* imgHeight, const uint32_t* imgWidth, const uint8_t*** image_out, const FILE* output_file);

/** \brief  Funkcja zapisuj�ca do struktury dane nag��wka pliku, zawieraj�cego informacje nt. obrazu, m.in. rozdzielczo��, wysoko��, szeroko��, waga pliku, etc.
@param FileHeader wska�nik na podstruktur� m�wi�ca o tym, czy plik rzeczywi�cie jest plikiem mapy bitowej. Podstruktura m�wi m.in. od kt�rego bajtu zaczynaj� si� piksele.
@param Header wska�nik na podstruktur�, kt�rej dane opisuj� wymiary obrazu. Podstruktura zawiera przede wszystkim informacje techniczne obrazu.
@param input_file wska�nik na plik wej�ciowy.
*/
void ReadToStructure(const BMPFILEHEADER* FileHeader, const BITMAPHEADER* Header, const FILE* input_file);

/** \brief  Funkcja zapisuj�ca do pliku wyj�ciowego pozyskane przez funkcj� ReadToStructure dane, zapisane do struktury.
@param FileHeader wska�nik na podstruktur� m�wi�ca o tym, czy plik rzeczywi�cie jest plikiem mapy bitowej. Podstruktura m�wi m.in. od kt�rego bajtu zaczynaj� si� piksele.
@param Header wska�nik na podstruktur�, kt�rej dane opisuj� wymiary obrazu. Podstruktura zawiera przede wszystkim informacje techniczne obrazu.
@param output_file wska�nik na plik wyj�ciowy.
*/
void WriteFromStructure(const BMPFILEHEADER* FileHeader, const BITMAPHEADER* Header, const  FILE* output_file);

/** \brief  Funkcja zamienia kolor danego przez adres piksela.
@param pixel wska�nik do piksela edytowanego.
@param color wsp�czynnik m�wi�cy o tym, na jaki kolor ma by� zamieniony dany piksel (1: bia�y / 0: czarny).
@return wska�nik na piksel zmodyfikowany.
*/
uint8_t* change_pixel_color(uint8_t* pixel, uint8_t color);

/** \brief  Funkcja sprawdza jakiego koloru jest podany piksel.
@param pixel wska�nik do piksela, kt�rego poszczeg�lne sk�adowego koloru maj� by� sprawdzone.
@return 0 je�eli wszystkie sk�adowe koloru piksela s� r�wne zero. W przeciwnym wypadku 1.
*/
uint8_t check_pixel_color(uint8_t* pixel);

/** \brief  G��wny algorytm, kt�ry odpowiada za wykonanie operacji morfologicznych na obrazie.
*			Funkcja dopasowuje struktur� sita do piksela modyfikowanego tak, by mo�na by�o sprawdzi� warunki zamiany piksela modyfikowanego.
@param type znak warunkuj�cy operacj�, kt�ra ma by� wykonana przez funkcj� ('e' � erozja; 'd' � dylatacja).
@param image_in wska�nik do pocz�tku tablicy na dane wej�ciowe.
@param image_out wska�nik do pocz�tku tablicy na dane wyj�ciowe.
@param width szeroko�� obrazu.
@param width wysoko�� obrazu.
@param sieve wska�nik na struktur� zawieraj�c� dane elementu strukturalnego.
@param coordinates tablica zawieraj�ca wsp�rz�dne po�o�enia piksela modyfikowanego (g��wnego).
*/
void operation(const uint8_t type, uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates);

/** \brief Funkcja otwarcia morfologicznego, kt�ra wykonuje na obrazie w odpowiedniej kolejno�ci operacje w celu usuni�cia szczeg�ow z obrazu (erozja -> dylatacja).
@param image_in wska�nik do pocz�tku tablicy na dane wej�ciowe.
@param width szeroko�� obrazu.
@param width wysoko�� obrazu.
@param sieve wska�nik na struktur� zawieraj�c� dane elementu strukturalnego.
@param coordinates tablica zawieraj�ca wsp�rz�dne po�o�enia piksela modyfikowanego (g��wnego).
*/
void opening(uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates);

/** \brief Funkcja zamkni�cia morfologicznego, kt�ra wykonuje na obrazie w odpowiedniej kolejno�ci operacje w celu "zamalowania" niewype�nionych do ko�ca szczelin (dylatacja-> erozja).
*		   Wymagany efekt �ci�le zale�y of elementu strukturalnego.
@param image_in wska�nik do pocz�tku tablicy na dane wej�ciowe.
@param width szeroko�� obrazu.
@param width wysoko�� obrazu.
@param sieve wska�nik na struktur� zawieraj�c� dane elementu strukturalnego.
@param coordinates tablica zawieraj�ca wsp�rz�dne po�o�enia piksela modyfikowanego (g��wnego).
*/
void closing(uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates);

/** \brief  Funkcja wczytuj�ca do specjalnej struktury element strukturalny.
@param stream wska�nik do pliku, kt�ry zawiera element strukturalny.
@return wska�nik na dynamiczn� list� jednokierunkow� zawieraj�c� element strukturalny.
*/
pixel_structure* load_sieve(FILE* stream);

/** \brief  Funkcja dealokuj�ca pami��, potrzebn� by wczyta� element strukturalny.
@param sieve wska�nik na dynamiczn� list� jednokierunkow� zawieraj�c� element strukturalny.
*/
void deallocate_sieve(pixel_structure* sieve);

/** \brief  Algorytm wykrywaj�cy wsp�rz�dne piksela modyfikowanego (g��wnego) elementu strukturalnego.
@param sieve wska�nik na dynamiczn� list� jednokierunkow� zawieraj�c� element strukturalny.
@return wska�nik na tablic� wsp�rz�dnych punktu g��wnego elementu strukturalnego.
*/
uint32_t* main_point(pixel_structure* sieve);


#endif