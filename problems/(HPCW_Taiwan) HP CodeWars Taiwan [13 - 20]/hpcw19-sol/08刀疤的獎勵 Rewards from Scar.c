#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 50001
int a[MAXN];
int b[MAXN];
int a_t[MAXN];
int b_t[MAXN];
int comp_int(const void *i, const void *j){
  return *(int *)i - *(int *)j;
}
int main(){
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  for(int i = 0; i < n; i++)
    scanf("%d", a + i);
  for(int i = 0; i < m; i++)
    scanf("%d", b + i);
  a[n++] = b[m++] = 0;
  qsort(a, n, sizeof(int), comp_int);
  qsort(b, m, sizeof(int), comp_int);
  for(int i = 0; i < n; i++)
    a_t[i] = 1;
  for(int i = 0; i < m; i++)
    b_t[i] = 1;
  int a_n = 0, b_n = 0;
  for(int i = 1; i < n; i++)
    a[i] == a[a_n] ? a_t[a_n]++ : (a[++a_n] = a[i]);
  for(int i = 1; i < m; i++)
    b[i] == b[b_n] ? b_t[b_n]++ : (b[++b_n] = b[i]);
  for(int i = 0, x; i < q; i++){
    scanf("%d", &x);
    int s = 0, r = b_n, c = 0;
    while(s <= a_n && r >= 0){
      int sum = a[s] + b[r];
      if(sum == x){
        c += a_t[s] * b_t[r];
        r--, s++;
      }
      else
        sum > x ? r-- : s++;
    }
    printf("%d%c", c, i == q - 1 ? '\n' : ' ');
  }
  return 0;
}
