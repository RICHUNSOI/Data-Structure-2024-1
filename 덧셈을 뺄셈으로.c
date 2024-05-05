//202111296 이준수
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

struct polynomial1 { // 다항식 구조체 타입 선언
	int degree; // 다항식의 차수
	float coef[MAX_DEGREE]; // 다항식의 계수
}; */

#define MAX_TERMS 101
typedef struct polynomial2 {
	float coef; //다항식의 계수
	int expon; // 다항식의 차수
}polynomial2;
polynomial2 terms[MAX_TERMS] = { {8,3}, {7,1}, {1,0}, {10,3}, {3,2}, {1,0} }; // 식 A, B가 동시에 들어가 있음
//A : 8x^3 + 7x + 1
//B : 10x^3 + 3x^2 + 1
int avail = 6; // 식 A의 항의 갯수 + 식 B의 항의 갯수로 초기화를 시키는 것
//이 부분은 식 C를 terms에 넣을 때의 terms의 index를 의미함

/*struct studentTag {
	char name[10];   // 문자배열로 된 이름
	int age;         	 // 나이를 나타내는 정수값
	double gpa;	 // 평균평점을 나타내는 실수값
};*/

/*typedef unsigned int UINT32;

typedef struct studentTag {
	char name[10];  // 문자배열로 된 이름
	int age;         	 // 나이를 나타내는 정수값
	double gpa;	 // 평균평점을 나타내는 실수값
} student;
*/

/*
polynomial1 poly_add1(polynomial1 A, polynomial1 B) {
	polynomial1 C;//결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {
			C.coef[Cpos] = A.coef[Apos];
			degree_a--;
			printf("Apos: %d / Bpos: %d / Cpos: %d\n", Apos, Bpos, Cpos);
			printf("A.coef[%d]: %.2f / B.coef[%d]: %.2f / C.coef[%d]: %.2f\n", Apos, A.coef[Apos], Bpos, B.coef[Bpos], Cpos, C.coef[Cpos]);
			Cpos++;
			Apos++;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos] = A.coef[Apos] + B.coef[Bpos];
			degree_a--;
			degree_b--;
			printf("Apos: %d / Bpos: %d / Cpos: %d\n", Apos, Bpos, Cpos);
			printf("A.coef[%d]: %.2f / B.coef[%d]: %.2f / C.coef[%d]: %.2f\n", Apos, A.coef[Apos], Bpos, B.coef[Bpos], Cpos, C.coef[Cpos]);
			Apos++;
			Bpos++;
			Cpos++;
		}
		else {
			C.coef[Cpos] = B.coef[Bpos];
			degree_b--;
			printf("Apos: %d / Bpos: %d / Cpos: %d\n", Apos, Bpos, Cpos);
			printf("A.coef[%d]: %.2f / B.coef[%d]: %.2f / C.coef[%d]: %.2f\n", Apos, A.coef[Apos], Bpos, B.coef[Bpos], Cpos, C.coef[Cpos]);
			Cpos++;
			Bpos++;
		}
		printf("---\n");
	}
	return C;
}

void print_poly(polynomial1 p) {
	for (int i = p.degree; i > 0; i--) {
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1f \n", p.coef[p.degree]);
}
*/

char compare(int a, int b) {
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void subtract(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void poly_sub2(int Astart, int Aend, int Bstart, int Bend, int* Cstart, int* Cend) {
	float tempcoef;
	*Cstart = avail;
	while (Astart <= Aend && Bstart <= Bend) {
		switch (compare(terms[Astart].expon, terms[Bstart].expon)) {
		case '>':
			subtract(terms[Astart].coef, terms[Astart].expon);
			printf("Astart: %d / Bstart: %d / avail : %d\n", Astart, Bstart, avail);
			printf("A:terms[%d].coef: %.2f / B:terms[%d].coef: %.2f / C:terms[%d].coef: %.2f\n", Astart, terms[Astart].coef, Bstart, terms[Bstart].coef, avail - 1, terms[avail - 1].coef);
			Astart++;
			break;
		case '=':
			tempcoef = terms[Astart].coef - terms[Bstart].coef;
			if (tempcoef)
				subtract(tempcoef, terms[Astart].expon);
			printf("Astart: %d / Bstart: %d / avail : %d\n", Astart, Bstart, avail);
			printf("A:terms[%d].coef: %.2f / B:terms[%d].coef: %.2f / C:terms[%d].coef: %.2f\n", Astart, terms[Astart].coef, Bstart, terms[Bstart].coef, avail - 1, terms[avail - 1].coef);
			Astart++;
			Bstart++;
			break;
		case '<':
			subtract(-terms[Bstart].coef, terms[Bstart].expon);
			printf("Astart: %d / Bstart: %d / avail : %d\n", Astart, Bstart, avail);
			printf("A:terms[%d].coef: %.2f / B:terms[%d].coef: %.2f / C:terms[%d].coef: %.2f\n", Astart, terms[Astart].coef, Bstart, terms[Bstart].coef, avail - 1, terms[avail - 1].coef);
			Bstart++;
			break;
		}
	}

	for (; Astart <= Aend; Astart++) {
		subtract(terms[Astart].coef, terms[Astart].expon);
	}
	for (; Bstart <= Bend; Bstart++) {
		subtract(terms[Bstart].coef, terms[Bstart].expon);
	}
	*Cend = avail - 1;
}

void print_poly(int start, int end) {
	for (int i = start; i < end; i++)
		printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
	printf("%3.1fx^%d\n", terms[end].coef, terms[end].expon);

}

int main() {
	/*unsigned int ori = 1;
	UINT32 mine = 1;
	printf("%d %d", ori, mine);
	*/

	/*struct studentTag s1;
	strcpy(s1.name, "Kim");
	s1.age = 20;
	s1.gpa = 4.3;
	printf("Name : %s\n", s1.name);
	printf("Age : %d\n", s1.age);
	printf("GPA : %.2f\n", s1.gpa);

	studentTag s2 = { "Kim", 20, 4.3 };
	printf("Name : %s\n", s2.name);
	printf("Age : %d\n", s2.age);
	printf("GPA : %.2f\n", s2.gpa);*/

	/*student a = {"Kim", 20, 4.3};
	student b = { "Park", 21, 4.2 };

	printf("A Name : %s\n", a.name);
	printf("A Age : %d\n", a.age);
	printf("A GPA : %.2f\n", a.gpa);
	printf("B Name : %s\n", b.name);
	printf("B Age : %d\n", b.age);
	printf("B GPA : %.2f\n", b.gpa);*/

	/*polynomial1 a = {5, {3, 6, 0, 0, 0, 10}};
	polynomial1 b = { 4, {7, 0, 5, 0, 1} };
	polynomial1 c;

	print_poly(a);
	print_poly(b);
	printf("-----------------------\n");
	c = poly_add1(a, b);
	printf("-----------------------\n");
	print_poly(c);*/

	int Astart = 0, Aend = 2, Bstart = 3, Bend = 5, Cstart, Cend;
	poly_sub2(Astart, Aend, Bstart, Bend, &Cstart, &Cend);
	print_poly(Astart, Aend);
	print_poly(Bstart, Bend);
	printf("-------------------------------------------\n");
	print_poly(Cstart, Cend);


	return 0;
}