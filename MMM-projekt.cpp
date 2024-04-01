#include <iostream>
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

void getTransmittance(double *a1, double *a0, double *b2, double *b1, double *b0, double *k1, double *z1, double *p1, double *k2, double *z2, double *p2)
{
    setlocale(LC_ALL, "PL");
    system("cls");

    char parameter;

    bool A0, A1, B0, B1, B2, K1, Z1, P1, K2, Z2, P2;
    A0 = false;
    A1 = false;
    B0 = false;
    B1 = false;
    B2 = false;
    K1 = false;
    Z1 = false;
    P1 = false;
    K2 = false;
    Z2 = false;
    P2 = false;

    char choice;


    bool close = false;
    bool close1 = false;
    bool close2 = false;
    bool close3 = false;

    while (!close)
    {
        system("cls");
        std::cout << "Wybierz, jakiemu elementowi chcesz nadać parametry:" << std::endl;
        std::cout << "1. Transmitancja obiektu" << std::endl;
        std::cout << "2. Sterownik LEAD" << std::endl;
        std::cout << "3. Sterownik LAG" << std::endl;
        std::cout << "4. Zatwierdź i wyświetl wykresy wejścia i wyjścia" << std::endl;
        std::cin >> choice;
        close1 = false;
        close2 = false;
        close3 = false;

        switch (choice)
        {
        case '1':
            while (!close1)
            {
                system("cls");
                std::cout << "Transmitancja obiektu:" << std::endl;
                std::cout << "              ";
                if (!A1) {
                    std::cout << "a1";
                }
                else {
                    std::cout << *a1;
                }
                std::cout << "*s + ";
                if (!A0) {
                    std::cout << "a0" << std::endl;
                }
                else {
                    std::cout << *a0 << std::endl;
                }

                std::cout << "G(s) = -----------------------" << std::endl;

                std::cout << "         ";
                if (!B2) {
                    std::cout << "b2";
                }
                else {
                    std::cout << *b2;
                }
                std::cout << "*s^2 + ";
                if (!B1) {
                    std::cout << "b1";
                }
                else {
                    std::cout << *b1;
                }
                std::cout << "*s + ";
                if (!B0) {
                    std::cout << "b0" << std::endl;
                }
                else {
                    std::cout << *b0 << std::endl;
                }

                std::cout << "Który parametr chcesz zmienić?:" << std::endl;
                std::cout << "1. a1" << std::endl;
                std::cout << "2. a0" << std::endl;
                std::cout << "3. b2" << std::endl;
                std::cout << "4. b1" << std::endl;
                std::cout << "5. b0" << std::endl;
                std::cout << "6. Zatwierdź" << std::endl;

                std::cin >> parameter;
                switch (parameter) {
                case '1':
                    std::cout << "Podaj nową wartość parametru a1:";
                    std::cin >> *a1;
                    A1 = true;
                    break;
                case '2':
                    std::cout << "Podaj nową wartość parametru a0:";
                    std::cin >> *a0;
                    A0 = true;
                    break;
                case '3':
                    std::cout << "Podaj nową wartość parametru b2:";
                    std::cin >> *b2;
                    B2 = true;
                    break;
                case '4':
                    std::cout << "Podaj nową wartość parametru b1:";
                    std::cin >> *b1;
                    B1 = true;
                    break;
                case '5':
                    std::cout << "Podaj nową wartość parametru b0:";
                    std::cin >> *b0;
                    B0 = true;
                    break;
                case '6':
                    if (A1 && A0 && B2 && B1 && B0)
                    {
                        close1 = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Nie nadano wartości wszystkim parametrom";
                        std::cin >> parameter;
                    }
                }
            }
            break;
        case '2':
            while (!close2)
            {
                system("cls");
                std::cout << "Transmitacja sterownika LEAD: " << std::endl;
                std::cout << "             (s - ";
                if (!Z1) {
                    std::cout << "z1";
                }
                else {
                    std::cout << *z1;
                }
                std::cout << ')' << std::endl;

                std::cout << "G(s) = ";
                if (!K1) {
                    std::cout << "k1";
                }
                else {
                    std::cout << *k1;
                }
                std::cout << "* --------------" << std::endl;
                std::cout << "             (s - ";
                if (!P1) {
                    std::cout << "p1";
                }
                else {
                    std::cout << *p1;
                }
                std::cout << ')' << std::endl;

                std::cout << "Który parametr chcesz zmienić?:" << std::endl;
                std::cout << "1. k1" << std::endl;
                std::cout << "2. z1" << std::endl;
                std::cout << "3. p1" << std::endl;
                std::cout << "4. Zatwierdź" << std::endl;

                std::cin >> parameter;
                switch (parameter) {
                case '1':
                    std::cout << "Podaj nową wartość parametru k1:";
                    std::cin >> *k1;
                    K1 = true;
                    break;
                case '2':
                    std::cout << "Podaj nową wartość parametru z1:";
                    std::cin >> *z1;
                    Z1 = true;
                    break;
                case '3':
                    std::cout << "Podaj nową wartość parametru p1:";
                    std::cin >> *p1;
                    P1 = true;
                    break;
                case '4':
                    if (K1 && Z1 && P1)
                    {
                        close2 = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Nie nadano wartości wszystkim parametrom";
                        std::cin >> parameter;
                    }
                    break;
                }
            }
            break;

        case '3':
            while (!close3)
            {
                system("cls");
                std::cout << "Transmitacja sterownika LAG: " << std::endl;
                std::cout << "             (s - ";
                if (!Z2) {
                    std::cout << "z2";
                }
                else {
                    std::cout << *z2;
                }
                std::cout << ')' << std::endl;

                std::cout << "G(s) = ";
                if (!K2) {
                    std::cout << "k2";
                }
                else {
                    std::cout << *k2;
                }
                std::cout << "* --------------" << std::endl;
                std::cout << "             (s - ";
                if (!P2) {
                    std::cout << "p2";
                }
                else {
                    std::cout << *p2;
                }
                std::cout << ')' << std::endl;

                std::cout << "Który parametr chcesz zmienić?:" << std::endl;
                std::cout << "1. k2" << std::endl;
                std::cout << "2. z2" << std::endl;
                std::cout << "3. p2" << std::endl;
                std::cout << "4. Zatwierdź" << std::endl;

                std::cin >> parameter;
                switch (parameter) {
                case '1':
                    std::cout << "Podaj nową wartość parametru k2:";
                    std::cin >> *k2;
                    K2 = true;
                    break;
                case '2':
                    std::cout << "Podaj nową wartość parametru z2:";
                    std::cin >> *z2;
                    Z2 = true;
                    break;
                case '3':
                    std::cout << "Podaj nową wartość parametru p2:";
                    std::cin >> *p2;
                    P2 = true;
                    break;
                case '4':
                    if (K2 && Z2 && P2)
                    {
                        close3 = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Nie nadano wartości wszystkim parametrom";
                        std::cin >> parameter;
                    }
                        
                    break;
                }
            }
            break;
        case '4':
            if (A0 && A1 && B0 && B1 && B2 && K1 && Z1 && P1 && K2 && Z2 && P2)
                close = true;
            else
            {
                system("cls");
                std::cout << "Nie nadano wszystkich potrzebnych wartości" << std::endl;
                std::cin >> choice;
            }
                
        }
        
    }
}


