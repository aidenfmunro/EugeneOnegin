#include <stdio.h>

void swapSmall(int* a, int* b);

void myQsort(int* arr, size_t start, size_t end);

int main()
{
    int arr[13] = {7, 9, 3, 10, 6, 5, 11, 12, 2, 1, 8, 4, 13};
    myQsort(arr, 0, 12);
    for(size_t i = 0; i < 13; i++)
        printf("%d", arr[i]);
}

void myQsort(int* arr, size_t start, size_t end)
{
    size_t s = start;
    size_t e = end;

    size_t pivot = arr[(s + e) / 2];

    while (arr[s] < pivot)
        s++;
    while (arr[e] > pivot)
        e++;
    
    if (s <= e)
        swapSmall(&arr[s++], &arr[e--]);

    if (start < e)
        myQsort(arr, start, e);
    if (end > s)
        myQsort(arr, s, end);

}

void swapSmall(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

