#include <stdio.h>

// quicksort: sort v[left]...v[right] into increasing order
void quicksort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left > right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last - 1);
    quicksort(v, last + 1, right);
}

// swap: interchange v[i] and v[j]
void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int main(void)
{
    int array[10];

    for (int i = 0; i < 10; i++) {
        printf("array[%d] = ", i);
        scanf("%d", &array[i]);
    }
    quicksort(array, array[0], array[9]);

    for (int i = 0; i < 10; i++)
        printf("array[%d] = %d\n", i, array[i]);
    
    return 0;
}
