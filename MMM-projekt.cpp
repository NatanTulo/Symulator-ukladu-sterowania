#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <cmath>
#include <matplot/matplot.h>

using namespace matplot;

#define N 4
#define h 0.001
#define T 10.0
#define PI 3.14159265

typedef struct { double n[N]; } Vect;
typedef struct { double n[N][N]; } Matr;
typedef union { char c[sizeof(double)]; double d; } Box;

Vect operator+(const Vect& U, const Vect& V) {
    Vect W;
    for (int i = 0; i < N; i++)
        W.n[i] = U.n[i] + V.n[i];
    return W;
}

Vect operator*(const Vect& U, const double& d) {
    Vect W;
    for (int i = 0; i < N; i++)
        W.n[i] = U.n[i] * d;
    return W;
}

Vect operator*(const Matr& A, const Vect& V) {
    Vect W;
    for (int i = 0; i < N; i++) {
        W.n[i] = 0;
        for (int j = 0; j < N; j++)
            W.n[i] += A.n[i][j] * V.n[j];
    }
    return W;
}

double operator*(const Vect& U, const Vect& V) {
    double s = 0;
    for (int i = 0; i < N; i++)
        s += U.n[i] * V.n[i];
    return s;
}

void Grafika(double* a1, double* a0, double* b2, double* b1, double* b0, double* k1, double* z1, double* p1, double* k2, double* z2, double* p2, double* m, double *ff, bool *wyswietlWykresy, bool *zamknij, bool *harmonicImput, bool *rectangularImput, bool *triangularImput)
{
    // Utworzenie głównego okna
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Korektor Lead-Lag");

    // Załaduj czcionkę
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
    }

    // Utworzenie pola tekstowego
    sf::Text inputText("", font, 30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(50.f, 50.f);

    sf::Text zatwierdzanie(L"ZATWIERDŹ", font, 20);
    zatwierdzanie.setFillColor(sf::Color::Black);
    zatwierdzanie.setPosition(1700, 920);

    sf::RectangleShape przyciskZatwierdzania(sf::Vector2f(150.0f, 50.0f));
    przyciskZatwierdzania.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    przyciskZatwierdzania.setPosition(1680.0f, 907.0f);

    sf::Text cofanie("COFNIJ", font, 20);
    cofanie.setFillColor(sf::Color::Black);
    cofanie.setPosition(1719, 920);

    sf::RectangleShape przyciskCofania(sf::Vector2f(150.0f, 50.0f));
    przyciskCofania.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    przyciskCofania.setPosition(1680.0f, 907.0f);

    sf::Text wychodzenie(L"WYJDŹ", font, 20);
    wychodzenie.setFillColor(sf::Color::Black);
    wychodzenie.setPosition(1719, 840);

    sf::RectangleShape przyciskWychodzenia(sf::Vector2f(150.0f, 50.0f));
    przyciskWychodzenia.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    przyciskWychodzenia.setPosition(1680.0f, 827.0f);

    //OKNO GŁÓWNE
    sf::Text wyborCzynnosci(L"WYBIERZ, CO CHCESZ ZROBIĆ:", font, 30);
    wyborCzynnosci.setFillColor(sf::Color::Black);
    wyborCzynnosci.setPosition(750.f, 50.f);

    sf::RectangleShape czynnosc(sf::Vector2f(600.0f, 80.0f));
    czynnosc.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    czynnosc.setPosition(250.0f, 300.0f);

    sf::RectangleShape czynnosc1(sf::Vector2f(600.0f, 80.0f));
    czynnosc1.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    czynnosc1.setPosition(250.0f, 500.0f);

    sf::RectangleShape czynnosc2(sf::Vector2f(600.0f, 80.0f));
    czynnosc2.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    czynnosc2.setPosition(1050.0f, 300.0f);

    sf::RectangleShape czynnosc3(sf::Vector2f(600.0f, 80.0f));
    czynnosc3.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    czynnosc3.setPosition(1050.0f, 500.0f);

    sf::RectangleShape czynnosc4(sf::Vector2f(800.0f, 80.0f));
    czynnosc4.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    czynnosc4.setPosition(550.0f, 800.0f);


    sf::Text wyborWejscia(L"wybierz sygnał wejściowy", font, 30);
    wyborWejscia.setFillColor(sf::Color::Black);
    wyborWejscia.setPosition(370.f, 320.f);


    sf::Text transmitancjaObiektu(L"podaj parametry transmitancji obiektu", font, 30);
    transmitancjaObiektu.setFillColor(sf::Color::Black);
    transmitancjaObiektu.setPosition(300.f, 520.f);

    sf::Text transmitancjaLead("podaj parametry sterownika LEAD", font, 30);
    transmitancjaLead.setFillColor(sf::Color::Black);
    transmitancjaLead.setPosition(1125.f, 320.f);

    sf::Text transmitancjaLag("podaj parametry sterownika LAG", font, 30);
    transmitancjaLag.setFillColor(sf::Color::Black);
    transmitancjaLag.setPosition(1125.f, 520.f);

    sf::Text zakoncz(L"zakończ i wyświetl wykresy", font, 30);
    zakoncz.setFillColor(sf::Color::Black);
    zakoncz.setPosition(750.f, 820.f);

    sf::RectangleShape button1(sf::Vector2f(10.f, 10.f));
    button1.setFillColor(sf::Color::White);
    button1.setOutlineColor(sf::Color::Black);
    button1.setOutlineThickness(2);
    button1.setPosition(150.f, 215.f);

    //KONIEC OKNA GŁÓWNEGO

    //WPROWADZANIE PARAMETRÓW OBIEKTU

    sf::Text wstepObiekt(L"PODAJ TRANSMITANCJĘ OBIEKTU: ", font, 30.f);
    wstepObiekt.setFillColor(sf::Color::Black);
    wstepObiekt.setPosition(720.f, 50.f);

    sf::RectangleShape kreskaUlamkowa(sf::Vector2f(770.f, 3.f));
    kreskaUlamkowa.setFillColor(sf::Color::Black);
    kreskaUlamkowa.setPosition(650.f, 500.f);

    sf::Text wstep("G(S) = ", font, 40.f);
    wstep.setFillColor(sf::Color::Black);
    wstep.setPosition(500.f, 475.f);


    sf::RectangleShape miejsceNaA1(sf::Vector2f(150.f, 60.f));
    miejsceNaA1.setFillColor(sf::Color::White);
    miejsceNaA1.setOutlineThickness(1.f);
    miejsceNaA1.setOutlineColor(sf::Color::Black);
    miejsceNaA1.setPosition(815.f, 435.f);

    sf::Text wprowadzanieA1("", font, 40);
    wprowadzanieA1.setFillColor(sf::Color::Black);
    wprowadzanieA1.setPosition(miejsceNaA1.getPosition().x + 10, miejsceNaA1.getPosition().y + 5);


    sf::Text s1("*s   + ", font, 40.f);
    s1.setFillColor(sf::Color::Black);
    s1.setPosition(980.f, 440.f);

    sf::RectangleShape miejsceNaA0(sf::Vector2f(150.f, 60.f));
    miejsceNaA0.setFillColor(sf::Color::White);
    miejsceNaA0.setOutlineThickness(1.f);
    miejsceNaA0.setOutlineColor(sf::Color::Black);
    miejsceNaA0.setPosition(1105.f, 435.f);

    sf::Text wprowadzanieA0("", font, 40);
    wprowadzanieA0.setFillColor(sf::Color::Black);
    wprowadzanieA0.setPosition(miejsceNaA0.getPosition().x + 10, miejsceNaA0.getPosition().y + 5);

    sf::RectangleShape miejsceNaB2(sf::Vector2f(150.f, 60.f));
    miejsceNaB2.setFillColor(sf::Color::White);
    miejsceNaB2.setOutlineThickness(1.f);
    miejsceNaB2.setOutlineColor(sf::Color::Black);
    miejsceNaB2.setPosition(670.f, 508.f);

    sf::Text wprowadzanieB2("", font, 40);
    wprowadzanieB2.setFillColor(sf::Color::Black);
    wprowadzanieB2.setPosition(miejsceNaB2.getPosition().x + 10, miejsceNaB2.getPosition().y + 5);

    sf::Text s2("*s   +", font, 40.f);
    s2.setFillColor(sf::Color::Black);
    s2.setPosition(835.f, 515.f);

    sf::Text potega("2", font, 20.f);
    potega.setFillColor(sf::Color::Black);
    potega.setPosition(868.f, 510.f);

    sf::RectangleShape miejsceNaB1(sf::Vector2f(150.f, 60.f));
    miejsceNaB1.setFillColor(sf::Color::White);
    miejsceNaB1.setOutlineThickness(1.f);
    miejsceNaB1.setOutlineColor(sf::Color::Black);
    miejsceNaB1.setPosition(960.f, 508.f);

    sf::Text wprowadzanieB1("", font, 40);
    wprowadzanieB1.setFillColor(sf::Color::Black);
    wprowadzanieB1.setPosition(miejsceNaB1.getPosition().x + 10, miejsceNaB1.getPosition().y + 5);

    sf::Text s3("*s   +", font, 40.f);
    s3.setFillColor(sf::Color::Black);
    s3.setPosition(1125.f, 515.f);

    sf::RectangleShape miejsceNaB0(sf::Vector2f(150.f, 60.f));
    miejsceNaB0.setFillColor(sf::Color::White);
    miejsceNaB0.setOutlineThickness(1.f);
    miejsceNaB0.setOutlineColor(sf::Color::Black);
    miejsceNaB0.setPosition(1250.f, 508.f);

    sf::Text wprowadzanieB0("", font, 40);
    wprowadzanieB0.setFillColor(sf::Color::Black);
    wprowadzanieB0.setPosition(miejsceNaB0.getPosition().x + 10, miejsceNaB0.getPosition().y + 5);


    std::string podajA1;
    std::string podajA0;
    std::string podajB2;
    std::string podajB1;
    std::string podajB0;

    bool inputA1Active = false;
    bool inputA0Active = false;
    bool inputB2Active = false;
    bool inputB1Active = false;
    bool inputB0Active = false;

    //KONIEC WPROWADZANIA PARAMETRÓW OBIEKTU


    //WPROWADZANIE PARAMETRÓW LEADA

    sf::Text wstepLead(L"PODAJ TRANSMITANCJĘ STEROWNIKA LEAD: ", font, 30.f);
    wstepLead.setFillColor(sf::Color::Black);
    wstepLead.setPosition(610.f, 50.f);

    sf::RectangleShape kreskaUlamkowa1(sf::Vector2f(345.f, 3.f));
    kreskaUlamkowa1.setFillColor(sf::Color::Black);
    kreskaUlamkowa1.setPosition(920.f, 500.f);

    sf::Text wstep1("G(S) = ", font, 40.f);
    wstep1.setFillColor(sf::Color::Black);
    wstep1.setPosition(600.f, 475.f);

    sf::RectangleShape miejsceNaK1(sf::Vector2f(150.f, 60.f));
    miejsceNaK1.setFillColor(sf::Color::White);
    miejsceNaK1.setOutlineThickness(1.f);
    miejsceNaK1.setOutlineColor(sf::Color::Black);
    miejsceNaK1.setPosition(745.f, 470.f);

    sf::Text wprowadzanieK1("", font, 40);
    wprowadzanieK1.setFillColor(sf::Color::Black);
    wprowadzanieK1.setPosition(miejsceNaK1.getPosition().x + 10, miejsceNaK1.getPosition().y + 5);

    sf::Text s4("(s   -", font, 40.f);
    s4.setFillColor(sf::Color::Black);
    s4.setPosition(940.f, 440.f);

    sf::RectangleShape miejsceNaZ1(sf::Vector2f(150.f, 60.f));
    miejsceNaZ1.setFillColor(sf::Color::White);
    miejsceNaZ1.setOutlineThickness(1.f);
    miejsceNaZ1.setOutlineColor(sf::Color::Black);
    miejsceNaZ1.setPosition(1065.f, 435.f);

    sf::Text wprowadzanieZ1("", font, 40);
    wprowadzanieZ1.setFillColor(sf::Color::Black);
    wprowadzanieZ1.setPosition(miejsceNaZ1.getPosition().x + 10, miejsceNaZ1.getPosition().y + 5);

    sf::Text nawias1(")", font, 40.f);
    nawias1.setFillColor(sf::Color::Black);
    nawias1.setPosition(1225.f, 440.f);

    sf::Text s5("(s   -", font, 40.f);
    s5.setFillColor(sf::Color::Black);
    s5.setPosition(940.f, 515.f);

    sf::RectangleShape miejsceNaP1(sf::Vector2f(150.f, 60.f));
    miejsceNaP1.setFillColor(sf::Color::White);
    miejsceNaP1.setOutlineThickness(1.f);
    miejsceNaP1.setOutlineColor(sf::Color::Black);
    miejsceNaP1.setPosition(1065.f, 508.f);

    sf::Text wprowadzanieP1("", font, 40);
    wprowadzanieP1.setFillColor(sf::Color::Black);
    wprowadzanieP1.setPosition(miejsceNaP1.getPosition().x + 10, miejsceNaP1.getPosition().y + 5);


    sf::Text nawias2(")", font, 40.f);
    nawias2.setFillColor(sf::Color::Black);
    nawias2.setPosition(1225.f, 515.f);

    sf::Text  mnozenie("*", font, 40.f);
    mnozenie.setFillColor(sf::Color::Black);
    mnozenie.setPosition(900.f, 483.f);

    std::string podajK1;
    std::string podajZ1;
    std::string podajP1;
    bool inputK1Active = false;
    bool inputZ1Active = false;
    bool inputP1Active = false;

    //KONIEC WPROWADZANIA PARAMETRÓW LEADA

    //WPROWADZANIE PARAMETRÓW LAGA

    sf::Text wstepLag(L"PODAJ TRANSMITANCJĘ STEROWNIKA LAG: ", font, 30.f);
    wstepLag.setFillColor(sf::Color::Black);
    wstepLag.setPosition(610.f, 50.f);

    sf::RectangleShape miejsceNaK2(sf::Vector2f(150.f, 60.f));
    miejsceNaK2.setFillColor(sf::Color::White);
    miejsceNaK2.setOutlineThickness(1.f);
    miejsceNaK2.setOutlineColor(sf::Color::Black);
    miejsceNaK2.setPosition(745.f, 470.f);

    sf::Text wprowadzanieK2("", font, 40);
    wprowadzanieK2.setFillColor(sf::Color::Black);
    wprowadzanieK2.setPosition(miejsceNaK2.getPosition().x + 10, miejsceNaK2.getPosition().y + 5);

    sf::RectangleShape miejsceNaZ2(sf::Vector2f(150.f, 60.f));
    miejsceNaZ2.setFillColor(sf::Color::White);
    miejsceNaZ2.setOutlineThickness(1.f);
    miejsceNaZ2.setOutlineColor(sf::Color::Black);
    miejsceNaZ2.setPosition(1065.f, 435.f);

    sf::Text wprowadzanieZ2("", font, 40);
    wprowadzanieZ2.setFillColor(sf::Color::Black);
    wprowadzanieZ2.setPosition(miejsceNaZ2.getPosition().x + 10, miejsceNaZ2.getPosition().y + 5);

    sf::RectangleShape miejsceNaP2(sf::Vector2f(150.f, 60.f));
    miejsceNaP2.setFillColor(sf::Color::White);
    miejsceNaP2.setOutlineThickness(1.f);
    miejsceNaP2.setOutlineColor(sf::Color::Black);
    miejsceNaP2.setPosition(1065.f, 508.f);

    sf::Text wprowadzanieP2("", font, 40);
    wprowadzanieP2.setFillColor(sf::Color::Black);
    wprowadzanieP2.setPosition(miejsceNaP2.getPosition().x + 10, miejsceNaP2.getPosition().y + 5);

    std::string podajK2;
    std::string podajZ2;
    std::string podajP2;
    bool inputK2Active = false;
    bool inputZ2Active = false;
    bool inputP2Active = false;

    //KONIEC WPROWADZANIA PARAMETRÓW LAGA

    //WYBÓR SYGNAŁU WEJŚCIOWEGO
    sf::Text rodzajWejscia(L"WYBIERZ SYGNAŁ WEJŚCIOWY:", font, 30);
    rodzajWejscia.setFillColor(sf::Color::Black);
    rodzajWejscia.setPosition(720.f, 50.f);

    sf::Text harmoniczny(L"sygnał harmoniczny", font, 30);
    harmoniczny.setFillColor(sf::Color::Black);
    harmoniczny.setPosition(820.f, 300.f);

    sf::Text prostokatny(L"sygnał prostokątny", font, 30);
    prostokatny.setFillColor(sf::Color::Black);
    prostokatny.setPosition(820.f, 450.f);

    sf::Text trojkatny(L"sygnał trójkątny", font, 30);
    trojkatny.setFillColor(sf::Color::Black);
    trojkatny.setPosition(835.f, 600.f);


    sf::RectangleShape sygnal1(sf::Vector2f(600.0f, 80.0f));
    sygnal1.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    sygnal1.setPosition(645.0f, 280.0f);

    sf::RectangleShape sygnal2(sf::Vector2f(600.0f, 80.0f));
    sygnal2.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    sygnal2.setPosition(645.0f, 430.0f);

    sf::RectangleShape sygnal3(sf::Vector2f(600.0f, 80.0f));
    sygnal3.setFillColor(sf::Color(211, 211, 211)); // Szary kolor
    sygnal3.setPosition(645.0f, 580.0f);

    //KONIEC WYBORU WEJŚCIA

    //PARAMETRY SYGNAŁU HARMONICZNEGO

    sf::Text parametryHarmoniczny(L"PODAJ WARTOŚCI PARAMETRÓW SYGNAŁU WEJŚCIOWEGO:", font, 30);
    parametryHarmoniczny.setFillColor(sf::Color::Black);
    parametryHarmoniczny.setPosition(470.f, 300.f);

    sf::Text harmonicznyAmplituda("AMPLITUDA:", font, 30);
    harmonicznyAmplituda.setFillColor(sf::Color::Black);
    harmonicznyAmplituda.setPosition(750.f, 400.f);

    sf::Text harmonicznyCzestotliwosc(L"CZĘSTOTLIWOŚĆ:", font, 30);
    harmonicznyCzestotliwosc.setFillColor(sf::Color::Black);
    harmonicznyCzestotliwosc.setPosition(710.f, 500.f);

    sf::RectangleShape miejsceNaAmplitudeH(sf::Vector2f(150.f, 60.f));
    miejsceNaAmplitudeH.setFillColor(sf::Color::White);
    miejsceNaAmplitudeH.setOutlineThickness(1.f);
    miejsceNaAmplitudeH.setOutlineColor(sf::Color::Black);
    miejsceNaAmplitudeH.setPosition(945.f, 390.f);

    sf::Text wprowadzanieAmplitudyH("", font, 40);
    wprowadzanieAmplitudyH.setFillColor(sf::Color::Black);
    wprowadzanieAmplitudyH.setPosition(miejsceNaAmplitudeH.getPosition().x + 10, miejsceNaAmplitudeH.getPosition().y + 5);

    sf::RectangleShape miejsceNaCzestotliwoscH(sf::Vector2f(150.f, 60.f));
    miejsceNaCzestotliwoscH.setFillColor(sf::Color::White);
    miejsceNaCzestotliwoscH.setOutlineThickness(1.f);
    miejsceNaCzestotliwoscH.setOutlineColor(sf::Color::Black);
    miejsceNaCzestotliwoscH.setPosition(995.f, 490.f);

    sf::Text wprowadzanieCzestotliwosciH("", font, 40);
    wprowadzanieCzestotliwosciH.setFillColor(sf::Color::Black);
    wprowadzanieCzestotliwosciH.setPosition(miejsceNaCzestotliwoscH.getPosition().x + 10, miejsceNaCzestotliwoscH.getPosition().y + 5);

    std::string podajAmplitudeH;
    std::string podajCzestotliwoscH;
    bool AmplitudaHActive = false;
    bool CzestotliwoscHActive = false;


    //AKTYWNE OKNA
    bool isCzynnoscActive = true;
    bool isObiektActive = false;
    bool isLeadActive = false;
    bool isLagActive = false;
    bool isWejscieActive = false;
    bool isHarmonicznyActive = false;



    std::string inputValue;

    // Flaga do sprawdzenia, czy przycisk został utworzony
    bool buttonCreated = false;

    // Główna pętla programu
    while (window.isOpen())
    {
        // Przetwarzanie zdarzeń
        sf::Event event;
        while (window.pollEvent(event))
        {

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            // Zamknięcie okna: wyjście
            if (event.type == sf::Event::Closed)
                window.close();


            if (isCzynnoscActive)
            {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (wyborWejscia.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        isCzynnoscActive = false;
                        isWejscieActive = true;
                    }
                    else if (transmitancjaObiektu.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        isCzynnoscActive = false;
                        isObiektActive = true;
                    }
                    else if (transmitancjaLead.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        isCzynnoscActive = false;
                        isLeadActive = true;
                    }
                    else if (transmitancjaLag.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        isCzynnoscActive = false;
                        isLagActive = true;
                    }
                    else if (przyciskWychodzenia.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        *wyswietlWykresy = false;
                    }
                }

                if (czynnosc.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && (podajAmplitudeH.empty() || podajCzestotliwoscH.empty())) {
                    czynnosc.setFillColor(sf::Color(144, 238, 144));
                }
                else if (czynnosc.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !podajAmplitudeH.empty() && !podajCzestotliwoscH.empty())
                    czynnosc.setFillColor(sf::Color(211, 211, 211));
                else if (!podajAmplitudeH.empty() && !podajCzestotliwoscH.empty())
                    czynnosc.setFillColor(sf::Color(144, 238, 144));
                else {
                    czynnosc.setFillColor(sf::Color(211, 211, 211));
                }

                if (czynnosc1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && (podajA1.empty() || podajB2.empty() || podajB1.empty() || podajB0.empty() || podajA0.empty())) {
                    czynnosc1.setFillColor(sf::Color(144, 238, 144));
                }
                else if (czynnosc1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !podajA1.empty() && !podajA0.empty() && !podajB2.empty() && !podajB1.empty() && !podajB0.empty())
                    czynnosc1.setFillColor(sf::Color(211, 211, 211));
                else if (!podajA1.empty() && !podajA0.empty() && !podajB2.empty() && !podajB1.empty() && !podajB0.empty())
                    czynnosc1.setFillColor(sf::Color(144, 238, 144));
                else {
                    czynnosc1.setFillColor(sf::Color(211, 211, 211));
                }

                if (czynnosc2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && (podajK1.empty() || podajP1.empty() || podajZ1.empty())) {
                    czynnosc2.setFillColor(sf::Color(144, 238, 144));
                }
                else if (czynnosc2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !podajK1.empty() && !podajP1.empty() && !podajZ1.empty())
                    czynnosc2.setFillColor(sf::Color(211, 211, 211));
                else if (!podajK1.empty() && !podajP1.empty() && !podajZ1.empty())
                    czynnosc2.setFillColor(sf::Color(144, 238, 144));
                else {
                    czynnosc2.setFillColor(sf::Color(211, 211, 211));
                }

                if (czynnosc3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && (podajK2.empty() || podajP2.empty() || podajZ2.empty()))
                    {
                    czynnosc3.setFillColor(sf::Color(144, 238, 144));
                }
                else if (czynnosc3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !podajK2.empty() && !podajP2.empty() && !podajZ2.empty())
                    czynnosc3.setFillColor(sf::Color(211, 211, 211));
                else if (!podajK2.empty() && !podajP2.empty() && !podajZ2.empty())
                    czynnosc3.setFillColor(sf::Color(144, 238, 144));
                else {
                    czynnosc3.setFillColor(sf::Color(211, 211, 211));
                }

                if (czynnosc4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !podajAmplitudeH.empty() && !podajCzestotliwoscH.empty() && !podajA1.empty() && !podajA0.empty() && !podajB2.empty() && !podajB1.empty() && !podajB0.empty() && !podajK1.empty() && !podajK2.empty() && !podajZ1.empty() && !podajZ2.empty() && !podajP1.empty() && !podajP2.empty()) {
                    czynnosc4.setFillColor(sf::Color(144, 238, 144));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        window.close();
                    }
                }
                else if (czynnosc4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    czynnosc4.setFillColor(sf::Color(255, 110, 110));
                else {
                    czynnosc4.setFillColor(sf::Color(211, 211, 211));
                }

                if (przyciskWychodzenia.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    przyciskWychodzenia.setFillColor(sf::Color(144, 238, 144));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        *wyswietlWykresy = false;
                        window.close();
                        *zamknij = true;
                    }
                }
                else {
                    przyciskWychodzenia.setFillColor(sf::Color(211, 211, 211));
                }
            }

            if (isObiektActive)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (miejsceNaA1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputA1Active = true;
                        inputA0Active = false;
                        inputB2Active = false;
                        inputB1Active = false;
                        inputB0Active = false;
                        miejsceNaA1.setOutlineThickness(2.f);
                        miejsceNaA0.setOutlineThickness(1.f);
                        miejsceNaB2.setOutlineThickness(1.f);
                        miejsceNaB1.setOutlineThickness(1.f);
                        miejsceNaB0.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaA0.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputA1Active = false;
                        inputA0Active = true;
                        inputB2Active = false;
                        inputB1Active = false;
                        inputB0Active = false;
                        miejsceNaA1.setOutlineThickness(1.f);
                        miejsceNaA0.setOutlineThickness(2.f);
                        miejsceNaB2.setOutlineThickness(1.f);
                        miejsceNaB1.setOutlineThickness(1.f);
                        miejsceNaB0.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaB2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputA1Active = false;
                        inputA0Active = false;
                        inputB2Active = true;
                        inputB1Active = false;
                        inputB0Active = false;
                        miejsceNaA1.setOutlineThickness(1.f);
                        miejsceNaA0.setOutlineThickness(1.f);
                        miejsceNaB2.setOutlineThickness(2.f);
                        miejsceNaB1.setOutlineThickness(1.f);
                        miejsceNaB0.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaB1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputA1Active = false;
                        inputA0Active = false;
                        inputB2Active = false;
                        inputB1Active = true;
                        inputB0Active = false;
                        miejsceNaA1.setOutlineThickness(1.f);
                        miejsceNaA0.setOutlineThickness(1.f);
                        miejsceNaB2.setOutlineThickness(1.f);
                        miejsceNaB1.setOutlineThickness(2.f);
                        miejsceNaB0.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaB0.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputA1Active = false;
                        inputA0Active = false;
                        inputB2Active = false;
                        inputB1Active = false;
                        inputB0Active = true;
                        miejsceNaA1.setOutlineThickness(1.f);
                        miejsceNaA0.setOutlineThickness(1.f);
                        miejsceNaB2.setOutlineThickness(1.f);
                        miejsceNaB1.setOutlineThickness(1.f);
                        miejsceNaB0.setOutlineThickness(2.f);
                    }
                    else if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        isObiektActive = false;
                        isCzynnoscActive = true;
                        if (!podajA1.empty())
                        {
                            *a1 = std::stod(podajA1);
                        }
                        if (!podajA0.empty())
                        {
                            *a0 = std::stod(podajA0);
                        }
                        if (!podajB2.empty())
                        {
                            *b2 = std::stod(podajB2);
                        }
                        if (!podajB1.empty())
                        {
                            *b1 = std::stod(podajB1);
                        }
                        if (!podajB0.empty())
                        {
                            *b0 = std::stod(podajB0);
                        }
                    }
                }

                if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    przyciskZatwierdzania.setFillColor(sf::Color(144, 238, 144));
                }
                else {
                    przyciskZatwierdzania.setFillColor(sf::Color(211, 211, 211));
                }

                if (inputA1Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajA1.empty()) {
                            podajA1.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajA1 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieA1.setString(podajA1);
                }

                if (inputA0Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajA0.empty()) {
                            podajA0.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajA0 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieA0.setString(podajA0);
                }

                if (inputB2Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajB2.empty()) {
                            podajB2.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajB2 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieB2.setString(podajB2);
                }

                if (inputB1Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajB1.empty()) {
                            podajB1.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajB1 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieB1.setString(podajB1);
                }

                if (inputB0Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajB0.empty()) {
                            podajB0.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajB0 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieB0.setString(podajB0);
                }
            }

            if (isLeadActive)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (miejsceNaK1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputK1Active = true;
                        inputZ1Active = false;
                        inputP1Active = false;
                        miejsceNaK1.setOutlineThickness(2.f);
                        miejsceNaZ1.setOutlineThickness(1.f);
                        miejsceNaP1.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaZ1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputK1Active = false;
                        inputZ1Active = true;
                        inputP1Active = false;
                        miejsceNaK1.setOutlineThickness(1.f);
                        miejsceNaZ1.setOutlineThickness(2.f);
                        miejsceNaP1.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaP1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputK1Active = false;
                        inputZ1Active = false;
                        inputP1Active = true;
                        miejsceNaK1.setOutlineThickness(1.f);
                        miejsceNaZ1.setOutlineThickness(1.f);
                        miejsceNaP1.setOutlineThickness(2.f);
                    }
                    else if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        isLeadActive = false;
                        isCzynnoscActive = true;
                        if (!podajK1.empty())
                        {
                            *k1 = std::stod(podajK1);
                        }
                        if (!podajP1.empty())
                        {
                            *p1 = std::stod(podajP1);
                        }
                        if (!podajZ1.empty())
                        {
                            *z1 = std::stod(podajZ1);
                        }
                    }
                }

                if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    przyciskZatwierdzania.setFillColor(sf::Color(144, 238, 144));
                }
                else {
                    przyciskZatwierdzania.setFillColor(sf::Color(211, 211, 211));
                }

                if (inputK1Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajK1.empty()) {
                            podajK1.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajK1 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieK1.setString(podajK1);
                }

                if (inputZ1Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajZ1.empty()) {
                            podajZ1.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajZ1 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieZ1.setString(podajZ1);
                }

                if (inputP1Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajP1.empty()) {
                            podajP1.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajP1 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieP1.setString(podajP1);
                }
            }

            if (isLagActive)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (miejsceNaK2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputK2Active = true;
                        inputZ2Active = false;
                        inputP2Active = false;
                        miejsceNaK2.setOutlineThickness(2.f);
                        miejsceNaZ2.setOutlineThickness(1.f);
                        miejsceNaP2.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaZ2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputK2Active = false;
                        inputZ2Active = true;
                        inputP2Active = false;
                        miejsceNaK2.setOutlineThickness(1.f);
                        miejsceNaZ2.setOutlineThickness(2.f);
                        miejsceNaP2.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaP2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        inputK2Active = false;
                        inputZ2Active = false;
                        inputP2Active = true;
                        miejsceNaK2.setOutlineThickness(1.f);
                        miejsceNaZ2.setOutlineThickness(1.f);
                        miejsceNaP2.setOutlineThickness(2.f);
                    }
                    else if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        isLagActive = false;
                        isCzynnoscActive = true;
                        if (!podajK2.empty())
                        {
                            *k2 = std::stod(podajK2);
                        }
                        if (!podajP2.empty())
                        {
                            *p2 = std::stod(podajP2);
                        }
                        if (!podajZ2.empty())
                        {
                            *z2 = std::stod(podajZ2);
                        }
                    }
                }

                if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    przyciskZatwierdzania.setFillColor(sf::Color(144, 238, 144));
                }
                else {
                    przyciskZatwierdzania.setFillColor(sf::Color(211, 211, 211));
                }

                if (inputK2Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajK2.empty()) {
                            podajK2.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajK2 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieK2.setString(podajK2);
                }

                if (inputZ2Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajZ2.empty()) {
                            podajZ2.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajZ2 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieZ2.setString(podajZ2);
                }

                if (inputP2Active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajP2.empty()) {
                            podajP2.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajP2 += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieP2.setString(podajP2);
                }
            }

            // Obsługa zatwierdzenia wprowadzonej wartości enterem
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                // Przekonwertuj wartość na int
                int intValue = std::stoi(inputValue);

                // Utwórz przycisk z wartością
                sf::RectangleShape button(sf::Vector2f(150.f, 50.f));
                button.setFillColor(sf::Color::Green);
                button.setPosition(50.f, 150.f);

                sf::Text buttonText(inputValue, font, intValue);
                buttonText.setFillColor(sf::Color::Black);
                buttonText.setPosition(50.f, 150.f);

                // Rysuj przycisk z wartością
                window.draw(button);
                window.draw(buttonText);

                // Wyświetl okno z przyciskiem
                window.display();

                // Zatrzymaj działanie programu na 5 sekund
                sf::sleep(sf::seconds(5));

                // Gdy wartość zostanie zatwierdzona, wyczyść pole tekstowe
                inputValue.clear();
                inputText.setString(inputValue);

                // Ustaw flagę, że przycisk został utworzony
                buttonCreated = true;
            }


            if (isWejscieActive)
            {
                if (sygnal1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    sygnal1.setFillColor(sf::Color(144, 238, 144));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        isWejscieActive = false;
                        isHarmonicznyActive = true;
                        *harmonicImput = true;
                    }
                }
                else {
                    sygnal1.setFillColor(sf::Color(211, 211, 211));
                }

                if (sygnal2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    sygnal2.setFillColor(sf::Color(144, 238, 144));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        *harmonicImput = false;
                        *rectangularImput = true;
                        isWejscieActive = false;
                        isHarmonicznyActive = true;
                    }
                }
                else {
                    sygnal2.setFillColor(sf::Color(211, 211, 211));
                }

                if (sygnal3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    sygnal3.setFillColor(sf::Color(144, 238, 144));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        *harmonicImput = false;
                        *rectangularImput = false;
                        *triangularImput = true;
                        isWejscieActive = false;
                        isHarmonicznyActive = true;
                    }
                }
                else {
                    sygnal3.setFillColor(sf::Color(211, 211, 211));
                }

                if (przyciskCofania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    przyciskCofania.setFillColor(sf::Color(144, 238, 144));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        isWejscieActive = false;
                        isCzynnoscActive = true;
                    }
                }
                else {
                    przyciskCofania.setFillColor(sf::Color(211, 211, 211));
                }
            }

            if (isHarmonicznyActive)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (miejsceNaAmplitudeH.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        AmplitudaHActive = true;
                        CzestotliwoscHActive = false;
                        miejsceNaAmplitudeH.setOutlineThickness(2.f);
                        miejsceNaCzestotliwoscH.setOutlineThickness(1.f);
                    }
                    else if (miejsceNaCzestotliwoscH.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        AmplitudaHActive = false;
                        CzestotliwoscHActive = true;
                        miejsceNaAmplitudeH.setOutlineThickness(1.f);
                        miejsceNaCzestotliwoscH.setOutlineThickness(2.f);
                    }
                    else if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        isHarmonicznyActive = false;
                        isCzynnoscActive = true;
                        AmplitudaHActive = false;
                        CzestotliwoscHActive = false;
                    }
                }

                if (przyciskZatwierdzania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    przyciskZatwierdzania.setFillColor(sf::Color(144, 238, 144));
                }
                else {
                    przyciskZatwierdzania.setFillColor(sf::Color(211, 211, 211));
                    if (!podajAmplitudeH.empty())
                    {
                        *m = std::stod(podajAmplitudeH);
                    }
                    if (!podajCzestotliwoscH.empty())
                    {
                        *ff = std::stod(podajCzestotliwoscH);
                    }
                }

                if (AmplitudaHActive && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajAmplitudeH.empty()) {
                            podajAmplitudeH.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajAmplitudeH += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieAmplitudyH.setString(podajAmplitudeH);
                }

                if (CzestotliwoscHActive && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!podajCzestotliwoscH.empty()) {
                            podajCzestotliwoscH.pop_back(); // Usuń ostatni znak w przypadku naciśnięcia Backspace
                        }
                    }
                    else if (event.text.unicode == '1' || event.text.unicode == '2' || event.text.unicode == '3' || event.text.unicode == '4' || event.text.unicode == '5' || event.text.unicode == '6' || event.text.unicode == '7' || event.text.unicode == '8' || event.text.unicode == '9' || event.text.unicode == '0' || event.text.unicode == '.') {
                        podajCzestotliwoscH += static_cast<char>(event.text.unicode); // Dodaj nowy znak
                    }
                    wprowadzanieCzestotliwosciH.setString(podajCzestotliwoscH);
                }
            }

        }

        // Czyszczenie ekranu
        window.clear(sf::Color::White);

        // Rysuj pole tekstowe

        if (isCzynnoscActive)
        {
            window.draw(inputText);
            window.draw(czynnosc);
            window.draw(czynnosc1);
            window.draw(czynnosc2);
            window.draw(czynnosc3);
            window.draw(wyborCzynnosci);
            window.draw(wyborWejscia);
            window.draw(transmitancjaObiektu);
            window.draw(transmitancjaLead);
            window.draw(transmitancjaLag);
            window.draw(czynnosc4);
            window.draw(zakoncz);
            window.draw(przyciskWychodzenia);
            window.draw(wychodzenie);
        }
        else if (isObiektActive)
        {
            window.draw(kreskaUlamkowa);
            window.draw(wstep);
            window.draw(miejsceNaA1);
            window.draw(s1);
            window.draw(miejsceNaA0);
            window.draw(miejsceNaB2);
            window.draw(s2);
            window.draw(potega);
            window.draw(miejsceNaB1);
            window.draw(s3);
            window.draw(miejsceNaB0);
            window.draw(wstepObiekt);
            window.draw(wprowadzanieA1);
            window.draw(wprowadzanieA0);
            window.draw(wprowadzanieB2);
            window.draw(wprowadzanieB1);
            window.draw(wprowadzanieB0);
            window.draw(przyciskZatwierdzania);
            window.draw(zatwierdzanie);
        }
        else if (isLeadActive)
        {
            window.draw(wstepLead);
            window.draw(kreskaUlamkowa1);
            window.draw(miejsceNaK1);
            window.draw(wstep1);
            window.draw(s4);
            window.draw(miejsceNaZ1);
            window.draw(nawias1);
            window.draw(s5);
            window.draw(miejsceNaP1);
            window.draw(nawias2);
            window.draw(mnozenie);
            window.draw(wprowadzanieK1);
            window.draw(wprowadzanieZ1);
            window.draw(wprowadzanieP1);
            window.draw(przyciskZatwierdzania);
            window.draw(zatwierdzanie);
        }
        else if (isLagActive)
        {
            window.draw(wstepLag);
            window.draw(kreskaUlamkowa1);
            window.draw(miejsceNaK2);
            window.draw(wstep1);
            window.draw(s4);
            window.draw(miejsceNaZ2);
            window.draw(nawias1);
            window.draw(s5);
            window.draw(miejsceNaP2);
            window.draw(nawias2);
            window.draw(mnozenie);
            window.draw(wprowadzanieK2);
            window.draw(wprowadzanieZ2);
            window.draw(wprowadzanieP2);
            window.draw(przyciskZatwierdzania);
            window.draw(zatwierdzanie);
        }
        else if (isWejscieActive)
        {
            window.draw(rodzajWejscia);
            window.draw(sygnal1);
            window.draw(sygnal2);
            window.draw(sygnal3);
            window.draw(harmoniczny);
            window.draw(trojkatny);
            window.draw(prostokatny);
            window.draw(przyciskCofania);
            window.draw(cofanie);
        }
        else if (isHarmonicznyActive)
        {
            window.draw(parametryHarmoniczny);
            window.draw(harmonicznyAmplituda);
            window.draw(harmonicznyCzestotliwosc);
            window.draw(miejsceNaAmplitudeH);
            window.draw(wprowadzanieAmplitudyH);
            window.draw(miejsceNaCzestotliwoscH);
            window.draw(wprowadzanieCzestotliwosciH);
            window.draw(przyciskZatwierdzania);
            window.draw(zatwierdzanie);
        }



        //window.draw(button1);

        // Aktualizacja okna
        window.display();
    }
}

