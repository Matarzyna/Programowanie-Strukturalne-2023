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
void ZapiszPlik(struct pomiar *glowa, char ktora[], char nazwa[])
{
	strcat(nazwa, ktora);
	strcat(nazwa, ".txt");
	FILE *plik;
	plik = fopen(nazwa, "w+");
	if (plik == NULL)
	{
		printf("\n Nie udalo sie utworzyc pliku\n");
		exit(1);
	}
	while (glowa != NULL)
	{
		fprintf(plik,"%d %d %s %lf\n",
			glowa->nr_pomiaru,
			glowa->nr_czujnika,
			glowa->data_i_czas,
			glowa->temp);
		glowa = glowa->nast;
	}
	fclose(plik);

	for (int i = 0; i < strlen(nazwa); ++i)
	{
		if (nazwa[i] == ktora[0])
		{
			nazwa[i] = '\0';
		}
	}
}

struct pomiar * pobierzzPliku(struct pomiar *glowa, char nazwa[])
{
	FILE* plik;
	plik = (fopen(nazwa, "r"));
	if (plik == NULL)
	{
		printf("Blad odczytu pliku z danymi wejsciowymi");
		exit(1);
	}

	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *wsk = NULL, *pom = NULL;

	while (!feof(plik))
	{
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
	return glowa;
}

struct pompom rozdziel(struct pomiar *glowa, int ile[])
{
	
	struct pompom wynik;
	struct pomiar *wsk = NULL, *pom = NULL,*x=NULL;

	//nullowanie 4 glow dodatkowych list
	wynik.jeden = NULL;
	wynik.dwa = NULL;
	wynik.trzy = NULL;
	wynik.cztery = NULL;


	//:(
	while (glowa->nast!= NULL)
	{
		wsk = glowa->nast; 
		glowa->nast = NULL;
		glowa->poprz = NULL;

		switch (glowa->nr_czujnika)
		{
		case 1:
			ile[0]++;
			if (wynik.jeden == NULL)
			{
				wynik.jeden = glowa;
			}
			else
			{
				x = wynik.jeden;
				while (x->nast != NULL)
				{
					pom = x;
					x = x->nast;
				}
				x->nast = glowa;
				x->nast->poprz = pom;
			}
			break;
		case 2:
			ile[1]++;
			if (wynik.dwa == NULL)
			{
				wynik.dwa = glowa;
			}
			else
			{
				x = wynik.dwa;
				while (x->nast != NULL)
				{
					pom = x;
					x = x->nast;
				}
				x->nast = glowa;
				x->nast->poprz = pom;
			}	
			break;
		case 3:
			ile[2]++;
			if (wynik.trzy == NULL)
			{
				wynik.trzy = glowa;
			}
			else
			{
				x = wynik.trzy;
				while (x->nast != NULL)
				{
					pom = x;
					x = x->nast;
				}
				x->nast = glowa;
				x->nast->poprz = pom;
			}
			break;
		case 4:
			ile[3]++;
			if (wynik.cztery == NULL)
			{
				wynik.cztery = glowa;
			}
			else
			{
				x = wynik.cztery;
				while (x->nast != NULL)
				{
					pom = x;
					x = x->nast;
				}
				x->nast = glowa;
				x->nast->poprz = pom;
			}
			break;
		}
		
		glowa = wsk;
	}


	return wynik;
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
void maxmin(struct pomiar* glowa)
{
	double max = glowa->temp; 
	struct pomiar*  p1 = glowa;
	double min = glowa->temp;
	struct pomiar*  p2 = glowa;


	while (glowa != NULL) //szukanie minimum i maksimum
	{
		if (max < glowa->temp)
		{
			p1 = glowa; //p1 - wskaznik na max
			max = glowa->temp;
		}
		else if (min > glowa->temp)
		{
			p2 = glowa; //p2 - wskaznik na min
			min = glowa->temp;
		}
		glowa = glowa->nast;
	}

	printf("\nNajwyzsza temperatura to: %lf\nNajnizsza temperatura to :%lf", max, min);
}
int main()
{

	
	char wejscie[50] = "Dane.txt";
	/*printf("Podaj nazwe pliku z danymi wejsciowymi:\n");
	scanf("%s", wejscie, sizeof(wejscie));\*/
	
	//deklaracja glowy glownej listy z danymi
	struct pomiar * glowa=NULL;
	glowa = pobierzzPliku(glowa, wejscie);

	//4 listy na kazdy czujnik
	struct pomiar *pierwsza = NULL, *druga = NULL, *trzecia = NULL, *czwarta = NULL;
	int ile[4] = { 0 };//tablica zliczajaca ilosci pomiarow w danym z czujnikow
	struct pompom wyniki;

	//rozdzielenie glowy na 4 rozne listy w zaleznocsci od czujnika 
	wyniki = rozdziel(glowa, ile);
	pierwsza = wyniki.jeden;
	druga = wyniki.dwa;
	trzecia = wyniki.trzy;
	czwarta = wyniki.cztery;
	
	//zapis do pliku oddzielnych list
	printf("Podaj nazwe pliku do zapisu (bez .txt): ");
	char nazwa[50];
	scanf_s("%s", nazwa, sizeof(nazwa));
	ZapiszPlik(pierwsza, "1", nazwa);
	ZapiszPlik(druga, "2", nazwa);
	ZapiszPlik(trzecia, "3", nazwa);
	ZapiszPlik(czwarta, "4", nazwa);

	//wypisywanie min, max i ilosci elementow w listach
	printf("\nLista nr 1:\n%d elementow",ile[0]);
	maxmin(pierwsza);
	putchar('\n');

	printf("\nLista nr 2:\n%d elementow", ile[1]);
	maxmin(druga);
	putchar('\n');

	printf("\nLista nr 3:\n%d elementow", ile[2]);
	maxmin(trzecia);
	putchar('\n');

	printf("\nLista nr 4:\n%d elementow", ile[3]);
	maxmin(czwarta);

	//usuwanie list
	usunListe(pierwsza);
	usunListe(druga);
	usunListe(trzecia);
	usunListe(czwarta);




	return 0;
}