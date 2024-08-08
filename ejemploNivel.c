#include <stdio.h>

int main() {
    int porcentaje;

    printf("Ingrese el porcentaje de su prueba:\n");
    scanf("%d", &porcentaje);

    if (porcentaje>=90)
    {
        printf("Tiene un nivel maximo.");
    } else {
        if (porcentaje >= 75 && porcentaje < 90){
            printf("Tiene un nivel medio.");
        }
        else {
        if (porcentaje >= 50 && porcentaje < 75){
            printf("Tiene un nivel regular.");
        }else {
            printf("Esta fuera de nivel.");
        }
    }
    }











    return 0;
}