#include <stdio.h>
#include <stdlib.h>

int ArraySize(int *array) {
    int size = 0;
    while (array[size] != NULL) {
        size++;
    }
    return size;
}

int main() {
    int array[] = {1, 4, 7, 9, 12};
    int size = ArraySize(array);
    printf("Size of array: %d\n", size);
    return 0;
}
