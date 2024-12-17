import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class Main {
    private static double average(List<Nota> note){
        double sum = note.stream().map(Nota::getNota).reduce(0.0, Double::sum);
        return sum / note.size();
    }

    public static void main(String[] args) {
        List<Student> students = new ArrayList<>();

        students.add(new Student("ABC",220).setId(1L));
        students.add(new Student("BAC",221).setId(2L));
        students.add(new Student("CBA",222).setId(3L));

        List<Tema> teme = new ArrayList<>();

        teme.add(new Tema("D","abcdefg"));
        teme.add(new Tema("E","abcdefg"));
        teme.add(new Tema("F","abcdefg"));

        List<Nota> note = new ArrayList<>();

        note.add(new Nota(students.get(0),teme.get(0), 9.5, "SLG"));
        note.add(new Nota(students.get(0),teme.get(1), 9, "LSG"));
        note.add(new Nota(students.get(0),teme.get(2), 9.2, "GLS"));

        note.add(new Nota(students.get(1),teme.get(0), 9, "SLG"));
        note.add(new Nota(students.get(1),teme.get(1), 7.56, "LSG"));
        note.add(new Nota(students.get(1),teme.get(2), 8, "GLS"));

        note.add(new Nota(students.get(2),teme.get(0), 9, "SLG"));
        note.add(new Nota(students.get(2),teme.get(1), 4, "LSG"));
        note.add(new Nota(students.get(2),teme.get(2), 8.49, "GLS"));

        Map<Student, List<Nota>> studentGrades= note.stream()
                .filter(x->x.getStudent().getName().contains("A"))
                .collect(Collectors.groupingBy(Nota::getStudent));


        Map<Student, Double> averageGrades = studentGrades.entrySet().stream()
                .collect(Collectors.groupingBy(Map.Entry::getKey, Collectors.averagingDouble(e->average(e.getValue()))));

//        Map<Student, Double> averageGrades = studentGrades.entrySet().stream()
//                .collect(Collectors.groupingBy(Map.Entry::getKey, Collectors.collectingAndThen(Collectors.toList(), x->average(x.getValu))));

        averageGrades.entrySet()
                .stream()
                .sorted(Map.Entry.<Student,Double>comparingByValue().reversed())
                .forEach(x->System.out.println(x.getKey().getName() + ' ' + x.getValue()));

        System.out.println('\n');

        Map<Student,Double> sortedAverageGrades = averageGrades.entrySet()
                .stream()
                .sorted(Map.Entry.<Student,Double>comparingByValue().reversed())
                .collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue, (value1,value2) ->value1,LinkedHashMap::new));

        sortedAverageGrades.forEach((x,y)->System.out.println(x.getName()+ ' ' + y));

        ///Raport 2

        System.out.println('\n');


        Map<String,Double> teacherAverages=note
                .stream()
                .filter(nota -> nota.getProfessor().contains("L"))
                .collect(Collectors.groupingBy(Nota::getProfessor, Collectors.averagingDouble(Nota::getNota)))
                .entrySet()
                .stream()
                .sorted(Map.Entry.<String,Double>comparingByValue().reversed())
                .collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue, (value1,value2) ->value1,LinkedHashMap::new));

        teacherAverages.forEach((x,y) -> System.out.println(x + ' ' + y));

        System.out.println('\n');

        ///Raport 3

        note
                .stream()
                .filter(nota -> nota.getStudent().getGroup() == 221)
                .collect(Collectors.groupingBy(Nota::getTema, Collectors.counting()))
                .entrySet()
                .stream()
                .sorted(Map.Entry.<Tema,Long>comparingByValue().reversed())
                .forEach(x->System.out.println(x.getKey().getId() + ' ' + x.getValue()));

        ///Raport 4

        System.out.println("Raport 4");

        note
                .stream()
                .filter(nota -> String.valueOf(nota.getStudent().getGroup()).startsWith("2"))
                .collect(Collectors.groupingBy(x -> x.getStudent().getGroup(), Collectors.collectingAndThen(Collectors.toList(),groupGrades -> new GroupDTO(average(groupGrades), (long) groupGrades.size()))))
                .entrySet()
                .stream()
                .sorted((e1,e2) -> Double.compare(e2.getValue().getAverage(),e1.getValue().getAverage()))
                .forEach(x -> System.out.println(x.getKey().toString() + ' ' + x.getValue().getAverage() + ' ' + x.getValue().getCount()));
    }
}