#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define DATOS 5
#define MAX_LENGTH 30
const int lengthPasajeros;
int contadores[4] = {0, 0, 0, 0};
double importe[4] = {0, 0, 0, 0};
double precios[4] = {25000, 14000, 19000, 23000};
char *codigos[4] = {"BRA", "MDQ", "MZA", "BRC"};
int menoresCinco[4] = {0, 0, 0, 0} ;

void mostrarDatos(char pasajeros[][DATOS][MAX_LENGTH])
{
    int maxLongitud[DATOS] = {0}; // Array para almacenar las longitudes máximas por columna

    // Calcula las longitudes máximas para cada columna
    for (int i = 0; i < lengthPasajeros; i++)
    {
        for (int j = 0; j < DATOS; j++)
        {
            int longitudActual = strlen(pasajeros[i][j]);
            if (longitudActual > maxLongitud[j])
            {
                maxLongitud[j] = longitudActual;
            }
        }
    }

    // Muestra los datos con alineación
    printf("\n");
    for (int i = 0; i < lengthPasajeros; i++)
    {
        for (int j = 0; j < DATOS; j++)
        {
            printf("%-*s\t", maxLongitud[j] + 2, pasajeros[i][j]); // Alineación izquierda
        }
        printf("\n");
    }
}

int mostrarMenu()
{
    printf("\nMenu\n1. Mostrar lista de pasajeros ordenada por Apellido y Nombre\n2. Mostrar lista de pasajeros ordenada por Codigo Destino y Apellido - Nombre\n3. Mostrar lista de Destinos\n4. Buscar por pasajero\n5. Mostrar estadisticas\n6. Salir\n");

    return 0;
}

void validarDNI(char dni[MAX_LENGTH])
{

    printf("Ingrese su DNi\n");
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

    // esto aprovecha la taba ascii para poder calculcar los numeros
    int primerDigito = dni[0] - '0';
    int segundoDigito = (dni[1] - '0') * 10 + (dni[2] - '0');
    if ((primerDigito == 5 || primerDigito == 6) && (segundoDigito <= 60 || segundoDigito >= 10))
    {
        validacion3 = true;
    }

    /*     if (validacion1 && validacion2 && validacion3)
        {
            printf("Se valido su dni con exito\n");
        }
        else
        {
            printf("Su dni es invalido\n");
            validarDNI(dni);
        } */

    if (!validacion1 || !validacion2 || !validacion3)
    {
        printf("Su dni es invalido\n");
        validarDNI(dni);
    }
}

void validarDestino(int opcion, int i, char edad[MAX_LENGTH], char pasajeros[][DATOS][MAX_LENGTH], bool bandera)
{
    int index = opcion - 1;
    int formaPago;
    char precio[MAX_LENGTH];

    strcpy(pasajeros[i][3], codigos[index]);
    printf("Desea abonar con tarjeta de credito?1-Si 2-No\n");
    scanf("%d", &formaPago);

    if (contadores[index] <= 60)
    {

        if (formaPago !=1)
        {
            if (atof(edad) < 5)
            {
                menoresCinco[index]++;
                importe[index] += 2000;
                
            }
            else
            {

                importe[index] += precios[index];
            }
        }
        else
        {
            if (atof(edad) < 5)
            {
                menoresCinco[index]++;
                importe[index] += 2000*1.05;
            }
            else
            {

                importe[index] += precios[index]*1.05;
            }
        }

        contadores[index]++;
    }
    else
    {
        printf("no hay cupos para el destino %s \n", codigos[index]);
        bandera = false;
    }
}

int cargarPasajeros(char pasajeros[][DATOS][MAX_LENGTH])
{

    int opcion = 1;
    char dni[MAX_LENGTH];
    char nombre[MAX_LENGTH];
    char apellido[MAX_LENGTH];
    char apellidoNombre[MAX_LENGTH];
    char edad[MAX_LENGTH];
    char codigoDestino[MAX_LENGTH];
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
            bandera = true;
            if (opcion < 1 || opcion > 4)
            {
                printf("destino no encontrado\n");
            }
            
            printf("Seleccione el destino deseado\n1-Brasil\n2-Mar del Plata\n3-Mendoza\n4-Bariloche\n");
            scanf("%d", &opcion);
            validarDestino(opcion, i, edad, pasajeros, bandera);

        } while (opcion < 1 || opcion > 4 || bandera == false);
    }

    return 0;
};

void crearCopia(char pasajeros[][DATOS][MAX_LENGTH], char copia[][DATOS][MAX_LENGTH])
{

    for (size_t i = 0; i < lengthPasajeros; i++)
    {
        for (int j = 0; j < DATOS; j++)
        {
            strcpy(copia[i][j], pasajeros[i][j]);
        }
    }
}

void ordenarPorApellidoNombre(char pasajeros[][DATOS][MAX_LENGTH], char copia[][DATOS][MAX_LENGTH])
{
    char aux[MAX_LENGTH];
    for (int i = 0; i < lengthPasajeros - 1; i++)
    {
        for (int j = i + 1; j < lengthPasajeros; j++)
        {
            if (strcmp(pasajeros[i][1], pasajeros[j][1]) > 0)
            {
                for (int k = 0; k < DATOS; k++)
                {
                    strcpy(aux, copia[i][k]);
                    strcpy(copia[i][k], copia[j][k]);
                    strcpy(copia[j][k], aux);
                }
            }
        }
    }
    for (int i = 0; i < lengthPasajeros; i++)
    {
        char auxiliar[MAX_LENGTH];
        strcpy(auxiliar, copia[i][0]);
        strcpy(copia[i][0], copia[i][1]);
        strcpy(copia[i][1], auxiliar);
    }

    mostrarDatos(copia);
}

