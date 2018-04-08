#include "header.h"
#include "des.h"

uint64_t des_encryption();
Boolean DesPrinting;
void binaryOutput(long int n, int bitsNum, char name[])
{
	printf("%20s: ", name);
	for (int i = bitsNum; i > 0; i--)
	{
		long int temp = (n >> (i - 1)) & 0x0000000000000001;
		if (temp == 1)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}
void des()
{
	printf("Press 0 only print result, press 1 print every step of encryp:");
	scanf("%d", &DesPrinting);
	uint64_t input = 0x0123456789ABCDEF;
	uint64_t key = 0x133457799BBCDFF1;
	uint64_t result;
	//uint64_t result = input;
	/*printf("please input the 64 bits plaintext in hexadecimal: ");
	scanf("%llX", &input);
	printf("please input the 64 bits key in hexadecimal: ");
	scanf("%llX", &key);
	printf("%llX\n", input);
	printf("%llX\n", key);*/

	result = des_encryption(input, key);
	if (DesPrinting)
		binaryOutput(result, 64, "result");
	printf("%9cCipher Text: %016lX\n",' ', result);
}

uint64_t des_encryption(uint64_t input, uint64_t key)
{
	//Key generate
	printf("\nGenerating the key for every loop of des...\n\n");
	uint64_t IPResult = 0;  //64-bits
	uint64_t PC1Result = 0; //56-bits
	uint64_t C_joint_D = 0; //56-bits
	uint64_t C = 0;			//28-bits
	uint64_t D = 0;			//28-bits
	uint64_t subKey[16];	//the subkey array for 16 subkey.

	//get every bits of key and do the Peruted_choice_one
	for (int i = 0; i < 56; i++)
	{
		PC1Result <<= 1;
		PC1Result |= (key >> (64 - PC_1[i])) & 1;
	}
	// left hand side of the key
	C = ((PC1Result >> 28) & 0x000000000fffffff);
	// right hand side of the key
	D = (PC1Result & 0x000000000fffffff);
	if (DesPrinting)
	{
		binaryOutput(C, 28, "C");
		binaryOutput(D, 28, "D");
	}
	//form 16  48-bits subkey
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < schedule_of_left_shifts[i]; j++)
		{
			//shift 1-bits left, use the |& to let it form a shift loop.
			C = (0x0fffffff & (C << 1)) | ((0x00000001) & (C >> 27));
			D = (0x0fffffff & (D << 1)) | ((0x00000001) & (D >> 27));
		}
		C_joint_D = 0;
		C_joint_D = ((C << 28) | (D));

		subKey[i] = 0;
		for (int j = 0; j < 48; j++)
		{
			subKey[i] <<= 1;
			subKey[i] |= (C_joint_D >> (56 - PC_2[j])) & 1;
		}
		if (DesPrinting)
		{
			binaryOutput(C, 28, "C");
			binaryOutput(D, 28, "D");
			binaryOutput(subKey[i], 48, "Subkey:");
		}
	}

	printf("\nApplying the key for every loop of encrpt...\n\n");
	uint64_t L = 0;			  //32-bits
	uint64_t R = 0;			  //32-bits
	uint64_t EResult = 0;	 //48-bits
	uint32_t S_BoxResult = 0; //32-bits
	uint32_t PResult = 0;	 //32-bits
	uint64_t TempResiger = 0; //Templt store the variable.
	//get every bits of plaintext and do the initial_message_permutation
	for (int i = 0; i < 64; i++)
	{
		IPResult <<= 1;
		IPResult |= (input >> (64 - IP[i])) & 0x01;
	}
	// left hand side of the plaintext;
	L = (IPResult >> 32) & 0x00000000ffffffff;
	// right hand side of the plaintext;
	R = IPResult & 0x00000000ffffffff;

	for (int i = 0; i < 16; i++)
	{
		//apply e-table
		for (int j = 0; j < 48; j++)
		{
			EResult <<= 1;
			EResult |= (R >> (32 - E_Table[j])) & 1;
		}
		//XOR with the subkey.
		EResult = EResult ^ subKey[i];
		if (DesPrinting)
			binaryOutput(EResult, 48, "EResult");
		//S-BOX
		char row, column;

		for (int j = 7; j >= 0; j--)
		{
			row = ((EResult >> (6 * j)) & (0x84 >> 2));
			//normalize the row into 0-3
			row = (row > 1) ? (row - 30) : (row);

			column = (((EResult >> (6 * j)) & (0x1E)) >> 1);

			//row = 0 - 3
			//column = 0 - F
			S_BoxResult <<= 4;
			S_BoxResult |= (S_box[7 - j][16 * row + column] & 0x0f);
		}
		if (DesPrinting)
			binaryOutput(S_BoxResult, 32, "S-box result");

		//permutation
		for (int j = 0; j < 32; j++)
		{
			PResult <<= 1;
			PResult |= (S_BoxResult >> (32 - P[j])) & 1;
		}
		if (DesPrinting)
			binaryOutput(PResult, 32, "Permutation result");

		TempResiger = R;
		R = PResult ^ L;
		L = TempResiger;
	}

	printf("\nFinish the loop and apply Inverse Initial Permutation...\n\n");
	input = 0;
	TempResiger = 0;
	TempResiger = ((R << 32) | L);
	if (DesPrinting)
		binaryOutput(TempResiger, 64, "RL");
	for (int j = 0; j < 64; j++)
	{
		input <<= 1;
		input |= (TempResiger >> (64 - IIP[j])) & 1;
	}
	return input;
}