int main() {
    //choice();
    //matplotTest();
    int i, total;
    double aa3, aa2, aa1, aa0, bb3, bb2, bb1, bb0, w;
    Matr A;
    Vect B, C, Ax, Bu, xi, xi_1;
    double D, Cx, Du;

    double a11, a00, b22, b11, b00, k11, z11, p11, k22, z22, p22;
    a11 = 0;
    a00 = 0;
    b22 = 0;
    b11 = 0;
    b00 = 0;
    k11 = 0;
    z11 = 0;
    k22 = 0;
    z22 = 0;
    p22 = 0;

    getTransmittance(&a11, &a00, &b22, &b11, &b00, &k11, &z11, &p11, &k22, &z22, &p22);
    

    aa0 = (b00 * p11 * p22 + k11 * k22 * a00 * z11 * z22) / b22;
    aa1 = (-b00 * p11 - b00 * p22 + b11 * p11 * p22 - k11 * k22 * a00 * z11 - k11 * k22 * a00 * z22 + k11 * k22 * a11 * z11 * z22)/b22;
    aa2 = (b00 - b11 * p11 - b11 * p22 + p11 * p22 * b22 + k11 * k22 * a00 - k11 * k22 * a11 * z11 - k11 * k22 * a11 * z22) / b22;
    aa3 = (b11 - b22 * p11 - b22 * p22 + k11 * k22 * a11) / b22;

    bb0 = (k11 * k22 * a00 * z11 * z22) / b22;
    bb1 = (-k11 * k22 * a00 * z22 + k11 * k22 * a11 * z11 * z22) / b22;
    bb2 = (k11 * k22 * a00 - k11 * k22 * a11 * z11 - k11 * k22 * a11 * z22) / b22;
    bb3 = k11 * k22 * a11 / b22;

    A.n[0][0] = 0; A.n[0][1] = 1; A.n[0][2] = 0; A.n[0][3] = 0;
    A.n[1][0] = 0; A.n[1][1] = 0; A.n[1][2] = 1; A.n[1][3] = 0;
    A.n[2][0] = 0; A.n[2][1] = 0; A.n[2][2] = 0; A.n[2][3] = 1;
    A.n[3][0] = -aa0; A.n[3][1] = -aa1; A.n[3][2] = -aa2; A.n[3][3] = -aa3;
    B.n[0] = 0; B.n[1] = 0; B.n[2] = 0; B.n[3] = 1;
    C.n[0] = bb0; C.n[1] = bb1; C.n[2] = bb2; C.n[3] = bb3;
    D = 0;

    total = static_cast<int>(1.0 * T / h);
    w = 2.0 * PI * L / T;

    std::vector<double> us(total + 1);
    std::vector<double> uf(total + 1);
    std::vector<double> ut(total + 1);
    std::vector<double> y(total + 1);
    

    for (i = 0; i <= total; i++) {
        us[i] = M * sin(w * i * h);
        uf[i] = (us[i] > 0) ? M : -M;
        double t1 = fmod(w * i * h, (2 * M)) - M;
        ut[i] = (t1 < 0) ? (M + t1) : (M - t1);
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

   

    plot(time, y, "-b");
    xlabel("Time (s)");
    ylabel("y(t)");
    title("y(t)");
    show();

    return 0;
}