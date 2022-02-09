#include <iostream>
#include <windows.h>
#include <string>
#include <random>
#include <iomanip>
#include "Graph.h"
#include "SA.h"
#include "DP.h"
#include "TS.h"

//czy dywersyfikacja włączona
bool diversification = true;

//kryterium stopu
int timeToStop=10;

void makeGraphRandom(Graph* graph);

/// <summary>
/// Ustawianie nazwy pliku
/// </summary>
/// <returns>Wprowadzona nazwa</returns>
std::string setFileName() {
    system("CLS");
    std::string fileName;
    std::cout << "Podaj nazwe pliku do zaladowania wraz z jego rozszerzeniem:";
    std::cin >> fileName;
    return fileName;
}

bool isChoiceValid(int choice, int n1, int n2) {
    if (choice >= n1 && choice <= n2) return true;
    else return false;
}

void menu() {

    int choice = 0;
    std::string fileName;
    Graph graph(0, 0, 0);
    //TODO: sprawdzenie czy struktury nie sa puste przed wykonaniem na nich algorytmu
    while (choice != 9) {
        system("CLS");
        std::cout << "Kryterium stopu: " << timeToStop << " s\n\n\n";
        std::cout << "MENU\n";
        std::cout << "Wybierz opcje:\n";
        std::cout << "1.Wczytaj graf miast z pliku\n";
        std::cout << "2.Wyswietl graf miast\n";
        std::cout << "3.Wprowadz kryterium stopu(w sekundach)\n";
        std::cout << "4.Tabu Search\n";
        std::cout << "5.Symulowane wyzarzanie\n";
        std::cout << "6.Losuj graf\n";
        std::cout << "7.Dynamic Programming (dla porownania)\n";
        std::cout << "8.Wlacz/wylacz dywersyfikacje\n";
        std::cout << "9.Wyjscie\n";
        std::cout << "Wybor:";
        std::cin >> choice;
        std::cin.clear();							//resetujemy status strumienia wejść
        if (isChoiceValid(choice, 1, 9)) {
            switch (choice) {
            case 1: {
                fileName = setFileName();
                graph.loadGraphFromFile(fileName);
                std::cout << "\nGraf zostal zaladowany!\n";
                system("PAUSE");
                break;
            }
            case 2: {
                graph.printGraphMatrix();
                system("PAUSE");
                break;
            }
            case 3: {
                system("CLS");
                std::cout << "Podaj czas w sekundach:";
                std::cin >> timeToStop;
                if (!std::cin.good()) {
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    timeToStop = 10;
                    std::cout << "\nWprowadzono niedozwolona wartosc!\n";
                }
                else {
                    std::cout << "\nKtyterium stopu to teraz " << timeToStop << " s.\n";
                }
                
                system("PAUSE");
                break;
            }
            case 4: {
                system("cls");
                TS* ts = new TS();
                ts->search(&graph, timeToStop, diversification);
                std::cout << "\n";
                system("PAUSE");
                break;
            }
            case 5: {
                SA* sa = new SA();
                system("CLS");
                sa->simulateAnneling(&graph, timeToStop);
                std::cout << "\n";
                system("PAUSE");
                break;
            }
            case 6: {
                system("CLS");
                int sizeToResizeTo;
                std::cout << "Podaj rozmiar grafu do wylosowania: ";
                std::cin >> sizeToResizeTo;
                system("CLS");
                if (sizeToResizeTo > 1) {
                    graph.resizeMatrix(sizeToResizeTo);
                    makeGraphRandom(&graph);
                    std::cout << "Wylosowano graf!";
                    system("PAUSE");
                }
                break;
            }
            case 7: {
                system("cls");
                DP* dp = new DP();
                dp->findPath(&graph);
                system("PAUSE");
                break;
            }
            case 8: {
                if (!diversification) {
                    system("cls");
                    diversification = true;
                    std::cout << "Dywersyfikacja zostala wlaczona!\n";
                    system("PAUSE");
                }
                else {
                    system("cls");
                    diversification = false;
                    std::cout << "Dywersyfikacja zostala wylaczona!\n";
                    system("PAUSE");
                }
            }
            case 9: {
                break;
            }
            }
        }
        else {
            std::cout << "Podano liczba spoza zakresu! Podaj liczbe jeszcze raz!";
            system("PAUSE");
        }
    }
    return;
}



void makeGraphRandom(Graph* graph) {


    for (int i = 0; i < graph->getSize(); i++) {
        for (int j = 0; j < graph->getSize(); j++) {
            if (i != j)
                graph->addEdge(i, j, Random::generateRandomNumber(1,10000));
            else
                graph->addEdge(i, j, 0);
        }
    }

    return;
}

#pragma optimize("", off)
int main()
{
    menu();
    /*
    int testGraphSize = 20;

    long float totalTime = 0;

    long long int frequency, start, elapsed;
    srand(time(NULL));
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    for (int i = 0; i < 100; i++) {
        Graph* testGraph = new Graph(testGraphSize, 0, 0);
        makeGraphRandom(testGraph);

        start = read_QPC();//
        BB::findPath(testGraph);
        elapsed = read_QPC() - start;//

        std::cout << "Time [us] = " << (1000000.0 * elapsed) /
            frequency << "\n";
        totalTime += (1000000.0 * elapsed) /
            frequency;
    }
    std::cout << "Srednia:" << totalTime / 100000<< "[ms]\n";
    system("PAUSE");
    */

    return 0;

}
#pragma optimize("", on)
