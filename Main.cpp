#include <fstream>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <random>
#include <string>

using namespace ::std;

int przestaw = 0;
int przesu = 0;
float czas1=0;
float czas2 = 0;

/*
Rand_MAX = 32767;
3 x Rand_MAX = 98301;
Missing = 1699;
----------------->3 x Rand_MAX + Missing = 100000;<-----------------
Missing = 18932;
----------------->4 x Rand_MAX + Missing = 150000;<-----------------
*/

//Generuje losowe liczby miedzy 0 a 150000
int randGen()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 150000);

	//cout << dis(gen) << endl;
	return dis(gen);
}

//Zapisuje do pliku.
void saveToFile(int tab[], int n,string file)
{
	fstream plik;
	plik.open(file, ios::in | ios::out);

	for (int i = 0; i < n; i++)
	{
		plik << tab[i];
		plik << endl;
	}

	if (przestaw > 0)
	{
		plik << "liczba przestawien : ";
		plik << przestaw;
		plik << endl;
	}
	if (przesu > 0)
	{
		plik << "liczba Przesuniec : ";
		plik << przesu;
		plik << endl;
	}
	if (czas1 > 0)
	{
		plik << "czas wykonywania sortowania: ";
		plik << czas2;
		plik << " ms";
		plik << endl;
	}
}


void saveToFile2(int tab[], int n, string file)
{
	ofstream plik (file);
	//plik.open(file, ios::in | ios::out);

	for (int i = 0; i < n; i++)
	{
		plik << tab[i];
		plik << endl;
	}

	if (przestaw > 0)
	{
		plik << "liczba przestawien : ";
		plik << przestaw;
		plik << endl;
	}
	if (przesu > 0)
	{
		plik << "liczba Przesuniec : ";
		plik << przesu;
		plik << endl;
	}
	if (czas1 > 0)
	{
		plik << "czas wykonywania sortowania: ";
		plik << czas2;
		plik << " ms";
		plik << endl;
	}
}

//Sortowanie

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

		przesu++;

		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = w;
			i++;
			j--;
			przestaw++;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
}

