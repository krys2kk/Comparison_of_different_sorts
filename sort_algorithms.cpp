#include "sort_algorithms.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>

void inssort(int* tablica, int size) 
{
    for (int i = 1; i < size; i++) 
    {
        int key = tablica[i];
        int j = i - 1;
        while (j >= 0 && tablica[j] > key) 
        {                                   //przesuwanie kolejnych liczb z tabeli w lewo, dopóki nie napotkaj¹ liczby mniejszej
            tablica[j + 1] = tablica[j];
            j--;
        }
        tablica[j + 1] = key;
    }
}

void merge(int* tablica, int left, int mid, int right) {
    int n1 = mid - left + 1;                                
    int n2 = right - mid;
    int* L = new int[n1];               //tworzenie dwóch tabel o rozmiarach odpowiadaj¹cych tym posortowanym inssortem
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)        //przepisanie danych z tabeli g³ównej do odpowiednich w funkcji
        L[i] = tablica[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = tablica[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {                                   //porównywanie kolejnych liczb z tabel i wpisywanie mniejszej z nich do tabeli g³ównej
        if (L[i] <= R[j]) 
        {
            tablica[k] = L[i];
            i++;
        }
        else 
        {
            tablica[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {                                   //przepisywanie pozosta³ej czêœci tabeli wewnêtrznej, gdy druga z nich siê skoñczy
        tablica[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) 
    {
        tablica[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void timsort(int* tablica, int size) 
{
    const int RUN = 64;
    for (int i = 0; i < size; i += RUN)
        inssort(tablica + i, std::min(RUN, size - i));                          //sortowanie fragmentów tablicy g³ównej o rozmiarze RUN inssortem

    for (int sizeMerge = RUN; sizeMerge < size; sizeMerge *= 2) 
    {                                                                           //rekurencyjne powtarzanie mergesortu, dopóki rozmiar dwóch tabel w nim jest mniejszy od rozmiaru tabeli g³ównej
        for (int left = 0; left < size; left += 2 * sizeMerge) 
        {
            int mid = std::min(left + sizeMerge - 1, size - 1);
            int right = std::min(left + 2 * sizeMerge - 1, size - 1);
            if (mid < right)
                merge(tablica, left, mid, right);
        }
    }
}

void dpqs(int* tablica, int size) 
{
    if (size <= 1) return;
    int L = tablica[0];                                                 //ustalanie osi
    int R = tablica[size - 1];
    if (R < L)
        std::swap(L, R);

    int* numL = new int[size];                                          //tworzenie nowych tabel do zapisu trzech grup liczb
    int* numM = new int[size];
    int* numR = new int[size];
    int lc = 0, mc = 0, rc = 0;

    for (int i = 1; i < size - 1; i++) 
    {                                                                   //porównywanie liczby z dwiema osiami
        if (tablica[i] < L)
            numL[lc++] = tablica[i];
        else if (tablica[i] < R)
            numM[mc++] = tablica[i];
        else
            numR[rc++] = tablica[i];
    }

    int index = 0;
    for (int i = 0; i < lc; i++) tablica[index++] = numL[i];            //przepisywanie trzech tabel do jednej po kolei
    tablica[index++] = L;
    for (int i = 0; i < mc; i++) tablica[index++] = numM[i];
    tablica[index++] = R;
    for (int i = 0; i < rc; i++) tablica[index++] = numR[i];

    dpqs(tablica, lc);                                      //rekurencyjne powtórzenie algorytmu dla trzech czêœci tabeli, dopóki ich rozmiar bêdzie wiêkszy ni¿ 1
    dpqs(tablica + lc + 1, mc);
    dpqs(tablica + lc + mc + 2, rc);
    delete[] numL;
    delete[] numM;
    delete[] numR;
}

void heapify(int* tab, int size, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && tab[left] > tab[largest])            //porównywanie trzech elementów tabeli, aby wy³oniæ najwiêkszy
        largest = left;
    if (right < size && tab[right] > tab[largest])
        largest = right;

    if (largest != i) 
    {                                                       //zamienianie elementu i z elementem 2 * i + 1 lub 2 * i + 2, jeœli te s¹ wiêksze, co mo¿na zobrazowaæ jako stertê i wyci¹ganie najwiêkszego elementu listy na szczyt (pocz¹tek tabeli) 
        std::swap(tab[i], tab[largest]);
        heapify(tab, size, largest);
    }
}

void heapsort(int* tablica, int size) 
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(tablica, size, i);                          //sortowanie tablicy do postaci takiej, ¿e na pocz¹tku s¹ najwiêksze liczby

    for (int j = size - 1; j > 0; j--) 
    {
        std::swap(tablica[0], tablica[j]);                  //sortowanie tablicy do koñca
        heapify(tablica, j, 0);
    }
}
