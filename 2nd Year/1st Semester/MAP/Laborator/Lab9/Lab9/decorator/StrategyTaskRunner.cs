using System.ComponentModel;
using Lab9.factory;
using IContainer = Lab9.model.IContainer;
using Task = Lab9.model.Task;

namespace Lab9.decorator;

public class StrategyTaskRunner : ITaskRunner
{

    private IContainer _container;

    public StrategyTaskRunner(Strategy strategy)
    {
        _container = TaskContainerFactory.GetInstance().CreateContainer(strategy);
    }

    public void executeOneTask()
    {
        model.Task task = _container.Remove();
        task.Execute();
    }

    public void ExecuteAll()
    {
        while (HasTask())
        {
            executeOneTask();
        }
    }

    public void AddTask(Task t)
    {
        _container.Add(t);
    }

    public bool HasTask()
    {
        return !_container.IsEmpty();
    }
}