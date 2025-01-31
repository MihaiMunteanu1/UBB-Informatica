package org.example.examen.domain;

import java.util.Objects;

public class AdoptionCentre extends Entity<Long>{
    private String name;
    private String location;
    private int capacity;

    public AdoptionCentre(Long id,String name, String location, int capacity) {
        setId(id);
        this.name = name;
        this.location = location;
        this.capacity = capacity;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        AdoptionCentre that = (AdoptionCentre) o;
        return capacity == that.capacity && Objects.equals(name, that.name) && Objects.equals(location, that.location);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), name, location, capacity);
    }

    @Override
    public String toString() {
        return "AdoptionCentre{" +
                "name='" + name + '\'' +
                ", location='" + location + '\'' +
                ", capacity=" + capacity +
                '}';
    }
}
