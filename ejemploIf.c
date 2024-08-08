#include <stdio.h>

int main() {
  int sueldo;

  printf("Ingrese su sueldo:\n");
  scanf("%d", &sueldo);

  if (sueldo>3000)
  {
    printf("Usted debe pagar impuestos.");
  }else{
    printf("Usted no debe pagar impuestos.");
  }












    return 0;
}