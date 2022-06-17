// cryptoDemo.cpp : Defines the entry point for the console application.
// Windows: cl cryptoDemo.cpp
// Linux: gcc -o cryptoDemo cryptoDemo.cpp -lcrypto

#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 2500

#include "aes.h"

#pragma comment(lib,"libcrypto.lib")

void AES_encrypt(char filename[], char password[])
{
	int i, j, len, nLoop, nRes, pwdlen, inLen, enlen;
	char inString[N];
	char enString[N];
	FILE* fp;
	unsigned char buf[16];
	unsigned char buf2[16];
	unsigned char aes_keybuf[32];
	AES_KEY aeskey;

	// 准备32字节(256位)的AES密码字节
	pwdlen = strlen(password);
	memset(aes_keybuf, 0x90, 32);
	if (pwdlen < 32)
		len = pwdlen;
	else
		len = 32;
	for (i = 0; i < len; i++)
		aes_keybuf[i] = password[i];
	AES_set_encrypt_key(aes_keybuf, 256, &aeskey);
	//读入需要加密的文件
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Sourse File Open Error\n");
		return;
	}
	else
		printf("Sourse File Open Success\n");
	memset(inString, 0, N);
	memset(enString, 0, N);
	fread(inString, sizeof(char), N, fp);
	fclose(fp);

	inLen = strlen(inString);
	nLoop = inLen / 16;
	nRes = inLen % 16;
	// 加密输入的字节串
	for (i = 0; i < nLoop; i++)
	{
		memset(buf, 0, 16);
		for (j = 0; j < 16; j++)
			buf[j] = inString[i * 16 + j];
		AES_encrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			enString[i * 16 + j] = buf2[j];
	}
	if (nRes > 0)
	{
		memset(buf, 0, 16);
		for (j = 0; j < nRes; j++)
			buf[j] = inString[i * 16 + j];
		AES_encrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			enString[i * 16 + j] = buf2[j];
	}
	enString[i * 16 + j] = 0;

	//将加密结果输出
	if ((fp = fopen("ciphertext.out", "wb")) == NULL)
	{
		printf("Ciphertext File Open Error\n");
		return;
	}
	else
		printf("Ciphertext File Open Success\n");
	fwrite(enString, sizeof(char), strlen(inString), fp);
	fclose(fp);
	printf("Encrypt Success!");
}

void AES_decrypt(char filename[], char password[])
{
	int i, j, len, nLoop, nRes, pwdlen, inLen;
	char inString[N];
	char deString[N];
	FILE* fp;
	unsigned char buf[16];
	unsigned char buf2[16];
	unsigned char aes_keybuf[32];
	AES_KEY aeskey;

	// 准备32字节(256位)的AES密码字节
	pwdlen = strlen(password);
	memset(aes_keybuf, 0x90, 32);
	if (pwdlen < 32)
		len = pwdlen;
	else
		len = 32;
	for (i = 0; i < len; i++)
		aes_keybuf[i] = password[i];
	AES_set_decrypt_key(aes_keybuf, 256, &aeskey);
	//读入需要解密的文件
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("Source File Open Error\n");
		return;
	}
	else
		printf("Source File Open Success\n");
	memset(inString, 0, N);
	fread(inString, sizeof(char), N, fp);

	inLen = 0;
	for (i = 0; i < N; i++)
	{
		if (inString[i] == 0 && inString[i + 1] == 0)
			break;
		else
			inLen++;
	}

	nLoop = inLen / 16;
	nRes = inLen % 16;
	// 解密输入的字节串
	for (i = 0; i < nLoop; i++)
	{
		memset(buf, 0, 16);
		for (j = 0; j < 16; j++)
			buf[j] = inString[i * 16 + j];
		AES_decrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			deString[i * 16 + j] = buf2[j];
	}
	if (nRes > 0)
	{
		memset(buf, 0, 16);
		for (j = 0; j < 16; j++)
			buf[j] = inString[i * 16 + j];
		AES_decrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			deString[i * 16 + j] = buf2[j];
	}
	deString[i * 16 + nRes] = 0;
	fclose(fp);
	//将解密结果输出
	if ((fp = fopen("plaintext.out", "w")) == NULL)
	{
		printf("Plaintext File Open Error\n");
		return;
	}
	else
		printf("Plaintext File Open Success\n");
	fwrite(deString, sizeof(char), inLen, fp);
	fclose(fp);
	printf("Decrypt Success!\n");
}

int main(int argc, char* argv[])
{
	if (memcmp(argv[1], "enc", 3) == 0)
		AES_encrypt(argv[2], argv[3]);
	else
	{
		if (memcmp(argv[1], "dec", 3) == 0)
			AES_decrypt(argv[2], argv[3]);
		else
			printf("Mode Error!\n");
	}

	return 0;
}
