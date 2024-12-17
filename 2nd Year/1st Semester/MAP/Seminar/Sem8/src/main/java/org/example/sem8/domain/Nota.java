package org.example.sem8.domain;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class Nota  {
    private Student student;
    private Tema tema;
    private double value;
    private LocalDate date;
    private String profesor;

    public Nota(Student student, Tema tema, double value, LocalDate date, String profesor) {
        this.student = student;
        this.profesor = profesor;
        this.date = date;
        this.value = value;
        this.tema = tema;
    }

    public Student getStudent() {
        return student;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public String getProfesor() {
        return profesor;
    }

    public void setProfesor(String profesor) {
        this.profesor = profesor;
    }

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public double getValue() {
        return value;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public Tema getTema() {
        return tema;
    }

    public void setTema(Tema tema) {
        this.tema = tema;
    }

    @Override
    public String toString() {
        return "Nota{" +
                "student=" + student +
                ", tema=" + tema +
                ", value=" + value +
                ", date=" + date +
                ", profesor='" + profesor + '\'' +
                '}';
    }
}
