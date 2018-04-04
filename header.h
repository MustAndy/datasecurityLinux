#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
//#include <syslib.h>

typedef enum {
  FALSE,
  TRUE
} Boolean;
void vigenereCipher();
void E_CaesarCipher();
void D_CaesarCipher();
void PlayfairCipher();
void s_des();
void s_RC4();
void Cols_Rows_Transposition();
void RC4();
void des();
#endif