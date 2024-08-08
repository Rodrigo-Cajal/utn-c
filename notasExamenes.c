#include <stdio.h>

int main() {
   int estudiantes = 1;
   float notas, sumaNotas, promedio;

do
{
    printf("Ingrese la nota del estudiante %d: ", estudiantes);
    scanf("%f", &notas);
    estudiantes++;
    sumaNotas += notas;
} while (estudiantes < 10);

    promedio = sumaNotas / 10;
    printf("El promedio de notas es: %0.2f", promedio);









    return 0;
}