// cryptoDemo.cpp : Defines the entry point for the console application.
// Windows: cl cryptoDemo.cpp
// Linux: gcc -o cryptoDemo cryptoDemo.cpp -lcrypto

#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aes.h"

#pragma comment(lib,"libeay32.lib")

void testAes(char inString[], int inLen, char passwd[], int pwdLen)
{
	int i,j, len, nLoop, nRes;
	char enString[1024];
	char deString[1024];

	unsigned char buf[16];
	unsigned char buf2[16];
	unsigned char aes_keybuf[32];
	AES_KEY aeskey;

	// 准备32字节(256位)的AES密码字节
	memset(aes_keybuf,0x90,32);
	if(pwdLen<32){ len=pwdLen; } else { len=32;}
	for(i=0;i<len;i++) aes_keybuf[i]=passwd[i];
	// 输入字节串分组成16字节的块	
	nLoop=inLen/16; nRes = inLen%16;
	// 加密输入的字节串
	AES_set_encrypt_key(aes_keybuf,256,&aeskey);
	for(i=0;i<nLoop;i++){
		memset(buf,0,16);
		for(j=0;j<16;j++) buf[j]=inString[i*16+j];
		AES_encrypt(buf,buf2,&aeskey);
		for(j=0;j<16;j++) enString[i*16+j]=buf2[j];
	}
	if(nRes>0){
		memset(buf,0,16);
		for(j=0;j<nRes;j++) buf[j]=inString[i*16+j];
		AES_encrypt(buf,buf2,&aeskey);
		for(j=0;j<16;j++) enString[i*16+j]=buf2[j];
		//puts("encrypt");
	}
	enString[i*16+j]=0;
	// 密文串的解密	
	AES_set_decrypt_key(aes_keybuf,256,&aeskey);
	for(i=0;i<nLoop;i++){
		memset(buf,0,16);
		for(j=0;j<16;j++) buf[j]=enString[i*16+j];
		AES_decrypt(buf,buf2,&aeskey);
		for(j=0;j<16;j++) deString[i*16+j]=buf2[j];
	}
	if(nRes>0){
		memset(buf,0,16);
		for(j=0;j<16;j++) buf[j]=enString[i*16+j];
		AES_decrypt(buf,buf2,&aeskey);
		for(j=0;j<16;j++) deString[i*16+j]=buf2[j];
		//puts("decrypt");
	}
	deString[i*16+nRes]=0;
	//比较解密后的串是否与输入的原始串相同
	if(memcmp(inString,deString,strlen(inString))==0)
	{ printf("test success\r\n");} else { printf("test fail\r\n");}
   	printf("The original string is:\n  %s ", inString);
   	printf("The encrypted string is:\n  %s ", enString);
   	printf("The decrypted string is:\n  %s ", deString);
}

int main(int argc, char* argv[])
{
	char inString[] = "This is a sample. I am a programer.\n";
	char passwd[] = "0123456789ABCDEFGHIJK";

	testAes(inString, strlen(inString), passwd, strlen(passwd));

	return 0;
}
