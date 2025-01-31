package org.example.examen.utils.observer;

import org.example.examen.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);

}