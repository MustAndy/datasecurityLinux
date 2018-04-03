#
# makefile for data security 
# wang,jingqing
# 30/03/2018
#
CC = gcc

CFLAGS = #-Wall

OBJS = main.o CaesarCipher.o Cols_Rows_Transposition.o des.o PlayfairCipher.o RC4.o s_des.o s_RC4.o vigenereCipher.o

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: header.h des.h
	$(CC) $(CFLAGS) -c main.c

CaesarCipher.o:header.h
	$(CC) $(CFLAGS) -c CaesarCipher.c

Cols_Rows_Transposition.o:header.h
	$(CC) $(CFLAGS) -c Cols_Rows_Transposition.c

des.o:header.h des.h
	$(CC) $(CFLAGS) -c des.c

PlayfairCipher.o:header.h
	$(CC) $(CFLAGS) -c PlayfairCipher.c

s_des.o:header.h
	$(CC) $(CFLAGS) -c s_des.c

RC4.o:header.h
	$(CC) $(CFLAGS) -c RC4.c	

vigenereCipher.o:header.h
	$(CC) $(CFLAGS) -c vigenereCipher.c

s_RC4.o:header.h
	$(CC) $(CFLAGS) -c s_RC4.c
	
clean:
	-rm main $(OBJS)
