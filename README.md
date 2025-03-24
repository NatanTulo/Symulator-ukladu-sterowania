# Symulator układu sterowania

## Opis projektu
Dany jest układ opisany transmitancją:

$$
G(s)=\frac{a_1 s + a_0}{b_2 s^2 + b_1 s + b_0}
$$

gdzie a1, a0, b2, b1, b0 to parametry modelu.

Projekt polega na implementacji symulatora tego układu wraz z parą sterowników LEAD-LAG, działających w konfiguracji z ujemnym sprzężeniem zwrotnym.

## Funkcjonalności
- Symulacja odpowiedzi czasowej układu na różne pobudzenia:
  - Sygnał harmoniczny
  - Sygnał prostokątny o skończonym czasie trwania
  - Sygnał trójkątny
- Możliwość zmiany parametrów transmitancji:
  - a1, a0 (licznik)
  - b2, b1, b0 (mianownik)
- Regulacja parametrów sterowników LEAD oraz LAG

## Działanie symulatora
Symulator przetwarza zadane pobudzenie oraz parametry sterowników, wykonując obliczenia metodą Eulera, a następnie wizualizuje przebiegi sygnałów wejściowego i wyjściowego przy użyciu biblioteki Matplot.

## Wymagania
- Biblioteka SFML do obsługi interfejsu graficznego
- Biblioteka Matplot do wykreślania wykresów

## Uruchomienie
Kompilacja oraz uruchomienie projektu odbywa się w środowisku obsługującym C++.