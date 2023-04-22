#include <stdio.h>

#define size 5
#define len 20

#pragma warning(disable : 4996)

struct para {
	char sname[len];
	int grade;
};

typedef struct para para;

para wiersz(FILE* f, para *p){


}

int main() {
	FILE* plik;
	if ((plik = fopen("przyklad.txt", "r")) == NULL)
	{
		printf("blad odczytu");
		return 0;
	}

	para tab[size];

	fclose(plik);
	return 0;
}

