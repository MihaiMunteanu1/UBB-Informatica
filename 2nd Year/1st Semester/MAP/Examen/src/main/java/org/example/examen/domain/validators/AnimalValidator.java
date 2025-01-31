package org.example.examen.domain.validators;

import org.example.examen.domain.Animal;
import org.example.examen.domain.Type;
import org.example.examen.exceptions.ValidationException;

public class AnimalValidator implements Validator<Animal>{
    @Override
    public void validate(Animal entity) throws ValidationException {
        StringBuilder errors = new StringBuilder();

        if (entity == null) {
            throw new ValidationException("Animalul trebuie sa existe\n");
        }

        if (entity.getName() == null) {
            errors.append("Numele nu poate sa fie null\n");
        }

        if (entity.getCentreId() < 0) {
            errors.append("Centrul de adoptie trebuie sa existe\n");
        }

        try {
            Type.valueOf(entity.getType().name());
        } catch (IllegalArgumentException e) {
            errors.append("Tip invalid\n");
        }

        if(!errors.toString().isEmpty()){
            throw new ValidationException(errors.toString());
        }
    }
}
