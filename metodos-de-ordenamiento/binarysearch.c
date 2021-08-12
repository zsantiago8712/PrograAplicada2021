#include <stdio.h>
#include <stdlib.h>


int binary_search(int nums[], int search, int start, int end);

int main(void)
{
    int nums[] = {1, 3, 5, 9, 12, 15, 16, 17, 18};
    int posicion;

    posicion = binary_search(nums, 12, 0, 9 - 1);
    if(posicion < 0)
    {
        printf("El numero no esta en la lista\n");
        exit(0);
    }
    printf("%d--%d\n", posicion, nums[posicion]);


}

int binary_search(int nums[], int search, int start, int end)
{
    if(end >= start)
    {
        int mid = start + (end - start) / 2;

        if(nums[mid] < search)
        {
            binary_search(nums, search, mid + 1, end);

        }else if(nums[mid] > search)
        {
            binary_search(nums, search, start, mid - 1);
        }
        else
        {
            return mid;
        }
    }

    return -1;
}