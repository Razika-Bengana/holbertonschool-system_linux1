#ifndef LAPS_H_
#define LAPS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_CARS 100

/**
 * struct Car - A structure representing a car in a race
 *
 * @id: the ID of the car
 * @laps: the number of laps completed by the car
 */

typedef struct Car
{
	int id;
	int laps;
} Car;

/**
 * struct Race - A structure representing a race
 *
 * @cars: an array of cars in the race
 * @num_cars: the number of cars in the race
 */

typedef struct Race
{
	Car cars[MAX_CARS];
	int num_cars;
} Race;


int find_car(int id);
void add_car(int id, Race *race);
void sort_cars(Race *race);
void race_state(int *id, size_t size);


#endif /* laps.h */
