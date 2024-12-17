
using Lab9.decorator;
using Lab9.factory;
using Lab9.model;

namespace Lab9;

public class Program
{

    private static MessageTask[] MessageTasks()
    {
        MessageTask task1 = new MessageTask("1", "A", "AA", "2", "1", DateTime.Now);
        MessageTask task2 = new MessageTask("2", "B", "BB", "3", "2", DateTime.Now);
        MessageTask task3 = new MessageTask("3", "C", "CC", "4", "3", DateTime.Now);
        MessageTask task4 = new MessageTask("4", "D", "DD", "5", "4", DateTime.Now);
        MessageTask task5 = new MessageTask("5", "E", "EE", "1", "5", DateTime.Now);

        return new MessageTask[]{task1, task2, task3, task4, task5};
    }
    
    public static void Main(String[] args)
    {
        Console.WriteLine("Test QUICK");
        int[] n1 = [5, 2, 4];
        SortingTask t1 = new SortingTask("1", "A", n1, SortingStrategy.Quick);
        t1.Execute();

        Console.WriteLine("Test BUBBLE");
        int[] n2 = { 12, 3, 4 };
        SortingTask t2 = new SortingTask("2", "B", n2, SortingStrategy.Bubble);
        t2.Execute();

        if (args.Length != 1)
        {
            Console.WriteLine("Introduceti un argument: FIFO sau LIFO\n");
            return;
        }

        Strategy strategy;
        try
        {
            strategy = (Strategy)Enum.Parse(typeof(Strategy), args[0], true);
        }
        catch (ArgumentException)
        {
            Console.WriteLine("Strategie invalida!\n");
            return;
        }

        Console.WriteLine("Strategia: " + args[0] + "\n");

        MessageTask[] messageTasks = MessageTasks();

        Console.WriteLine("StrategyTaskRunner: \n");
        ITaskRunner strategyTaskRunner = new StrategyTaskRunner(strategy);
        foreach (MessageTask task in messageTasks)
        {
            strategyTaskRunner.AddTask(task);
        }
        strategyTaskRunner.ExecuteAll();

        Console.WriteLine("\nDelayTaskRunner: \n");
        ITaskRunner delayTaskRunner = new DelayTaskRunner(strategyTaskRunner);
        foreach (MessageTask task in messageTasks)
        {
            delayTaskRunner.AddTask(task);
        }
        delayTaskRunner.ExecuteAll();

        Console.WriteLine("\nPrinterTaskRunner: \n");
        ITaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        foreach (MessageTask task in messageTasks)
        {
            printerTaskRunner.AddTask(task);
        }
        printerTaskRunner.ExecuteAll();
    }

}
