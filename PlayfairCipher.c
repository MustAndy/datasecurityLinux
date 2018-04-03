#include"header.h"


void PlayfairCipher()
{
	char alphabet[25] = "abcdefghiklmnopqrstuvwxyz";
	int numState[25] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char matrix[5][5];
	//input module

	//int PlainLength;
	//printf("please input the length of the plaintext:");
	//scanf("%d", &PlainLength);
	//char *plaintext = malloc(PlainLength + 1);
	//printf("please input the plaintext:");
	//scanf("%s", plaintext);

	//int KeyLength;
	//printf("please input the length of the key:");
	//scanf("%d", &KeyLength);
	//char *key = malloc(KeyLength + 1);
	//printf("please input the key:");
	//scanf("%s", key);

	char plaintext[1024];
	printf("please input the plaintext:");
	scanf("%s", plaintext);
	int PlainLength;
	PlainLength = strlen(plaintext);
	plaintext[PlainLength] = '\0';

	char key[1024];
	printf("please input the key:");
	scanf("%s", key);
	int KeyLength;
	KeyLength = strlen(key);

	int RowCounter = 0;
	int ColoumCounter = 0;
	//handle keyword
	for (int a = 0; a < KeyLength; a++)
	{
		if (key[a] == 'j')
			key[a] = 'i';
	}
	printf("The key after handling is :%s\n", key);

	//handle plaintext
	int HandlePlainLength = 0;
	for (int a = 0; a < PlainLength; a++)
	{
		if (plaintext[a] == plaintext[a + 1])
			HandlePlainLength++;
		if (plaintext[a] == 'j')
			plaintext[a] = 'i';
	}
	HandlePlainLength += PlainLength;

	char *HandlePlainText = malloc(HandlePlainLength);
	int HandlePlainCounter = 0;
	for (int a = 0; a < PlainLength; a++)
	{
		if (plaintext[a] == plaintext[a + 1])
		{
			HandlePlainText[HandlePlainCounter] = plaintext[a];
			HandlePlainCounter += 1;
			HandlePlainText[HandlePlainCounter] = 'x';
			HandlePlainCounter += 1;
		}
		else
		{
			HandlePlainText[HandlePlainCounter] = plaintext[a];
			HandlePlainCounter += 1;
		}
	}
	if ((HandlePlainLength % 2) != 0)
	{
		HandlePlainLength += 1;
		HandlePlainText[HandlePlainCounter] = 'x';
		HandlePlainText[HandlePlainCounter + 1] = '\0';
	}
	else
		HandlePlainText[HandlePlainCounter] = '\0';

	printf("The plaintext after handling is :%s\n", HandlePlainText);

	//put keyword into matrix
	for (int a = 0; a < KeyLength; a++)
	{
		for (int b = 0; b < 26; b++)
		{
			if (key[a] == alphabet[b])
			{
				if (numState[b] == 0)
				{
					matrix[RowCounter][ColoumCounter] = alphabet[b];
					numState[b] = 1;
					ColoumCounter += 1;
					if (RowCounter >= 5)
						RowCounter -= 5;
					else if (ColoumCounter >= 5)
					{
						ColoumCounter -= 5;
						RowCounter += 1;
					}
				}
			}
		}
	}
	//full the matrix with lefted alphabet
	for (int b = 0; b < 26; b++)
	{
		if (numState[b] == 0)
		{
			matrix[RowCounter][ColoumCounter] = alphabet[b];
			numState[b] = 1;
			ColoumCounter += 1;
			if (RowCounter >= 5)
				RowCounter -= 5;
			else if (ColoumCounter >= 5)
			{
				ColoumCounter -= 5;
				RowCounter += 1;
			}
		}
	}
	//handle Encryption
	int ARow, BRow, AColumn, BColumn;
	for (int a = 0; a < HandlePlainLength; a += 2)
	{
		for (int b = 0; b < 5; b++)
		{
			for (int c = 0; c < 5; c++)
			{
				if (HandlePlainText[a] == matrix[b][c])
				{
					ARow = b;
					AColumn = c;
				}
				else if (HandlePlainText[a + 1] == matrix[b][c])
				{
					BRow = b;
					BColumn = c;
				}
			}
		}
		if (ARow == BRow)
		{
			HandlePlainText[a] = matrix[ARow][((AColumn + 1) >= 5) ? (AColumn + 1 - 5) : (AColumn + 1)];
			HandlePlainText[a + 1] = matrix[BRow][((BColumn + 1) >= 5) ? (BColumn + 1 - 5) : (BColumn + 1)];
		}
		else if (AColumn == BColumn)
		{
			HandlePlainText[a] = matrix[((ARow + 1) >= 5) ? (ARow + 1 - 5) : (ARow + 1)][AColumn];
			HandlePlainText[a + 1] = matrix[((BRow + 1) >= 5) ? (BRow + 1 - 5) : (BRow + 1)][BColumn];
		}
		else
		{
			HandlePlainText[a] = matrix[ARow][BColumn];
			HandlePlainText[a + 1] = matrix[BRow][AColumn];
		}
	}
	//print martrix
	printf("\nThe forming martrix is as follow: \n");
	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 5; b++)
			printf("%c ", matrix[a][b]);
		printf("\n");
	}

	//print result
	HandlePlainText[HandlePlainLength] = '\0';
	printf("\nThe encrption result is: %s\n", HandlePlainText);
}