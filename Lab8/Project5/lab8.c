#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h> 
#include <limits.h>

#define errno   (*_errno())
#define dlugosc 200



#pragma warning( disable : 6031 )
#pragma warning( disable : 4996 )

void zapisz_czas(FILE* plik)
{
	time_t curr = time(NULL);
	struct tm tm = *localtime(&curr);
	char buf[64];
	strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", &tm);
	fprintf(plik, "%s\t", buf);

}

int runda(void)
{
	char alfabet[] = "abcdefghijklmnoprqstuvwxyz";
	
		int losowa = rand() % 26;
		int druga = rand() % 26;
		char litera = '\0';
		while ((losowa == druga) || (abs(losowa - druga) < 2))
		{
			druga = rand() % 26;
		}
		while (getchar() != '\n');
		if (losowa < druga)
		{
			printf("\nPodaj litere z przedzialu ( %c  - %c ):\n", alfabet[losowa], alfabet[druga]);
			scanf_s("%c", &litera, 1);
			if (litera < alfabet[losowa] || litera > alfabet[druga])
			{
				return 0;
			}
		}
		else
		{
			printf("\nPodaj litere z przedzialu ( %c  - %c ):\n",  alfabet[druga], alfabet[losowa] );
			scanf_s("%c", &litera, 1);
			if (litera > alfabet[losowa] || litera < alfabet[druga])
			{
				return 0;
			}
		}
	return 1;
}



int main(int argc, char* argv[])
{
	//ustawienie srand
	srand((unsigned)time(NULL));

	char *strerror(int errnum);	int powtorz = 1;	
//(u)otworzenie log 
		FILE* log;
		log = fopen("log.txt", "a");

		if (log == NULL) {

			log = freopen("log.txt", "a+", stderr);
			fprintf(log, "B³¹d otwarcia pliku log.txt\n");

			if (log == NULL) {
				printf("Nie uda³o siê otworzyæ pliku log.txt");
				return 1;
			}
		}
	

//wpis w log 
		fprintf(log, "\n");
		zapisz_czas(log);
		fprintf(log, "Uruchomienie programu\n");
		
	
		do {
//pobranie nicku
		char nick[dlugosc] = { '\0' };
		char nazwa[dlugosc] = { "gra-" };

		printf("Podaj swoj nick: ");
		scanf_s("%s", nick, dlugosc);
	
//pobranie liczby rund
		int liczba;
		printf("Podaj ile rund chcesz zagrac: ");
		while (getchar() != '\n');
		scanf_s("%d", &liczba);

	//utworzenie pliku gra-nick.txt
		FILE* plik;

		strcat(nazwa, nick);
		strcat(nazwa, ".txt");

		zapisz_czas(log);
		fprintf(log, "Rozpoczecie gry, gracz: %s\n", nick);

		plik = fopen(nazwa, "a+");
		if (errno)
		{
			
			freopen("log.txt", "a+", stderr);
			
			zapisz_czas(stderr);
			fprintf(stderr, "pliku %s nie udalo sie otworzyc\n", nazwa);

			zapisz_czas(stderr);
			fprintf(stderr, "Koniec dzialania programu\n");

			fclose(log);
			exit(0);
		}
	//poczatek gry
		int wynik;
		
		
		for (int i = 0; i < liczba; ++i)
		{
			wynik = runda();
			fprintf(plik, "%d\n", wynik);
		}
		fclose(plik);
	//koniec gry
		zapisz_czas(log);
		fprintf(log, "Koniec gry\n");

		printf("\nJesli chcesz grac dalej kliknij 1, aby zamknac gre kliknij 0 \n");
		while (getchar() != '\n');
		scanf_s("%d", &powtorz);

	
		
	} while (powtorz);
	zapisz_czas(log);
	fprintf(log, "Koniec programu\n\n");
	fclose(log);
		
	return 0;
}