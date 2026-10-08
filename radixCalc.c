#include <stdio.h>    // printf, fgets
#include <stdlib.h>   // strtol
#include <errno.h>    // errno, ERANGE
#include <limits.h>   // INT_MIN, INT_MAX
#include <stdbool.h>
#include <string.h>
#include <math.h>

int valueTable[256];
int IntToCharTable[26];

void initTable(void) {
	for (int i = 0; i<256l; i++) {
		valueTable[i] = -1;
	}
	for (int i = 0; i<10; i++) {
		valueTable['0' + i] = i;
	}
	for (int i = 0; i<26; i++) {
		valueTable['A' + i] = i+10;
	}
	for (int i = 0; i<26; i++) {
		valueTable['a' + i] = i+10;
	}

}

bool getStr(char StrPTR[30]) {
	printf("\n:");
	char buff[30];
	char *ptr = fgets(buff, sizeof(buff), stdin);
	if (ptr == NULL) {
		return false;
	} else {
		int len = strlen(ptr);
		*(ptr + len-1) = '\0';
		strcpy(StrPTR, ptr);
		return true;
	}
}

bool strToInt(int *Number, char str[]) {

	char *end;
	long Linput = 0;

	errno = 0;
	Linput = strtoll(str, &end, 10);
	if ((strcmp(end, str) == 0) || (errno == ERANGE) || ( Linput < INT_MIN) || (Linput > INT_MAX)) {
		return false;
	} else {
		*(Number) = (int)Linput;
		return true;
	}

}


bool getInt(int *Number) {
	char buff[30];
	bool STRsuccess = getStr(buff);
	if (!STRsuccess) return false;

	bool INTSuccess = strToInt(Number, buff);
	if (!INTSuccess) return false;

	return true;
}

int singleCharacterToInt(char Char) {
	return valueTable[(unsigned int)Char] ;
}


int TranslateToDecimalBase(char* RadixNum, int OriginalRadixBase) {
	int RadixBase10Number = 0;

	int strLen = strlen(RadixNum);
	for (int i=0; i<strLen; i++) {
		int Num = singleCharacterToInt(RadixNum[strLen-i-1]);
		if (Num == -1) {
			printf("Invalid Charcter: %s\n", &RadixNum[strLen-i-1]);
			printf("\n Invalid characters");
			return 2;
		}

		RadixBase10Number += Num * pow(OriginalRadixBase, i);
	}
	return RadixBase10Number;
}

void TranslateToNonDecimalBase(char *RadixNum, int RadixBase10Number, int TargetRadixBase, char TotalNumber[70]) {
	int strLen = strlen(RadixNum);
	int lastDivisionNumber = RadixBase10Number;
	while (true) {
		if (lastDivisionNumber == 0) {
			break;
		}
		int division = lastDivisionNumber / TargetRadixBase;

		memmove(TotalNumber +1, TotalNumber, strLen+1);
		int numberToPut = lastDivisionNumber - (division * TargetRadixBase);
		if (numberToPut > 9) {
			TotalNumber[0] = 'A' + (numberToPut-10);
		} else {
			TotalNumber[0] = '0' + (numberToPut);
		}
		lastDivisionNumber = division;
	}	
}


int ConvertBasesMain() {
	printf("\n\nEnter radix Number");
	
	char RadixNum[30];
	if (!getStr(RadixNum)) return 2;


	printf("Enter Original Radix Base");

	int OriginalRadixBase = 0;
	if (!getInt(&OriginalRadixBase)) return 2;


	printf("Enter Target Radix Base");

	int TargetRadixBase = 0;
	if (!getInt(&TargetRadixBase)) return 2;
	
	int RadixBase10Number = 0;

	if (OriginalRadixBase == 10) {
		if (!strToInt(&RadixBase10Number, RadixNum)) return 2; // transfer the radix num to int and pushes it to radixbase10num 
								       // -   confident no errors because Base10 doesnt include letters
	} else {
		OriginalRadixBase = TranslateToDecimalBase(RadixNum, OriginalRadixBase);
	}

	
	printf("\nRadix 10: %d", RadixBase10Number);
	
	if (TargetRadixBase == 10) {
		return 0;
	}
	char TotalNumber[70] = "";
	TranslateToNonDecimalBase("", RadixBase10Number, TargetRadixBase, TotalNumber);	

	printf("\nRadix %d: %s\n",TargetRadixBase, TotalNumber);
	return 0;

}


int ArithmeticOnNonDecimalBases() {
	printf("\nEnter Radix Base");

	int OriginalRadixBase = 0;
	if (!getInt(&OriginalRadixBase)) return 2;


	printf("\n\nPlease select an arithmetic operation: ");
	printf("\n[/] - Division");
	printf("\n[*] - Multiplication");
	printf("\n[-] - Subtraction");
	printf("\n[+] - Addition");
		
	char ArithemticOperation[30];
	if (!getStr(ArithemticOperation)) return 2;


	printf("\n\nEnter first radix number");
	
	char RadixNumFirst[30];
	if (!getStr(RadixNumFirst)) return 2;

	printf("\nEnter second radix Number");
	
	char RadixNumSecond[30];
	if (!getStr(RadixNumSecond)) return 2;

	int Radix10One = 0;
	int Radix10Two = 0;
	if (OriginalRadixBase != 10) {
		Radix10One = TranslateToDecimalBase(RadixNumFirst, OriginalRadixBase);
		Radix10Two = TranslateToDecimalBase(RadixNumSecond, OriginalRadixBase);
	} else {
		strToInt(&Radix10One, RadixNumFirst);
		strToInt(&Radix10Two, RadixNumSecond);
	}
	printf("\n\n%s %c %s\n", RadixNumFirst, ArithemticOperation[0], RadixNumSecond);

	if (ArithemticOperation[0] == '+') {
		int Answer = Radix10One + Radix10Two;
		char answerInOriginalBase[70]; 
		TranslateToNonDecimalBase("", Answer, OriginalRadixBase, answerInOriginalBase);
		printf("Equals: %s\n", answerInOriginalBase);
	} else if (ArithemticOperation[0] == '-') {
		int Answer = Radix10One - Radix10Two;
		char answerInOriginalBase[70]; 
		TranslateToNonDecimalBase("", Answer, OriginalRadixBase, answerInOriginalBase);
		printf("Equals: %s\n", answerInOriginalBase);
	} else if (ArithemticOperation[0] == '/') {
		int Answer = Radix10One / Radix10Two;
		char answerInOriginalBase[70]; 
		TranslateToNonDecimalBase("", Answer, OriginalRadixBase, answerInOriginalBase);
		printf("Equals: %s\n", answerInOriginalBase);
	} else if (ArithemticOperation[0] == '*') {
		int Answer = Radix10One * Radix10Two;
		char answerInOriginalBase[70]; 
		TranslateToNonDecimalBase("", Answer, OriginalRadixBase, answerInOriginalBase);
		printf("Equals: %s\n", answerInOriginalBase);
	}


	return 0;
}

int main()
{
	initTable();

	printf("\n[1] - Convert bases");
	printf("\n[2] - Arithemtic operations on non decimal bases");

	int Selection  = 0;
	if (!getInt(&Selection)) return  2;

	
	switch (Selection) {
		case 1: 
			return ConvertBasesMain();
			break;

		case 2:
			return ArithmeticOnNonDecimalBases();
			break;
	}

    	return 0;
}


