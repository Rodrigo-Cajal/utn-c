#include <stdio.h>

int main() {
    int num1, num2, num3, num4, suma, producto;

    printf("Ingrese un numero:\n");
    scanf("%d", &num1);

    printf("Ingrese otro numero:\n");
    scanf("%d", &num2);

    printf("Ingrese otro numero:\n");
    scanf("%d", &num3);

    printf("Ingrese otro numero:\n");
    scanf("%d", &num4);

    suma=num1+num2;
    producto=num3*num4;

    printf("La suma entre los dos primeros numeros es: %d\n", suma);

    printf("El producto entre los dos ultimos numeros es: %d\n", producto);










    return 0;
}