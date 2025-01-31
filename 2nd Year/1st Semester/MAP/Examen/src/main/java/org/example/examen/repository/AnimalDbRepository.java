package org.example.examen.repository;

import org.example.examen.domain.AdoptionCentre;
import org.example.examen.domain.Animal;
import org.example.examen.domain.Type;
import org.example.examen.domain.validators.Validator;

import java.sql.*;
import java.util.*;

public class AnimalDbRepository implements Repository<Long, Animal> {
    private final String url;
    private final String username;
    private final String password;
    private final Validator<Animal> validator;

    public AnimalDbRepository(String url, String username, String password, Validator<Animal> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }

    @Override
    public Optional<Animal> findOne(Long aLong) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from animal WHERE id = ?")) {
            statement.setLong(1, aLong);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    String name = resultSet.getString("name");
                    Type type = Type.valueOf(resultSet.getString("type"));
                    int centreId = resultSet.getInt("centreid");
                    Animal animal = new Animal(aLong, name, centreId, type);
                    return Optional.of(animal);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Animal> findAll() {
        Set<Animal> animale = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from animal");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = (long) resultSet.getInt("id");
                String name = resultSet.getString("name");
                Type type = Type.valueOf(resultSet.getString("type"));
                int centreId = resultSet.getInt("centreid");
                Animal animal = new Animal(id, name, centreId, type);
                animale.add(animal);
            }
            return animale;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return animale;
    }

    @Override
    public Optional<Animal> save(Animal entity) {
        return Optional.empty();
    }


    @Override
    public Optional<Animal> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Animal> update(Animal entity) {
        validator.validate(entity);
        Optional<Animal> animal = findOne(entity.getId());
        if (animal.isPresent() && !animal.get().equals(entity)) {
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement("UPDATE animal SET centreid = ? WHERE id = ?")) {
                statement.setInt(1, entity.getCentreId());
                statement.setInt(2, entity.getId().intValue());
                statement.executeUpdate();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return animal;
    }

}