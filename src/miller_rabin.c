#include "miller_rabin.h"
#include <stdlib.h>
#include <stdio.h>

// generate a random number less than or equal to x
int random_number(int x) {
  int divisor = RAND_MAX/(x+1);
  int retval;
  do {
    retval = rand()/divisor;
  } while (retval > x);
  return retval;
}

// only positive exponents. Vulnerable to overflow
int power(int x, int y) {
  int ret = 1;
  if (y == 0) {
    return ret;
  }
  if (y < 0) {
    return -1;
  }
  for (int i = 0; i < y; ++i) {
    ret *= x;
  }
  return ret;
}

// calculate a^b mod n
int power_mod(int a, int b, int n) {
  long long x = 1, y = a;
  while (b > 0) {
    if (b%2 == 1) {
      x =(x*y)%n;
    }
    y = (y*y)%n;
    b /= 2;
  }
  return x%n;
}

bool miller_rabin(int x) {
  if (x < 2 || (x > 2 && x%2 == 0)) {
    return F;
  }
  int d = x-1;
  int s = 0;
  while (d % 2 == 0) {
    d = d / 2;
    ++s;
  }
  int k = 30;
  for(int i =0; i < k; ++i) {
    int a = random_number(x-1);
    if (a < 2) {
      a = 2;
    }
    for (int j = 0; j <  s; ++j) {
      int root  = power_mod(a,power(2,s)*d,x);
      if (root != 1 && root != x-1) {
	return F;
      }
    }
  }
  return T;
}

int main() {
  int x;
  scanf("%d", &x);
  while (x != 0) {
    printf("%d\n",miller_rabin(x));
    scanf("%d", &x);
  }
  return 0;
}
  
    
