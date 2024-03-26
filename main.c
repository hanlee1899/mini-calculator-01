#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
#include "queue.h"
#include "stack.h"

NumStk* topN = NULL;
SignStk* topS = NULL;
Que* front = NULL;
Que* rear = NULL;

void exp_reset(char* exp) {
	for (int i = 0; i < sizeof(exp); i++) {
		exp[i] = '\0';
	}
}

int exp_check_grammar(char* exp, int len) {
	int i;

	for (i = 0; i < len; i++) {
		if (!(exp[i] >= 0 && exp[i] <= 127) || (exp[i] >= 65 && exp[i] <= 90)
		|| (exp[i] >= 97 && exp[i] <= 122)) {
			printf("[Error] : 한글과 영어는 입력을 허용하지 않습니다.\n");
			printf("다시 입력하세요.\n\n");
			break;
		}
	}

	if (i == len) {
		return 0;
	} else {
		return 1;
	}
}
	
int main(void) {
	char exp[1000];
	int len = 0;
	int checkgrm_signal;

	while (1) {
		exp_reset(exp);
		printf(">> ");
		fgets(exp, sizeof(exp), stdin);
		len = strlen(exp);
		checkgrm_signal = exp_check_grammar(exp, len - 1);

		if (checkgrm_signal == 1) {
			continue;
		}

		if (exp[0] == '\n') {
			printf("종료됨\n");
			exit(0);
		}

		for (int i = 0; i < len - 1; i++) {
			que_enQueue(exp[i]);
		}

		que_toStack(len);
		que_toStack_end();
	}

	return 0;
}