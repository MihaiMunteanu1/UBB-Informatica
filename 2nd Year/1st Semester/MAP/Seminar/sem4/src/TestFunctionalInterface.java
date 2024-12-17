import java.util.List;

public class TestFunctionalInterface<E> {
    public static <E> void printArie(List<E> l, Arie<E> f) {
        l.forEach(x->System.out.println(f.compute(x)));
    }
}