void calculations(double* a1, double* a0, double* b2, double* b1, double* b0, double* k1, double* z1, double* p1, double* k2, double* z2, double* p2, double* aa0, double* aa1, double* aa2, double* aa3, double* bb0, double* bb1, double* bb2, double* bb3)
{
    *aa0 = ((*b0) * (*p1) * (*p2) + (*k1) * (*k2) * (*a0) * (*z1) * (*z2)) / (*b2);
    *aa1 = (-(*b0) * (*p1) - (*b0) * (*p2) + (*b1) * (*p1) * (*p2) - (*k1) * (*k2) * (*a0) * (*z1) - (*k1) * (*k2) * (*a0) * (*z2) + (*k1) * (*k2) * (*a1) * (*z1) * (*z2)) / (*b2);
    *aa2 = ((*b0) - (*b1) * (*p1) - (*b1) * (*p2) + (*p1) * (*p2) * (*b2) + (*k1) * (*k2) * (*a0) - (*k1) * (*k2) * (*a1) * (*z1) - (*k1) * (*k2) * (*a1) * (*z2)) / (*b2);
    *aa3 = ((*b1) - (*b2) * (*p1) - (*b2) * (*p2) + (*k1) * (*k2) * (*a1)) / (*b2);

    *bb0 = ((*k1) * (*k2) * (*a0) * (*z1) * (*z2)) / (*b2);
    *bb1 = (-(*k1) * (*k2) * (*a0) * (*z1) - (*k1) * (*k2) * (*a0) * (*z2) + (*k1) * (*k2) * (*a1) * (*z1) * (*z2)) / (*b2);
    *bb2 = ((*k1) * (*k2) * (*a0) - (*k1) * (*k2) * (*a1) * (*z1) - (*k1) * (*k2) * (*a1) * (*z2)) / (*b2);
    *bb3 = ((*k1) * (*k2) * (*a1)) / (*b2);

}

