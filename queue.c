#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "queue.h"
#include "stack.h"

extern NumStk* topN;
extern SignStk* topS;
extern Que* front;
extern Que* rear;

void que_enQueue(char x) {
	if (front == NULL && rear == NULL) {
		Que* tmp = (Que*) malloc(sizeof(Que));

		tmp->next = NULL;
		tmp->data = x;
		front = tmp;
		rear = tmp;
	} else {
		Que* tmp = (Que*) malloc(sizeof(Que));

		tmp->next = NULL;
		tmp->data = x;
		rear->next = tmp;
		rear = tmp;
	}
}

void que_deQueue(void) {
	Que* del;

	del = front;
	front = front->next;

	if (front == NULL) {
		rear = NULL;
	}

	free(del);
}

void que_deQueue_space(Que* where) {
	Que* del_before;
	Que* del_where;

	del_before = where;
	del_where = where->next;
	del_before->next = del_where->next;

	if (del_where->next == NULL) {
		rear = del_before;
	}

	free(del_where);
}

void que_check_grammar(void) {
	int sign = 0;
	int open_bracket = 0;
	int close_bracket = 0;
	int error_openclose = 0;
	int num_signal = 0;
	int opt_signal = 0;
	int space_signal = 0;
	int error_cnt = 0;
	Que* check;

	check = front;

	while (check->next != NULL) {
		if (check->next->data == ' ') {
			space_signal++;
			que_deQueue_space(check);
		} else {
			check = check->next;
		}
	}

	if (front->data == ' ') {
		space_signal++;
		que_deQueue();
	}

	check = front;

	while (check != NULL) {
		error_cnt++;

		if (check->data != 37 && !(check->data >= 40 && check->data <= 43)
		&& check->data != 45 && check->data != 47
		&& !(check->data >= 48 && check->data <= 57) && check->data != 94) {
			printf("[Error] : 0 ~ 9와 +, -, *, /, %%, ^, (, ) 의 기호만 입력할 수 있습니다.\n");
			printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
			sign++; 
		} else {
			if (check->data == '(') {
				open_bracket++;
			}

			if (check->data == ')') {
				close_bracket++;
			}

			if (check->data >= '0' && check->data <= '9') {
				num_signal++;
			}

			if (check->data == '+' || check->data == '-'
			|| check->data == '*' || check->data == '/'
			|| check->data == '%' || check->data == '^'
			|| check->data == '(' || check->data == ')') {
				opt_signal++;
			}

			if (error_openclose == 0 && open_bracket < close_bracket) {
				printf("[Error] : 닫는 괄호가 여는 괄호보다 먼저일 수 없습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
				sign++;
				error_openclose = 1;
			}

			if (check == rear) {
				if (check->data == '+' || check->data == '-'
				|| check->data == '*' || check->data == '/'
				|| check->data == '%' || check->data == '^'
				|| check->data == '(') {
					printf("[Error] : 마지막 입력 데이터는 숫자이거나, 닫힌 괄호이어야 합니다.\n");
					printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
					sign++; 
				}	
			}

			if (check == front) {
				if (check->data == '+' || check->data == '-'
				|| check->data == '*' || check->data == '/'
				|| check->data == '%' || check->data == '^') {
					printf("[Error] : 수식의 시작은 열린 괄호이거나, 숫자이어야 합니다.\n");
					printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
					sign++; 
				}
			}

			if (check->next != NULL) { 
				if ((check->data >= '0' && check->data <= '9') && check->next->data == '(') {
					printf("[Error] : 피연산자 다음으로 열린 괄호가 올 수 없습니다.\n");
					printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt + 1, check->next->data);
					sign++;
				}

				if (check->data == ')' && (check->next->data >= '0' && check->next->data <= '9')) {
					printf("[Error] : 닫힌 괄호 다음으로 피연산자가 올 수 없습니다.\n");
					printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt + 1, check->next->data);
					sign++;
				}

				if ((check->data == '+' || check->data == '-'
				|| check->data == '*' || check->data == '/'
				|| check->data == '%' || check->data == '^'
				|| check->data == '(') && !(check->next->data >= '0' && check->next->data <= '9')
				&& check->next->data != '(') {
					if (check->data == '(' && (check->next->data == '+'
					|| check->next->data == '-' || check->next->data == '*'
					|| check->next->data == '/' || check->next->data == '%'
					|| check->next->data == '^')) {
						printf("[Error] : 열린 괄호 다음으로 연산자가 올 수 없습니다.\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt + 1, check->next->data);
						sign++; 
					} else if (check->data == '(' && check->next->data == ')') {
						printf("[Error] : 괄호 안에는 수식이 존재해야 합니다.\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt + 1, check->next->data);
						sign++; 
					} else if ((check->data == '+' || check->data == '-'
					|| check->data == '*' || check->data == '/'
					|| check->data == '%' || check->data == '^')
					&& check->next->data == ')') {
						printf("[Error] : 닫는 괄호 전에 연산자가 존재할 수 없습니다.\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
						sign++; 
					} else if ((check->data == '+' || check->data == '-'
					|| check->data == '*' || check->data == '/'
					|| check->data == '%' || check->data == '^')
					&& (check->next->data == '+' || check->next->data == '-'
					|| check->next->data == '*' || check->next->data == '/'
					|| check->next->data == '%' || check->next->data == '^')) { 
						printf("[Error] : 연산자는 연속적으로 입력될 수 없습니다.\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt + 1, check->next->data);
						sign++; 
					}
				}
			}		
		}

		check = check->next;
	}

	if (open_bracket - close_bracket != 0) {
		printf("[Error] : 괄호의 짝이 맞지않습니다.\n\n");
		sign++;
	}

	if (space_signal > 0 && (num_signal == 0 && opt_signal == 0)) {
		printf("[Error] : 입력이 모두 공백입니다. \n\n");
		sign++;
	}

	if (num_signal == 0 && opt_signal > 0) {
		printf("[Error] : 피연산자가 입력되어야 합니다. \n\n");
		sign++;
	}

	if (sign > 0) {
		printf("[Error Count]-----------------------\n");
		printf("오류 메시지의 개수 : %d 개\n",sign);
		printf("------------------------------------\n\n");
		exit(-1);
	}
}

void que_toStack(int len) {
	char qToStack[len];
	int cnt = 0;
	int checksign_signal;

	que_check_grammar();

	for (int i = 0; i < len; i++) {
		qToStack[i] = '\0';
	}

	while (1) {
		if (front->data >= '0' && front->data <= '9') {
			qToStack[cnt++] = front->data;
			que_deQueue();

			if (front == NULL && rear == NULL) {
				stk_pushNum((double) atoi(qToStack));
				break;
			}

			if (front->data == ' ' || front->data == '+'
			|| front->data == '-' || front->data == '*'
			|| front->data == '/' || front->data == '%'
			|| front->data == '^' || front->data == ')') { 
				stk_pushNum((double) atoi(qToStack));
				cnt = 0;

				for (int i = 0; i < len; i++) {
					qToStack[i] = '\0';
				}
			}
		}

		if (front->data == '+' || front->data == '-'
		|| front->data == '*' || front->data == '/'
		|| front->data == '%'	|| front->data == '^'
		|| front->data == '(' || front->data == ')') {
			checksign_signal = cal_checkSign(front->data);

			if (checksign_signal == 1) {
				while (front != NULL) {
					que_deQueue();
				}

				break;
			}

			que_deQueue();

			if (front == NULL && rear == NULL) {
				break;
			}
		}
	}
}

void que_toStack_end(void) {
	int calcur_signal;

	while (topS != NULL) {
		calcur_signal = cal_calcur(topS->data);
		
		if (calcur_signal == 1) {
			return;
		}
	}
	
	cal_result();
}