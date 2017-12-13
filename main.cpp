#include <fstream>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <random>
#include <string>

using namespace ::std;

int przestaw = 0;
int przesu = 0;
clock_t czas1 = 0;
clock_t czas2 = 0;

int do_wykresu = 0;

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
void saveToFile(int tab[], int n, string file)
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
	ofstream plik(file);
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

		przesu++; //<-------------------- PRZESUNIECIE++!!! -------------------->

		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = w;
			i++;
			j--;
			przestaw++; //<-------------------- PRZESTAWIENIE++!!! -------------------->
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
	for (int gap = n / 2; gap > 0; gap /= 2) //<-------------------- zamienic 2 przy gap na np. 3 !!! -------------------->
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
			przestaw++; //<-------------------- PRZESTAWIENIE++!!! -------------------->
		}
	}

	//czas2 = clock();
	//czas2 -= czas1;
	return 0;
}



void merge(int pocz, int sr, int kon, int tab[], int t[])
{
	int i, j, q;
	for (i = pocz; i <= kon; i++) t[i] = tab[i];  // Skopiowanie danych do tablicy pomocniczej
	i = pocz; j = sr + 1; q = pocz;                 // Ustawienie wskaŸników tablic
	while (i <= sr && j <= kon) {         // Przenoszenie danych z sortowaniem ze zbiorów pomocniczych do tablicy g³ównej
		if (t[i]<t[j])
			tab[q++] = t[i++];
		else
			tab[q++] = t[j++];

		przestaw++; //<-------------------- PRZESTAWIENIE++!!! -------------------->
	}
	while (i <= sr) tab[q++] = t[i++]; // Przeniesienie nie skopiowanych danych ze zbioru pierwszego w przypadku, gdy drugi zbiór siê skoñczy³
}
/* Procedura sortowania tab[pocz...kon] */
void mergesort(int pocz, int kon, int tab[], int t[])
{
	//czas1 = clock();
	int sr;
	if (pocz<kon) {
		sr = (pocz + kon) / 2;
		mergesort(pocz, sr, tab, t);    // Dzielenie lewej czêœci
		mergesort(sr + 1, kon, tab, t);   // Dzielenie prawej czêœci
		merge(pocz, sr, kon, tab, t);   // £¹czenie czêœci lewej i prawej
	}
	//czas2 = clock();
	//czas2 -= czas1;
}



void wszystko(int n)
{
	string file;
	string wyniczek;

	wyniczek = "wynik";
	wyniczek += to_string(n);
	wyniczek += ".txt";

	ofstream wynik(wyniczek);

	//wynik.open(wyniczek, ios::in | ios::out);

	int *tab = new int[n];
	int *ortab = new int[n];
	int *t = new int[n];

	for (int i = 0; i < n; i++) // wczytywanie liczb do tablicy
	{
		tab[i] = randGen();
	}

	for (int i = 0; i < n; i++)
	{
		ortab[i] = tab[i];
	}

	file = "wejscie";
	file += to_string(n);
	file += ".txt";
	cout << file << endl;
	saveToFile2(tab, n, file);
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

	wynik << czas2;
	wynik << endl;
	/*
	wynik << przestaw;
	wynik << endl;
	wynik << przesu;
	wynik << endl;
	*/
	wynik << przestaw + przesu;
	wynik << endl;

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

	wynik << czas2;
	wynik << endl;
	wynik << przestaw;
	wynik << endl;

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

	wynik << czas2;
	wynik << endl;
	wynik << przestaw;
	wynik << endl;

	czas1 = 0;
	czas2 = 0;
	przestaw = 0;
	przesu = 0;
	//Podmiana tablicy
	for (int i = 0; i < n; i++)
		tab[i] = ortab[i];
}

void ladowanie_wykresu(int tab1[], int tab2[], int n)
{
	fstream wynik;

	string wyniczek;

	wyniczek = "wynik";
	wyniczek += to_string(n);
	wyniczek += ".txt";

	wynik.open(wyniczek, ios::in | ios::out);
	/*
	switch (n)
	{
	case 10000:
	wynik >> tab1[do_wykresu];
	wynik >> tab2[do_wykresu];
	do_wykresu++;
	wynik >> tab1[do_wykresu];
	wynik >> tab2[do_wykresu];
	do_wykresu++;
	wynik >> tab1[do_wykresu];
	wynik >> tab2[do_wykresu];
	do_wykresu++;
	break;
	case 25000:
	break;
	case 50000:
	break;
	case 75000:
	break;
	case 100000:
	break;
	case 150000:
	break;
	}
	*/

	/*
	if (n == 10000)
	{
	}else if (n == 25000)
	{
	}else if (n == 50000)
	{
	}else if (n == 75000)
	{
	}
	else if (n == 100000)
	{
	}
	else if (n == 150000)
	{
	}
	*/

	wynik >> tab1[do_wykresu];
	wynik >> tab2[do_wykresu];
	do_wykresu++;
	wynik >> tab1[do_wykresu];
	wynik >> tab2[do_wykresu];
	do_wykresu++;
	wynik >> tab1[do_wykresu];
	wynik >> tab2[do_wykresu];
	do_wykresu++;

}

