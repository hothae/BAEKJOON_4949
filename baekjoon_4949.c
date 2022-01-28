#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>

#define SIZE 100

char stack[SIZE];		//괄호들만 담길 배열이므로 사용자로부터 입력받는 문자열은 다른 곳에다가 저장해야 함.
int top = -1;

int push(char data) {
	if (top > SIZE) return -1;	//만약 스택이 꽉찼으면,
	return stack[++top] = data;	//그렇지 않으면 문자 하나 담기, 여기서 data는 괄호
}

int pop() {
	if (top < 0) return -1;	//이미 스택이 비어있으면 pop할 이유가없으므로
	else return stack[top--] = '\0';	//그게 아닌 경우 해당 스택의 top값을 낮추고 낮추기전 배열에있던 값은 지우고 NULL로 대체
}

char peek() {	//바로 직전에 스택에 담긴 값, 비교용으로 반드시 필요
	return stack[top];
}

void result(char* ch,int size) {
	for (int i = 0; i < size; i++) {	//size는 문자열의 길이 만큼만 반복해서 비교함
			if (ch[i] == '[' || ch[i] == ']' || ch[i] == '(' || ch[i] == ')') {	//해당 문자들만 스택에 쌓임
				if (top == -1) push(ch[i]);		//만약 스택이 비었을 때 입력되면, 즉 맨처음에는 반드시 그냥 스택에 쌓임
				else {	//그 이후
					if (peek() == '(' && ch[i] == ')') pop();	// 직전에 스택에 담긴 문자가 ( 인데 그다음에 담기는 값이 ) 이면 짝찾기 성공, pop함수 실행
					else if (peek() == '[' && ch[i] == ']') pop();	//직전에 스택에 담긴 문자가 [ 인데 그다음에 담기는 값이 ] 이면 짝찾기 성공, pop함수 실행
					else push(ch[i]);					//짝찾기가 실패 해도, 해당 네개의 문자열은 스택에 담겨야 함. ★이 부분이 처음에 없어서 디버깅 오류가 났었음★
				}
			}
		}
	if (top == -1) printf("yes\n");		//top = -1 이면, 해당 문자열들이 짝을찾아서 다 pop에 의해 빠져나갔으므로 완벽한 문장
	else printf("no\n");
}

int main() {
	char str[SIZE];	//사용자로부터 입력받을 문자열, 괄호만 입력받을것이 아니기 때문에
	while (1) {
		top = -1;	// 전역변수로 선언했지만 한번 더 선언 해줌
		gets(str);	// 공백문자를 포함해서 줄바꿈 문자'\n' 입력받을 때까지 문자열 받기 scanf랑 다름.
		if (strcmp(str,".") == 0) break;	//만약 입력받은 문자열이 . 하나이면 프로그램 종료
		else result(str, strlen(str));	//그게 아닌 경우 입력받은 문자열중 괄호만을 스택에 담아 완벽한 문장인지 찾는 과정
	}

	return 0;
}

/*
스택을 이용해 ()[] 중괄호 대괄호 짝찾기
입력받는 문자열을 공백문자 포함해서 입력받으려면
scanf() 가 아닌, gets()를 이용해야 하며
입력받는 문자열중 ()[] 가 입력되었을 때,
스택이 비어있으면 무조건 스택에 해당 값을 집어넣고
그 이후에 들어오는 문자를 비교함

비교하기 위해 이전에 입력된 문자가 무엇인지를 반환하는 함수 peek() 필요
바로 이전에 스택에 담긴 문자가 ( 일때 이다음으로 스택에 담기는 문자가 ) 이면 문자열 내에서 짝이므로 pop 을 통해 top의 값을 1 낮춤
이과정을 반복해서 스택내에서 top의 값으로 짝찾기 완료 유무 여부에 따른 출력
*/