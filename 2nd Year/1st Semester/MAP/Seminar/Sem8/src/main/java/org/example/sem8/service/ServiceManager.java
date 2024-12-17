package org.example.sem8.service;

import org.example.sem8.domain.Nota;
import org.example.sem8.domain.Student;
import org.example.sem8.domain.Tema;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;

public class ServiceManager {

    public List<Student> findAllStudents() {
        Student s1 = new Student("a",1);
        s1.setId(1L);
        Student s2 = new Student("b",2);
        s2.setId(2L);
        Student s3 = new Student("c",3);
        s3.setId(3L);

        return Arrays.asList(s1,s2,s3);
    }

    public List<Tema> findAllHomeWorks() {
        Tema t1 = new Tema("1","greu");
        Tema t2 = new Tema("2","usor");
        Tema t3 = new Tema("3","mediu");
        Tema t4 = new Tema("4","foarte-greu");

        return Arrays.asList(t1,t2,t3,t4);
    }

    public List<Nota> findAllGrades() {
        return getNote(findAllStudents(),findAllHomeWorks());
    }

    private List<Nota> getNote(List<Student> studenti, List<Tema> teme){
        return Arrays.asList(
                new Nota(studenti.get(0), teme.get(0), 10d, LocalDate.of(2019, 11, 2), "profesor1"),
                new Nota(studenti.get(1), teme.get(0), 9d, LocalDate.of(2022, 8, 21), "profesor1"),
                new Nota(studenti.get(1), teme.get(1), 10d, LocalDate.of(2024, 10, 20), "profesor2"),
                new Nota(studenti.get(1), teme.get(2), 10d, LocalDate.of(2024, 4, 10), "profesor2"),
                new Nota(studenti.get(2), teme.get(1), 7d, LocalDate.of(2024, 6, 8), "profesor1"),
                new Nota(studenti.get(2), teme.get(3), 9d, LocalDate.of(2024, 7, 7), "profesor2"),
                new Nota(studenti.get(1), teme.get(3), 10d, LocalDate.of(2023, 1, 9), "profesor2")
        );
    }
}
