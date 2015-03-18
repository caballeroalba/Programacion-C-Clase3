#include "tarea.h"
#include <string.h>

struct tarea *curso_tarea_alloc(void)
{
	return (struct tarea *)malloc(sizeof(struct tarea));
}

void curso_tarea_free(struct tarea *c)
{
	if (c->flags & (1 << CURSO_TAREA_ATTR_NOMBRE_TAREA))
		xfree(c->nombre_tarea);

	if (c->flags & (1 << CURSO_TAREA_ATTR_DESC_TAREA))
		xfree(c->desc_tarea);
		
        if (c->flags & (1 << CURSO_TAREA_ATTR_USUARIO))
		xfree(c->usuario);
		
	if (c->flags & (1 << CURSO_TAREA_ATTR_PRIORIDAD))
		xfree(c->prioridad);

	xfree(c);
}

bool curso_tarea_attr_is_set(const struct tarea *c, uint16_t attr)
{
	return c->flags & (1 << attr);
}

void curso_tarea_attr_unset(struct tarea *c, uint16_t attr)
{
	if (!(c->flags & (1 << attr)))
		return;

	switch (attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if (c->nombre_tarea) {
			xfree(c->nombre_tarea);
			c->nombre_tarea = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		if (c->desc_tarea) {
			xfree(c->desc_tarea);
			c->desc_tarea = NULL;
		}
		break;
		
        case CURSO_TAREA_ATTR_USUARIO:
		if (c->usuario) {
			xfree(c->usuario);
			c->usuario = NULL;
		}
		break;
		
	case CURSO_TAREA_ATTR_PRIORIDAD:
		if (c->prioridad) {
			xfree(c->prioridad);
			c->prioridad = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_ID:
		break;
	}

	c->flags &= ~(1 << attr);
}

void curso_tarea_set_data(struct tarea *c, uint16_t attr, const void *data,
			  uint32_t data_len)
{
	if (attr > CURSO_TAREA_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if (c->nombre_tarea)
			xfree(c->nombre_tarea);

		c->nombre_tarea = strdup(data);
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		if (c->desc_tarea)
			xfree(c->desc_tarea);

		c->desc_tarea = strdup(data);
		break;
		
        case CURSO_TAREA_ATTR_USUARIO:
		if (c->usuario)
			xfree(c->usuario);

		c->usuario = strdup(data);
		break;
		
	case CURSO_TAREA_ATTR_PRIORIDAD:
		if (c->prioridad)
			xfree(c->prioridad);

		c->prioridad = *((uint32_t *)data);
		break;
	case CURSO_TAREA_ATTR_ID:
		c->id = *((uint32_t *)data);
		break;
	}

	c->flags |= (1 << attr);
}

void curso_tarea_attr_set_u32(struct tarea *c, uint16_t attr, uint32_t data)
{
	curso_tarea_set_data(c, attr, &data, sizeof(uint32_t));
}

void curso_tarea_attr_set_str(struct tarea *c, uint16_t attr, const char *data)
{
	curso_tarea_set_data(c, attr, data, 0);
}

const void *curso_tarea_attr_get_data(struct tarea *c, uint16_t attr)
{
	if (!(c->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		return c->nombre_tarea;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		return c->desc_tarea;
	case CURSO_TAREA_ATTR_USUARIO:
		return c->usuario;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		return c->prioridad;
	case CURSO_TAREA_ATTR_ID:
		return &c->id;
	}
	return NULL;
}

uint32_t curso_tarea_attr_get_u32(struct tarea *c, uint16_t attr)
{
	const void *ret = curso_tarea_attr_get_data(c, attr);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *curso_tarea_attr_get_str(struct tarea *c, uint16_t attr)
{
	return curso_tarea_attr_get_data(c, attr);
}

int curso_tarea_snprintf(char *buf, size_t size, struct tarea *c)
{
	return snprintf(buf, size, "nombre_tarea %s desc_tarea %s id %d",
			c->nombre_tarea, c->desc_tarea, c->id);
}
