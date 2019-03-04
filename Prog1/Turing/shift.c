#include <stdio.h>

int main() {
  int i = 1;
  int a = 0;
    while (i != 0) {
      i <<= 1;
      a++;
    }
  printf("Szóhossz: %d bit\n",a);
}
