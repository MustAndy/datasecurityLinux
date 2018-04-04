#include "header.h"

void encrpt(int row, int column, int PlainLength, char *matrix[], char plaintext[], int KeyLength, int keyInt[]);

void Cols_Rows_Transposition()
{

	//int PlainLength;
	//printf("please input the length of the plaintext:");
	//scanf("%d", &PlainLength);
	//char *plaintext = malloc(PlainLength + 1);
	//printf("please input the plaintext:");
	//scanf("%s", plaintext);


	//int KeyLength;
	//printf("please input the length of the key:");
	//scanf("%d", &KeyLength);
	//
	//char *keyChar = malloc(KeyLength + 1);
	//printf("please input the key:");
	//scanf("%s", keyChar);


		//input module
	char plaintext[1024];
	printf("please input the plaintext:");
	scanf("%s", plaintext);
	int PlainLength;
	PlainLength = strlen(plaintext);
	plaintext[PlainLength] = '\0';

	char keyChar[10];
	printf("please input the key which is under 10 byte:");
	scanf("%s", keyChar);
	int KeyLength;
	KeyLength = strlen(keyChar);
	int *keyInt = malloc(KeyLength + 1);

	int round;
	printf("please input the number of rounds:");
	scanf("%d", &round);

	for (int a = 0; a < KeyLength; a++)
		keyInt[a] = keyChar[a] - '0';

	char **matrix;//matrix[row][column];
	int column = KeyLength;
	int row = (PlainLength / KeyLength) + 1;

	// dynamic memory apply for matrix
	matrix = (char **)malloc(sizeof(char *)*row);
	for (int a = 0; a < row; a++)
		*(matrix + a) = (char *)malloc(sizeof(char)*column);

	for (int c = 0; c < round; c++)
		encrpt(row, column, PlainLength, matrix, plaintext, KeyLength, keyInt);


	plaintext[PlainLength] = '\0';
	printf("Result: %s\n", plaintext);

}

void encrpt(int row, int column, int PlainLength, char *matrix[], char plaintext[], int KeyLength, int keyInt[])
{
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < column; b++)
		{
			if ((a*(column)+b) >= PlainLength)
				matrix[a][b] = '\0';
			else
				matrix[a][b] = plaintext[a*(column)+b];
			//printf("%c ", matrix[a][b]);//for test matrix
		}
		//printf("\n"); //for test matrix
	}


	int counter = 0; int c = 0;
	for (int a = 0; a < column; a++)
	{
		for (c = 0; c < KeyLength; c++)
		{
			if ((keyInt[c] - 1) == a)
				break;
		}
		for (int b = 0; b < row; b++)
		{
			if (matrix[b][c] == '\0')
				continue;
			else
			{
				plaintext[counter] = matrix[b][c];
				counter++;
			}
		}
	}
	plaintext[PlainLength] = '\0';
}