#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "stack.h"

extern NumStk* topN;
extern SignStk* topS;

int cal_checkSign(char queSign) {
	int stk;
	int q;
	int calcur_signal;

	if (queSign == ')') {
		while (topS->data != '(') {
			calcur_signal = cal_calcur(topS->data);

			if (calcur_signal == 1) {
				return 1;
			}
		}

		stk_popSign();
		return 0;
	}

	if (topS == NULL) {
		stk_pushSign(queSign);
		return 0;
	} else {
		stk = cal_priority(topS->data);
		q = cal_priority(queSign);
	}

	if (stk >= q) {
		if (topS->data == '(') {
			stk_pushSign(queSign);
			return 0;
		} else {
			calcur_signal = cal_calcur(topS->data);

			if (calcur_signal == 1) {
				return 1;
			}

			stk_pushSign(queSign);
		}
	} else {
		stk_pushSign(queSign);
	}

	return 0;
}

int cal_priority(char opt) {
	switch (opt) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
		case '^':
			return 2;
		case '(':
		case ')':
			return 3;
	}
}

int cal_calcur(char opt) {
	double result = 1.0;

	if (opt == '+') {
		result = topN->next->data + topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '-') {
		result = topN->next->data - topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '*') {
		result = topN->next->data * topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '/') {
		if (topN->data == 0) {
			printf("Divided by zero\n\n");

			while (topN != NULL) {
				stk_popNum();
			}

			while (topS != NULL) {
				stk_popSign();
			}

			return 1;
		}

		result = topN->next->data / topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '%') {
		if (topN->data == 0) {
			printf("Modulo by zero\n\n");

			while (topN != NULL) {
				stk_popNum();
			}

			while (topS != NULL) {
				stk_popSign();
			}

			return 1;
		}

		result = fmod(topN->next->data, topN->data);
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '^') {
		for (int i = 0; i < topN->data; i++) {
			result *= topN->next->data;
		}

		stk_popSign();	
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	}
}

void cal_result(void) {
	if (topN == NULL) {
		return;
	} else {	
		if (topN->data - (int) topN->data == 0) {
			printf("result: %d\n\n", (int) topN->data);
		} else {
			printf("result: %.1lf\n\n", topN->data);
		}

		stk_popNum();
	}
}