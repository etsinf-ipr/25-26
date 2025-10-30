
int year;

printf("Introduce un año: ");
scanf("%d", &year);

if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    printf("%d es un año bisiesto.\n", year);
else
    printf("%d no es un año bisiesto.\n", year);