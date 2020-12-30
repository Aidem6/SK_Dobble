#include "cards.h"

void Cards::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Cards::printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

void Cards::randomize(int arr[], int n)
{
    srand (time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

void Cards::randomize()
{
    int n = sizeof(cards) / sizeof(cards[0]);
    randomize(stash, n);
}
