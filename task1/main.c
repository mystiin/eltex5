#include <stdio.h>

int add(int a, int b);
int subt(int a, int b);

int main(int argc, char *argv[]) {

  if(argc != 3) {
    printf("Usage: %s x y\n", argv[0]);
    return 1;
  }

  int x = atoi(argv[1]);
  int y = atoi(argv[2]);

  int sum = add(x, y);
  int diff = subt(x, y);

  printf("sum: %d\n", sum);
  printf("diff: %d\n", diff);

  return 0;
}