void QuickSort(int tab[], int p, int r)
{
	int q;

	//czas1 = clock();

	if (p < r)
	{
		q = partition(tab, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		QuickSort(tab, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		QuickSort(tab, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}
	//czas2 = clock();
	//czas2 -= czas1;
}



int shellSort(int arr[], int n)
{
	//czas1 = clock();

	// Start with a big gap, then reduce the gap
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size.
		// The first gap elements a[0..gap-1] are already in gapped order
		// keep adding one more element until the entire array is
		// gap sorted 
		for (int i = gap; i < n; i += 1)
		{
			// add a[i] to the elements that have been gap sorted
			// save a[i] in temp and make a hole at position i
			int temp = arr[i];

			// shift earlier gap-sorted elements up until the correct 
			// location for a[i] is found
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			//  put temp (the original a[i]) in its correct location
			arr[j] = temp;
			przestaw++;
		}
	}

	//czas2 = clock();
	//czas2 -= czas1;
	return 0;
}



void merge(int pocz, int sr, int kon,int tab[],int t[])
{
	int i, j, q;
	for (i = pocz; i <= kon; i++) t[i] = tab[i];  // Skopiowanie danych do tablicy pomocniczej
	i = pocz; j = sr + 1; q = pocz;                 // Ustawienie wska�nik�w tablic
	while (i <= sr && j <= kon) {         // Przenoszenie danych z sortowaniem ze zbior�w pomocniczych do tablicy g��wnej
		if (t[i]<t[j])
			tab[q++] = t[i++];
		else
			tab[q++] = t[j++];

		przestaw++;
	}
	while (i <= sr) tab[q++] = t[i++]; // Przeniesienie nie skopiowanych danych ze zbioru pierwszego w przypadku, gdy drugi zbi�r si� sko�czy�
}
/* Procedura sortowania tab[pocz...kon] */
void mergesort(int pocz, int kon, int tab[], int t[])
{
	//czas1 = clock();
	int sr;
	if (pocz<kon) {
		sr = (pocz + kon) / 2;
		mergesort(pocz, sr, tab, t);    // Dzielenie lewej cz�ci
		mergesort(sr + 1, kon, tab, t);   // Dzielenie prawej cz�ci
		merge(pocz, sr, kon, tab, t);   // ��czenie cz�ci lewej i prawej
	}
	//czas2 = clock();
	//czas2 -= czas1;
}



void wszystko(int tab[], int ortab[], int n, int t[])
{
	string file;

	//int *t = new int[n];
	czas1 = clock();
	QuickSort(tab, 0, n - 1);
	czas2 = clock();
	czas2 -= czas1;
	// zapis do pliku
	file = "wyjscie_QS";
	file += to_string(n);
	file += ".txt";
	cout << file << endl;
	saveToFile2(tab, n, file);
	czas1 = 0;
	czas2 = 0;
	przestaw = 0;
	przesu = 0;
	//Podmiana tablicy
	for (int i = 0; i < n; i++)
		tab[i] = ortab[i];
	//ShellSort
	czas1 = clock();
	shellSort(tab, n);
	czas2 = clock();
	czas2 -= czas1;
	//zapis do pliku
	file = "wyjscie_SS";
	file += to_string(n);
	file += ".txt";
	cout << file << endl;
	saveToFile2(tab, n, file);
	czas1 = 0;
	czas2 = 0;
	przestaw = 0;
	przesu = 0;
	//Podmiana tablicy
	for (int i = 0; i < n; i++)
		tab[i] = ortab[i];

	//MergeSort
	czas1 = clock();
	mergesort(0, n - 1, tab, t);
	czas2 = clock();
	czas2 -= czas1;
	//zapis do pliku
	file = "wyjscie_MS";
	file += to_string(n);
	file += ".txt";
	cout << file << endl;
	saveToFile2(tab, n, file);
	czas1 = 0;
	czas2 = 0;
	przestaw = 0;
	przesu = 0;
	//Podmiana tablicy
	for (int i = 0; i < n; i++)
		tab[i] = ortab[i];
}


int main()
{
	srand(time(NULL));
	fstream plik;
	string file = "wejscie.txt";

	int n,i,wybor=0;

	//Wprowadzenie danych. Generowanie tablicy.

	cout << "Prosze podac dlugosc listy: " << endl;
	cin >> n;
	cout << "Wilekosc twojej tablicy wynosi " << n << endl;

	int *tab = new int[n];
	int *ortab = new int[n];
	int *t = new int[n];

	//Wprowadzenie wartosci do tablicy.

	do
	{
		cout << "Wybierz metode wprowadzania: 1- automatyczna \t 2-reczna" << endl;
		cin >> wybor;
	} while (wybor<=0 || wybor>=3);

	if (wybor == 1)
	{
		for (i = 0; i < n; i++) // wczytywanie liczb do tablicy
		{
			tab[i] = randGen();
		}
	}

	if (wybor == 2)
	{
		for (i = 0; i < n; i++) // wczytywanie liczb do tablicy
		{
			cout << "Podaj liczba: ";
			cin >> tab[i];
		}
	}

	//koniec wprowadzania do tablicy

	//zapasowa tablica

	for (int i = 0; i < n; i++)
	{
		ortab[i] = tab[i];
	}

	//zapis do pliku

	cout << file << endl;
	saveToFile(tab, n, file);


	czas1 = clock();
	QuickSort(tab, 0, n - 1); // wywolanie funkcji sortujacej
	czas2 = clock();
	czas2 -= czas1;

	
	// zapis do pliku
	file = "wyjscie_QS.txt";
	cout << file << endl;
	saveToFile(tab, n, file);
	czas1 = 0;
	czas2 = 0;
	przestaw = 0;
	przesu = 0;

	//Podmiana tablicy

	for (int i = 0; i < n; i++)
	{
		tab[i] = ortab[i];
	}


	//ShellSort

	czas1 = clock();
	shellSort(tab, n);
	czas2 = clock();
	czas2 -= czas1;

	//zapis do pliku
	file = "wyjscie_SS.txt";
	cout << file << endl;
	saveToFile(tab, n, file);
	czas1 = 0;
	czas2 = 0;
	przestaw = 0;
	przesu = 0;

	//Podmiana tablicy

	for (int i = 0; i < n; i++)
	{
		tab[i] = ortab[i];
	}


	//MergeSort

	czas1 = clock();
	mergesort(0,n-1,tab,t);
	czas2 = clock();
	czas2 -= czas1;

	//zapis do pliku
	file = "wyjscie_MS.txt";
	cout << file << endl;
	saveToFile(tab, n, file);
	czas1 = 0;
	czas2 = 0;
	przestaw = 0;
	przesu = 0;

	//Podmiana tablicy

	for (int i = 0; i < n; i++)
	{
		tab[i] = ortab[i];
	}

	//system("pause");
	wszystko(tab, ortab, 1000, t);
	wszystko(tab, ortab, 25000, t);
	wszystko(tab, ortab, 50000, t);
	wszystko(tab, ortab, 75000, t);
	wszystko(tab, ortab, 100000, t);
	wszystko(tab, ortab, 150000, t);




	delete[] tab; // zwolnienie tablicy zaalokowanej dynamicznie


	//system("Pause");
	return 0;
}









/*
file = "wyjscie_QS";
file += to_string(n);
file += ".txt";
*/


/*
for (i = 0; i < n; i++) // wypisanie posortowanej tablicy
cout << "tablica[" << i << "] = " << tab[i] << endl;
*/




/*
czas1 = clock();
QuickSort(tab, 0, n - 1);
czas2 = clock();
czas2 -= czas1;
// zapis do pliku
file = "wyjscie_QS" + n;
file += ".txt";
saveToFile2(tab, n, file);
czas1 = 0;
czas2 = 0;
przestaw = 0;
przesu = 0;
//Podmiana tablicy
for (int i = 0; i < n; i++)
tab[i] = ortab[i];

//ShellSort
czas1 = clock();
shellSort(tab, n);
czas2 = clock();
czas2 -= czas1;
//zapis do pliku
file = "wyjscie_SS" + n;
file += ".txt";
saveToFile2(tab, n, file);
czas1 = 0;
czas2 = 0;
przestaw = 0;
przesu = 0;
//Podmiana tablicy
for (int i = 0; i < n; i++)
tab[i] = ortab[i];

//MergeSort
czas1 = clock();
mergesort(0, n - 1, tab, t);
czas2 = clock();
czas2 -= czas1;
//zapis do pliku
file = "wyjscie_MS" + n;
file += ".txt";
saveToFile2(tab, n, file);
czas1 = 0;
czas2 = 0;
przestaw = 0;
przesu = 0;
//Podmiana tablicy
for (int i = 0; i < n; i++)
tab[i] = ortab[i];
*/