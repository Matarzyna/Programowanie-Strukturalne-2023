#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#pragma warning( disable : 6031 )
#pragma warning( disable : 4996 )
#define IleCz 4 //ilosc czujnikow

struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *nast;
};

struct Pompom {
	struct pomiar* pierwsza;
	struct pomiar* druga;
	struct pomiar* trzecia;
	struct pomiar* czwarta;
};

struct pomiar* pierwsza_F(char nazwa[], struct pomiar* glowa)
{
	FILE* wejscie;
	
	wejscie = fopen(nazwa, "r");
	if (!wejscie)
	{
		printf("Nie udalo sie otworzyc pliku");
		exit(0);
	}

	struct pomiar *wsk = NULL;
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;


	while (!feof(wejscie))
	{
		fscanf(wejscie, "%d%d%s%lf",
			&nr_pomiaru,
			&nr_czujnika,
			data_i_czas,
			&temp);
		if (glowa == NULL)
			glowa = wsk = (struct pomiar*) calloc(1, sizeof(struct pomiar));
		else
		{
			wsk->nast = (struct pomiar*) calloc(1, sizeof(struct pomiar));
			wsk = wsk->nast;
		}
		wsk->nr_pomiaru = nr_pomiaru;
		wsk->nr_czujnika = nr_czujnika;
		strcpy(wsk->data_i_czas, data_i_czas);
		wsk->temp = temp;
	}

	fclose(wejscie);

	return glowa;
}

void druga_F(struct pomiar* glowa)
{
	struct pomiar* pom = glowa;
	int ile[IleCz] = { 0 }; // tablica do zliczania czujnikow
	while (pom != NULL)
	{
		switch (pom->nr_czujnika)
		{
			case 1:
				ile[0]++;
				break;
			case 2:
				ile[1]++;
				break;
			case 3:
				ile[2]++;
				break;
			case 4:
				ile[3]++;
				break;
		}
		pom = pom->nast;
	}

	for (int i = 0; i < IleCz; ++i)
	{
		printf("\nCzujnik nr %d - ilosc pomiarow: %d\n", i + 1, ile[i]);
	}
	putchar('\n');

	printf("Pierwszy element: %d %d %s %.2lf\n",
		glowa->nr_pomiaru,
		glowa->nr_czujnika,
		glowa->data_i_czas,
		glowa->temp);

	pom = glowa; //pom - przedostatni element;
	struct pomiar* pom1 = pom->nast;	//pom1 - ostatni element;

	while (pom1->nast != NULL)
	{
		pom = pom1;
		pom1 = pom->nast;
	}
	printf("Przedostatni element: %d %d %s %.2lf\n",
		pom->nr_pomiaru,
		pom->nr_czujnika,
		pom->data_i_czas,
		pom->temp);

	printf("Ostatni element: %d %d %s %.2lf\n",
		pom1->nr_pomiaru,
		pom1->nr_czujnika,
		pom1->data_i_czas,
		pom1->temp);
}

struct Pompom trzecia_F(struct pomiar* glowa)
{
	struct pomiar * wsk = NULL, *wsk2=NULL, *wsk3=NULL, *wsk4=NULL;
	struct Pompom x ;
	x.pierwsza = NULL;
	x.druga = NULL;
	x.trzecia = NULL;
	x.czwarta = NULL;
	

	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;

	while (glowa!= NULL)
	{
		nr_pomiaru = glowa->nr_pomiaru;
		nr_czujnika =  glowa->nr_czujnika;
		strcpy(data_i_czas, glowa->data_i_czas);
		temp = glowa->temp;

		switch (nr_czujnika)
		{
		case 1:
			if (x.pierwsza == NULL)
			{
				x.pierwsza = wsk = (struct pomiar*) calloc(1, sizeof(struct pomiar));		
			}
			else 
			{
				wsk->nast = (struct pomiar*) calloc(1, sizeof(struct pomiar));
				wsk = wsk->nast;
			}
			wsk->nr_pomiaru = nr_pomiaru;
			wsk->nr_czujnika = nr_czujnika;
			strcpy(wsk->data_i_czas, data_i_czas);
			wsk->temp = temp;
			
			break;
		case 2:
			if (x.druga == NULL)
			{
				x.druga = wsk2 = (struct pomiar*) calloc(1, sizeof(struct pomiar));
			}
			else
			{
				wsk2->nast = (struct pomiar*) calloc(1, sizeof(struct pomiar));
				wsk2 = wsk2->nast;
			}
			wsk2->nr_pomiaru = nr_pomiaru;
			wsk2->nr_czujnika = nr_czujnika;
			strcpy(wsk2->data_i_czas, data_i_czas);
			wsk2->temp = temp;
				break;
		case 3:
			if (x.trzecia == NULL)
			{
				x.trzecia = wsk3 = (struct pomiar*) calloc(1, sizeof(struct pomiar));
			}
			else
			{
				wsk3->nast = (struct pomiar*) calloc(1, sizeof(struct pomiar));
				wsk3 = wsk3->nast;
			}
			wsk3->nr_pomiaru = nr_pomiaru;
			wsk3->nr_czujnika = nr_czujnika;
			strcpy(wsk3->data_i_czas, data_i_czas);
			wsk3->temp = temp;
				break;
		case 4:
			if (x.czwarta == NULL)
			{
				x.czwarta = wsk4 = (struct pomiar*) calloc(1, sizeof(struct pomiar));
			}
			else
			{
				wsk4->nast = (struct pomiar*) calloc(1, sizeof(struct pomiar));
				wsk4 = wsk4->nast;
			}
			wsk4->nr_pomiaru = nr_pomiaru;
			wsk4->nr_czujnika = nr_czujnika;
			strcpy(wsk4->data_i_czas, data_i_czas);
			wsk4->temp = temp;
			break;
		}
		glowa = glowa->nast;
		
	}
	return x;
}

