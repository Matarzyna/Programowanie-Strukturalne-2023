#include <stdio.h>
#include <string.h>
#include <math.h>
#define size 2


struct tr_t
{
	char czy_da_sie;
	int  ktory;
	double pole;
};

struct pom_t
{
	char da_sie;
	double p;
};

typedef struct tr_t tr_t;
typedef struct pom_t pom_t;

//int ile(struct s_t tab[])
//{
//	int ilosc = 0;
//	for (int i = 0; i < size; ++i)
//	{
//		if (strlen(tab[i].napis) > tab[i].n)
//		{
//			ilosc++;
//			for(int j= tab[i].n;j< strlen(tab[i].napis);++j)
//				tab[i].napis[j] = '\0';
//			
//			
//		}
//	}
//	return ilosc;
//}

tr_t najmniejszy_troj(pom_t t[])
{
	char cos;
	int gdzie = 0;
	double min = t[0].p;
	for (int i = 1; i < size; ++i)
	{
		if ((t[i].p < min) && (t[i].p != -1))
		{
			cos = 't';
			min = t[i].p;
			gdzie = i;
		}
		else
			cos = 'n';
	}
	tr_t wynik = {cos,gdzie,min};
	return wynik;
}
double policz_pole(double a, double b, double c)
{
	double p = (a + b + c) / 2;
	return (sqrt(p*(p - a)*(p - b)*(p - c)));
}
void wyp_pom(pom_t t[], float tab[][3])
{
	for (int i = 0; i < size; ++i)
	{
		if ((tab[i][0] + tab[i][1] < tab[i][2]) && (tab[i][1] + tab[i][2] < tab[i][0]) && (tab[i][2] + tab[i][0] < tab[i][1]))
		{
			t[i].da_sie = 't';
			t[i].p = policz_pole(tab[i][0], tab[i][1], tab[i][2]);
		}
		else t[i].da_sie = 'n';
	}
}

int main()
{
	
	tr_t x;
	float tab[size][3];
	pom_t t[size];
	//wpisywanie do tablicy
	for (int i = 0; i < size; ++i) 
	{
		printf("Podaj 1. bok %d. trojkata:\n", i + 1);
		scanf_s("%f", tab[i][0]);

		printf("Podaj 2. bok %d. trojkata:\n", i + 1);
		scanf_s("%f", tab[i][1]);

		printf("Podaj 3. bok %d. trojkata:\n", i + 1);
		scanf_s("%f", tab[i][2]);
		t[i].p = -1;
	}

	wyp_pom(t, tab);
	x = najmniejszy_troj(t);
	if (x.czy_da_sie == 'n')
	{
		printf("Nie da sie zbudowac zadnego trojkata");
		return 0;
	}
	else
		printf("Najmniejszy trojkat znajduje sie w %d kolumnie ma pole %f\n", x.ktory, x.pole);
	return 0;

	//wypisywanie tablicy
	/*for (int i = 0; i < size; ++i) 
	{
		printf("%d. napis:", i + 1);
		printf("%s \n", tab[i].napis);
		printf("%d. liczba:", i + 1);
		printf("%d\n\n", tab[i].n);
	}*/
	return 0;
}