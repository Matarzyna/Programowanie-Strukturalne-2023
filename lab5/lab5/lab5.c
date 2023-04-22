#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning( disable : 4996 )



int bin2int(char liczba[], int n)
{
	//konwersja z binarnych na dziesietne
	// n - ilosc kolumn
	// temp - indeks potegi dwojki

	int temp = 0;
	int wynik = 0;
	for (int i = n; i >= 0; --i)
	{
		if (liczba[i] == '0' || liczba[i] == '1')
		{
			if (liczba[i] == '1') 
				wynik += (int)pow(2, temp);

			temp++;
		}
	}
	return wynik;
}

int main() {


	//////////////////////////////////////////////////////////////////
	// m - WIERSZE													//
	// n - KOLUMNY													//
	//																//
	// wymagania pliku wejsciowego: 								//
	// - liczby binarne zaczynajace sie od 1						//
	// - NIE WIECEJ niz m wierszy									//
	// - MNIEJ niz n znakow  										//
	//////////////////////////////////////////////////////////////////


	int m, n;

	putchar('\n');
	printf("Podaj liczbe wierszy:");
	scanf("%d", &m);
	printf("Podaj liczbe kolumn:");
	scanf("%d", &n);
	putchar('\n');


	//alokacja tablicy dwywum. dynamicznej
	char** t1=malloc(m*sizeof(char*));

	if (t1 == NULL)
	{
		printf("Nie udalo sie zaalokowac tablicy");
		return 0;
	}

	for (int i = 0; i < m; ++i)

		t1[i] = malloc(n * sizeof(char));

	if (t1[1] == NULL)
	{
		printf("Nie udalo sie zaalokowac tablicy");
		return 0;
	}

	FILE* In;

	//check czy udalo sie otworzyc plik
	if ((In = fopen("test.txt", "r")) == NULL)
	{
		printf("Nie udalo sie otworzyc pliku");
		return 0;
	}

	//podliczanie ilosci wierszy w pliku
	int num; 
	for (int i = 0; i < m; ++i)
	{	
		fscanf(In, "%s", t1[i]);
		if (feof(In))
		{
			num = i+1; //ilosc wierszy w pliku
			break;
		}
	}

	//jesli plik pusty (0 wierszy)
	if (num == 0)
	{
		printf("Plik jest pusty");
		return 0;
	}


	//wypisanie nieposortowanych liczb zmienionych z bin na dec
	for (int i = 0; i < num; i++)
	{
		printf("%s ", t1[i]);
		printf("%d\n", bin2int(t1[i], n));
	}
	putchar('\n');


	//sortowanie przez wybor bez dodatkowej tablicy
	int max = bin2int(t1[0], n);

	char* temp;
	int gdzie=0, temp2;
	
	for (int j = 0; j < num; ++j)
	{
		for (int i = j; i < num; i++)
		{
			temp2 = bin2int(t1[i], n);
			if (max < temp2)
			{
				gdzie = i;
				max = temp2;
			}
		}
		temp = t1[gdzie];
		t1[gdzie] = t1[j];
		t1[j] = temp;
		max = 0;
	}

	//wypisanie posortowanych liczb
	for (int i = 0; i < num; i++)
	{
		printf("%s\n", t1[i]);
		//printf("%d\n", bin2int(t1[i], n));
	}
	

	//zwalnianie dwuwym. tablicy dynamicznej
	for (int i = 0; i < m; i++)
		free(t1[i]);
	free(t1);
		
	//zamkniecie pliku
	fclose(In);


	return 0;

	

	/*
	struct student{
		int nr_ID;
		char nazwisko[40];
		char imie[40];
		double punkty;
	};
	typedef struct student st;

	struct zdrugiej{
		st* wskaznik;
		int rozmiar;
	};
	typedef struct zdrugiej F2_t;


	int		ile_wierszy(FILE* plik)
	{
	//zliczanie wierszy
		int num;
		for (int i = 0; i < m; ++i)
		{
			fscanf(plik, "%s", t1[i]);
			if (feof(plik))
			{
				num = i+1; //ilosc wierszy w pliku
				break;
			}
		}
		rewind(plik);

	return num;
	}

	st* tab=(st*)malloc(ile*sizeof(st));	//alokacja tablicy dynamicznej typu strukturalnego
	
	for(int i=gdzie;i<ile-1;++i)
		t[i]=t[i+1];


	*/


}