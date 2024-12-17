import java.util.*;

public class Mainn {

    public void main() {
        Student s1=new Student("Dan",4.5f);
        Student s2=new Student("Ana",8.5f);
        Student s3=new Student("Dan",4.5f);

        Set<Student> set=new HashSet<>();
        set.add(s1);
        set.add(s2);
        set.add(s3);

        for(Student s:set){
            //System.out.println(s);
        }

        System.out.println();

        Set<Student> treeSet=new TreeSet<>();
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);

        for(Student s:treeSet){
            //System.out.println(s);
        }

        System.out.println();

        ///Si comparable din clasa Student poate fi comentat daca dam argument de new Comparator..
        Set<Student> treeSet2=new TreeSet<>(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o2.getNume().compareTo(o1.getNume());
            }
        });
        treeSet2.add(s1);
        treeSet2.add(s2);
        treeSet2.add(s3);

        for(Student s:treeSet2){
            //System.out.println(s);
        }
        ///5)

        Map<String,Student> map=new TreeMap<>();
        map.put(s1.getNume(),s1);
        map.put(s2.getNume(),s2);
        map.put(s3.getNume(),s3);

        for(Map.Entry<String,Student> s: map.entrySet()){
            //System.out.println(s.getKey()+" "+s.getValue());
        }

        System.out.println();

        Map<String,Student> hash=new HashMap<>();
        hash.put(s1.getNume(),s1);
        hash.put(s2.getNume(),s2);
        hash.put(s3.getNume(),s3);

        for(Map.Entry<String,Student> s: hash.entrySet()){
            //System.out.println(s.getKey()+" "+s.getValue().getMedia());
        }
    }
}


///II.
public static List<Student> getList() {
    List<Student> l = new ArrayList<>();
    l.add(new Student("1", 9.7f));
    l.add(new Student("2", 7.3f));
    l.add(new Student("3", 6f));
    l.add(new Student("4", 6.9f));
    l.add(new Student("5", 9.5f));
    l.add(new Student("6", 9.9f));
    return l;
}

public void main() {

    ///I.
    //Mainn m=new Mainn();
    //m.main();

    ///II.
    MyMap map=new MyMap();

    //MyMapComposition map=new MyMapComposition();

    List<Student> students=getList();
    for(Student s:students){
        map.addStudent(s);
    }

    for(Map.Entry<Integer,List<Student>> o:map.getEntries()){
        //System.out.println("Medie=: "+o.getKey());
        List<Student> sortedStudents=o.getValue();
        Collections.sort(sortedStudents);
        //System.out.println("Studenti: ");
        for(Student s:sortedStudents){
            //System.out.println(s.getNume());
        }
    }

    ///III.
    Student s1=new Student("Dan",4.5f);
    Student s2=new Student("Ana",8.5f);
    Student s3=new Student("Dan",4.5f);
    Repository<String,Student> repo= new InMemoryRepository<>();
    repo.save(s1);
    repo.save(s2);
    repo.save(s3);

    for(Student s:repo.findAll()){
        System.out.println(s);
    }
}