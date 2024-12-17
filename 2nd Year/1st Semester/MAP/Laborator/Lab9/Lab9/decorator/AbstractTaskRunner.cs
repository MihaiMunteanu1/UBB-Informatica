using Task = Lab9.model.Task;

namespace Lab9.decorator;

public abstract class AbstractTaskRunner : ITaskRunner
{
    private ITaskRunner _taskRunner;
    
    public AbstractTaskRunner(ITaskRunner taskRunner) {
        _taskRunner = taskRunner;
    }

    public virtual void executeOneTask()
    {
        _taskRunner.executeOneTask();
    }
    
    public virtual void ExecuteAll() {
        while (HasTask()) {
            executeOneTask();
        }
    }

    public  virtual void AddTask(Task t) {
        _taskRunner.AddTask(t);
    }

    public virtual  bool HasTask() {
        return _taskRunner.HasTask();
    }
}