# SK_Dobble
===============Gra na spostrzegawczość przez sieć===============

Opis:

Gracz łączy się do serwera i wysyła swój nick. Jeśli nick jest już używany, serwer prosi o podanie nowego nicku. Powtarza tę czynność tak długo, aż zaproponowany nick będzie unikalny.

Gracz po wybraniu nicku trafia do menu, w którym może dołączyć do gry lub przeczytać zasady rozgrywki.

Jeśli gra już trwa, gracz czeka na rozpoczęcie nowej gry. Jeśli nie, gracz widzi listę graczy i czeka na rozpoczęcie gry.

Gra rozpoczyna się po minucie, odkąd do pokoju dołączyło przynajmniej trzech graczy.

Gracze dostają równą liczbę kart, po 8 różnych symboli na każdej z nich. Widzą tylko jedną ze swoich kart "położoną na górze".
Każdy gracz widzi też jedną kartę wspólną dla wszystkich graczy, która jest kartą porównawczą. Każdy z graczy porównuje swoją kartę ze wspólna kartą porównawczą i szuka na nich identycznego elementu(każde dwie karty z całej talii mają dokładnie jeden identyczny element).

Karta gracza, który jako pierwszy poprawnie wskaże wspólny element ląduje na górze wspólnego stosu kart i staje się kartą, względem której reszta graczy porównuje swoje karty. Jeżeli jakiś gracz wskaże błędny element (np. strzela, żeby być pierwszym) zostaje zablokowany aż kolejna karta trafi na wspólny stos. 

Na górze ekranu gry wyświetlane są punkty wszystkich graczy aktualizowane na bieżąco. Za poprawne wskazanie karty jako pierwszy, gracz dostaje jeden punkt. Jeżeli dwóch lub więcej graczy dokładnie w tym samym momencie wskaże poprawny element, wszyscy dostają po jednym punkcie, a na wspólny stos trafia losowa karta z ich kart. 

Gra trwa do momentu aż wszystkie osoby poza ostatnią pozbędą się swoich kart.


# Budowanie projektu

1. Stworz katalog build i zbuduj w nim projekt:
  1.1. mkdir build
  1.2. cd build
  1.3. cmake ..
  1.4. make
2. Program klienta jest w katalogu Dobble, serwer w katalogu Server
  1.1. cd Dobble && ./client
  1.2. cd Server && ./server
