namespace Lab9.model;

public class QueueContainer : AbstractContainer
{
    public QueueContainer()
    {
        tasks = new Task[10];
        size = 0;
    }

    public override Task Remove()
    {
        if (!IsEmpty())
        {
            Task task = tasks[0];
            for (int i = 0; i < tasks.Length - 1; i++)
            {
                tasks[i] = tasks[i + 1];
            }

            size--;
            return task;
        }

        return null;
    }
    
}