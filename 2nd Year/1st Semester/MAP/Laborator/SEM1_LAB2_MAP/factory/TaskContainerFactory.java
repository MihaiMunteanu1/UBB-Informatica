package sem1_2.factory;

import sem1_2.model.Container;
import sem1_2.model.QueueContainer;
import sem1_2.model.StackContainer;

public class TaskContainerFactory implements Factory {

    private static final TaskContainerFactory instance = new TaskContainerFactory();

    public static TaskContainerFactory getInstance() {
        return instance;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        return switch (strategy) {
            case FIFO -> new QueueContainer();
            case LIFO -> new StackContainer();
        };
    }
}
