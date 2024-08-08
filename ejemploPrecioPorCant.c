#include <stdio.h>

int main() {
  int cantidad;
  float precio, importe;

  printf("Ingrese el precio del producto:\n");
  scanf("%f", &precio);

  printf("Ingrese la cantidad del producto:\n");
  scanf("%d", &cantidad);

    importe=precio*cantidad;

    printf("El importe a abonar es: %0.2f", importe);











    return 0;
}