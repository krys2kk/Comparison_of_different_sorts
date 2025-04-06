#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <functional>
#include "sort_algorithms.h"
#include "utilities.h"

using namespace std;

int main() {
    int sizes[6] = { 1000, 10000, 50000, 100000, 500000, 1000000 };             //rozmiary
    float soorts[8] = { 0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, 1 };             //stopnie posortowania
    int runs = 100;
    long long results[100];                                                     //tabela z wynikami

    for (int o = 2; o < 3; o++) {                                               //pêtla zmieniaj¹ca sort
        for (int p = 7; p < 8; p++) {                                           //pêtla zmieniaj¹ca stopieñ sortu
            for (int l = 0; l < 6; l++) {                                       //pêtla zmieniaj¹ca rozmiar
                int sizeee = sizes[l];
                for (int g = 0; g < runs; g++) {                                //pêtla generuj¹ca sortowania
                    int* tabb = gentab(sizeee);
                    sort(tabb, tabb + int(sizeee * soorts[p]), greater<int>());                 //dodaæ '' dla odwrotnego sortowania
                    auto start = chrono::high_resolution_clock::now();
                    switch (o) {
                    case 0:
                        timsort(tabb, sizeee);
                        break;
                    case 1:
                        heapsort(tabb, sizeee);
                        break;
                    case 2:
                        dpqs(tabb, sizeee);
                        break;
                    }
                    auto end = chrono::high_resolution_clock::now();
                    auto run = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[g] = run.count();
                    delete[] tabb;
                }
                int Mean = countMean(results, runs);
                sort(results, results + runs);
                int min = results[0];
                int max = results[runs - 1];
                fstream plikk("C:\\Users\\Krzysztof\\Desktop\\sorted_10k.txt", ios::out | ios::app);  //Œcie¿ka do pliku
                switch (o) {
                case 0:
                    plikk << "TS sort " << soorts[p] << " " << sizeee << endl;
                    break;
                case 1:
                    plikk << "HS sort " << soorts[p] << " " << sizeee << endl;
                    break;
                case 2:
                    plikk << "DPQS sort " << soorts[p] << " " << sizeee << endl;
                    break;
                }
                plikk << min << endl;                                                               //zapisywanie wyników do pliku .txt
                plikk << Mean << endl;
                plikk << max << endl;
                plikk.close();
            }
        }
    }
    return 0;
}
