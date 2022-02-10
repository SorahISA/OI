#include <stdio.h>

int ReverseNumber(int number) {
    int reverse = 0, i;
    for (i = 0; i < 4; i++) {
        reverse = reverse*10+number%10;
        number = number/10;
    }
    //printf("Reverse Number: %d\n",reverse);
    return reverse;
}

int IsPrimeNumber(int number) {
   	int i;
	if (number < 2) {
		return 0;
	} else {
		for (i = 2; i < number; i++) {
			if (number%i == 0) {
				return 0;
			}
		}
	}
	return 1;
}

int main(void)
{
    int number, reverse;
    scanf ("%d",&number);
    reverse = ReverseNumber(number);
    if (IsPrimeNumber(number) && IsPrimeNumber(reverse)) {
		printf("IS VIP\n");
	} else {
		printf("NOT VIP\n");
		return 0;
	}
    return 0;
}