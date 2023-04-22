#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#pragma warning( disable : 6031 )
#pragma warning( disable : 4996 )

struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *nast;
	struct pomiar *poprz;
};

struct pompom
{
	struct pomiar* jeden;
	struct pomiar* dwa;
	struct pomiar* trzy;
	struct pomiar* cztery;
};


struct pomiar * pierwsza_F(struct pomiar *glowa, char nazwa[])
{
	_Bool czyPusty = 1; //zmienna pomocnicza do ustalenia czy plik pusty
	FILE* plik;
	plik = (fopen(nazwa, "r"));
	
	//sprawdzenie bledu odczytu
	if (plik == NULL)
	{
		printf("Blad odczytu pliku z danymi wejsciowymi");
		exit(0);
	}

	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *wsk = NULL, *pom = NULL; //pom do zapisywania poprzedniego elementu

	while (!feof(plik))
	{
		czyPusty = 0;
		//pobranie danych z pliku
		fscanf(plik, "%d%d%s%lf",
			&nr_pomiaru,
			&nr_czujnika,
			data_i_czas,
			&temp);
		//tworzenie listy dwukierunkowej
		if (glowa == NULL)
		{
			glowa = wsk = (struct pomiar*) calloc(1, sizeof(struct pomiar));
			glowa->poprz = NULL;
		}
		else
		{
			pom = wsk;
			wsk->nast = (struct pomiar*) calloc(1, sizeof(struct pomiar));
			wsk = wsk->nast;
			wsk->poprz = pom;
		}
		//wsadzenie danych z pliku do listy

		wsk->nr_pomiaru = nr_pomiaru;
		wsk->nr_czujnika = nr_czujnika;
		strcpy(wsk->data_i_czas, data_i_czas);
		wsk->temp = temp;
	}
	wsk->nast = NULL;
	fclose(plik);

	//jesli plik jest pusty
	if (czyPusty)
	{
		printf("\nPlik jest pusty.\n");
			return NULL;
	}
	return glowa;
}

void druga_F(struct pomiar *glowa)
{
	//oblicz i wypisz ile pomiarow, wypisz pierwszy , przedostatni i ostatni element
	int zlicz = 0;
	struct pomiar* pom = glowa; //pom - PRZEDostatni element
	if (pom)
		zlicz++;

	struct pomiar* pom1 = pom->nast;	//pom1 - ostatni element;
	if (pom1)
		zlicz++;

	while (pom1->nast != NULL) //szukanie konca listy
	{
		pom = pom1;
		pom1 = pom->nast;
		zlicz++;
	}
	printf("Ilosc pomiarow : %d\n", zlicz);
	printf("Pierwszy element: %d %d %s %.2lf\n",
		glowa->nr_pomiaru,
		glowa->nr_czujnika,
		glowa->data_i_czas,
		glowa->temp);

	printf("Przedostatni element: %d %d %s %.2lf\n",
		pom->nr_pomiaru,
		pom->nr_czujnika,
		pom->data_i_czas,
		pom->temp);

	printf("Ostatni element: %d %d %s %.2lf\n\n",
		pom1->nr_pomiaru,
		pom1->nr_czujnika,
		pom1->data_i_czas,
		pom1->temp);
}

struct pompom trzecia_F(struct pomiar *glowa)
{
	struct pompom wynik;

	//utworzenie 4 nowych list i null na glowy
	wynik.jeden = NULL;
	wynik.dwa = NULL;
	wynik.trzy = NULL;
	wynik.cztery = NULL;

	//zmienne pomocnicze do kopiowania danych
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;

