package org.example.sem8.domain;

import java.io.Serial;
import java.io.Serializable;

public class Entity<ID> implements Serializable {
    private ID id;
    @Serial
    private static final long serialVersionUID = 4500794925126064682L;

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }
}
