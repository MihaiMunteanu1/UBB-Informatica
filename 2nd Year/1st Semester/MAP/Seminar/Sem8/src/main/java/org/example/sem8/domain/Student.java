package org.example.sem8.domain;

public class Student extends Entity<Long> {
    private String name;
    private int grup;

    public Student(String name, int grup ) {
        this.grup = grup;
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getGrup() {
        return grup;
    }

    public void setGrup(int grup) {
        this.grup = grup;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", grup=" + grup +
                '}';
    }
}
