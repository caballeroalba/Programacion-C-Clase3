#include "gestor_tarea.h"

int main(void)
{
	struct tarea *c1, *c2;
	struct gestor_tarea *con;
	char info[4000];

	c1 = curso_tarea_alloc();

	curso_tarea_attr_set_str(c1, CURSO_TAREA_ATTR_DESC_TAREA, "hacer ejercecicio 1");
	curso_tarea_attr_set_str(c1, CURSO_TAREA_ATTR_NOMBRE_TAREA, "tarea 1");
	curso_tarea_attr_set_u32(c1, CURSO_TAREA_ATTR_ID, 0);

	c2 = curso_tarea_alloc();

	curso_tarea_attr_set_str(c2, CURSO_TAREA_ATTR_DESC_TAREA, "hacer ejercicio 2");
	curso_tarea_attr_set_str(c2, CURSO_TAREA_ATTR_NOMBRE_TAREA, "tarea 2");
	curso_tarea_attr_set_u32(c2, CURSO_TAREA_ATTR_ID, 0);

	con = curso_gestor_tarea_alloc();

	curso_gestor_tarea_attr_set_str(con, CURSO_GESTOR_TAREA_ATTR_AUTOR,
					 "José María");

	curso_gestor_tarea_attr_set_tarea(con, CURSO_GESTOR_TAREA_ATTR_TAREA,
					   c1);

	curso_gestor_tarea_attr_set_tarea(con, CURSO_GESTOR_TAREA_ATTR_TAREA,
					   c2);

	curso_gestor_tarea_snprintf(info, sizeof(info), con);
	printf("%s", info);
  printf("el numero de tareas es %d\n",curso_gestor_tarea_attr_get_u32(con,CURSO_GESTOR_TAREA_ATTR_NUM_TAREAS));
	curso_gestor_tarea_free(con);
	return 0;
}
