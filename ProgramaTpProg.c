#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PASAJEROS 240
#define MAX_DESTINOS 4
#define MAX_PASAJEROS_POR_DESTINO 60


char codigoDestino[MAX_DESTINOS][4] = {"BRA", "MDQ", "MZA", "BRC"};
char nombreDestino[MAX_DESTINOS][20] = {"Brasil", "Mar del Plata", "Mendoza", "Bariloche"};
float importePorPasajero[MAX_DESTINOS] = {25000.0, 14000.0, 19000.0, 23000.0};
int cantidadPasajerosDestino[MAX_DESTINOS] = {0, 0, 0, 0};
float totalCobradoDestino[MAX_DESTINOS] = {0.0, 0.0, 0.0, 0.0};

int dni[MAX_PASAJEROS];
char apellido[MAX_PASAJEROS][50];
char nombre[MAX_PASAJEROS][50];
int edad[MAX_PASAJEROS];
char destinoSeleccionado[MAX_PASAJEROS][4];
int pagoConTarjeta[MAX_PASAJEROS];

int numPasajeros = 0;


void cargarPasajeros();
void mostrarListaOrdenadaApellido();
void mostrarListaOrdenadaDestino();
void mostrarListaDestinos();
void buscarPasajero();
void mostrarEstadisticas();
int validarDNI(int dni);
void ordenarPorApellido();
void ordenarPorDestino();

int main() {
    int opcion;

    cargarPasajeros();

    do {
        printf("\n Menu \n");
        printf("1. Mostrar lista de pasajeros ordenada por Apellido y Nombre\n");
        printf("2. Mostrar lista de pasajeros ordenada por Codigo Destino y Apellido - Nombre\n");
        printf("3. Mostrar lista de Destinos\n");
        printf("4. Buscar por pasajero\n");
        printf("5. Mostrar estadisticas\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarListaOrdenadaApellido();
                break;
            case 2:
                mostrarListaOrdenadaDestino();
                break;
            case 3:
                mostrarListaDestinos();
                break;
            case 4:
                buscarPasajero();
                break;
            case 5:
                mostrarEstadisticas();
                break;
            case 6:
                printf("Gracias por usar el sistema.\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente nuevamente.\n");
        }
    } while (opcion != 6);

    return 0;
}

void cargarPasajeros() {
    printf("Ingrese la cantidad de pasajeros: ");
    scanf("%d", &numPasajeros);

    for (int i = 0; i < numPasajeros; i++) {
        printf("Ingrese DNI del pasajero %d: ", i + 1);
        scanf("%d", &dni[i]);
        while (!validarDNI(dni[i])) {
            printf("DNI invalido. Ingrese nuevamente: ");
            scanf("%d", &dni[i]);
        }

        printf("Ingrese Apellido del pasajero %d: ", i + 1);
        scanf("%s", apellido[i]);

        printf("Ingrese Nombre del pasajero %d: ", i + 1);
        scanf("%s", nombre[i]);

        printf("Ingrese Edad del pasajero %d: ", i + 1);
        scanf("%d", &edad[i]);

        printf("Ingrese codigo de destino (BRA, MDQ, MZA, BRC) del pasajero %d: ", i + 1);
        scanf("%s", destinoSeleccionado[i]);

        printf("¿El pasajero paga con tarjeta de credito? (1 para Si, 0 para No): ");
        scanf("%d", &pagoConTarjeta[i]);

        for (int j = 0; j < MAX_DESTINOS; j++) {
            if (strcmp(destinoSeleccionado[i], codigoDestino[j]) == 0) {
                cantidadPasajerosDestino[j]++;
                float importe = importePorPasajero[j];
                if (edad[i] < 5) {
                    importe = 2000.0;
                }
                if (pagoConTarjeta[i] == 1) {
                    importe *= 1.05;
                }
                totalCobradoDestino[j] += importe;
                break;
            }
        }
    }
}

int validarDNI(int dni) {
    int length = snprintf(NULL, 0, "%d", dni);
    if (length < 7 || length > 8) return 0;

    int firstDigit = dni / (int)pow(10, length - 1);
    return (firstDigit == 5 || firstDigit == 6 || (firstDigit >= 1 && firstDigit <= 6));
}

void ordenarPorApellido() {
    for (int i = 0; i < numPasajeros - 1; i++) {
        for (int j = i + 1; j < numPasajeros; j++) {
            if (strcmp(apellido[i], apellido[j]) > 0 || (strcmp(apellido[i], apellido[j]) == 0 && strcmp(nombre[i], nombre[j]) > 0)) {
                // Intercambiar pasajeros
                int tempDni = dni[i];
                dni[i] = dni[j];
                dni[j] = tempDni;

                char tempApellido[50];
                strcpy(tempApellido, apellido[i]);
                strcpy(apellido[i], apellido[j]);
                strcpy(apellido[j], tempApellido);

                char tempNombre[50];
                strcpy(tempNombre, nombre[i]);
                strcpy(nombre[i], nombre[j]);
                strcpy(nombre[j], tempNombre);

                int tempEdad = edad[i];
                edad[i] = edad[j];
                edad[j] = tempEdad;

                char tempDestino[4];
                strcpy(tempDestino, destinoSeleccionado[i]);
                strcpy(destinoSeleccionado[i], destinoSeleccionado[j]);
                strcpy(destinoSeleccionado[j], tempDestino);

                int tempPago = pagoConTarjeta[i];
                pagoConTarjeta[i] = pagoConTarjeta[j];
                pagoConTarjeta[j] = tempPago;
            }
        }
    }
}

