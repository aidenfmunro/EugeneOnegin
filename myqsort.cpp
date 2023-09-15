#include <stdio.h>

void swapSmall(int* a, int* b);

void myQsort(int* arr, int start, int end);

int main()
{
    int arr[13] = {7, 9, 3, 10, 6, 5, 11, 12, 2, 1, 8, 4, 13};
    myQsort(arr, 0, 12);
    for(size_t i = 0; i < 13; i++)
        printf("%d", arr[i]);
}

void myQsort(int* arr, int start, int end)
{
    int left = start;
    int right = end;
    int pivot = arr[(left + right) / 2];

    while (left <= right)
        {
          while (arr[left] < pivot)
            left++;
          while (arr[right] > pivot)
            right--;
          swapSmall(&arr[left++], &arr[right--]);
        }
    
    if (start < right)
        myQsort(arr, start, right);
    if (end > left)
        myQsort(arr, left, end);
}

void swapSmall(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

