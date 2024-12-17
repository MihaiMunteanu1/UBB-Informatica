package sem1_2;

import sem1_2.decorator.DelayTaskRunner;
import sem1_2.decorator.PrinterTaskRunner;
import sem1_2.decorator.StrategyTaskRunner;
import sem1_2.decorator.TaskRunner;
import sem1_2.factory.SortingStrategy;
import sem1_2.factory.Strategy;
import sem1_2.model.MessageTask;
import sem1_2.model.SortingTask;

import java.time.LocalDateTime;

public class Sem1_2Test {

    private static MessageTask[] MessageTasks() {
        MessageTask task1 = new MessageTask("1", "A", "AA", "2", "1", LocalDateTime.now());
        MessageTask task2 = new MessageTask("2", "B", "BB", "3", "2", LocalDateTime.now());
        MessageTask task3 = new MessageTask("3", "C", "CC", "4", "3", LocalDateTime.now());
        MessageTask task4 = new MessageTask("4", "D", "DD", "5", "4", LocalDateTime.now());
        MessageTask task5 = new MessageTask("5", "E", "EE", "1", "5", LocalDateTime.now());

        return new MessageTask[]{task1, task2, task3, task4, task5};
    }

    public static void main(String[] args) {

        System.out.println("Test QUICK");
        int[] n1 = {5, 2, 4};
        SortingTask t1 = new SortingTask("1","A",n1, SortingStrategy.QUICK);
        t1.execute();


        System.out.println("Test BUBBLE");
        int[] n2 = {12, 3, 4};
        SortingTask t2 = new SortingTask("2","B", n2, SortingStrategy.BUBBLE);
        t2.execute();


        if (args.length != 1) {
            System.out.println("Introduceti un argument: FIFO sau LIFO\n");
            return;
        }

        Strategy strategy;
        try {
            strategy = Strategy.valueOf(args[0]);
        } catch (IllegalArgumentException e) {
            System.out.println("Strategie invalida!\n");
            return;
        }

        System.out.println("Strategia: "+args[0]+"\n");

        MessageTask[] messageTasks = MessageTasks();

        System.out.println("StrategyTaskRunner: \n");
        TaskRunner strategyTaskRunner = new StrategyTaskRunner(strategy);
        for (MessageTask task : messageTasks) {
            strategyTaskRunner.addTask(task);
        }
        strategyTaskRunner.executeAll();


        System.out.println("\nDelayTaskRunner: \n");
        TaskRunner delayTaskRunner = new DelayTaskRunner(strategyTaskRunner);
        for (MessageTask task : messageTasks) {
            delayTaskRunner.addTask(task);
        }
        delayTaskRunner.executeAll();


        System.out.println("\nPrinterTaskRunner: \n");
        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        for (MessageTask task : messageTasks) {
            printerTaskRunner.addTask(task);
        }
        printerTaskRunner.executeAll();
    }

}