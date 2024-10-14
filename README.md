Kluczowe punkty do stworzenia gry:

1. **Rysowanie świata gry i postaci**  
   Należy stworzyć okno gry, w którym będą rysowane wszystkie elementy za pomocą biblioteki graficznej (np. SFML). Postać gracza, przeciwnicy oraz ściany powinny być reprezentowane jako obiekty 2D, takie jak prostokąty. Mapa musi być podzielona na różne typy obiektów (ściany, otwarte przestrzenie, drzwi).

2. **Sterowanie i mechanika ruchu**  
   Powinien zostać zaimplementowany system sterowania postacią, bazujący na klawiaturze do ruchu i myszce do celowania, wzorowany na grze Hotline Miami. Należy wdrożyć mechanikę strzelania oraz ataków, zależnie od rodzaju broni, którą postać posiada. Należy również zastosować system kolizji, aby zapobiec przenikaniu postaci przez ściany.

3. **Mechanika ograniczonego pola widzenia (FOV – Field of View)**  
   Ograniczone pole widzenia można uzyskać za pomocą rzutowania promieni (raycasting), sprawdzając, czy promienie napotykają przeszkody (ściany). Każdy promień powinien definiować obszar, który gracz widzi, a pozostałe części ekranu mogą być przyciemnione lub niewidoczne. Promienie należy ograniczyć do stożka widzenia, np. 120 stopni przed postacią, aby zasymulować ograniczoną wizję.

4. **System kolizji**  
   Aby uniemożliwić postaci przenikanie przez ściany lub inne przeszkody, należy zaimplementować system detekcji kolizji. Kolizje można wykrywać, sprawdzając, czy prostokąty reprezentujące postać i ściany nachodzą na siebie.

5. **AI przeciwników**  
   Sztuczna inteligencja przeciwników powinna być zaprojektowana w taki sposób, aby mogli oni ścigać gracza, atakować go i unikać przeszkód. Przeciwnicy powinni reagować na dźwięki, obecność gracza w polu widzenia lub inne wydarzenia. Można wykorzystać algorytmy, takie jak A* (A-star), do poruszania się przeciwników po mapie w kierunku gracza.

6. **System walki i broni**  
   Każda broń musi mieć określone statystyki, takie jak zasięg, szybkość strzelania oraz ilość amunicji. Należy dodać mechanikę punktów życia dla postaci i przeciwników, które będą redukowane po trafieniach.

7. **Różnorodność poziomów**  
   Powinien zostać stworzony system umożliwiający łatwe generowanie różnych poziomów gry lub wczytywanie ich z plików. Mapy mogą być opisane w prostych plikach tekstowych, zawierających informacje o układzie ścian, drzwi oraz przeciwników.

8. **Audio i muzyka**  
   W grze należy zaimplementować system odtwarzania muzyki i efektów dźwiękowych (strzały, kroki, wybuchy). Biblioteka SFML oferuje wbudowane funkcje do obsługi dźwięku.

9. **Optymalizacja i debugowanie**  
   Podczas implementacji gry, zwłaszcza przy rzutowaniu promieni, należy zadbać o wydajność poprzez stosowanie odpowiednich algorytmów i struktur danych, aby zminimalizować zbędne obliczenia. Debugowanie powinno obejmować kolizje, poprawność działania pola widzenia oraz AI przeciwników.

10. **Testowanie i balans rozgrywki**  
   Należy testować różne poziomy trudności gry, balansując siłę przeciwników oraz reakcje gracza. Warto sprawdzić, czy system wizji działa poprawnie na różnych mapach, uwzględniając różnorodne przeszkody.