int main() {
    int i, total;
    double aa33, aa22, aa11, aa00, bb33, bb22, bb11, bb00, w;
    Matr A;
    Vect B, C, Ax, Bu, xi, xi_1;
    double D, Cx, Du;

    double a11, a00, b22, b11, b00, k11, z11, p11, k22, z22, p22;
    double M;
    double f;

    bool wyswietlaj = true;
    bool koniec = false;

    bool wejscieSinus = false;
    bool wejscieProstokat = false;
    bool wejscieTrojkat = false;

    while (!koniec)
    {
        Grafika(&a11, &a00, &b22, &b11, &b00, &k11, &z11, &p11, &k22, &z22, &p22, &M, &f, &wyswietlaj, &koniec, &wejscieSinus, &wejscieProstokat, &wejscieTrojkat );

        std::cout << "czestotliwosc = " << f << std::endl;
        std::cout << "a0 = " << a00 << std::endl;
        std::cout << "b2 = " << b22 << std::endl;
        std::cout << "b1 = " << b11 << std::endl;
        std::cout << "b0 = " << b00 << std::endl;
        std::cout << "k1 = " << k11 << std::endl;
        std::cout << "z1 = " << z11 << std::endl;
        std::cout << "p1 = " << p11 << std::endl;
        std::cout << "k2 = " << k22 << std::endl;
        std::cout << "z2 = " << z22 << std::endl;
        std::cout << "p2 = " << p22 << std::endl;

        if (wyswietlaj)
        {
            calculations(&a11, &a00, &b22, &b11, &b00, &k11, &z11, &p11, &k22, &z22, &p22, &aa00, &aa11, &aa22, &aa33, &bb00, &bb11, &bb22, &bb33);


            A.n[0][0] = 0; A.n[0][1] = 1; A.n[0][2] = 0; A.n[0][3] = 0;
            A.n[1][0] = 0; A.n[1][1] = 0; A.n[1][2] = 1; A.n[1][3] = 0;
            A.n[2][0] = 0; A.n[2][1] = 0; A.n[2][2] = 0; A.n[2][3] = 1;
            A.n[3][0] = -aa00; A.n[3][1] = -aa11; A.n[3][2] = -aa22; A.n[3][3] = -aa33;
            B.n[0] = 0; B.n[1] = 0; B.n[2] = 0; B.n[3] = 1;
            C.n[0] = bb00; C.n[1] = bb11; C.n[2] = bb22; C.n[3] = bb33;
            D = 0;

            total = static_cast<int>(1.0 * T / h);
            w = 2.0 * PI * f;

            std::vector<double> us(total + 1);
            std::vector<double> uf(total + 1);
            std::vector<double> ut(total + 1);
            std::vector<double> y(total + 1);


            for (i = 0; i <= total; i++) {
                us[i] = M * sin(w * i * h);
                uf[i] = (us[i] > 0) ? M : -M;
                double t1 = fmod(w * i * h, (2*M)) - M;
                ut[i] = (t1 < 0) ? (M + t1) : (M - t1);
            }

            xi_1.n[0] = xi_1.n[1] = xi_1.n[2] = xi_1.n[3] = 0;

            for (i = 0; i <= total; i++) {
                Ax = A * xi_1;
                if (wejscieSinus)
                {
                    Bu = B * us[i];
                    Du = D * us[i];
                }
                else if (wejscieProstokat)
                {
                    Bu = B * uf[i];
                    Du = D * uf[i];
                }
                else if (wejscieTrojkat)
                {
                    Bu = B * ut[i];
                    Du = D * ut[i];
                }
                
                Cx = C * xi_1;
                xi = Ax + Bu;
                xi = xi * h;
                xi = xi_1 + xi;
                xi_1 = xi;
                y[i] = Cx + Du;
            }

            std::vector<double> time(total + 1);
            for (i = 0; i <= total; ++i) {
                time[i] = i * h;
            }


            std::cout << "a0 =" << aa00 << std::endl;
            std::cout << "a1 = " << aa11 << std::endl;
            std::cout << "a2 = " << aa22 << std::endl;
            std::cout << "a3 = " <<aa33 << std::endl;
            std::cout << "b0 = " << bb00 << std::endl;
            std::cout << "b1 = " << bb11 << std::endl;
            std::cout << "b2 = " << bb22 << std::endl;
            std::cout << "b3 =" << bb33 << std::endl;

            if (wejscieSinus)
            {
                plot(time, us, "-r");
                xlabel("Time (s)");
                ylabel("u(t)");
                title("u(t)");
                show();
            }
            else if (wejscieProstokat)
            {
                plot(time, uf, "-r");
                xlabel("Time (s)");
                ylabel("u(t)");
                title("u(t)");
                show();
            }
            else if (wejscieTrojkat)
            {
                plot(time, ut, "-r");
                xlabel("Time (s)");
                ylabel("u(t)");
                title("u(t)");
                show();
            }
            

            plot(time, y, "-b");
            xlabel("Time (s)");
            ylabel("y(t)");
            title("y(t)");
            show();
        }
    }
    
    

    return 0;
}