void ordenarPorDestino() {
    for (int i = 0; i < numPasajeros - 1; i++) {
        for (int j = i + 1; j < numPasajeros; j++) {
            if (strcmp(destinoSeleccionado[i], destinoSeleccionado[j]) > 0 || (strcmp(destinoSeleccionado[i], destinoSeleccionado[j]) == 0 && strcmp(apellido[i], apellido[j]) > 0)) {
                // Intercambiar pasajeros
                int tempDni = dni[i];
                dni[i] = dni[j];
                dni[j] = tempDni;

                char tempApellido[50];
                strcpy(tempApellido, apellido[i]);
                strcpy(apellido[i], apellido[j]);
                strcpy(apellido[j], tempApellido);

                char tempNombre[50];
                strcpy(tempNombre, nombre[i]);
                strcpy(nombre[i], nombre[j]);
                strcpy(nombre[j], tempNombre);

                int tempEdad = edad[i];
                edad[i] = edad[j];
                edad[j] = tempEdad;

                char tempDestino[4];
                strcpy(tempDestino, destinoSeleccionado[i]);
                strcpy(destinoSeleccionado[i], destinoSeleccionado[j]);
                strcpy(destinoSeleccionado[j], tempDestino);

                int tempPago = pagoConTarjeta[i];
                pagoConTarjeta[i] = pagoConTarjeta[j];
                pagoConTarjeta[j] = tempPago;
            }
        }
    }
}

void mostrarListaOrdenadaApellido() {
    ordenarPorApellido();
    printf("\nLista de pasajeros ordenada por Apellido y Nombre:\n");
    for (int i = 0; i < numPasajeros; i++) {
        printf("%s %s, DNI: %d, Edad: %d, Destino: %s\n", apellido[i], nombre[i], dni[i], edad[i], destinoSeleccionado[i]);
    }
}

void mostrarListaOrdenadaDestino() {
    ordenarPorDestino();
    printf("\nLista de pasajeros ordenada por Codigo Destino y Apellido - Nombre:\n");
    for (int i = 0; i < numPasajeros; i++) {
        printf("%s - %s %s, DNI: %d, Edad: %d\n", destinoSeleccionado[i], apellido[i], nombre[i], dni[i], edad[i]);
    }
}

void mostrarListaDestinos() {
    float totalCobrado = 0.0;
    printf("\nLista de Destinos:\n");
    for (int i = 0; i < MAX_DESTINOS; i++) {
        printf("Codigo: %s, Cantidad pasajeros: %d, Importe Total Cobrado: %.2f\n", codigoDestino[i], cantidadPasajerosDestino[i], totalCobradoDestino[i]);
        totalCobrado += totalCobradoDestino[i];
    }
    printf("Importe total de todos los destinos: %.2f\n", totalCobrado);
}

void buscarPasajero() {
    int dniBuscado;
    printf("Ingrese el DNI del pasajero a buscar: ");
    scanf("%d", &dniBuscado);
    while (!validarDNI(dniBuscado)) {
        printf("DNI invalido. Ingrese nuevamente: ");
        scanf("%d", &dniBuscado);
    }

    int encontrado = 0;
    for (int i = 0; i < numPasajeros; i++) {
        if (dni[i] == dniBuscado) {
            encontrado = 1;
            float importe = 0.0;
            for (int j = 0; j < MAX_DESTINOS; j++) {
                if (strcmp(destinoSeleccionado[i], codigoDestino[j]) == 0) {
                    importe = importePorPasajero[j];
                    if (edad[i] < 5) {
                        importe = 2000.0;
                    }
                    if (pagoConTarjeta[i] == 1) {
                        importe *= 1.05;
                    }
                    break;
                }
            }
            printf("Pasajero encontrado: %s %s, DNI: %d, Edad: %d, Destino: %s, Importe a abonar: %.2f\n", apellido[i], nombre[i], dni[i], edad[i], destinoSeleccionado[i], importe);
            break;
        }
    }
    if (!encontrado) {
        printf("No existe pasajero con ese DNI.\n");
    }
}

void mostrarEstadisticas() {
    printf("\nEstadisticas:\n");

    // a) Por cada destino porcentaje de pasajeros
    for (int i = 0; i < MAX_DESTINOS; i++) {
        float porcentaje = (float)cantidadPasajerosDestino[i] / numPasajeros * 100;
        printf("Destino: %s, Porcentaje de pasajeros: %.2f%%\n", nombreDestino[i], porcentaje);
    }

    // b) Destino más solicitado
    int maxPasajeros = 0;
    int destinoMasSolicitado = 0;
    for (int i = 0; i < MAX_DESTINOS; i++) {
        if (cantidadPasajerosDestino[i] > maxPasajeros) {
            maxPasajeros = cantidadPasajerosDestino[i];
            destinoMasSolicitado = i;
        }
    }
    printf("Destino mas solicitado: %s\n", nombreDestino[destinoMasSolicitado]);

    // c) Porcentaje de menores de 5 años de cada destino
    for (int i = 0; i < MAX_DESTINOS; i++) {
        int menoresDeCinco = 0;
        for (int j = 0; j < numPasajeros; j++) {
            if (strcmp(destinoSeleccionado[j], codigoDestino[i]) == 0 && edad[j] < 5) {
                menoresDeCinco++;
            }
        }
        float porcentajeMenores = (float)menoresDeCinco / cantidadPasajerosDestino[i] * 100;
        printf("Destino: %s, Porcentaje de menores de 5 anos: %.2f%%\n", nombreDestino[i], porcentajeMenores);
    }
}
