#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define errno   (*_errno())
#define dlugosc 200

#pragma warning( disable : 6031 )
#pragma warning( disable : 4996 )

void zapisz_czas(FILE* plik)
{
	time_t curr;
	struct tm *newtime;
	time(&curr);
	newtime = localtime(&curr);
	fprintf(plik, "%s\t", asctime(newtime));
}


int main(int argc, char* argv[])
{
	char *strerror(int errnum);
	time_t poczatek, koniec;
	FILE* log;
	log = fopen("log.txt", "r");
	if (!log)
	{
		log = fopen("log.txt", "w+");
	}
	else
	{
		fclose(log);
		log = fopen("log.txt", "a+");
	}
	if (errno)
	{
		perror("Blad otwarcia pliku" );
	}
	fprintf(log, "Uruchomienie programu: ");
	zapisz_czas(log);
	fprintf(log, "\n");
	srand((unsigned)time(NULL));

	
	char nick[dlugosc] = { '\0' };
	char nazwa[dlugosc] = { '\0' };
	printf("Podaj swoj nick:");
	zapisz_czas(log);
	fprintf(log,"Podaj swoj nick: ");

	scanf_s("%s", nick, dlugosc);
	fprintf(log, "%s\n",nick);

	printf("Podaj liczbe z zakresu (0,10):");
	zapisz_czas(log);
	fprintf(log,"Podaj liczbe z zakresu (0,10): ");
	int liczba;

	assert(scanf_s("%d", &liczba));
	assert(liczba < 10);
	assert(liczba > 0);
	while (getchar() != '\n');
	
	fprintf(log, "%d\n", liczba);
	char alfabet[] = "abcdefghijklmnoprqstuvwxyz";

	int losowa = 0;
	int trafienia = 0;
	printf("Kliknij podana litere w jak najszybszym czasie\n");
	zapisz_czas(log);
	fprintf(log, "Kliknij podana litere w jak najszybszym czasie\n");

	poczatek = time(NULL);
	
	for (int i = 0; i < liczba; ++i)
	{
		char c;
		losowa = rand() % 26;
		printf("%d. litera: %c\t", i + 1, alfabet[losowa]);
		zapisz_czas(log);
		fprintf(log, "%d. litera: %c\t", i + 1, alfabet[losowa]);
		if ((c = getchar()) == alfabet[losowa])
		{
			zapisz_czas(log);
			fprintf(log, "Nacisnieto klawisz: %c\t", c);
			printf("Trafiony!\n");
			fprintf(log,"Trafiony!\n");
			trafienia++;
		}
		else
		{
			zapisz_czas(log);
			printf("Nietrafiony!\n");
			fprintf(log,"Nietrafiony!\t");
		}

		while (getchar() != '\n');

	}
	koniec = time(NULL);
	double ile = difftime( koniec, poczatek);
	//printf("CZAS REAKCJI : %.2lf\n", ile);
	
	
	FILE* plik;

	strcpy(nazwa, nick);
	strcat(nazwa, ".txt");

	plik = fopen(nazwa, "r");
	if (plik == NULL)
	{

		plik = fopen(nazwa, "w+");
		printf("Tworze plik o nazwie %s w folderze:\n %s\n", nazwa, argv[0]);
		zapisz_czas(log);
		fprintf(log,"Tworze plik o nazwie %s w folderze:\n %s\n", nazwa, argv[0]);
		fprintf(plik, "Liczba trafien:  Czas: \n");

	}
	else
	{
		zapisz_czas(log);
		fclose(plik);
		plik = fopen(nazwa, "a");
		printf("\nDopisuje wyniki do istniejacego pliku\n");
		fprintf(log,"\nDopisuje wyniki do istniejacego pliku\n");
	}
	if (errno)
	{
		perror("Blad otwarcia pliku");
	}
	zapisz_czas(log);
	fprintf(plik, " %d \t\t%.1lf\n", trafienia, ile);
	fprintf(log, " %d \t\t%.1lf\n", trafienia, ile);
	

	fprintf(log, "Zamkniecie programu: ");
	zapisz_czas(log);
	fprintf(log, "\n\n");
	fclose(log);
	fclose(plik);
	return 0;
}