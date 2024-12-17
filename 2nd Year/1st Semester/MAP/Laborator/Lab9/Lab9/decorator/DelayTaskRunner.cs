using System.Reflection.Metadata;
using System.Runtime.Serialization;

namespace Lab9.decorator;

public class DelayTaskRunner : AbstractTaskRunner
{
    public DelayTaskRunner(ITaskRunner taskRunner) : base(taskRunner){}

    private static string _format = "HH:mm:ss";

    public override void executeOneTask()
    {
        try
        {
            Thread.Sleep(3000);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
        
        base.executeOneTask();
    }
}