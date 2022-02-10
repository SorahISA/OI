#include <cstdio>
#include <cstring>
#include <algorithm>

#pragma warning(disable:4996)

using namespace std;

const int maxn = 40000 + 10;
const int x = 17;

char s[maxn];
int n, m, pos;
int rak[maxn];
unsigned long long H[maxn], xp[maxn], hah[maxn];

bool cmp(const int& a, const int& b) {
	return hah[a] < hah[b] || (hah[a] == hah[b] && a < b);
}

void getH() {
	H[n] = 0;
	for (int i = n - 1; i >= 0; i--) H[i] = H[i + 1] * x + (s[i] - 'a');
}

void getXp() {
	xp[0] = 1;
	for (int i = 1; i <= n; i++) xp[i] = xp[i - 1] * x;
}

bool possible(int L) {
	int cnt = 0;
	pos = -1;
	for (int i = 0; i <= n - L; i++) {
		rak[i] = i;
		hah[i] = H[i] - H[i + L] * xp[L];
	}
	sort(rak, rak + n - L + 1, cmp);
	for (int i = 0; i <= n - L; i++) {
		if (!i || hah[rak[i]] != hah[rak[i - 1]]) cnt = 0;
		if (++cnt >= m) pos = max(pos, rak[i]);
	}
	return pos >= 0;
}

void solve() {
	n = (int)strlen(s);
	getH();
	getXp();
	if (!possible(1)) puts("none");
	else {
		int L = 1, R = n + 1;
		while (R - L > 1) {
			int M = (L + R) >> 1;
			if (possible(M)) L = M;
			else R = M;
		}
		possible(L);
		printf("%d %d\n", L, pos);
	}
}

int main()
{
	scanf("%d", &m);
	scanf("%s", s);
	solve();
	
	return 0;
}
