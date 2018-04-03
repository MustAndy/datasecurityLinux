#include "header.h"

void vigenereCipher()
{
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
	//input module

	//int length;
	//printf("please input the length of the input:");
	//scanf("%d", &length);
	//int templen = length + 1;

	//char *plaintext = malloc(templen);
	//char *key = malloc(templen);
	//printf("please input the plaintext:");
	//scanf("%s", plaintext);
	//printf("please input the key:");
	//scanf("%s", key);

	//plaintext[length] = '\0';
	//key[length] = '\0';

	char plaintext[1024];
	printf("please input the plaintext:");
	scanf("%s", plaintext);
	int length;
	length = strlen(plaintext);
	plaintext[length] = '\0';

	char key[1024];
	printf("please input the %d bytes key:", length);
	scanf("%s", key);

	plaintext[length] = '\0';
	key[length] = '\0';

	int *plaintextNum = malloc(length - 1);
	int *keynum = malloc(length - 1);
	char *result = malloc(length);

	//calculate the corresponding number.
	for (int a = 0; a < length; a++)
	{
		for (int b = 0; b < 26; b++)
		{
			if (plaintext[a] == alphabet[b])
			{
				plaintextNum[a] = b;
			}
			if (key[a] == alphabet[b])
			{
				keynum[a] = b;
			}
		}
	}

	//Contrast alphabet
	int temp;
	for (int a = 0; a < length; a++)
	{
		temp = (plaintextNum[a] + keynum[a]) % 26;

		result[a] = alphabet[temp];
	}
	result[length] = '\0';
	printf("Result: %s\n", result);
}