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

char *TranslateToNonDecimalBase(int DecimalRadixNumber, int TargetRadixBase) {
	char *TotalNumber = malloc(sizeof(char)*50);
	int occupiedBytes = 1;
	*TotalNumber = '\n';
	int NumberToDivide = DecimalRadixNumber;
	while (true) {
		int division = NumberToDivide / TargetRadixBase; // INTEGER DIVISION!	
		int Remainder = NumberToDivide * (division - TargetRadixBase); // only works if division was produced in an integer division
		if (occupiedBytes != 0) {
			memmove(TotalNumber+1, TotalNumber, occupiedBytes);
		}
		if (Remainder < 10) {
			*TotalNumber = '0' + Remainder; // 0 has a specific ascii number and its counting up to 9 so basically ascii representation of 0 plus the int 9 equals 9 in ascii
		} else {
			*TotalNumber = 'A' + (Remainder - 10); // if remainder is 10 we want to produce A so remove the ten and ascii of A plus zero still equals A
		}

		occupiedBytes++;
		
		if (division == 0) {
			break;
		} else {
			NumberToDivide = division;
		}
	}
	
	char *OptimizedStringNumber = malloc(sizeof(char)*occupiedBytes); // return a string with the fit to the number - small optimization will be unnoticeable
	strcpy(OptimizedStringNumber, TotalNumber);

	free(TotalNumber);
	TotalNumber = NULL;

	return OptimizedStringNumber;
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
	char *TotalNumber; 
	TotalNumber = TranslateToNonDecimalBase(RadixBase10Number, TargetRadixBase);	

	printf("\nRadix %d: %s\n",TargetRadixBase, TotalNumber);
	free(TotalNumber);
	TotalNumber = NULL;
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
	int Answer;
	if (ArithemticOperation[0] == '+') {
		Answer = Radix10One + Radix10Two;
	} else if (ArithemticOperation[0] == '-') {
		Answer = Radix10One - Radix10Two;
	} else if (ArithemticOperation[0] == '/') {
		Answer = Radix10One / Radix10Two;
	} else if (ArithemticOperation[0] == '*') {
		Answer = Radix10One * Radix10Two;
	}
	char *AnswerTranslatedToOriginalBase;
	AnswerTranslatedToOriginalBase = TranslateToNonDecimalBase(Answer, OriginalRadixBase);
	printf("Equals: %s\n", AnswerTranslatedToOriginalBase);

	free(AnswerTranslatedToOriginalBase);
	AnswerTranslatedToOriginalBase = NULL;
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


