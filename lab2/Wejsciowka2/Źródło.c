#include <stdio.h>
#include <string.h>
#define max 50


void fillA(char A[][5])
{
	int count = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			A[j][i] = 'a' + count;

			if (A[j][i] == 'q')
			{
				A[j][i]++; count++;
			}
			count++;
		}
	}
}

void read(char A[][5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			printf_s("%c ", A[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
	return;
}

char* findAddress(char x, char A[][5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < max; ++j)
		{
			if (A[i][j] == x)
				return &A[i][j];
		}
	}
	return NULL;
}

void fillB(char* B[], char C[], char A[][5])
{
	for (int i = 0; i < max; ++i)
	{
		if (C[i] == '\n')
		{
			B[i] = NULL;
			return;
		}
		B[i] = findAddress(C[i], A);
	}
}

void readBP(char* B[])
{
	int i = 0;
	while (B[i] != NULL)
	{
		printf("%c", *B[i]);
		i++;
	}
	putchar('\n');
}


void changeRows1(char A[][5])
{
	char temp1, temp2;
	for (int i = 0; i < 5; ++i) //1z4
	{
		temp1 = A[0][i]; //0z4
		A[0][i] = A[4][i];
		temp2 = A[1][i];
		A[1][i] = temp1;
		temp1 = A[2][i];
		A[2][i] = temp2;
		temp2 = A[3][i];
		A[3][i] = temp1;
		A[4][i] = temp2;
	}
}

void changeRows2(char A[][5])
{
	char temp1, temp2;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 5; ++i)
		{
			temp1 = A[0][i];
			A[0][i] = A[4][i];
			temp2 = A[1][i];
			A[1][i] = temp1;
			temp1 = A[2][i];
			A[2][i] = temp2;
			temp2 = A[3][i];
			A[3][i] = temp1;
			A[4][i] = temp2;
		}
}
void fillC(char** C[], char* B[], char A[][5])
{
	int count = 0;//printf("%d ", count);
	int spol = 0;
	for (int i = 0; i < max; ++i)
	{
		if (B[i] != NULL)
		{
			if (*B[i] == 'a' || *B[i] == 'e' || *B[i] == 'i' || *B[i] == 'o' || *B[i] == 'u' || *B[i] == 'y')
			{
				//printf("%c", *B[i]);
				count++;
			}
			else spol++;
		}
	}
	//printf(" ilosc samoglosek: %d\n", count);
	//printf(" ilosc spolglosek: %d\n", spol);
	spol = count;
	for (int i = 0;B[i] != NULL; ++i) // spisanie samoglosek
	{
		
		
		if ((*B[i] == 'a' || *B[i] == 'e' || *B[i] == 'i' || *B[i] == 'o' || *B[i] == 'u' || *B[i] == 'y') && count != 0)
		{
			C[i] = &B[i];

			count--;
			printf("%c", **C[i]);
				//printf("%d\n", count);
		}
		

	}

	for (int i = 0; B[i] != NULL; ++i) //sprawdzanie spolglosek
	{
		if (*B[i] != 'a' && *B[i] != 'e' && *B[i] != 'i' && *B[i] != 'o' && *B[i] != 'u' && *B[i] != 'y')
		{
			C[i + spol] = &B[i];
			//printf("%c", *B[i]);
			printf("%c", **C[i + spol]);
		}
	}
	for (int i = 0; ; ++i)
	{
		if (B[i] == NULL)
		{
			C[i] = NULL;
			return;
		}
	}

}
int main()
{
	char A[5][5];
	char* B[max] = { NULL };
	char T[max];
	char** C[max] = { NULL };

	fillA(A);
	read(A);

	scanf_s("%s", &T, max);
	fillB(B, T, A);

	//readBP(B);

	//changeRows1(A);
	//read(A);
	//readBP(B);

	//changeRows2(A);
	//read(A);
	//readBP(B);

	fillC(C, B, A);

	return 0;
}












