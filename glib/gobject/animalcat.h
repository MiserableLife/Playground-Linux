
#ifndef _ANIMAL_CAT_H_
#define _ANIMAL_CAT_H_
#include <glib-object.h>
#include <gio/gio.h>
G_BEGIN_DECLS
#define ANIMAL_TYPE_CAT animal_cat_get_type()
G_DECLARE_DERIVABLE_TYPE (AnimalCat, animal_cat, ANIMAL, CAT, GObject) 
struct _AnimalCatClass
{
		GObjectClass parent_class;
			void (*say_meow) (AnimalCat*);
};
AnimalCat* 
animal_cat_new();
void 
animal_cat_say_meow(AnimalCat* self);
G_END_DECLS
#endif /* _ANIMAL_CAT_H_ */

