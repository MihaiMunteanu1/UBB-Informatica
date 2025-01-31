package org.example.examen.domain.validators;

import org.example.examen.domain.AdoptionCentre;
import org.example.examen.exceptions.ValidationException;

public class AdoptionCentreValidator implements Validator<AdoptionCentre> {
    @Override
    public void validate(AdoptionCentre entity) throws ValidationException {
        StringBuilder errors = new StringBuilder();
        if (entity.getName().isEmpty()) {
            errors.append("Nume invalid\n");
        }
        if (entity.getLocation().isEmpty()) {
            errors.append("Locatie invalida\n");
        }
        if (entity.getCapacity() < 0) {
            errors.append("Capacitate invalida\n");
        }

        if (!errors.toString().isEmpty()) {
            throw new ValidationException(errors.toString());
        }
    }
}
