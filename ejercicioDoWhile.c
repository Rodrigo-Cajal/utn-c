#include <stdio.h>

int main() {
    float ventaCliente, totalVentas = 0;

    do
    {
        printf("Ingrese el monto de la venta, para finalizar y ver el monto total de ingresos en el dia ponga 0:\n");
        scanf("%f", &ventaCliente);
        totalVentas+=ventaCliente;
    } while (ventaCliente != 0);
    printf("El ingreso total del dia es de: %0.2f", totalVentas);










    return 0;
}