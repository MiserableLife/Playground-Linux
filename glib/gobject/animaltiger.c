#include <stdio.h>

#include "animaltiger.h"

struct _AnimalTiger
{
	AnimalCat parent;
};

G_DEFINE_TYPE (AnimalTiger, animal_tiger, ANIMAL_TYPE_CAT)

static void
animal_tiger_real_say_meow (AnimalTiger * self)
{
		printf ("Tiger say: ARRRRGH !!!/n");
}


static void
animal_tiger_class_init (AnimalTigerClass * self)
{
		printf ("First instance of AnimalTiger was created./n");
			AnimalCatClass * parent_class = ANIMAL_CAT_CLASS (self);
				parent_class-> say_meow = animal_tiger_real_say_meow;
}

static void
animal_tiger_init (AnimalTiger * self)
{
		printf ("Tiger cub was born./n");
}

AnimalTiger *
animal_tiger_new ()
{
		return g_object_new (ANIMAL_TYPE_TIGER, NULL);
}
