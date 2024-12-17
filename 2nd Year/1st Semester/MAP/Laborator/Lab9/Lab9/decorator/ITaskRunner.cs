using Task = Lab9.model.Task;

namespace Lab9.decorator;

public interface ITaskRunner
{
    void executeOneTask();
    void ExecuteAll();
    void AddTask(Task t);
    bool HasTask();
}