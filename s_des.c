#include "header.h"

void s_des_encryption(char subplain1[5], char subplain2[5], char key[9]);
void s_des()
{
	char key[11];		   //input key
	char tempkey[11];	  //store key
	char subkey1[9];	   //subkey k1
	char subkey2[9];	   //subkey k2
	char plaintext[9];	 //input plaintext
	char ciphertext[9];	//output ciphertext

	printf("please input the 8-bits plaintext:");
	scanf("%s", plaintext);
	printf("please input the 10-bits key:");
	scanf("%s", key);
	int p10[10] = { 3, 5, 2, 7, 4, 10, 1, 9, 8, 6 };
	int p8[8] = { 6, 3, 7, 4, 8, 5, 10, 9 };
	int IP[8] = { 2, 6, 3, 1, 4, 8, 5, 7 };
	char subplain1[5]; //plaintext after IP op and cut into two parts.
	char subplain2[5];
	char Tempplain1[5]; // right part of encryption output
	char Tempplain2[5]; // left part of encryption output


	for (int a = 0; a < 10; a++)
		tempkey[a] = key[(p10[a] - 1)];

	int b = 1;
	int c = 6;
	for (int a = 0; a < 5; a++)
	{
		key[a] = tempkey[b];
		key[a + 5] = tempkey[c];
		b++;
		c++;
		if (b > 4)
			b = 0;
		if (c > 9)
			c = 5;
	}
	for (int a = 0; a < 10; a++)
		tempkey[a] = key[a];

	for (int a = 0; a < 8; a++)
		subkey1[a] = key[(p8[a] - 1)];

	b = 2;
	c = 7;
	for (int a = 0; a < 5; a++)
	{
		key[a] = tempkey[b];
		key[a + 5] = tempkey[c];
		b++;
		c++;
		if (b > 4)
			b = 0;
		if (c > 9)
			c = 5;
	}
	for (int a = 0; a < 8; a++)
		subkey2[a] = key[(p8[a] - 1)];

	subkey1[8] = '\0';
	subkey2[8] = '\0';
	printf("k1: %s\n", subkey1);
	printf("k2: %s\n", subkey2);

	for (int a = 0; a < 8; a++)
		if (a > 3)
		{
			subplain2[a - 4] = plaintext[(IP[a] - 1)];
			Tempplain2[a - 4] = plaintext[(IP[a] - 1)];
		}
		else
		{
			subplain1[a] = plaintext[(IP[a] - 1)];
			Tempplain1[a] = plaintext[(IP[a] - 1)];
		}

	subplain1[4] = '\0';
	subplain2[4] = '\0';
	Tempplain1[4] = '\0'; //use for (ip-1),right output
	Tempplain2[4] = '\0'; //use for (ip-1),left output
	s_des_encryption(subplain1, subplain2, subkey1);
	for (int a = 0; a < 4; a++)
		Tempplain1[a] = subplain1[a];

	s_des_encryption(Tempplain2, subplain1, subkey2);

	for (int a = 0; a < 8; a++)
		if (a > 3)
			ciphertext[(IP[a] - 1)] = Tempplain1[a - 4];
		else
			ciphertext[(IP[a] - 1)] = Tempplain2[a];

	ciphertext[8] = '\0';
	printf("cipher: %s\n", ciphertext);

}

void s_des_encryption(char subplain1[5], char subplain2[5], char key[9])
{
	int p4[4] = { 2, 4, 3, 1 };
	int EP[8] = { 4, 1, 2, 3, 2, 3, 4, 1 };
	int IP[8] = { 2, 6, 3, 1, 4, 8, 5, 7 };
	char s0[4][4][2] = { {"01", "00", "11", "10"}, {"11", "10", "01", "00"}, {"00", "10", "01", "11"}, {"11", "01", "11", "10"} };
	char s1[4][4][2] = { {"00", "01", "10", "11"}, {"10", "00", "01", "11"}, {"11", "00", "01", "00"}, {"10", "01", "00", "11"} };
	char EPText[9], EPFront[5], EPEnd[5], p4Text[5];
	for (int a = 0; a < 8; a++)
		EPText[a] = subplain2[(EP[a] - 1)];

	EPText[8] = '\0';
	printf("EPText:%s\n", EPText);
	for (int a = 0; a < 8; a++)
		if (a > 3)
			(EPText[a] ^ key[a]) ? (EPEnd[a - 4] = '1') : (EPEnd[a - 4] = '0');
		else
			(EPText[a] ^ key[a]) ? (EPFront[a] = '1') : (EPFront[a] = '0');

	EPFront[4] = '\0';
	EPEnd[4] = '\0';
	printf("EP ^/ key1:%s%s\n", EPFront, EPEnd);
	//s0
	int row, column;
	if (EPFront[0] ^ EPFront[3])
		(EPFront[0] == '1') ? (row = 2) : (row = 1);
	else
		(EPFront[0] == '1') ? (row = 3) : (row = 0);

	if (EPFront[1] ^ EPFront[2])
		(EPFront[1] == '1') ? (column = 2) : (column = 1);
	else
		(EPFront[1] == '1') ? (column = 3) : (column = 0);

	p4Text[0] = s0[row][column][0];
	p4Text[1] = s0[row][column][1];
	//s1
	if (EPEnd[0] ^ EPEnd[3])
		(EPEnd[0] == '1') ? (row = 2) : (row = 1);
	else
		(EPEnd[0] == '1') ? (row = 3) : (row = 0);

	if (EPEnd[1] ^ EPEnd[2])
		(EPEnd[1] == '1') ? (column = 2) : (column = 1);
	else
		(EPEnd[1] == '1') ? (column = 3) : (column = 0);

	p4Text[2] = s1[row][column][0];
	p4Text[3] = s1[row][column][1];
	p4Text[4] = '\0';
	printf("s0s1:%s\n", p4Text);
	for (int a = 0; a < 4; a++)
		subplain2[a] = p4Text[(p4[a] - 1)];

	for (int a = 0; a < 4; a++)
		(subplain2[a] ^ subplain1[a]) ? (subplain1[a] = '1') : (subplain1[a] = '0');
}