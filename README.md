# PGK_PPM_IMPL

## PPM
implementacja najprostszego formatu pliku RGB bez kompresji  
* `PPM(std::istream &in) - konstruktor do załadowania pliku ppm z dowolnego strumienia wejściowego (nie obsługuje komentarzy);`  
* `PPM(int w, int h, int max_color = 255, color bg) - konstruktor tworzy pusty plik z tłem równym bg;`  
* `void SetPixel(int w, int h, color px); - ustawia kolor wskazanego pixela na px`  
* `color GetPixel(int w, int h); - zwraca kolor pixela na podanych współrzednych`  
* `bool In(int w, int h); - Sprawdz czy piksel mieści sie w obrazku`  
* `int GetMaxColor() - pobiera rozdzielczość palety kolorów np 256 - 24 bitowa paleta(True color)`  
* `void SetMaxColor(int max_color); - ustawia rozdzielczość, w obrazku nie może znajdować sie wartość większa niż max_color`  
* `friend std::ostream &operator<<(std::ostream &out, PPM &img); -  można wypisać zawartośc obiektu w formie pliku ppm do dowolnego strumienia wyjściowego` 

## funcs
implementacja algorytmów z PGK