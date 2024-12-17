using System.Runtime.Serialization;

namespace Lab9.decorator;

public class PrinterTaskRunner : AbstractTaskRunner
{
    private static string _format = "HH:mm:ss";


    public PrinterTaskRunner(ITaskRunner taskRunner) : base(taskRunner) {}

    public override void executeOneTask()
    {
        base.executeOneTask();
        Console.WriteLine("Task executed at: "+DateTime.Now.ToString(_format));
    }
}