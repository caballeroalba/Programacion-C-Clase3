#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	int linea = 0;

	while (linea < 6) {
		fprintf(file, "Linea %d: Mensaje de prueba\n", linea);// comprobar que no daque no sea menor que 0
		linea++;
	}
	rewind(file);
}

int main (void)
{
	FILE *file = fopen("datos.dat", "a+"); 
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return -1;

	genera_mensaje(file);

	code = malloc(100); //malloc debe ser de 100 y comprobar que el malloc se crea bien
	while(fgets(code, 100, file)) {//no se hace comprobación del fgets pero el propio while hace la comprboacion al devolver 1 y por eso entra
		printf("%s", code);
	}
 //cerrar fichero y comprobar el cerrado
	free(code);
	return 0;
}
