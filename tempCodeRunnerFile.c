#include <stdio.h>
#include <windows.h>

#define MAX_SIZE 100

// Función para imprimir un conjunto
void imprimirConjunto(int conjunto[], int size)
{
    printf("{ ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", conjunto[i]);
    }
    printf("}\n");
}

// Función para realizar la unión de dos conjuntos
void unionConjuntos(int conjuntoA[], int sizeA, int conjuntoB[], int sizeB)
{
    int unionResultante[MAX_SIZE];
    int i, j, k = 0;

    // Copiar elementos de conjuntoA a la unión
    for (i = 0; i < sizeA; i++)
    {
        unionResultante[k++] = conjuntoA[i];
    }

    // Copiar elementos de conjuntoB que no estén en conjuntoA
    for (i = 0; i < sizeB; i++)
    {
        int estaEnUnion = 0;
        for (j = 0; j < sizeA; j++)
        {
            if (conjuntoB[i] == conjuntoA[j])
            {
                estaEnUnion = 1;
                break;
            }
        }
        if (!estaEnUnion)
        {
            unionResultante[k++] = conjuntoB[i];
        }
    }

    // Imprimir el resultado de la unión
    imprimirConjunto(unionResultante, k);
}

// Función para realizar la intersección de dos conjuntos
void interseccionConjuntos(int conjuntoA[], int sizeA, int conjuntoB[], int sizeB)
{
    int interseccionResultante[MAX_SIZE];
    int i, j, k = 0;

    // Copiar elementos de conjuntoA que también estén en conjuntoB
    for (i = 0; i < sizeA; i++)
    {
        for (j = 0; j < sizeB; j++)
        {
            if (conjuntoA[i] == conjuntoB[j])
            {
                interseccionResultante[k++] = conjuntoA[i];
                break;
            }
        }
    }

    // Imprimir el resultado de la intersección
    imprimirConjunto(interseccionResultante, k);
}

// Función para realizar la diferencia de dos conjuntos
void diferenciaConjuntos(int conjuntoA[], int sizeA, int conjuntoB[], int sizeB)
{
    int diferenciaResultante[MAX_SIZE];
    int i, j, k = 0;

    // Copiar elementos de conjuntoA que no estén en conjuntoB
    for (i = 0; i < sizeA; i++)
    {
        int estaEnConjuntoB = 0;
        for (j = 0; j < sizeB; j++)
        {
            if (conjuntoA[i] == conjuntoB[j])
            {
                estaEnConjuntoB = 1;
                break;
            }
        }
        if (!estaEnConjuntoB)
        {
            diferenciaResultante[k++] = conjuntoA[i];
        }
    }

    // Imprimir el resultado de la diferencia
    imprimirConjunto(diferenciaResultante, k);
}

int main()
{
    int conjuntoA[MAX_SIZE];
    int sizeA;
    int conjuntoB[MAX_SIZE];
    int sizeB;
    int opcion;

    do
    {
        printf("Ingrese el tamaño del conjunto A: ");
        scanf("%d", &sizeA);
        printf("Ingrese los elementos del conjunto A: ");
        for (int i = 0; i < sizeA; i++)
        {
            scanf("%d", &conjuntoA[i]);
        }

        printf("Ingrese el tamaño del conjunto B: ");
        scanf("%d", &sizeB);
        printf("Ingrese los elementos del conjunto B: ");
        for (int i = 0; i < sizeB; i++)
        {
            scanf("%d", &conjuntoB[i]);
        }

        printf("Conjunto A: ");
        imprimirConjunto(conjuntoA, sizeA);

        printf("Conjunto B: ");
        imprimirConjunto(conjuntoB, sizeB);

        printf("Unión: ");
        unionConjuntos(conjuntoA, sizeA, conjuntoB, sizeB);

        printf("Intersección: ");
        interseccionConjuntos(conjuntoA, sizeA, conjuntoB, sizeB);

        printf("Diferencia (A - B): ");
        diferenciaConjuntos(conjuntoA, sizeA, conjuntoB, sizeB);

        printf("Diferencia (B - A): ");
        diferenciaConjuntos(conjuntoB, sizeB, conjuntoA, sizeA);
        

        printf("¿Desea volver a ingresar los datos? Presione 1 para sí o 0 para salir: ");
        Sleep(30000);
        scanf("%d", &opcion);

    } while (opcion == 1);

    return 0;
}