#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cmath>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

void inssort(int* tablica, int size) {
    for (int i = 1; i < size; i++) {
        int key = tablica[i];
        int j = i - 1;
        while (j >= 0 && tablica[j] > key) {
            tablica[j + 1] = tablica[j];
            j--;
        }
        tablica[j + 1] = key;
    }
}

void merge(int* tablica, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = tablica[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = tablica[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            tablica[k] = L[i];
            i++;
        }
        else {
            tablica[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tablica[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        tablica[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void timsort(int* tablica, int size) {
    const int RUN = 64;
    for (int i = 0; i < size; i += RUN)
        inssort(tablica + i, min(RUN, size - i));

    for (int sizeMerge = RUN; sizeMerge < size; sizeMerge *= 2) {
        for (int left = 0; left < size; left += 2 * sizeMerge) {
            int mid = min(left + sizeMerge - 1, size - 1);
            int right = min(left + 2 * sizeMerge - 1, size - 1);
            if (mid < right)
                merge(tablica, left, mid, right);
        }
    }
}
void dpqs(int* tablica, int size)
{
    if (size <= 1) return;

    int L = tablica[0];
    int R = tablica[size - 1];
    if (R < L)
        swap(L, R);

    int* numL = new int[size];
    int* numM = new int[size];
    int* numR = new int[size];
    int lc = 0, mc = 0, rc = 0;

    for (int i = 1; i < size - 1; i++)
    {
        if (tablica[i] < L)
            numL[lc++] = tablica[i];
        else if (tablica[i] < R)
            numM[mc++] = tablica[i];
        else
            numR[rc++] = tablica[i];
    }

    int index = 0;
    for (int i = 0; i < lc; i++) tablica[index++] = numL[i];
    tablica[index++] = L;
    for (int i = 0; i < mc; i++) tablica[index++] = numM[i];
    tablica[index++] = R;
    for (int i = 0; i < rc; i++) tablica[index++] = numR[i];

    dpqs(tablica, lc);
    dpqs(tablica + lc + 1, mc);
    dpqs(tablica + lc + mc + 2, rc);
    delete[] numL;
    delete[] numM;
    delete[] numR;
}
void heapify(int* tab, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && tab[left] > tab[largest])
        largest = left;

    if (right < size && tab[right] > tab[largest])
        largest = right;

    if (largest != i) {
        std::swap(tab[i], tab[largest]);
        heapify(tab, size, largest);
    }
}

void heapsort(int* tablica, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(tablica, size, i);

    for (int j = size - 1; j > 0; j--) {
        std::swap(tablica[0], tablica[j]);
        heapify(tablica, j, 0);
    }
}
int countMean(long long* tab, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += tab[i];
    int mean = sum / size;
    return mean;
}

int* gentab(const int size)
{
    int* tab = new int[size];
    srand(time(nullptr));
    for (int i = 0; i < size; i++)
        tab[i] = rand() % 1000000;
    return tab;
}
int main()
{
        int sizes[6] = { 1000, 10000, 50000, 100000, 500000, 1000000 };
        float soorts[8] = { 0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, 1 };
        int runs = 100;
        long long results[100];
        for (int o = 2; o < 3; o++)
        {
            for (int p = 7; p < 8; p++)
            {
                for (int l = 0; l < 6; l++)
                {                
                    int sizeee = sizes[l];
                    for (int g = 0; g < runs; g++)
                    {
                        int* tabb = gentab(sizeee); 
                        sort(tabb, tabb + int(sizeee * soorts[p]), greater<int>());            //, greater<int>()
                        auto start = chrono::high_resolution_clock::now();
                        switch (o)
                        {
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
                    fstream plikk("C:\\Users\\Krzysztof\\Desktop\\sorted_10k.txt", ios::out | ios::app);
                    switch (o)
                    {
                        case 0:
                            plikk << "TS " << "sort " << soorts[p] << " " << sizeee << endl;
                            break;
                        case 1:
                            plikk << "HS " << "sort " << soorts[p] << " " << sizeee << endl;
                            break;
                        case 2:
                            plikk << "DPQS " << "sort " << soorts[p] << " " << sizeee << endl;
                            break;
                    }
                    plikk << min << endl;
                    plikk << Mean << endl;
                    plikk << max << endl;
                    plikk.close();
                }
            }
            
        }
    return 0;
}