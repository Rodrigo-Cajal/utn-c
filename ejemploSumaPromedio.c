#include <stdio.h>

int main() {
   int num1, num2, num3, num4, suma;
   float promedio;

    printf("Ingrese un numero:\n");
    scanf("%d", &num1);

    printf("Ingrese otro numero:\n");
    scanf("%d", &num2);

    printf("Ingrese otro numero:\n");
    scanf("%d", &num3);

    printf("Ingrese otro numero:\n");
    scanf("%d", &num4);

    suma=num1+num2+num3+num4;
    promedio=suma/4;

    printf("La suma entre los numeros es: %d\n", suma);

    printf("El promedio es: %0.2f", promedio);










    return 0;
}