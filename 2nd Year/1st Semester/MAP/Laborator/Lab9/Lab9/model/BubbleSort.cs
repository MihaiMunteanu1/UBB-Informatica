namespace Lab9.model;

public class BubbleSort : AbstractSorter
{

    public override void Sort(int[] array)
    {
        var nr = array.Length;
        for (var i = 0; i < nr; i++) {
            for (var j = 0; j < nr - 1; j++) {
                if (array[j] > array[j + 1]) {
                    (array[j], array[j+1]) = (array[j+1], array[j]);
                }
            }
        }
    }
}