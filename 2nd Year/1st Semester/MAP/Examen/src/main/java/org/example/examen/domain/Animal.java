package org.example.examen.domain;

import java.util.Objects;

public class Animal extends Entity<Long> {
    private String name;
    private int centreId;
    private Type type;

    public Animal(Long id, String name, int centreId, Type type) {
        setId(id);
        this.name = name;
        this.centreId = centreId;
        this.type = type;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCentreId() {
        return centreId;
    }

    public void setCentreId(int centreId) {
        this.centreId = centreId;
    }

    public Type getType() {
        return type;
    }

    public void setType(Type type) {
        this.type = type;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Animal animal = (Animal) o;
        return centreId == animal.centreId && Objects.equals(name, animal.name) && type == animal.type;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), name, centreId, type);
    }

    @Override
    public String toString() {
        return "Animal{" +
                "name='" + name + '\'' +
                ", centreId=" + centreId +
                ", type=" + type +
                '}';
    }
}
