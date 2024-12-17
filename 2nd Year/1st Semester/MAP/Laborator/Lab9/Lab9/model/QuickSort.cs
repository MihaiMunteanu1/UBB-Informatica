namespace Lab9.model;

public class QuickSort : AbstractSorter
{
    public override void Sort(int[] array)
    {
        QuickSortFunction(array, 0, array.Length-1);
    }
    
    public void QuickSortFunction(int[] arr, int begin, int end) {
        if (begin < end) {
            int pI = Partition(arr, begin, end);

            QuickSortFunction(arr, begin, pI- 1);
            QuickSortFunction(arr, pI + 1, end);
        }
    }

    private int Partition(int[] arr, int begin, int end) {
        int pivot = arr[end];
        int i = begin - 1;

        for (int j = begin; j < end; j++) {
            if (arr[j] <= pivot) {
                i++;

                int aux = arr[i];
                arr[i] = arr[j];
                arr[j] = aux;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[end];
        arr[end] = temp;

        return i + 1;
    }
}