using Lab9.factory;

namespace Lab9.model;

public class SortingTask : Task
{
    private AbstractSorter _abstractSorter;
    private int[] _array;

    public SortingTask(string id, string description, int[] array, SortingStrategy sortingStrategy) : base(id, description)
    {
        _array = array;
        switch (sortingStrategy)
        {
            case SortingStrategy.Bubble:
                _abstractSorter = new BubbleSort();
                break;
            case SortingStrategy.Quick:
                _abstractSorter = new QuickSort();
                break;
            default:
                throw new ArgumentException("Invalid sorting strategy");
        }
    }

    public override void Execute()
    {
        _abstractSorter.Sort(_array);
        Console.WriteLine(string.Join(", ", _array) + "\n");

    }
}