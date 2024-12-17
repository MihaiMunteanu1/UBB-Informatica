package sem1_2.model;

import java.util.ArrayList;
import java.util.List;

public class StackContainer extends AbstractCointainer {

    public StackContainer() {
        tasks = new Task[10];
        size = 0;
    }

    @Override
    public Task remove() {
        if (!isEmpty()) {
            return tasks[--this.size];
        }
        return null;
    }
}
