#include <stdio.h>

void bubbleSort(int* arr);
void swap(int* ptr1, int* ptr2);

int main() 
{
    int arr[] = {1, 3, 8, 4, 9, 2, 5, 7, 6, 0};
    bubbleSort(arr);
    for (size_t i = 0; i < 10; i++)
        printf("%d ", arr[i]);
}

void bubbleSort(int* arr)
{
    for (size_t i = 0; i < 10 - 1; i++)
        for (size_t j = 0; j < 10 - i - 1; j++)
          {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
          }
}

void swap(int* ptr1, int* ptr2)
{
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}