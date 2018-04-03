#include "header.h"

void E_CaesarCipher()
{
	//input module
	int length, k;
	char plaintext[1024];
	printf("please input the plain text:");
	scanf("%s", plaintext);
	printf("please input the number of k to move:");
	scanf("%d", &k);
	length = strlen(plaintext);
	//shift
	for (int p = 0; p <= length; p++)
	{
		plaintext[p] += k;
		if (plaintext[p] > 122)
			plaintext[p] = plaintext[p] - 26;
	}
	plaintext[length] = '\0';
	printf("result: %s\n", plaintext);
}

void D_CaesarCipher()
{
	//input module
	int length, k;
	char cipherText[1024];
	printf("please input the cipher text:");
	scanf("%s", cipherText);
	printf("please input the number of k:");
	scanf("%d", &k);
	length = strlen(cipherText);

	//shift
	for (int p = 0; p <= length; p++)
	{
		cipherText[p] -= k;
		if (cipherText[p] < 96)
			cipherText[p] = cipherText[p] + 26;
	}
	cipherText[length] = '\0';
	printf("result: %s\n", cipherText);
}