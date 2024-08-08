#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define DATOS 5
#define MAX_LENGTH 30

int lengthPasajeros;
int contadores[4] = {0, 0, 0, 0};
double importe[4] = {0, 0, 0, 0};
char datos[4][3][MAX_LENGTH] =
    {
        {"Brasil", "BRA", "25000"},
        {"Mar del Plata", "MDQ", "14000"},
        {"Mendoza", "MZA", "19000"},
        {"Bariloche", "BRC", "23000"},
};

int menoresCinco[4] = {0, 0, 0, 0};

void mostrarMenu()
{

    printf("\nMenu\n1. Mostrar lista de pasajeros ordenada por Apellido y Nombre\n2. Mostrar lista de pasajeros ordenada por Codigo Destino y Apellido - Nombre\n3. Mostrar lista de Destinos\n4. Buscar por pasajero\n5. Mostrar estadisticas\n6. Salir\n");
}

void validarDNI(char dni[MAX_LENGTH])
{
    printf("Ingrese su DNI\n");
    scanf("%s", dni);

    bool validacion1 = true;
    bool validacion2 = false;
    bool validacion3 = false;
    int longitud = strlen(dni);

    for (int i = 0; i < longitud; i++)
    {
        if (!isdigit(dni[i]))
        {
            validacion1 = false;
            break;
        }
    }

    if (longitud == 8 || longitud == 7)
    {
        validacion2 = true;
    }

    int primerDigito = dni[0] - '0';
    int segundoDigito = (dni[1] - '0') * 10 + (dni[2] - '0');
    if ((primerDigito == 5 || primerDigito == 6) && (segundoDigito <= 60 || segundoDigito >= 10))
    {
        validacion3 = true;
    }

    if (!validacion1 || !validacion2 || !validacion3)
    {
        printf("Su DNI es invalido\n");
        validarDNI(dni);
    }
}

void validarDestino(int opcion, int i, char edad[MAX_LENGTH], char pasajeros[][DATOS][MAX_LENGTH], bool *bandera)
{
    int index = opcion - 1;
    int formaPago;
    double convertirNumero = atof(datos[index][2]);
    strcpy(pasajeros[i][3], datos[index][1]);
    do
    {
        printf("Desea abonar con tarjeta de credito? 1-Si 2-No\n");
        scanf("%d", &formaPago);
        if (formaPago != 1 && formaPago != 2)
        {
            printf("Ingrese una forma de pago valida\n");
        }

    } while (formaPago != 1 && formaPago != 2);

    if (contadores[index] < 60)
    {
        double resultado;
        if (formaPago != 1)
        {
            if (atof(edad) < 5)
            {
                menoresCinco[index]++;
                importe[index] += 2000;
                resultado = 2000;
                //convierte un double en string almacenandolo en pasajeros i 4
                snprintf(pasajeros[i][4], sizeof(pasajeros[i][4]), "%.2lf", resultado);
            }
            else
            {
                importe[index] += convertirNumero;
                resultado = convertirNumero;
                snprintf(pasajeros[i][4], sizeof(pasajeros[i][4]), "%.2lf", resultado);
            }
        }
        else
        {
            if (atof(edad) < 5)
            {
                menoresCinco[index]++;
                importe[index] += 2000 * 1.05;
                resultado = 2000 * 1.05;
                snprintf(pasajeros[i][4], sizeof(pasajeros[i][4]), "%.2lf", resultado);
            }
            else
            {
                importe[index] += convertirNumero * 1.05;
                resultado = convertirNumero * 1.05;
                snprintf(pasajeros[i][4], sizeof(pasajeros[i][4]), "%.2lf", resultado);
            }
        }

        contadores[index]++;
    }
    else
    {
        printf("No hay cupos para el destino %s \n", datos[index][1]);
        *bandera = false;
    }
}

void cargarPasajeros(char pasajeros[][DATOS][MAX_LENGTH])
{
    int opcion = 1;
    char dni[MAX_LENGTH];
    char nombre[MAX_LENGTH];
    char apellido[MAX_LENGTH];
    char apellidoNombre[MAX_LENGTH];
    char edad[MAX_LENGTH];
    bool bandera;

    for (int i = 0; i < lengthPasajeros; i++)
    {
        validarDNI(dni);
        strcpy(pasajeros[i][0], dni);

        printf("Ingrese su nombre\n");
        scanf("%s", nombre);
        printf("Ingrese su apellido\n");
        scanf("%s", apellido);

        strcpy(apellidoNombre, (strcat(strcat(apellido, " "), nombre)));
        strcpy(pasajeros[i][1], apellidoNombre);

        printf("Ingrese su edad\n");
        scanf("%s", edad);
        strcpy(pasajeros[i][2], edad);

        do
        {

            printf("Seleccione el destino deseado\n1-Brasil\n2-Mar del Plata\n3-Mendoza\n4-Bariloche\n");
            scanf("%d", &opcion);
            if (opcion < 1 || opcion > 4)
            {
                printf("Destino no encontrado\n");
                bandera = false;
            }

            else
            {
                bandera = true;
                validarDestino(opcion, i, edad, pasajeros, &bandera);
            }
        } while (opcion < 1 || opcion> 4 );
    }
}

