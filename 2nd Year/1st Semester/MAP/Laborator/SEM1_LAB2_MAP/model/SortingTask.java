package sem1_2.model;

import sem1_2.factory.SortingStrategy;

import java.util.Arrays;

public class SortingTask extends Task{

    private AbstractSorter abstractSorter;
    private final int[] array;

    public SortingTask(String id, String description, int[] array, SortingStrategy sortingStrategy) {
        super(id, description);
        this.array = array;

        switch (sortingStrategy) {
            case QUICK -> abstractSorter = new QuickSort();
            case BUBBLE -> abstractSorter = new BubbleSort();
        }
    }

    @Override
    public void execute() {
        abstractSorter.sort(array);
        System.out.println(Arrays.toString(array)+"\n");
    }
}
