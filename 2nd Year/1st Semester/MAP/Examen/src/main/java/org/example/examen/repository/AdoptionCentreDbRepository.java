package org.example.examen.repository;

import org.example.examen.domain.AdoptionCentre;
import org.example.examen.domain.Animal;
import org.example.examen.domain.Type;

import java.sql.*;
import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;

public class AdoptionCentreDbRepository implements Repository<Long, AdoptionCentre> {
    private final String url;
    private final String username;
    private final String password;

    public AdoptionCentreDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<AdoptionCentre> findOne(Long aLong) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from adoptioncentre WHERE id = ?")) {
            statement.setLong(1, aLong);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    String name = resultSet.getString("name");
                    String location = resultSet.getString("location");
                    int capacity = resultSet.getInt("capacity");
                    AdoptionCentre adoptionCentre = new AdoptionCentre(aLong, name, location, capacity);
                    return Optional.of(adoptionCentre);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<AdoptionCentre> findAll() {
        Set<AdoptionCentre> centre = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from adoptioncentre");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = (long) resultSet.getInt("id");
                String name = resultSet.getString("name");
                String location = resultSet.getString("location");
                int capacity = resultSet.getInt("capacity");
                AdoptionCentre adoptionCentre = new AdoptionCentre(id, name, location, capacity);
                centre.add(adoptionCentre);
            }
            return centre;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return centre;
    }

    @Override
    public Optional<AdoptionCentre> save(AdoptionCentre entity) {
        return Optional.empty();
    }


    @Override
    public Optional<AdoptionCentre> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<AdoptionCentre> update(AdoptionCentre entity) {
        return Optional.empty();
    }

}