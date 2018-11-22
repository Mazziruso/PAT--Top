#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int len;
int *patNext;
char *pattern;
char s[1048580];
bool visit[1048580];

void getNext() {
	//initialization
	fill_n(patNext, N + 1, -1);
	int j = -1;
	patNext[0] = -1;
	for (int i = 1; i < N; i++) {
		while (j != -1 && pattern[i] != pattern[j + 1]) {
			j = patNext[j];
		}
		if (pattern[i] == pattern[j + 1]) {
			j++;
		}
		patNext[i] = j;
	}
}

int matchCnt(int start) {
	int j = -1;
	int cnt = 0;
	for (int i = start; i < len - 1; i++) {
		while (j != -1 && s[i] != pattern[j + 1]) {
			j = patNext[j];
		}
		if (j == -1 && visit[j]) {
			continue;
		}
		if (s[i] == pattern[j + 1]) {
			j++;
		}
		if (j == N - 1) {
			cnt++;
			visit[i - N + 1] = true;
			j = patNext[j];
		}
	}
	return cnt;
}

int main() {
	//initialization
	fill_n(visit, 1048580, false);
	
	scanf_s("%d\n", &N);
	fgets(s, 1048580, stdin); //会读入'\n'，因此len会比原来多1

	patNext = new int[N + 1];
	pattern = new char[N + 1];
	len = strlen(s);

	char *resStr = new char[N + 1];
	int cnt;
	int max = -1;
	for (int i = 0; i <= len - N - 1; i++) {
		if (!visit[i]) {
			strncpy_s(pattern, N + 1, s + i, N);
			getNext();
			cnt = matchCnt(i);
			if (max < cnt) {
				max = cnt;
				strncpy_s(resStr, N + 1, pattern, N);
			}
			else if (max == cnt && strcmp(pattern, resStr) < 0) {
				strncpy_s(resStr, N + 1, pattern, N);
			}
		}
	}

	resStr[N] = '\0';
	printf("%s %d\n", resStr, max);


	system("pause");
	return 0;
}