	struct pomiar *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL,*poprz = NULL;
	while (glowa != NULL)
	{
		nr_pomiaru = glowa->nr_pomiaru;
		nr_czujnika = glowa->nr_czujnika;
		strcpy(data_i_czas, glowa->data_i_czas);
		temp = glowa->temp;
		switch (glowa->nr_czujnika)
		{
		case 1:
			if (wynik.jeden == NULL)
			{
				wynik.jeden = p1 = (struct pomiar*)calloc(1, sizeof(struct pomiar));
			}
			else
			{
				poprz = p1;
				p1->nast = (struct pomiar*)calloc(1, sizeof(struct pomiar));
				p1 = p1->nast;
				p1->poprz = poprz;
			}
				p1->nr_pomiaru = nr_pomiaru;
				p1->nr_czujnika = nr_czujnika;
				strcpy(p1->data_i_czas,data_i_czas);
				p1->temp = temp;
			
			break;
		case 2:
			if (wynik.dwa == NULL)
			{
				wynik.dwa = p2 = (struct pomiar*)calloc(1, sizeof(struct pomiar));
			}
			else
			{
				poprz = p2;
				p2->nast = (struct pomiar*)calloc(1, sizeof(struct pomiar));
				p2 = p2->nast;
				p2->poprz = poprz;
			}
				p2->nr_pomiaru = nr_pomiaru;
				p2->nr_czujnika = nr_czujnika;
				strcpy(p2->data_i_czas, data_i_czas);
				p2->temp = temp;
			
			break;
		case 3:
			if (wynik.trzy == NULL)
			{
				wynik.trzy = p3 = (struct pomiar*)calloc(1, sizeof(struct pomiar));
			}
			else
			{
				poprz = p3;
				p3->nast = (struct pomiar*)calloc(1, sizeof(struct pomiar));
				p3 = p3->nast;
				p3->poprz = poprz;
			}
				p3->nr_pomiaru = nr_pomiaru;
				p3->nr_czujnika = nr_czujnika;
				strcpy(p3->data_i_czas, data_i_czas);
				p3->temp = temp;
			
			break;
		case 4:
			if (wynik.cztery == NULL)
			{
				wynik.cztery = p4 = (struct pomiar*)calloc(1, sizeof(struct pomiar));
			}
			else
			{
				poprz = p4;
				p4->nast = (struct pomiar*)calloc(1, sizeof(struct pomiar));
				p4 = p4->nast;
				p4->poprz = poprz;
			}
				p4->nr_pomiaru = nr_pomiaru;
				p4->nr_czujnika = nr_czujnika;
				strcpy(p4->data_i_czas, data_i_czas);
				p4->temp = temp;
			
			break;
		}
		glowa = glowa->nast;
	}
	return wynik;
}

struct pomiar * czwarta_F(struct pomiar *glowa)
{

	double max = glowa->temp;
	struct pomiar*  p1 = glowa;
	double min = glowa->temp;
	struct pomiar*  p2 = glowa;
	struct pomiar*  dzban = glowa;


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

	printf("\tLinijka z najwyzsza temperatura:\n\t\t%d %d %s %.2lf\n",
		p1->nr_pomiaru,
		p1->nr_czujnika,
		p1->data_i_czas,
		p1->temp);

	printf("\tLinijka z najnizsza temperatura:\n\t\t%d %d %s %.2lf\n\n",
		p2->nr_pomiaru,
		p2->nr_czujnika,
		p2->data_i_czas,
		p2->temp);

	
	if (p1->poprz == NULL)
	{
		glowa = glowa->nast;
		glowa->poprz = NULL;
	}
	else if (p1->nast == NULL)
	{
		p1->poprz->nast = NULL;
	}
	else
	{
		p1->poprz->nast = p1->nast;
		p1->nast->poprz = p1->poprz;
	}
	free(p1);


	if ( p2->poprz == NULL)
	{
		glowa = glowa->nast;
		glowa->poprz = NULL;
	}
	else if (p2->nast == NULL)
	{
		p2->poprz->nast = NULL;
	}
	else
	{
		p2->poprz->nast = p2->nast;
		p2->nast->poprz = p2->poprz;
	}
	free(p2);

	return glowa;
}

void usunListe(struct pomiar *glowa)
{
	struct pomiar * obecny = glowa;
	struct pomiar * nast = NULL;

	while (obecny != NULL)
	{
		nast = obecny->nast;
		free(obecny);
		obecny = nast;
	}
}

int main()
{
	char plik[50] = "Dane.txt";
	struct pomiar *glowa = NULL;
	glowa=pierwsza_F(glowa, plik);
	druga_F(glowa);

	struct pompom x;
	x = trzecia_F(glowa);
	usunListe(glowa);

	printf("----------------Przed 4.\n");
	druga_F(x.jeden);
	druga_F(x.dwa);
	druga_F(x.trzy);
	druga_F(x.cztery);

	printf("Lista nr 1:\n");
	x.jeden = czwarta_F(x.jeden);
	printf("Lista nr 2:\n");
	x.dwa = czwarta_F(x.dwa);
	printf("Lista nr 3:\n");
	x.trzy = czwarta_F(x.trzy);
	printf("Lista nr 4:\n");
	x.cztery = czwarta_F(x.cztery);


	printf("----------------Po 4.\n");

	druga_F(x.jeden);
	druga_F(x.dwa);
	druga_F(x.trzy);
	druga_F(x.cztery);

	usunListe(x.jeden);
	usunListe(x.dwa);
	usunListe(x.trzy);
	usunListe(x.cztery);

	return 0;
}