void ordenarPorApellidoNombre(char pasajeros[][DATOS][MAX_LENGTH])
{
    // Ordenar pasajeros por apellido y nombre

    char aux[MAX_LENGTH];
    for (int i = 0; i < lengthPasajeros - 1; i++)
    {
        for (int j = i + 1; j < lengthPasajeros; j++)
        {
            if (strcmp(pasajeros[i][1], pasajeros[j][1]) > 0)
            {
                for (int k = 0; k < DATOS; k++)
                {
                    strcpy(aux, pasajeros[i][k]);
                    strcpy(pasajeros[i][k], pasajeros[j][k]);
                    strcpy(pasajeros[j][k], aux);
                }
            }
        }
    }

    printf("%-20s %-15s %-15s %-15s\n", "Apellido Nombre", "DNI", "Edad", "Codigo");
    for (int i = 0; i < lengthPasajeros; i++)
    {
        printf("%-20s %-15s %-15s %-15s\n", pasajeros[i][1], pasajeros[i][0], pasajeros[i][2], pasajeros[i][3]);
    }
}

void ordenarPorCodigoDestinoApellido(char pasajeros[][DATOS][MAX_LENGTH])
{
    // Ordenar pasajeros por código de destino y apellido
    char aux[MAX_LENGTH];
    for (int i = 0; i < lengthPasajeros - 1; i++)
    {
        for (int j = i + 1; j < lengthPasajeros; j++)
        {
            if (strcmp(pasajeros[i][3], pasajeros[j][3]) > 0)
            {
                for (int k = 0; k < DATOS; k++)
                {
                    strcpy(aux, pasajeros[i][k]);
                    strcpy(pasajeros[i][k], pasajeros[j][k]);
                    strcpy(pasajeros[j][k], aux);
                }
            }
        }
    }

    printf("%-10s %-20s %-15s %-15s\n", "Codigo", "Apellido Nombre", "DNI", "Edad");
    for (int i = 0; i < lengthPasajeros; i++)
    {
        printf("%-10s %-20s %-15s %-15s\n", pasajeros[i][3], pasajeros[i][1], pasajeros[i][0], pasajeros[i][2]);
    }
}

void mostrarListaDeDestinos(char pasajeros[][DATOS][MAX_LENGTH])
{
    printf("%-15s %-10s %-10s\n", "Destino", "Pasajeros", "Importe");
    for (int i = 0; i < 4; i++)
    {
        printf("%-15s %-10d %.2lf\n", datos[i][0], contadores[i], importe[i]);
    }
}

void buscarPorPasajero(char pasajeros[][DATOS][MAX_LENGTH])
{
    char dni[MAX_LENGTH];
    int bandera = 0;
    validarDNI(dni);

    for (int i = 0; i < lengthPasajeros; i++)
    {
        if (strcmp(dni, pasajeros[i][0]) == 0)
        {
            printf("DNI: %s \nApellido Nombre: %s\nEdad: %s\nDestino: %s\nImporte: $%s\n", pasajeros[i][0], pasajeros[i][1], pasajeros[i][2], pasajeros[i][3], pasajeros[i][4]);
            bandera = 1;
            break;
        }
    }

    if (bandera == 0)
    {
        printf("Pasajero no encontrado\n");
    }
}

void mostrarEstadisticas()
{
    double porcentajePorDestino[4] = {0, 0, 0, 0};
    double porcentajePorDestinoMenores[4] = {0, 0, 0, 0};
    int mayor = contadores[0];
    int posicionMayor[4] = {0};
    int cantidadMayores = 1;
    int totalMenoresCinco = 0;

    for (int i = 1; i < 4; i++)
    {
        if (contadores[i] > mayor)
        {
            mayor = contadores[i];
            posicionMayor[0] = i;
            cantidadMayores = 1;
        }
        else if (contadores[i] == mayor)
        {
            posicionMayor[cantidadMayores++] = i;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        totalMenoresCinco += menoresCinco[i];
        if (contadores[i] != 0)
        {
            porcentajePorDestinoMenores[i] = ((double)menoresCinco[i] / (double)contadores[i]) * 100;
            porcentajePorDestino[i] = ((double)contadores[i] / (double)lengthPasajeros) * 100;
        }
        else
        {
            porcentajePorDestinoMenores[i] = 0;
            porcentajePorDestino[i] = 0;
        }
    }

    printf("Pasajeros: %d\nMenores de 5: %d\n", lengthPasajeros, totalMenoresCinco);

    if (cantidadMayores == 1)
    {
        printf("Destino mas solicitado fue: %s\n", datos[posicionMayor[0]][0]);
    }
    else
    {
        printf("Los destinos mas solicitados fueron: ");
        for (int i = 0; i < cantidadMayores; i++)
        {
            printf("%s", datos[posicionMayor[i]][0]);
            if (i < cantidadMayores - 1)
            {
                printf(", ");
            }
        }
        printf("\n");
    }

    printf("\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Destino: %s\nPorcentaje de pasajeros: %.2lf%%\nPorcentaje de menores de 5 anios: %.2lf%%\n", datos[i][0], porcentajePorDestino[i], porcentajePorDestinoMenores[i]);
        printf("\n");
    }
}

int main()
{
    int opcion;
    printf("Ingrese la cantidad de pasajeros\n");
    scanf("%d", &lengthPasajeros);

    char pasajeros[lengthPasajeros][DATOS][MAX_LENGTH];
    cargarPasajeros(pasajeros);

    do
    {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            ordenarPorApellidoNombre(pasajeros);
            break;
        case 2:
            ordenarPorCodigoDestinoApellido(pasajeros);
            break;
        case 3:
            mostrarListaDeDestinos(pasajeros);
            break;
        case 4:
            buscarPorPasajero(pasajeros);
            break;
        case 5:
            mostrarEstadisticas();
            break;
        case 6:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida. Por favor intente nuevamente.\n");
        }
    } while (opcion != 6);

    return 0;
}
