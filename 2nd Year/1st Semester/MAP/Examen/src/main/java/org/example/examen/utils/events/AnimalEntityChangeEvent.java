package org.example.examen.utils.events;

import org.example.examen.domain.Animal;

public class AnimalEntityChangeEvent implements Event{
    private final ChangeEventType type;
    private final Animal data;
    private Animal oldData;

    public AnimalEntityChangeEvent(ChangeEventType type, Animal data) {
        this.type = type;
        this.data = data;
    }
    public AnimalEntityChangeEvent(ChangeEventType type, Animal data, Animal oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Animal getData() {
        return data;
    }

    public Animal getOldData() {
        return oldData;
    }
}
