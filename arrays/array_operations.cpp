#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int greatest = *itemptr;

    for (int i = 1; i < size; ++i) {
        if (*(itemptr + i) > greatest) {
            greatest = *(itemptr + i);
        }
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = *itemptr;

    for (int i = 0; itemptr + i != endptr; ++i) {
        if (*(itemptr + i) > greatest) {
            greatest = *(itemptr + i);
        }
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    int i = 0;

    while (itemptr + i != endptr) {
        *(targetptr + i) = *(itemptr + i);
        ++i;
    }
    *(targetptr + i) = *(itemptr + i);
}

void reverse(int *leftptr, int *rightptr)
{
    rightptr = rightptr - 1;

    while (leftptr < rightptr) {
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;

        ++leftptr;
        --rightptr;
    }
}
