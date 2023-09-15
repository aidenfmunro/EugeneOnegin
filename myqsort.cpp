#include <stdio.h>

void swapSmall(int* a, int* b);

void myQsort(int* arr, int start, int end);

void sort2elem(int* arr, int left, int right);

int partition(int* arr, int left, int right);

int main()
{
    // int arr[13] = {7, 9, 3, 10, 8, 5, 11, 12, 2, 1, 6, 4, 13};
    int arr[] = {5, 4, 1, 3, 2};
    myQsort(arr, 0, 4);
    for(size_t i = 0; i < 5; i++)
        printf("%d ", arr[i]);
}

void myQsort(int* arr, int start, int end)
{
    if (start >= end)
        return;
    int point = partition(arr, start, end);

    myQsort(arr, start, point - 1);
    myQsort(arr, point + 1, end);
    
    

}

int partition(int* arr, int left, int right)
{
    int pivot = left;
    int pValue = arr[left];

    while (left < right)
      {
        while (arr[left] <= pValue)
            left++;
        while (arr[right] > pValue)
            right--;
        if (left < right)
            swapSmall(&arr[left], &arr[right]);
      }
      swapSmall(&arr[pivot], &arr[right]);
      return right;

}

void sort2elem(int* arr, int left, int right)
{
    if (arr[left] > arr[right])
        swapSmall(&arr[left], &arr[right]);
}


void swapSmall(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}