void ordenarPorCodigoDestinoApellido(char pasajeros[][DATOS][MAX_LENGTH], char copia[][DATOS][MAX_LENGTH])
{
    char aux[MAX_LENGTH];

    for (int i = 0; i < lengthPasajeros - 1; i++)
    {
        for (int j = i + 1; j < lengthPasajeros; j++)
        {
            if (strcmp(pasajeros[i][3], pasajeros[j][3]) > 0)
            {
                for (int k = 0; k < DATOS; k++)
                {
                    strcpy(aux, copia[i][k]);
                    strcpy(copia[i][k], copia[j][k]);
                    strcpy(copia[j][k], aux);
                }
            }
        }
    }

    for (int j = 0; j < lengthPasajeros; j++)
    {
        char auxiliar[MAX_LENGTH];
        strcpy(auxiliar, copia[j][0]);
        strcpy(copia[j][0], copia[j][3]);
        strcpy(copia[j][3], auxiliar);
    }

    for (int i = 0; i < lengthPasajeros; i++)
    {
        char auxiliar[20];
        strcpy(auxiliar, copia[i][2]);
        strcpy(copia[i][2], copia[i][3]);
        strcpy(copia[i][3], auxiliar);
    }

    mostrarDatos(copia);
}

void mostrarListaDeDestinos(char pasajeros[][DATOS][MAX_LENGTH])
{
    printf("%-15s %-10s %-10s\n", "Destino", "Pasajeros", "Importe");
    for (int i = 0; i < 4; i++)
    {
        printf("%-15s %-10d %.2lf\n", codigos[i], contadores[i], importe[i]);
    }
}

void buscarPorPasajero(char pasajeros[][DATOS][MAX_LENGTH])
{
    char dni[MAX_LENGTH];
    int bandera = 0;
    validarDNI(dni);

    for (int i = 0; i < lengthPasajeros; i++)
    {
        if (strcmp(pasajeros[i][0], dni) == 0)
        {
            printf("DNI: %s \n", pasajeros[i][0]);
            printf("Apellido Nombre: %s \n", pasajeros[i][1]);
            printf("Edad: %s \n", pasajeros[i][2]);
            printf("Destino: %s \n", pasajeros[i][3]);

            //falta el importe
            //printf("Importe: %.2lf \n", pasajeros[i][4]);

            bandera = 1;
        }
    }
    if (bandera == 0)
    {

        printf("No existe pasajero con ese DNI.\n");
    }
}








void mostrarEstadisticas(char pasajeros[][DATOS][MAX_LENGTH])
{
    double porcentajePorDestino[4] = {0};
    int totalPasajeros = 0;
    int destinoMasSolicitado = 0;
    double porcentajeMenoresCinco[4] = {0};

    // porcentaje de pasajeros por destino
    for (int i = 0; i < 4; i++)
    {
        totalPasajeros += contadores[i];
    }

    for (int i = 0; i < 4; i++)
    {
        porcentajePorDestino[i] = (contadores[i] / (double)totalPasajeros) * 100;
    }

    // destino más solicitado
    for (int i = 1; i < 4; i++)
    {
        if (contadores[i] > contadores[destinoMasSolicitado])
        {
            destinoMasSolicitado = i;
        }
    }

    //porcentaje de menores de 5 años por destino
    for (int i = 0; i < 4; i++)
    {
        porcentajeMenoresCinco[i] = (menoresCinco[i] / (double)contadores[i]) * 100;
    }


    printf("\nEstadisticas:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Porcentaje de pasajeros para destino %s: %.2lf%%\n", codigos[i], porcentajePorDestino[i]);
    }
    printf("Destino mas solicitado: %s\n", codigos[destinoMasSolicitado]);
    for (int i = 0; i < 4; i++)
    {
        printf("Porcentaje de menores de 5 años para destino %s: %.2lf%%\n", codigos[i], porcentajeMenoresCinco[i]);
    }
}

int main()
{
    int opcion;

    printf("Ingrese la cantidad de pasajeros\n");
    scanf("%d", &lengthPasajeros);
    char pasajeros[lengthPasajeros][DATOS][MAX_LENGTH];
    char copia[lengthPasajeros][DATOS][MAX_LENGTH];
    cargarPasajeros(pasajeros);

    do
    {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            crearCopia(pasajeros, copia);
            ordenarPorApellidoNombre(pasajeros, copia);
            break;
        case 2:
            crearCopia(pasajeros, copia);
            ordenarPorCodigoDestinoApellido(pasajeros, copia);
            break;
        case 3:
            mostrarListaDeDestinos(pasajeros);
            break;
        case 4:
            buscarPorPasajero(pasajeros);
            break;
        case 5:
            mostrarEstadisticas(pasajeros);
            break;
        case 6:
            printf("Gracias por usar nuestro programa\n");
            return 0; // Salir del programa
        default:
            printf("Elija una opcion valida\n");
            break;
        }
    } while (opcion != 6);

    return 0;
}





