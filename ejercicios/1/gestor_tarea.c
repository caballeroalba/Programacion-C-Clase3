#include "gestor_tarea.h"
#include <string.h>

struct gestor_tarea {
	struct list_head	tareas;
	const char        *autor;
	uint32_t          num_tareas;

	uint32_t		      flags;
};


struct gestor_tarea *curso_gestor_tarea_alloc(void)
{
	struct gestor_tarea *con;

	con = malloc(sizeof(struct gestor_tarea));
	if (con ==  NULL)
		return NULL;

	INIT_LIST_HEAD(&con->tareas);
	
	con->flags |= (1 << CURSO_GESTOR_TAREA_ATTR_NUM_TAREAS);

	return con;
}

void curso_gestor_tarea_free(struct gestor_tarea *con)
{
	
	struct tarea *c, *tmp;

	if (con->flags & (1 << CURSO_GESTOR_TAREA_ATTR_AUTOR))
		xfree(con->autor);

	list_for_each_entry_safe(c, tmp, &con->tareas, head) {
		list_del(&c->head);
		curso_tarea_free(c);
	}

	xfree(con);
}

void curso_gestor_tarea_attr_unset_tarea(struct gestor_tarea *con,
					  uint32_t pos)
{
	int i = 0;
	struct tarea *c, *tmp;

	if (pos < 0 || pos > con->num_tareas)
		return;

	list_for_each_entry_safe(c, tmp, &con->tareas, head) {
		if (i == pos) {
			list_del(&c->head);
			curso_tarea_free(c);
			break;
		}

		i++;
	}

	con->num_tareas--;
}

static void curso_gestor_tarea_set_data(struct gestor_tarea *con,
					 uint16_t attr, const void *data)
{
	struct tarea *c;

	if (attr > CURSO_GESTOR_TAREA_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_GESTOR_TAREA_ATTR_AUTOR:
		if (con->autor)
			xfree(con->autor);

		con->autor = strdup(data);
		break;
	case CURSO_GESTOR_TAREA_ATTR_TAREA:
		if (con->num_tareas > 50) {
			printf("El tareas esta lleno\n");
			break;
		}
		c = (struct tarea *)data;
		list_add(&c->head, &con->tareas);
		con->num_tareas++;
		break;
	}

	con->flags |= (1 << attr);
}

void curso_gestor_tarea_attr_set_str(struct gestor_tarea *con,
					uint16_t attr, const char *data)
{
	curso_gestor_tarea_set_data(con, attr, data);
}

void curso_gestor_tarea_attr_set_tarea(struct gestor_tarea *con,
					  uint16_t attr, struct tarea *data)
{
	curso_gestor_tarea_set_data(con, attr, data);
}

const void *curso_gestor_tarea_attr_get_data(struct gestor_tarea *con,
					      uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct tarea *c;

	if (!(con->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_GESTOR_TAREA_ATTR_AUTOR:
		return con->autor;
	case CURSO_GESTOR_TAREA_ATTR_NUM_TAREAS:
		return &con->num_tareas;
	case CURSO_GESTOR_TAREA_ATTR_TAREA:
		list_for_each_entry(c, &con->tareas, head) {
			if (i == pos)
				break;

			i++;
		}

		return c;
	}
	return NULL;
}

uint32_t curso_gestor_tarea_attr_get_u32(struct gestor_tarea *con,
					  uint16_t attr)
{
	const void *ret = curso_gestor_tarea_attr_get_data(con, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *curso_gestor_tarea_attr_get_str(struct gestor_tarea *con,
					     uint16_t attr)
{
	return curso_gestor_tarea_attr_get_data(con, attr, 0);
}

struct tarea *curso_gestor_tarea_attr_get_tarea(struct gestor_tarea *con,
					         uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gestor_tarea_attr_get_data(con, attr,
								 pos);
}

int curso_gestor_tarea_snprintf(char *buf, size_t size,
				 struct gestor_tarea *con)
{
	int ret = 0;
	struct tarea *c;

	ret += snprintf(buf, size,
			"el gestor_tarea propiedad de %s, tiene %d y son:\n",
			con->autor, con->num_tareas);

	list_for_each_entry(c, &con->tareas, head) {
		ret += curso_tarea_snprintf(buf + ret, size - ret, c);
		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
