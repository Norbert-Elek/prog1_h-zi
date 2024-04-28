#include <stdio.h>
#include <stdlib.h>

// Dinamikus tömb struktúra
typedef struct {
    int *érték;
    size_t méret;
} DynArray;

// Dinamikus tömb inicializálása
DynArray* da_init(size_t méret) {
    DynArray *dyn_array = (DynArray*)malloc(sizeof(DynArray));
    if (dyn_array == NULL) {
        printf("Memóriafoglalási hiba!\n");
        exit(1);
    }
    dyn_array->érték = (int*)malloc(méret * sizeof(int));
    if (dyn_array->érték == NULL) {
        printf("Memóriafoglalási hiba!\n");
        free(dyn_array);
        exit(1);
    }
    dyn_array->méret = méret;
    return dyn_array;
}

// Dinamikus tömb felszabadítása
void da_free(DynArray *dyn_array) {
    free(dyn_array->érték);
    free(dyn_array);
}

// Dinamikus tömbből átlag számítása
double da_average(const DynArray *dyn_array) {
    int sum = da_sum(dyn_array); // Összeg kiszámítása
    return (double)sum / dyn_array->méret;
}

// Dinamikus tömbből összeg számítása
int da_sum(const DynArray *dyn_array) {
    int sum = 0;
    for (size_t i = 0; i < dyn_array->méret; i++) {
        sum += dyn_array->érték[i];
    }
    return sum;
}

// numbers.txt beolvasása dinamikus tömbbe
DynArray* read_numbers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Hiba a fájl megnyitásakor!\n");
        exit(1);
    }

    DynArray *dyn_array = da_init(0); // Dinamikus tömb inicializálása

    int number;
    while (fscanf(file, "%d", &number) == 1) {
        dyn_array->érték = (int*)realloc(dyn_array->érték, (dyn_array->méret + 1) * sizeof(int));
        if (dyn_array->érték == NULL) {
            printf("Memóriafoglalási hiba!\n");
            fclose(file);
            da_free(dyn_array);
            exit(1);
        }
        dyn_array->érték[dyn_array->méret] = number;
        dyn_array->méret++;
    }

    fclose(file);
    return dyn_array;
}

int main() {
    DynArray *numbers = read_numbers("numbers.txt");

    // Átlag kiszámítása
    double average = da_average(numbers);
    printf("A számok átlaga: %.2f\n", average);

    da_free(numbers); // Dinamikus tömb felszabadítása

    return 0;
}
