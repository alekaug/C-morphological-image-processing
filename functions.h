/**
	@file functions.h
	@brief Plik nag³ówkowy zawieraj¹cy deklaracje funkcji.
	@author Aleksander Augustyniak
*/

#ifndef functions_h
#define functions_h


/** \brief  Funkcja alokuj¹ca tyle pamiêci, by pomieœciæ ca³y zakres kolorów (wysokoœæ x szerokoœæ x 3 sk³adowe).
@param imgHeight wskaŸnik na wysokoœæ obrazu.
@param imgWidth wskaŸnik na szerokoœæ obrazu.
@return wskaŸnik do adresu schowka na dane wejœciowe lub NULL.
*/
uint8_t*** AllocateInputMemory(const uint32_t* imgHeight, const uint32_t* imgWidth);

/** \brief  Funkcja dealokuj¹ca ca³¹ pamiêæ zajêt¹ przez funkcjê AllocateInputMemory. 
@param image_in wskaŸnik do pocz¹tku tablicy na dane wejœciowe.
@param imgHeight wskaŸnik na wysokoœæ obrazu.
@param imgWidth wskaŸnik na szerokoœæ obrazu.
@return NULL.
*/
uint8_t*** DeallocateInputMemory(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth);

/** \brief  Funkcja sczytuj¹ca do struktury poszczególne sk³adowe ka¿dego piksela obrazu wejœciowego.
*			Je¿eli którykolwiek ze sk³adowych koloru piksela ma wartoœæ wiêksz¹ od 0 – wszystkie sk³adowe s¹ maksymalizowane.
@param image_in wskaŸnik do pocz¹tku tablicy na dane wejœciowe.
@param imgHeight wskaŸnik na wysokoœæ obrazu.
@param imgWidth wskaŸnik na szerokoœæ obrazu.
@param input_file wskaŸnik na plik wejœciowy.
@param offset_byte numer bajtu, od którego zaczynaj¹ siê dane zwi¹zane z zawartoœci¹ poszczególnych sk³adowych pikseli.
*/
void ReadPixels(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth, const FILE* input_file, uint32_t* offset_byte);

/** \brief  Funkcja alokuj¹ca tyle pamiêci, by pomieœciæ ca³y zakres kolorów dla pliku wyjœciowego.
@param image_in wskaŸnik do pocz¹tku tablicy na dane wejœciowe.
@param imgHeight wskaŸnik na wysokoœæ obrazu.
@param imgWidth wskaŸnik na szerokoœæ obrazu.
@return wskaŸnik do adresu schowka na dane wyjœciowe lub NULL.
*/
uint8_t*** AllocateOutputMemory(uint8_t*** image_in, const uint32_t* imgHeight, const uint32_t* imgWidth);

/** \brief  Funkcja dealokuj¹ca ca³¹ pamiêæ zajêt¹ przez funkcjê AllocateOutputMemory.
@param image_out wskaŸnik do pocz¹tku tablicy na dane wejœciowe.
@param imgHeight wskaŸnik na wysokoœæ obrazu.
@param imgWidth wskaŸnik na szerokoœæ obrazu.
@return NULL.
*/
uint8_t*** DeallocateOutputMemory(uint8_t*** image_out, const uint8_t* imgHeight, const uint8_t* imgWidth);

/** \brief  Funkcja zapisuj¹ca bajty sk³adowych kolorów pikseli do pliku wyjœciowego.
@param imgHeight wskaŸnik na wysokoœæ obrazu.
@param imgWidth wskaŸnik na szerokoœæ obrazu.
@param image_out wskaŸnik do pocz¹tku tablicy na dane wyjœciowe.
@param output_file wskaŸnik na plik wyjœciowy.
*/
void SaveBMPFile(const uint32_t* imgHeight, const uint32_t* imgWidth, const uint8_t*** image_out, const FILE* output_file);

/** \brief  Funkcja zapisuj¹ca do struktury dane nag³ówka pliku, zawieraj¹cego informacje nt. obrazu, m.in. rozdzielczoœæ, wysokoœæ, szerokoœæ, waga pliku, etc.
@param FileHeader wskaŸnik na podstrukturê mówi¹ca o tym, czy plik rzeczywiœcie jest plikiem mapy bitowej. Podstruktura mówi m.in. od którego bajtu zaczynaj¹ siê piksele.
@param Header wskaŸnik na podstrukturê, której dane opisuj¹ wymiary obrazu. Podstruktura zawiera przede wszystkim informacje techniczne obrazu.
@param input_file wskaŸnik na plik wejœciowy.
*/
void ReadToStructure(const BMPFILEHEADER* FileHeader, const BITMAPHEADER* Header, const FILE* input_file);

