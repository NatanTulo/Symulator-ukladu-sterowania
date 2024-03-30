#include <cmath>
#include <matplot/matplot.h>

int matplotTest() {
    using namespace matplot;
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
    choice();
    //matplotTest();
    return 0;
}