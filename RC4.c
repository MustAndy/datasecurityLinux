#include "header.h"
typedef unsigned longULONG;
// static FILE *key_file, *input_file, *output_file;
static FILE* output_file;
void rc4_init(unsigned char* s, unsigned char* key, unsigned long Len)
{
    int i = 0, j = 0;
    char k[256] = { 0 };
    unsigned char tmp = 0;
    for (i = 0; i < 256; i++)
    {
        s[i] = i;
        k[i] = key[i % Len];
    }
    for (i = 0; i < 256; i++)
    {
        j = (j + s[i] + k[i]) % 256;
        tmp = s[i];
        s[i] = s[j]; //swap s[i] and s[j]
        s[j] = tmp;
    }
}

void rc4_crypt(unsigned char* s, unsigned char* Data, unsigned long Len)
{
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;
    for (k = 0; k < Len; k++)
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        tmp = s[i];
        s[i] = s[j]; //swap s[i] and s[j]
        s[j] = tmp;
        t = (s[i] + s[j]) % 256;
        Data[k] ^= s[t];
    }
}

void RC4()
{
    output_file = fopen("output.txt", "wb");
    if (!output_file)
    {
        printf("Could not open output file to write data.");
        exit(-1);
    }
    unsigned char s[256] = { 0 }, s2[256] = { 0 }; //S-box
    char key[256] = { "234567876543" };
    char pData[512] = "9876543234567890";
    unsigned long len = strlen(pData);
    int i;

    printf("pData=%s\n", pData);
    printf("key=%s,length=%ld\n\n", key, strlen(key));
    rc4_init(s, (unsigned char*)key, strlen(key));
    printf("init s and t\n\n");
    for (i = 0; i < 256; i++)
    {
        printf("%02X", s[i]);
        if (i && (i + 1) % 16 == 0)
            putchar('\n');
    }
    printf("\n\n");
    for (i = 0; i < 256; i++)
    {
        s2[i] = s[i];
    }
    printf("encryption: \n\n");
    rc4_crypt(s, (unsigned char*)pData, len);
    fprintf(output_file, "%s", pData);
    printf("pData=%x\n\n", pData);
    printf("decryption: \n\n");
    //rc4_init(s,(unsignedchar*)key,strlen(key));
    rc4_crypt(s2, (unsigned char*)pData, len);
    printf("pData=%s\n\n", pData);
}
