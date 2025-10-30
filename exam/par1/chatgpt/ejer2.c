int anio;
int esBisiesto;

anio = 2024; // ejemplo, normalmente se leería con scanf
esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);

if (esBisiesto)
    printf("%d es un año bisiesto\n", anio);
else
    printf("%d no es un año bisiesto\n", anio);