void wykres()
{
	//Wykres liczby przestawien od ilosci danych.
	int wykres_przestaw[18];

	//Wykres czasu wykonania funkcji sortujacych od ilosci danych
	int wykres_czas[18];

	ladowanie_wykresu(wykres_czas, wykres_przestaw, 10000);
	ladowanie_wykresu(wykres_czas, wykres_przestaw, 25000);
	ladowanie_wykresu(wykres_czas, wykres_przestaw, 50000);
	ladowanie_wykresu(wykres_czas, wykres_przestaw, 75000);
	ladowanie_wykresu(wykres_czas, wykres_przestaw, 100000);
	ladowanie_wykresu(wykres_czas, wykres_przestaw, 150000);

	for (int i = 0; i < 18; i++)
	{
		cout << wykres_czas[i] << endl;
		cout << wykres_przestaw[i] << endl;
	}

	int pomoc_wykresowa = 1;
	int en = 10000;

	/*
	QuickSort(wykres_czas, 0, 18 - 1);
	QuickSort(wykres_przestaw, 0, 18 - 1);
	for (int i = 0; i < 18; i++)
	{
	cout << wykres_czas[i] << endl;
	cout << wykres_przestaw[i] << endl;
	}
	*/
	system("Pause");
	system("cls");
	char wynik_czas[10][18] = {};
	char wynik_przestaw[10][18] = {};

	for (int i = 0; i < 18; i++)
	{
		if (wykres_czas[i] <= 5)
		{
			wynik_czas[0][i] = 254;
		}
		else if (wykres_czas[i] >= 6 && wykres_czas[i] <= 10)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
		}
		else if (wykres_czas[i] >= 11 && wykres_czas[i] <= 15)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
		}
		else if (wykres_czas[i] >= 16 && wykres_czas[i] <= 20)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
			wynik_czas[3][i] = 254;
		}
		else if (wykres_czas[i] >= 21 && wykres_czas[i] <= 25)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
			wynik_czas[3][i] = 254;
			wynik_czas[4][i] = 254;
		}
		else if (wykres_czas[i] >= 26 && wykres_czas[i] <= 30)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
			wynik_czas[3][i] = 254;
			wynik_czas[4][i] = 254;
			wynik_czas[5][i] = 254;
		}
		else if (wykres_czas[i] >= 31 && wykres_czas[i] <= 35)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
			wynik_czas[3][i] = 254;
			wynik_czas[4][i] = 254;
			wynik_czas[5][i] = 254;
			wynik_czas[6][i] = 254;
		}
		else if (wykres_czas[i] >= 36 && wykres_czas[i] <= 40)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
			wynik_czas[3][i] = 254;
			wynik_czas[4][i] = 254;
			wynik_czas[5][i] = 254;
			wynik_czas[6][i] = 254;
			wynik_czas[7][i] = 254;
		}
		else if (wykres_czas[i] >= 41 && wykres_czas[i] <= 45)
		{

			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
			wynik_czas[3][i] = 254;
			wynik_czas[4][i] = 254;
			wynik_czas[5][i] = 254;
			wynik_czas[6][i] = 254;
			wynik_czas[7][i] = 254;
			wynik_czas[8][i] = 254;
		}
		else if (wykres_czas[i] >= 46)
		{
			wynik_czas[0][i] = 254;
			wynik_czas[1][i] = 254;
			wynik_czas[2][i] = 254;
			wynik_czas[3][i] = 254;
			wynik_czas[4][i] = 254;
			wynik_czas[5][i] = 254;
			wynik_czas[6][i] = 254;
			wynik_czas[7][i] = 254;
			wynik_czas[8][i] = 254;
			wynik_czas[9][i] = 254;
		}
	}

	cout << "\tWYKRES DLA CZASU WYKONYWANIE POSZCZEGOLNYCH FUNKCJI " << endl;
	cout << "czas jest podany w przedziale od 0 do 46 sekund. jedna kropka oznacza 5 sekund" << endl;
	cout << "pierwszy poziom to quickSort, drugi to shellSort, a trzeci to mergeSort." << endl;
	cout << "dla " << en << endl;
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << wynik_czas[j][i];
		}
		//pomoc_wykresowa++;
		switch (pomoc_wykresowa)
		{
		case 3:
			en = 25000;
			break;
		case 6:
			en = 50000;
			break;
		case 9:
			en = 75000;
			break;
		case 12:
			en = 100000;
			break;
		case 15:
			en = 150000;
			break;
		}
		if (pomoc_wykresowa == 18) { pomoc_wykresowa = 1; }
		if (pomoc_wykresowa % 3 == 0)
		{
			cout << endl << "dla " << en;
		}
		pomoc_wykresowa++;
		cout << endl;
	}


	pomoc_wykresowa = 1;
	en = 10000;
	cout << endl << endl;

	for (int i = 0; i < 18; i++)
	{
		if (wykres_przestaw[i] <= 100000)
		{
			wynik_przestaw[0][i] = 254;
		}
		else if (wykres_przestaw[i] >= 100001 && wykres_przestaw[i] <= 200000)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
		}
		else if (wykres_przestaw[i] >= 200001 && wykres_przestaw[i] <= 400000)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
		}
		else if (wykres_przestaw[i] >= 400001 && wykres_przestaw[i] <= 600000)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
			wynik_przestaw[3][i] = 254;
		}
		else if (wykres_przestaw[i] >= 600001 && wykres_przestaw[i] <= 800000)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
			wynik_przestaw[3][i] = 254;
			wynik_przestaw[4][i] = 254;
		}
		else if (wykres_przestaw[i] >= 800001 && wykres_przestaw[i] <= 1000000)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
			wynik_przestaw[3][i] = 254;
			wynik_przestaw[4][i] = 254;
			wynik_przestaw[5][i] = 254;
		}
		else if (wykres_przestaw[i] >= 1000001 && wykres_przestaw[i] <= 1200000)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
			wynik_przestaw[3][i] = 254;
			wynik_przestaw[4][i] = 254;
			wynik_przestaw[5][i] = 254;
			wynik_przestaw[6][i] = 254;
		}
		else if (wykres_przestaw[i] >= 1200001 && wykres_przestaw[i] <= 1400000)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
			wynik_przestaw[3][i] = 254;
			wynik_przestaw[4][i] = 254;
			wynik_przestaw[5][i] = 254;
			wynik_przestaw[6][i] = 254;
			wynik_przestaw[7][i] = 254;
		}
		else if (wykres_przestaw[i] >= 1400001 && wykres_przestaw[i] <= 1600000)
		{

			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
			wynik_przestaw[3][i] = 254;
			wynik_przestaw[4][i] = 254;
			wynik_przestaw[5][i] = 254;
			wynik_przestaw[6][i] = 254;
			wynik_przestaw[7][i] = 254;
			wynik_przestaw[8][i] = 254;
		}
		else if (wykres_przestaw[i] >= 1600001)
		{
			wynik_przestaw[0][i] = 254;
			wynik_przestaw[1][i] = 254;
			wynik_przestaw[2][i] = 254;
			wynik_przestaw[3][i] = 254;
			wynik_przestaw[4][i] = 254;
			wynik_przestaw[5][i] = 254;
			wynik_przestaw[6][i] = 254;
			wynik_przestaw[7][i] = 254;
			wynik_przestaw[8][i] = 254;
			wynik_przestaw[9][i] = 254;
		}
	}

	cout << "\tWYKRES DLA ILOSCI WYKONANYCH OPERACJI DLA POSZCZEGOLNYCH FUNKCJI " << endl;
	cout << "Iloscsc wykonanych operacji podana jest w  przedziale od 0 do 1.600.000. jenda kropka oznacza 200.000 operacji" << endl;
	cout << "pierwszy poziom to quickSort, drugi to shellSort, a trzeci to mergeSort." << endl;
	cout << "dla " << en << endl;
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << wynik_przestaw[j][i];
		}
		//pomoc_wykresowa++;
		switch (pomoc_wykresowa)
		{
		case 3:
			en = 25000;
			break;
		case 6:
			en = 50000;
			break;
		case 9:
			en = 75000;
			break;
		case 12:
			en = 100000;
			break;
		case 15:
			en = 150000;
			break;
		}
		if (pomoc_wykresowa == 18) { pomoc_wykresowa = 1; }
		if (pomoc_wykresowa % 3 == 0)
		{
			cout << endl << "dla " << en;
		}
		pomoc_wykresowa++;
		cout << endl;
	}

}


int main()
{
	srand(time(NULL));
	fstream plik;
	string file = "wejscie.txt";

	int n, i, wybor = 0;

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
	} while (wybor <= 0 || wybor >= 3);

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
	mergesort(0, n - 1, tab, t);
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

	wszystko(10000);
	wszystko(25000);
	wszystko(50000);
	wszystko(75000);
	wszystko(100000);
	wszystko(150000);


	wykres();

	delete[] tab; // zwolnienie tablicy zaalokowanej dynamicznie


	system("Pause");
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