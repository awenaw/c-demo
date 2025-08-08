#include "person.h"

Person* person_create(const char* name, int age, const char* email) {
    Person* self = (Person*)malloc(sizeof(Person));
    if (!self) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    self->name = malloc(strlen(name) + 1);
    self->email = malloc(strlen(email) + 1);
    
    if (!self->name || !self->email) {
        free(self->name);
        free(self->email);
        free(self);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    strcpy(self->name, name);
    strcpy(self->email, email);
    self->age = age;
    
    return self;
}

void person_destroy(Person* self) {
    if (self) {
        free(self->name);
        free(self->email);
        free(self);
    }
}

void person_set_name(Person* self, const char* name) {
    if (self && name) {
        free(self->name);
        self->name = malloc(strlen(name) + 1);
        if (self->name) {
            strcpy(self->name, name);
        }
    }
}

void person_set_age(Person* self, int age) {
    if (self) {
        self->age = age;
    }
}

void person_set_email(Person* self, const char* email) {
    if (self && email) {
        free(self->email);
        self->email = malloc(strlen(email) + 1);
        if (self->email) {
            strcpy(self->email, email);
        }
    }
}

const char* person_get_name(Person* self) {
    return self ? self->name : NULL;
}

int person_get_age(Person* self) {
    return self ? self->age : -1;
}

const char* person_get_email(Person* self) {
    return self ? self->email : NULL;
}

void person_display(Person* self) {
    if (self) {
        printf("Person Information:\n");
        printf("  Name: %s\n", self->name);
        printf("  Age: %d\n", self->age);
        printf("  Email: %s\n", self->email);
        printf("  Status: %s\n", person_is_adult(self) ? "Adult" : "Minor");
    }
}

void person_celebrate_birthday(Person* self) {
    if (self) {
        self->age++;
        printf("Happy Birthday %s! You are now %d years old.\n", self->name, self->age);
    }
}

int person_is_adult(Person* self) {
    return self ? (self->age >= 18) : 0;
}