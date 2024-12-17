package sem1_2.model;

import sem1_2.model.AbstractSorter;

public class QuickSort extends AbstractSorter {
    @Override
    public void sort(int[] array) {
        quickSort(array, 0, array.length-1);
    }

    public void quickSort(int[] arr, int begin, int end) {
        if (begin < end) {
            int pI = partition(arr, begin, end);

            quickSort(arr, begin, pI- 1);
            quickSort(arr, pI + 1, end);
        }
    }

    private int partition(int[] arr, int begin, int end) {
        int pivot = arr[end];
        int i = begin - 1;

        for (int j = begin; j < end; j++) {
            if (arr[j] <= pivot) {
                i++;

                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[end];
        arr[end] = temp;

        return i + 1;
    }
}