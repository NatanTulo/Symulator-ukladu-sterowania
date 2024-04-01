﻿#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>

using namespace matplot;

#define N 4
#define h 0.001
#define T 10.0
#define L 2.5
#define M 8.0
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

int matplotTest() {
    std::vector<double> x = linspace(0, 2 * pi);
    std::vector<double> y = transform(x, [](auto x) { return sin(x); });

    plot(x, y, "-o");
    hold(on);
    plot(x, transform(y, [](auto y) { return -y; }), "--xr");
    plot(x, transform(x, [](auto x) { return x / pi - 1.; }), "-:gs");
    plot({ 1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1 }, "k");

    show();
}

void handleSquare(double amplitude, double fill, double duration, double offset, double period) {
    system("cls");
    std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << "\tOffset: " << offset << "\tOkres: " << period << std::endl;
}

bool choice() {
    setlocale(LC_ALL, "PL");
    system("cls");
    std::cout << "Wybierz sygnał wejściowy:" << std::endl;
    std::cout << "1. Prostokątny" << std::endl;
    std::cout << "2. Trójkątny" << std::endl;
    std::cout << "3. Harmoniczny" << std::endl;
    char choice;
    std::cin >> choice;
    while (choice != '1' && choice != '2' && choice != '3') {
        system("cls");
        std::cout << "Wybierz sygnał wejściowy:" << std::endl;
        std::cout << "1. Prostokątny" << std::endl;
        std::cout << "2. Trójkątny" << std::endl;
        std::cout << "3. Harmoniczny" << std::endl<<std::endl;
        std::cout << "Niepoprawny wybór" << std::endl;
		std::cin >> choice;
	}
    switch (choice) {
    case '1':
        system("cls");
        std::cout << "Wybierz parametry sygnału" << std::endl;
        std::cout << "Podaj amplitudę: ";
        double amplitude;
        while (!(std::cin >> amplitude) || amplitude <= 0) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            system("cls");
            std::cout << "Amplituda musi być większa od zera" << std::endl;
            std::cout << "Podaj amplitudę: ";
        }
        system("cls");
        std::cout << "Wybierz parametry sygnału" << std::endl;
        std::cout << "Amplituda: " << amplitude << std::endl;
        std::cout << "Podaj wypełnienie [%]: ";
        double fill;
        while (!(std::cin >> fill) || fill <= 0 || fill >= 100) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            system("cls");
            std::cout << "Wybierz parametry sygnału" << std::endl;
            std::cout << "Amplituda: " << amplitude << std::endl;
            std::cout << "Wypełnienie musi być z przedziału (0, 100)" << std::endl;
            std::cout << "Podaj wypełnienie [%]: ";
        }
        system("cls");
        std::cout << "Wybierz parametry sygnału" << std::endl;
        std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << std::endl;
        std::cout << "Podaj czas trwania sygnału: ";
        double duration;
        while (!(std::cin >> duration) || duration <= 0) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            system("cls");
            std::cout << "Czas trwania musi być większy od zera" << std::endl;
            std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << std::endl;
            std::cout << "Podaj czas trwania sygnału: ";
        }
        system("cls");
        std::cout << "Wybierz parametry sygnału" << std::endl;
        std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << std::endl;
        std::cout << "Podaj offset:";
        double offset;
        while (!(std::cin >> offset)) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
			system("cls");
            std::cout << "Offset musi być liczbą" << std::endl;
			std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << std::endl;
			std::cout << "Podaj offset:";
		}
        system("cls");
        std::cout << "Wybierz parametry sygnału" << std::endl;
        std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << "\tOffset: " << offset << std::endl;
        std::cout << "Wybierz jaki parametr chcesz podać:" << std::endl;
        std::cout << "1. Okres" << std::endl;
        std::cout << "2. Częstotliwość" << std::endl;
        char choice2;
        std::cin >> choice2;
        while (choice2 != '1' && choice2 != '2') {
            system("cls");
            std::cout << "Wybierz parametry sygnału" << std::endl;
            std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << "\tOffset: " << offset << std::endl;
            std::cout << "Wybierz jaki parametr chcesz podać:" << std::endl;
            std::cout << "1. Okres" << std::endl;
            std::cout << "2. Częstotliwość" << std::endl<<std::endl;
			std::cout << "Niepoprawny wybór" << std::endl;
			std::cin >> choice2;
		}       
        system("cls");
        std::cout << "Wybierz parametry sygnału" << std::endl;
        std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << "\tOffset: " << offset << std::endl;
        switch (choice2) {
            case '1':
                std::cout << "Podaj okres: ";
                double period;
                while (!(std::cin >> period) || period <= 0) {
                    std::cin.clear();
                    std::cin.ignore(1024, '\n');
                    system("cls");
                    std::cout << "Okres musi być większy od zera" << std::endl;
                    std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << "\tOffset: " << offset << std::endl;
                    std::cout << "Podaj okres: ";
                }
                handleSquare(amplitude, fill, duration, offset, period);
                break;
            case '2':
                std::cout << "Podaj częstotliwość: ";
                double frequency;
                while (!(std::cin >> frequency) || frequency <= 0) {
                    std::cin.clear();
                    std::cin.ignore(1024, '\n');
                    system("cls");
                    std::cout << "Częstotliwość musi być większa od zera" << std::endl;
                    std::cout << "Amplituda: " << amplitude << "\tWypełnienie: " << fill << '%' << "\tCzas trwania: " << duration << "\tOffset: " << offset << std::endl;
                    std::cout << "Podaj częstotliwość: ";
                }
                handleSquare(amplitude, fill, duration, offset, 1 / frequency);
                break;
            default:
                return 1;
        }
        break;
    case '2':
        // Sygnał trójkątny
        break;
    case '3':
        // Sygnał harmoniczny
        break;
    default:
        return 1;
    }
    return 0;
}



