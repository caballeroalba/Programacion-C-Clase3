#include "concesionario.h"
#include <stdio.h>
#include <getopt.h>


int main(int argc, char *argv[])
{
  int val, option_index= 0;
  static struct option long_options[]=
  {
    {"matricula", required_argument,0,'m'},
    {"id",required_argument,0,'i'},
    {"gama",required_argument,0,'g'},
    {"dueno",required_argument,0,'d'},
    {0}
  };
  if(argc ==1 ){
  printf("Faltan parametros de entrada, introduce -h para la ayuda\n");
  return 0;  
  }

  struct coche *c1;
	struct concesionario *con;
  char info[4000];

  c1 = curso_coche_alloc();
  con = curso_concesionario_alloc();

  while ((val=getopt_long(argc,argv,"m:i:g:d:h",long_options,&option_index)) !=-1 ){
    
    
    switch(val){
      case 1:
        printf ("opciones %s", long_options[option_index].name);
      case 'm':
        curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MATRICULA,optarg );

        break;
      case 'i':
        curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID,* (uint32_t *) (optarg) );
        break;
      case 'g':
        curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MARCA,optarg );
        break;

      case 'd':
        curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO,optarg);
        break;

      case 'h':
        printf("Debes introducir -d/-dueno -m/-matricula -i/-id -g/-gama\n");
        curso_concesionario_free(con);
        return -1;
      default:
        printf("Debes introducir -d/-dueno -m/-matricula -i/-id -g/-gama\n");
        curso_concesionario_free(con);
        return -1;

    }
    
  }

  
 
  	
  curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE,
					   c1);
	

	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);
  printf("el numero de coches es %d\n",curso_concesionario_attr_get_u32(con,CURSO_CONCESIONARIO_ATTR_NUM_COCHES));

	return 0;
  
}
