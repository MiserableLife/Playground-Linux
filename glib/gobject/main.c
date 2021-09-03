/* main.c */
#include "animaltiger.h"

int
main (int argc, char ** argv)
{
	AnimalTiger * tiger = animal_tiger_new ();
	animal_cat_say_meow (tiger);
	return 0;
}