int main() {
    //choice();
    //matplotTest();
    int i, total;
    double a3, a2, a1, a0, b3, b2, b1, b0, w;
    Matr A;
    Vect B, C, Ax, Bu, xi, xi_1;
    double D, Cx, Du;

    std::cout << "\n a3 = "; std::cin >> a3;
    std::cout << "\n a2 = "; std::cin >> a2;
    std::cout << "\n a1 = "; std::cin >> a1;
    std::cout << "\n a0 = "; std::cin >> a0;
    std::cout << "\n b3 = "; std::cin >> b3;
    std::cout << "\n b2 = "; std::cin >> b2;
    std::cout << "\n b1 = "; std::cin >> b1;
    std::cout << "\n b0 = "; std::cin >> b0;
    std::cout << "\n\n";

    A.n[0][0] = 0; A.n[0][1] = 1; A.n[0][2] = 0; A.n[0][3] = 0;
    A.n[1][0] = 0; A.n[1][1] = 0; A.n[1][2] = 1; A.n[1][3] = 0;
    A.n[2][0] = 0; A.n[2][1] = 0; A.n[2][2] = 0; A.n[2][3] = 1;
    A.n[3][0] = -a0; A.n[3][1] = -a1; A.n[3][2] = -a2; A.n[3][3] = -a3;
    B.n[0] = 0; B.n[1] = 0; B.n[2] = 0; B.n[3] = 1;
    C.n[0] = b0; C.n[1] = b1; C.n[2] = b2; C.n[3] = b3;
    D = 0;

    total = static_cast<int>(1.0 * T / h);
    w = 2.0 * PI * L / T;

    std::vector<double> us(total + 1);
    std::vector<double> uf(total + 1);
    std::vector<double> y(total + 1);

    for (i = 0; i <= total; i++) {
        us[i] = M * sin(w * i * h);
        uf[i] = (us[i] > 0) ? M : -M;
    }

    xi_1.n[0] = xi_1.n[1] = xi_1.n[2] = xi_1.n[3] = 0;

    for (i = 0; i <= total; i++) {
        Ax = A * xi_1;
        Bu = B * us[i];
        Cx = C * xi_1;
        Du = D * us[i];
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

    plot(time, us, "-r");
    xlabel("Time (s)");
    ylabel("u(t)");
    title("u(t)");
    show();

   

    // Create a plot for y(t)
    plot(time, y, "-b");
    xlabel("Time (s)");
    ylabel("y(t)");
    title("y(t)");
    show();

    return 0;
}