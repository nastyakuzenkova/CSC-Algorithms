#include <stdio.h>

 int main()
 {
  int n = 0;
  long m = 1;
  scanf("%d %ld", &n, &m);
  long const bound = m * m;
  long matrix_a[n][n];
  for (int i = 0; i < n; ++i) {
   for (int j = 0; j < n; ++j) {
    scanf("%ld", &matrix_a[i][j]);
   }
  }
  long matrix_b[n][n];
  for (int i = 0; i < n; ++i) {
   for (int j = 0; j < n; ++j) {
 	scanf("%ld", &matrix_b[j][i]);
   }
  }
  
  for (int i = 0; i < n; ++i) {
   for (int j = 0; j < n; ++j) {
    long x = 0;
    for (int k = 0; k < n; ++k) {
     if (x > bound) {
      x -= bound;
     }
     x += matrix_a[i][k] * matrix_b[j][k];;
    }
 printf("%ld ", (x % m));    
   }
   printf("\n");
  }
  
  return 0;
 }