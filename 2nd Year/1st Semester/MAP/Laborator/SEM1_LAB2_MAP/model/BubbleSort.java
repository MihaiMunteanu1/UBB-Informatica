package sem1_2.model;

import sem1_2.model.AbstractSorter;

public class BubbleSort extends AbstractSorter {
    @Override
    public void sort(int[] array) {
        int nr = array.length;
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nr - 1; j++) {
                if (array[j] > array[j + 1]) {
                    int aux = array[j];
                    array[j] = array[j+1];
                    array[j+1] = aux;
                }
            }
        }
    }
}