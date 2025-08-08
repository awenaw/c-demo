/*
 * Demo program showing class-like functionality with C structs
 * 
 * Compilation:
 * - macOS:   mkdir -p bin && clang -o bin/person_demo person.c demo.c
 * - Linux:   mkdir -p bin && gcc -o bin/person_demo person.c demo.c
 * 
 * Usage: ./bin/person_demo
 */

#include "person.h"

int main() {
    printf("=== C Struct Class-like Demo ===\n\n");
    
    Person* person1 = person_create("Alice Johnson", 25, "alice@example.com");
    Person* person2 = person_create("Bob Smith", 17, "bob@example.com");
    
    if (!person1 || !person2) {
        printf("Failed to create persons\n");
        return 1;
    }
    
    printf("1. Initial Information:\n");
    person_display(person1);
    printf("\n");
    person_display(person2);
    printf("\n");
    
    printf("2. Celebrating Birthdays:\n");
    person_celebrate_birthday(person1);
    person_celebrate_birthday(person2);
    printf("\n");
    
    printf("3. Updating Information:\n");
    person_set_name(person1, "Alice Johnson-Wilson");
    person_set_email(person1, "alice.wilson@example.com");
    person_set_age(person2, 18);
    printf("Updated Alice's name and email\n");
    printf("Updated Bob's age to 18\n\n");
    
    printf("4. Final Information:\n");
    person_display(person1);
    printf("\n");
    person_display(person2);
    printf("\n");
    
    printf("5. Getter Functions Demo:\n");
    printf("Person1 name: %s\n", person_get_name(person1));
    printf("Person1 age: %d\n", person_get_age(person1));
    printf("Person1 email: %s\n", person_get_email(person1));
    printf("Person2 is adult: %s\n", person_is_adult(person2) ? "Yes" : "No");
    printf("\n");
    
    printf("6. Memory Cleanup:\n");
    person_destroy(person1);
    person_destroy(person2);
    printf("All persons destroyed successfully\n");
    
    return 0;
}