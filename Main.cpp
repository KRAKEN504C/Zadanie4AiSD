#include <fstream>
#include <iostream>
#include <windows.h>

using namespace :: std;

/*
	Rand_MAX = 32767;
	3 x Rand_MAX = 98301;  
	Missing = 1699;
	----------------->3 x Rand_MAX + Missing = 100000;<-----------------
*/


int partition(int tablica[], int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
	int x = tablica[p]; // obieramy x
	int i = p, j = r, w; // i, j - indeksy w tabeli
	while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
	{
		while (tablica[j] > x) // dopoki elementy sa wieksze od x
			j--;
		while (tablica[i] < x) // dopoki elementy sa mniejsze od x
			i++;
		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = w;
			i++;
			j--;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
}

void QuickSort(long long int tab[], int p, int r)
{
	int q;
	if (p < r)
	{
		q = partition(tab, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		QuickSort(tab, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		QuickSort(tab, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}
}

int main()
{
	fstream plik;

	long long int n;

	cout << "Prosze podac dlugosc listy: " << endl;
	cin >> n;
	cout << "Wilekosc twojej tablicy wynosi " << n << endl;

	long long int *tab = new long long int [n];




	system("Pause");
	return 0;
}