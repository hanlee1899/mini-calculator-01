# 간단한 계산기 만들기 01

계산기는 실행되면 식이 입력되기를 기다리고 식을 입력하고 [enter]를 입력하면 결과를 출력한다.  
어떠한 식도 입력하지 않은 상태에서 [enter]를 입력하면 프로그램이 종료된다.

---

계산기는 다음과 같은 연산자를 포함한다.  
이 연산자들의 우선 순위는 수학에서 일반적인 우선순위를 따른다.
* '+' : 덧셈
* '-' : 뺄셈
* '*' : 곱셈
* '/' : 나눗셈
* '%' : 나머지 연산
* '^' : 지수 승 연산
* '(', ')' : 소괄호를 이용한 연산 우선 순위 결정
  
---

계산기 요구사항
1. 정수만 입력되며 길이 제한은 없어야 한다.
2. 스택과 큐를 통해 구현되어야 한다.
3. 입력문은 수식이며 "bc", "노래"와 같은 문자열은 입력을 거부해야 한다.
4. 오류 메시지를 출력해야 한다.
5. 단항 연산자는 허용되지 않는다.
6. 입력 수식에 오류가 포함되었을 경우 이를 찾아 오류를 출력해야 한다.

---

계산기 실행 후 입력 예<br><br>

./calculator  
\>> 1+1+2-3  
result: 1

\>> 16/2/2  
result: 4

\>> 1 + 2 * (3 - 5) * 6  
result: -23

\>> 16/(2/2)  
result: 16

\>> 16 % 2 % 1  
result: 0

\>> 16 % (2 % 1)  
Modulo by zero

\>> 2^3  
result: 8

[enter]  
종료됨
