#include "header.h"

void s_RC4()
{

	char plaintext[512];
	printf("please input the plaintext:(less than 8 bytes)");
	scanf("%s", plaintext);
	int PlainLength = strlen(plaintext);
	int *plainnum = malloc(PlainLength + 1);
	plaintext[PlainLength] = '\0';
	for (int a = 0; a < PlainLength; a++)
		plainnum[a] = plaintext[a] - '0';

	printf("please input the 4-bits' keys:");
	char keyChar[5];
	scanf("%s", keyChar);
	keyChar[4] = '\0';
	int keyInt[4];
	for (int a = 0; a < 4; a++)
		keyInt[a] = keyChar[a] - '0';


	//init 
	int S[8];
	int T[8];
	int Temp[8];
	int *Cipher = malloc(PlainLength + 1);
	for (int i = 0; i < 8; i++)
	{
		S[i] = i;
		T[i] = keyInt[i % 4];
	}

	//step2
	int j = 0;
	for (int i = 0; i < 8; i++)
	{
		j = (j + S[i] + T[i]) % 8;
		int temp = S[i];
		S[i] = S[j];
		S[j] = temp;
		/*	for (int o = 0; o < 8; o++)
				printf("%d", S[o]);
			printf("\n");*/
	}


	//step3
	j = 0; int i = 0, t = 0;
	for (int o = 0; o < PlainLength; o++)
	{
		i = (i + 1) % 8;
		j = (j + S[i]) % 8;
		//printf("i = %d,j = %d\n", i, j);
		int temp = S[i];
		S[i] = S[j];
		S[j] = temp;
		t = (S[i] + S[j]) % 8;
		//printf("t = %d,S[t] = %d\n", t, S[t]);
		Temp[o] = S[t];
	}

	//result
	printf("result:");
	for (int o = 0; o < PlainLength; o++)
	{
		Cipher[o] = Temp[o] ^ plainnum[o];
		printf("%d", Cipher[o]);
	}
	printf("\n");
}