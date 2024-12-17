using System.Diagnostics;
using Lab9.model;

namespace Lab9.factory;

public class TaskContainerFactory : IFactory
{
    
    private static readonly TaskContainerFactory _instance = new TaskContainerFactory();

    public static TaskContainerFactory GetInstance()
    {
        return _instance;
    }
    
    public IContainer CreateContainer(Strategy strategy)
    {
        if (strategy == Strategy.Fifo)
            return new QueueContainer();
        return new StackContainer();
    }
}