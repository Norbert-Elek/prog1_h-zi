#include <stdio.h>
#include <stdlib.h>

#define NUM_NUMBERS 100
#define MIN_RANGE 10
#define MAX_RANGE 99
#define SEED_VALUE 2050 // Állandó seed érték

void generate_random_numbers_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Hiba a fájl létrehozásakor!");
        exit(1);
    }
    
    srand(SEED_VALUE); // Állandó seed érték beállítása

    for (int i = 0; i < NUM_NUMBERS; i++) {
        int random_number = rand() % (MAX_RANGE - MIN_RANGE + 1) + MIN_RANGE;
        fprintf(file, "%d\n", random_number);
    }

    fclose(file);
}

int main() {
    generate_random_numbers_file("numbers.txt");
    printf("A numbers.txt fájl létrehozva és feltöltve!\n");
    return 0;
}
