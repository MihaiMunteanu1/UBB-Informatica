namespace Lab9.model;

public class StackContainer : AbstractContainer
{
    public StackContainer()
    {
        tasks = new Task[10];
        size = 0;
    }

    public override Task Remove()
    {
        if (!IsEmpty())
        {
            return tasks[--size];
        }

        return null;
    }
}