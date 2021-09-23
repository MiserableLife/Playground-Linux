#include "animalcat.h"

G_DEFINE_TYPE (AnimalCat, animal_cat, G_TYPE_OBJECT)

static void
animal_cat_real_say_meow(AnimalCat* self)
{
		printf("Cat say: MEOW!\n");
}


void 
animal_cat_say_meow(AnimalCat* self)
{
		AnimalCatClass* klass = ANIMAL_CAT_GET_CLASS (self);
			klass->say_meow(self);
}

static void
animal_cat_class_init(AnimalCatClass* self)
{
		printf("First instance of AnimalCat was created\n");
			self->say_meow = animal_cat_real_say_meow;
}


static void
animal_cat_init(AnimalCat* self)
{
		printf("Kitty was born.\n");
}


AnimalCat*
animal_cat_new()
{
		return g_object_new(ANIMAL_TYPE_CAT, NULL);
}



