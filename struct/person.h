/*
 * Person struct - simulating class functionality in C
 * 
 * Compilation:
 * - macOS:   mkdir -p bin && clang -o bin/person_demo person.c
 * - Linux:   mkdir -p bin && gcc -o bin/person_demo person.c
 */

#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char* name;
    int age;
    char* email;
} Person;

Person* person_create(const char* name, int age, const char* email);

void person_destroy(Person* self);

void person_set_name(Person* self, const char* name);
void person_set_age(Person* self, int age);
void person_set_email(Person* self, const char* email);

const char* person_get_name(Person* self);
int person_get_age(Person* self);
const char* person_get_email(Person* self);

void person_display(Person* self);
void person_celebrate_birthday(Person* self);
int person_is_adult(Person* self);

#endif