  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX INT_MAX

typedef struct {
	int x, y;
}Point;

void x_sorting(Point[], int);
void y_sorting(Point[], int);
double get_dist(Point, Point);
double get_min(double, double);
double Closest_Pair(Point[], int, int);
double Brute_Force_CPair(Point[], int, int);


void main() {

	Point p[30];
	int n, i;
	double dist;

	printf("Enter the number of points:");
	scanf("%d", &n);

	printf("\nEnter the two numbers (x, y coordiantes of N two-dimensional points)\n");
	for (i = 0; i < n; i++) {
		scanf("%d %d", &p[i].x, &p[i].y);
	}
	
	dist = Closest_Pair(p, 1, n);
	if (dist >= 10000)
		printf("\nSample Output\n\"Infinity\"");
	else
		printf("\nSample Output\n%.2f\n", dist);

}

/*
 * @ Description: an array P of points sorted on x-coordinate
 * @ Input: Point array, number of points
 * @ Output: Nothing
*/
void x_sorting(Point p[], int n) {

	int min = MAX, i, j, pos;
	Point temp;

	for (i = 0; i < n; i++) {
		min = p[i].x;
		for (j = i; j < n; j++) {
			if (min >= p[j].x) {
				min = p[j].x;
				pos = j;
			}
		}
		temp = p[i];
		p[i] = p[pos];
		p[pos] = temp;
	}
}

/*
* @ Description: an array P of points sorted on y-coordinate
* @ Input: Point array, number of points
* @ Output: Nothing
*/
void y_sorting(Point p[], int n) {

	int max = 0, i, j, pos;
	Point temp;

	for (i = 0; i < n; i++) {
		max = p[i].y;
		for (j = i; j < n; j++) {
			if (max <= p[j].y) {
				max = p[j].y;
				pos = j;
			}
		}
		temp = p[i];
		p[i] = p[pos];
		p[pos] = temp;
	}
}

/*
* @ Description: Calculate distance between two points
* @ Input: Two points value
* @ Output: Distance between two points
*/
double get_dist(Point p1, Point p2) {

	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

/*
* @ Description: Compare two distances and find minimum distance among them
* @ Input: Two distances value
* @ Output: Minimum distance
*/
double get_min(double d1, double d2) {

	if (d1 >= d2)
		return d2;
	else if (d1 < d2)
		return d1;

}

/*
* @ Description: Doing brute force algorithm for small number of points
*                Find every possible distance and return minimum distance among them
* @ Input: Point array, start position, end position
* @ Output: Minimum distance of two points
*/
double Brute_Force_CPair(Point p[], int l, int r) {
	
	double min = MAX;
	int i, j;

	for (i = l; i < r-1; i++) {
		min = get_dist(p[i], p[i + 1]);
		for (j = i+1; j < r; j++) {
			if (min >= get_dist(p[i], p[j])) {
				min = get_dist(p[i], p[j]);
			}
		}
	}
	return min;
}


/*
* @ Description: Find minimum distance of any two points. Using divide and conquer, brute force algorithm.
* @ Input: Point array, start position, end position
* @ Output: Minimum distance of any two points among all points set.
*/
double Closest_Pair(Point p[], int l, int r) {

	Point s[30];
	int q, i, j;
	double d1, d2, dist;

	x_sorting(p, r);
	
	if ((r - l) < 3)
		return Brute_Force_CPair(p, l, r);
	else {
		q = (l + r) / 2;
		d1 = Closest_Pair(p, l, q - 1);
		d2 = Closest_Pair(p, q, r);
		dist = get_min(d1, d2);

		for (i = l-1, j=0; i < r; i++) {
			if ((p[q].x - dist <= p[i].x) && (p[i].x <= p[q].x + dist)) {
				s[j] = p[i];
				j++;
			}
		}
		y_sorting(s, j);
		for (i = 0; i < j; i++) {
			for (int k = 1; k <= 7; k++) {
				if (dist > get_dist(s[i], s[i + k])) {
					dist = get_dist(s[i], s[i + k]);
				}
			}
		}
	}
	return dist;
}
