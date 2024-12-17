import java.sql.SQLOutput;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Collectors;

public class Main {
    public static <E> List<E> filterGeneric(List<E> list, Predicate<E> predicate) {
        return list.stream()
                .filter(predicate)
                .collect(Collectors.toList());
    }

    public static <E> List<E> filterGeneric2(List<E> list, Predicate<E> predicate, Comparator<E> comparator) {
        return list.stream()
                .filter(predicate)
                .sorted(comparator)
                .collect(Collectors.toList());
    }

    static <T> void printWithCondition(Predicate<T>pred, List<T> list){
        for(T item : list){
            if(pred.test(item)){
                System.out.println(item);
            }
        }
    }

    public static void main(String[] args) {

         ///1.)
        List<Circle> listaTest= new ArrayList<>();
        listaTest.add(new Circle(3));
        listaTest.add(new Circle(5));

        Arie<Circle> arieCircle = x -> x.getRaza()*x.getRaza()*Math.PI;

        //TestFunctionalInterface.printArie(listaTest,arieCircle);


        /// 2.)

        List<Circle> circleList = new ArrayList<>();
        circleList.add(new Circle(3));
        circleList.add(new Circle(2));
        circleList.add(new Circle(5));

        Predicate<Circle> hadRadiusLessThan4 = x->x.getRaza()<4;
        Predicate<Circle> radiusIsEven = x->x.getRaza()%2==0;
        Predicate<Circle> lessThan4andEven = hadRadiusLessThan4.and(radiusIsEven);

        //printWithCondition(hadRadiusLessThan4.negate(), circleList);
        //printWithCondition(lessThan4andEven, circleList);

        /// 3.)
        Function<String, Integer> converterLambda = x-> Integer.valueOf( x );
        Function<String, Integer> converterMethodReference = Integer::valueOf;

        //System.out.println(converterMethodReference.apply("3"));

        /// 4.)

        Supplier<LocalDate> localDateSupplier = ()->LocalDate.now();
        Supplier<LocalDate> localDateMethodReference = LocalDate::now;

        //System.out.println(localDateMethodReference.get());
        /// 5.)

        List<Integer> list= Arrays.asList(3,5,2,7, 12, 6, 9, 11);
        List<Integer> list2= List.of(3,5,7);

        Comparator<Integer> ascendingComparator = Integer::compare;
        Comparator<Integer> descendingComparator = (x,y) -> Integer.compare(y,x);

        ascendingComparator.compare(1,2);
        System.out.println(list);

        list.sort(ascendingComparator);
        System.out.println(list);

        list.sort(descendingComparator);
        System.out.println(list);

        Predicate<Integer> predCheckEven = x -> x % 2 == 0;
        List<Integer> evenNumber = filterGeneric(list, predCheckEven);
        System.out.println(list);
        System.out.println(evenNumber);

        System.out.println();

        List<Integer> evenSortedNumbers = filterGeneric2(list, predCheckEven, ascendingComparator);
        System.out.println(evenSortedNumbers);
    }
}