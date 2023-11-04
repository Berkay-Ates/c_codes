#include <stdio.h>

struct MinMax {
    int min;
    int max;
};


struct MinMax findMinMax(int arr[], int low, int high);


int main() {
    int arr[] = {12, 45, 78, 13, 6, 87, 56};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct MinMax result = findMinMax(arr, 0, n - 1);

    printf("En küçük eleman: %d\n", result.min);
    printf("En büyük eleman: %d\n", result.max);

    return 0;
}


struct MinMax findMinMax(int arr[], int low, int high) {
    struct MinMax result, left, right, mid;
    int midIndex;

    // Dizi tek eleman içeriyorsa, bu eleman hem min hem de max olur.
    if (low == high) {
        result.min = result.max = arr[low];
        return result;
    }

    // Dizi iki eleman içeriyorsa, min ve max'ı karşılaştırarak bulabiliriz.
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    // Dizi daha uzunsa, dizi yarıya bölünür ve her iki yarı için min ve max hesaplanır.
    midIndex = (low + high) / 2;
    left = findMinMax(arr, low, midIndex);
    right = findMinMax(arr, midIndex + 1, high);

    // Her iki yarının min ve max değerleri karşılaştırılarak son sonuç oluşturulur.
    if (left.min < right.min) {
        result.min = left.min;
    } else {
        result.min = right.min;
    }

    if (left.max > right.max) {
        result.max = left.max;
    } else {
        result.max = right.max;
    }

    return result;
}


