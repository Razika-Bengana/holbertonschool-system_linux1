#include "laps.h"

#define MAX_CARS 100

/**
 * get_race - function that returns a pointer to a Race struct
 *
 * Return: a pointer to a Race struct
 */

Race *get_race()
{
/* declare static variable to persist between calls */
	static Race *race;

/*
 * if race struct has not been initialized yet,
 * allocate memory and set number of cars to 0
*/
	if (race == NULL)
	{
		race = malloc(sizeof(Race));
		race->num_cars = 0;
	}
	return (race);
}


/**
 * find_car - function that searches for a car with the given id
 * @id: id of the car to find
 * Return: the index of the car in the race's array of cars,
 * or -1 if it is not found
 */

int find_car(int id)
{
/* get the race struct pointer */
	Race *race = get_race();
	int i;

/* if race struct has not been initialized, return -1 */
	if (race == NULL)
	{
		return (-1);
	}

/* search through the array of cars for a car with the given id */
	for (i = 0; i < race->num_cars; i++)
	{
		if (race->cars[i].id == id)
		{
			return (i);
		}
	}
/* if car with given id is not found, return -1 */
	return (-1);
}


/**
 * add_car - function that adds a car to the race's array of cars
 * with the specified id
 * @id: id of the car to add
 * @race: pointer to the race struct
 * Return: nothing (void)
 */

void add_car(int id, Race *race)
{
/* add car with specified id to the array of cars in the race */
	race->cars[race->num_cars].id = id;
	race->cars[race->num_cars].laps = 0;
	race->num_cars++;
	printf("Car %d joined the race\n", id);
}

/**
 * sort_cars - function that sorts the cars in the race's array of cars
 * by their id
 * @race: pointer to the race struct
 * Return: nothing (void)
 */

void sort_cars(Race *race)
{
	int i, j;
/* sort the cars in the array of cars in the race by their id */
	for (i = 0; i < race->num_cars - 1; i++)
	{
		for (j = i + 1; j < race->num_cars; j++)
		{
			if (race->cars[i].id > race->cars[j].id)
			{
				Car temp = race->cars[i];

				race->cars[i] = race->cars[j];
				race->cars[j] = temp;
			}
		}
	}
}

/**
  * race_state - function that updates the number of laps for each car
 * in the race, sorts the cars by their id, and prints the current race state
 * @id: pointer to an array of car ids
 * @size: size of the array of car ids
 * Return: nothing (void)
 */

void race_state(int *id, size_t size)
{
/* get the race struct pointer */
	Race *race = get_race();
	int i;

/* if size of car id array is 0, free allocated memory and return */
	if (size == 0)
	{
/* free allocated memory */
		race->num_cars = 0;
		return;
	}

	for (i = 0; i < (int) size; i++)
	{
		int car_idx = find_car(id[i]);

		if (car_idx == -1)
		{
			add_car(id[i], race);
		}
		else
		{
			race->cars[car_idx].laps++;
		}
	}

	sort_cars(race);


	printf("Race state:\n");

	for (i = 0; i < race->num_cars; i++)
	{
		printf("Car %d [%d laps]\n", race->cars[i].id, race->cars[i].laps);
	}
}
