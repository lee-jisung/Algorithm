#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define MAXN 100

typedef struct{
	
	int x, y; 

} Point;

int solution_cnt = 0;

void backtrack(int bishop_vector[], int depth, int n, int k);
void construct_candidate(int bishop_vector[], int depth, int n, int k, int candidate[], int *ncandidates);
int is_solution(int bishop_vector[], int depth, int n, int k);
int is_diagonal(int x1, int y1, int x2, int y2);
float get_slope(int x1, int y1, int x2, int y2);
Point get_pos(int pos, int n);

void main() {

	int n, k;

	while (1) {

		scanf("%d %d", &n, &k);

		if (n == 0 || k == 0 || n>10 || k>n) {
			puts("Thank you \n");
			exit(1);
		}
		if (n == 1) {
			printf("%d \n", n);
		}
		if (k == 1) {
			printf("%d \n", n*n);
		}
	
		int bishop_vector[10] = { 0, };
		for (int i = 0; i < n*n; i++) {
			bishop_vector[0] = i;
		    backtrack(bishop_vector, 0, n, k);
		}

		printf("%d \n", solution_cnt);
		solution_cnt = 0;
	}

}
/*
 *  Description: Doing Back tracking algorithm. check depth every pass, and if depth is same with number of bishop, then increase solution count
 *               if not same, find candidate and doing back tracking recursively
 *  Intput: solution vector array, depth pass, size of chess board, number of bishop.
 *  Output: Nothing
*/
void backtrack(int bishop_vector[], int depth, int n, int k) {

	if (is_solution(bishop_vector, depth, n, k)) {

		solution_cnt++;
		return;
	}
	
	depth++;
	int candidate[MAXN] = { 0, };
	int ncandidates = 0;

	construct_candidate(bishop_vector, depth, n, k, candidate, &ncandidates);
	
	for (int i = 0; i < ncandidates; i++) {
		bishop_vector[depth] = candidate[i];
		backtrack(bishop_vector, depth, n, k);
	}

}

/*
 *  Description: find position that rest of the bishop can positioned.
 *               If depth bigger than number of bishop, then stop find candidate.
 *               If bishop position that after last bishop positioned, make duplication of solution. So ignore this case.
 *  Input: solution vector array, depth pass, size of chess board, number of bishop, array of candidates, number of candidate
 *  Output: Nothing
 */
void construct_candidate(int bishop[], int depth, int n, int k, int candidate[], int *ncandidates) {
	
	if (depth > k - 1)
		return;

	int target[MAXN] = { FALSE, };
	for (int i = 0; i < depth; i++) {
		target[bishop[i]] = TRUE;
	}

	for (int i = 0; i < n*n; i++) {

		if (target[i] == TRUE)
			continue;

		if (i > bishop[depth - 1])
			continue;

		candidate[*ncandidates] = i;
		(*ncandidates)++;

	}
}

/*
 *  Description: If depth is not same with number of bishop, then return false.
 *               if one of the bishop positioned diagonally from another bishop, then return false
 *               There is no above case, then return trues
 *  Input: solution vector array, depth pass, size of chess board, number of bishop
 *  Output: If solution then return true, or not, return false
 */
int is_solution(int bishop_vector[], int depth, int n, int k) {

	if (depth != k - 1)
		return FALSE;

	for (int i = 0; i < k; i++) {
		Point lhs = get_pos(bishop_vector[i], n);

		for (int j = 0; j < k; j++) {

			if (i == j)
				continue;

			Point rhs = get_pos(bishop_vector[j], n);

			if (is_diagonal(lhs.x, lhs.y, rhs.x, rhs.y))
				return FALSE;
		}
	}
	return TRUE;
}

/*
 *  Description: Check that two bishops' position whether positioned diagonally or not.
 *  Input: two bishops' coordinate value
 *  Output: If positioned diagonally then return false, or not return true
 */
int is_diagonal(int x1, int y1, int x2, int y2) {
	
	if (x1 == x2 || y1 == y2)
		return FALSE;

	float slope = get_slope(x1, y1, x2, y2);

	if (slope < 0)
		slope *= -1;

	if (slope != 1)
		return FALSE;
	else
		return TRUE;
}

/*
*  Description: get slope of two bishops
*  Input: tow bishops' coordinate value
*  Output: slope value of two bishops.
*/
float get_slope(int x1, int y1, int x2, int y2) {

	float dx = (float)(x2 - x1);
	float dy = (float)(y2 - y1);

	if (dx == 0 || dy == 0)
		return 0;

	return dx / dy;
}

/*
*  Description: Make coordinate value of bishop's based on array position that numbered sequentially.
*  Input: array position, size of chess board
*  Output: coordinate value
*/
Point get_pos(int pos, const int n) {
	
	Point temp;
	temp.x = (pos % n) + 1;
	temp.y = (pos / n) + 1;
	return temp;
}
