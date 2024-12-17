namespace Lab9.model;

public abstract class AbstractContainer : IContainer
{
    protected Task[] tasks;
    protected int size;
    

    public virtual void Add(Task task)
    {
        if (tasks.Length == size)
        {
            Task[] t = new Task[tasks.Length * 2 ];
            Array.Copy(tasks, 0, t, 0, tasks.Length);
            tasks = t;
        }
        tasks[size] = task;
        size++;
    }
    
    public virtual Task Remove()
    {
        throw new NotImplementedException();
    }

    public virtual int Size()
    {
        return size;
    }

    public virtual bool IsEmpty()
    {
        return size == 0;
    }
}