/** \brief  Funkcja zapisuj¹ca do pliku wyjœciowego pozyskane przez funkcjê ReadToStructure dane, zapisane do struktury.
@param FileHeader wskaŸnik na podstrukturê mówi¹ca o tym, czy plik rzeczywiœcie jest plikiem mapy bitowej. Podstruktura mówi m.in. od którego bajtu zaczynaj¹ siê piksele.
@param Header wskaŸnik na podstrukturê, której dane opisuj¹ wymiary obrazu. Podstruktura zawiera przede wszystkim informacje techniczne obrazu.
@param output_file wskaŸnik na plik wyjœciowy.
*/
void WriteFromStructure(const BMPFILEHEADER* FileHeader, const BITMAPHEADER* Header, const  FILE* output_file);

/** \brief  Funkcja zamienia kolor danego przez adres piksela.
@param pixel wskaŸnik do piksela edytowanego.
@param color wspó³czynnik mówi¹cy o tym, na jaki kolor ma byæ zamieniony dany piksel (1: bia³y / 0: czarny).
@return wskaŸnik na piksel zmodyfikowany.
*/
uint8_t* change_pixel_color(uint8_t* pixel, uint8_t color);

/** \brief  Funkcja sprawdza jakiego koloru jest podany piksel.
@param pixel wskaŸnik do piksela, którego poszczególne sk³adowego koloru maj¹ byæ sprawdzone.
@return 0 je¿eli wszystkie sk³adowe koloru piksela s¹ równe zero. W przeciwnym wypadku 1.
*/
uint8_t check_pixel_color(uint8_t* pixel);

/** \brief  G³ówny algorytm, który odpowiada za wykonanie operacji morfologicznych na obrazie.
*			Funkcja dopasowuje strukturê sita do piksela modyfikowanego tak, by mo¿na by³o sprawdziæ warunki zamiany piksela modyfikowanego.
@param type znak warunkuj¹cy operacjê, która ma byæ wykonana przez funkcjê ('e' – erozja; 'd' – dylatacja).
@param image_in wskaŸnik do pocz¹tku tablicy na dane wejœciowe.
@param image_out wskaŸnik do pocz¹tku tablicy na dane wyjœciowe.
@param width szerokoœæ obrazu.
@param width wysokoœæ obrazu.
@param sieve wskaŸnik na strukturê zawieraj¹c¹ dane elementu strukturalnego.
@param coordinates tablica zawieraj¹ca wspó³rzêdne po³o¿enia piksela modyfikowanego (g³ównego).
*/
void operation(const uint8_t type, uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates);

/** \brief Funkcja otwarcia morfologicznego, która wykonuje na obrazie w odpowiedniej kolejnoœci operacje w celu usuniêcia szczegó³ow z obrazu (erozja -> dylatacja).
@param image_in wskaŸnik do pocz¹tku tablicy na dane wejœciowe.
@param width szerokoœæ obrazu.
@param width wysokoœæ obrazu.
@param sieve wskaŸnik na strukturê zawieraj¹c¹ dane elementu strukturalnego.
@param coordinates tablica zawieraj¹ca wspó³rzêdne po³o¿enia piksela modyfikowanego (g³ównego).
*/
void opening(uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates);

/** \brief Funkcja zamkniêcia morfologicznego, która wykonuje na obrazie w odpowiedniej kolejnoœci operacje w celu "zamalowania" niewype³nionych do koñca szczelin (dylatacja-> erozja).
*		   Wymagany efekt œciœle zale¿y of elementu strukturalnego.
@param image_in wskaŸnik do pocz¹tku tablicy na dane wejœciowe.
@param width szerokoœæ obrazu.
@param width wysokoœæ obrazu.
@param sieve wskaŸnik na strukturê zawieraj¹c¹ dane elementu strukturalnego.
@param coordinates tablica zawieraj¹ca wspó³rzêdne po³o¿enia piksela modyfikowanego (g³ównego).
*/
void closing(uint8_t*** image_in, uint8_t*** image_out, uint32_t width, uint32_t height, pixel_structure* sieve, uint32_t* coordinates);

/** \brief  Funkcja wczytuj¹ca do specjalnej struktury element strukturalny.
@param stream wskaŸnik do pliku, który zawiera element strukturalny.
@return wskaŸnik na dynamiczn¹ listê jednokierunkow¹ zawieraj¹c¹ element strukturalny.
*/
pixel_structure* load_sieve(FILE* stream);

/** \brief  Funkcja dealokuj¹ca pamiêæ, potrzebn¹ by wczytaæ element strukturalny.
@param sieve wskaŸnik na dynamiczn¹ listê jednokierunkow¹ zawieraj¹c¹ element strukturalny.
*/
void deallocate_sieve(pixel_structure* sieve);

/** \brief  Algorytm wykrywaj¹cy wspó³rzêdne piksela modyfikowanego (g³ównego) elementu strukturalnego.
@param sieve wskaŸnik na dynamiczn¹ listê jednokierunkow¹ zawieraj¹c¹ element strukturalny.
@return wskaŸnik na tablicê wspó³rzêdnych punktu g³ównego elementu strukturalnego.
*/
uint32_t* main_point(pixel_structure* sieve);


#endif