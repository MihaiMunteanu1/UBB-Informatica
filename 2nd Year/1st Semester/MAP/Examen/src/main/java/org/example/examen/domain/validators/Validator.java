package org.example.examen.domain.validators;

import org.example.examen.exceptions.ValidationException;

@FunctionalInterface
public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}
