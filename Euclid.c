#include <stdio.h>
#include <stdlib.h>

int extend_euclid(int, int, int*, int*);

void main() {

	int a, b, d, x, y;

	printf("If you enter the negative integers, then program will terminate.\n");
	printf("Enter the two positive integers: ");
	scanf("%d %d", &a, &b);


	while (1) {

		if (a < 0 || b < 0)
			exit(1);

		d = extend_euclid(a, b, &x, &y);

		printf("%d %d %d \n", x, y, d);

		printf("Enter the two positive integers: ");
		scanf("%d %d", &a, &b);	
	
	}
}

/*
 * Description: find X, Y and D that satisfy AX + BY = D where D is the greatest common divisor of A and B
 * Input: value of positive number A and B, address of x and y.
 * Output: the greatest common divisor of A and B
 */
int extend_euclid(int a, int b, int * x, int * y) {

	int x1, y1;
	int d;

	if(b > a)
		return extend_euclid(b, a, y, x); 

	if (b == 0) {  
		*x = 1;
		*y = 0;
		return a;
	}
	 
	d = extend_euclid(b, a%b, &x1, &y1);

	*x = y1;
	*y = (x1 - (a / b)*y1);

	return d;
}