void wyczysc(struct pomiar * glowa)
{
	struct pomiar * obecny = glowa;
	struct pomiar * nast = NULL;

	while (glowa->nast != NULL)
	{
		nast = obecny->nast;
		free(obecny);
		obecny = nast;
	}
}

struct pomiar* czwarta_F(struct pomiar* glowa)
{
	struct pomiar* p1 = glowa, *p2 = glowa, *dzban = glowa;
	double max = glowa->temp, min = glowa->temp;




	while (dzban != NULL) //szukanie minimum i maksimum
	{
		if (max < dzban->temp)
		{
			p1 = dzban; //p1 - wskaznik na max
			max = dzban->temp;
		}
		else if (min > dzban->temp)
		{
			p2 = dzban; //p2 - wskaznik na min
			min = dzban->temp;
		}
		dzban = dzban->nast;
	}
	dzban = glowa;

	//przesuniecie mninimum na koniec
	if (p2 == glowa) //jesli min jest 1. elementem
	{
		glowa = glowa->nast; //zmienienie glowy na nastepny element
		while (dzban!=NULL)
		{
			dzban = dzban->nast;
		}
		dzban = p2; //dolaczenie min na koniec listy
		p2->nast = NULL;
	}
	else if (p2->nast == NULL)
	{
		//min  juz na koncu nic nie rob jest git
	}
	else //min w srodku
	{
		while (dzban->nast != p2) //szukanie elementu przed minimum
		{
			dzban = dzban->nast;
		}
		dzban->nast = p2->nast; //usuniecie polaczenia el. przed min z min i polaczenie go z nastepnym
		while (!dzban)
		{
			dzban = dzban->nast; // szukanie konca listy
		}
		dzban = p2; //doklejenie min na koniec listy
		dzban->nast = p2 = NULL; // wstawienie null na koniec listy
	}



	dzban = glowa;
	//przesuniecie maksimum na poczatek
	if(glowa==p1)
	{
		//maksimum juz na poczatku jest git
	}
	else if (p1->nast == NULL) // jesli max na koncu
	{
		while (dzban->nast != p1) //szukanie elementu przed maximum
		{
			dzban = dzban->nast;
		}
		dzban->nast = NULL; // przedostatni element listy staje sie ostatnim
		p1->nast = glowa; //element po max staje sie poprzednim pierwszym
		glowa = p1; // przypisanie adresu max do glowy
	}

	else //max w srodku
	{
		while (dzban->nast != p1) //szukanie elementu przed max
		{
			dzban = dzban->nast;
		}
		dzban->nast = p1->nast; // 'ominiecie' maksimum
		p1->nast = glowa; //podpiecie glowy za max
		glowa = p1;//zastapienie poprzedniej glowy max
	}

	return glowa;
}

int main()
{
	//printf("PODAJ NAZWE PLIKU DO ZAPISU ( bez .txt)");
	//scanf_s("%s", tekst);
	//DODAJ TO MORDI W 174 LINIJCE


	char nazwa[40] = "Dane.txt";
	
	

	struct pomiar* listaG = NULL;
	listaG =	pierwsza_F(nazwa, listaG);

	printf("\n-----------------------------Glowna lista--------------------------------------------\n");
	druga_F(listaG);
	struct Pompom  pom; 
	pom = trzecia_F(listaG);
	
	printf("\n----------Pierwsza lista\n");
	druga_F(pom.pierwsza);
	printf("\n----------Druga lista\n");
	druga_F(pom.druga);
	printf("\n----------Trzecia lista\n");
	druga_F(pom.trzecia);
	printf("\n----------Czwarta lista\n");
	druga_F(pom.czwarta);

	
	printf("\n-----------------------------PO FUNKCJI 4--------------------------------------------\n");
	pom.pierwsza = (czwarta_F(pom.pierwsza));
	pom.druga = (czwarta_F(pom.druga));
	pom.trzecia = (czwarta_F(pom.trzecia));
	pom.czwarta = (czwarta_F(pom.czwarta));

	
	printf("\n---------------------Pierwsza lista\n");
	druga_F(pom.pierwsza);
	printf("\n---------------------Druga lista\n");
	druga_F(pom.druga);
	printf("\n---------------------Trzecia lista\n");
	druga_F(pom.trzecia);
	printf("\n---------------------Czwarta lista\n");
	druga_F(pom.czwarta);



	wyczysc(pom.pierwsza);
	wyczysc(pom.druga);
	wyczysc(pom.trzecia);
	wyczysc(pom.czwarta);

	return 0;
}