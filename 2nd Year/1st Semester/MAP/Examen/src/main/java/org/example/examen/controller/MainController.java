package org.example.examen.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.examen.domain.AdoptionCentre;
import org.example.examen.domain.Animal;
import org.example.examen.service.Service;
import org.example.examen.domain.Type;
import org.example.examen.utils.events.AnimalEntityChangeEvent;
import org.example.examen.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class MainController implements Observer<AnimalEntityChangeEvent> {
    Service service;
    AdoptionCentre adoptionCentre;
    Stage stage;

    @FXML
    TableView<Animal> tableAnimale;

    @FXML
    TableColumn<Animal, String> numeAnimal;

    @FXML
    TableColumn<Animal, Integer> centruId;

    @FXML
    TableColumn<Animal, String> typeAnimal;

    @FXML
    Label labelText;

    @FXML
    Label labelProcent;

    @FXML
    ComboBox<String> comboType;

    private final ObservableList<Animal> model = FXCollections.observableArrayList();

    public void setService(Service service, Stage stage, AdoptionCentre adoptionCentre) {
        this.stage = stage;
        this.service = service;
        this.adoptionCentre = adoptionCentre;
        service.addObserver(this);
        init();
        initializeTableViews();
    }

    private void initializeTableViews() {
        numeAnimal.setCellValueFactory(new PropertyValueFactory<>("name"));
        centruId.setCellValueFactory(new PropertyValueFactory<>("centreId"));
        typeAnimal.setCellValueFactory(new PropertyValueFactory<>("type"));
        tableAnimale.setItems(model);

    }

    public void init() {
        model.setAll(service.getAnimaleByCentre(adoptionCentre));

        labelText.setText("Nume: " + adoptionCentre.getName() + ", Locatia: " +
                adoptionCentre.getLocation() + ", Capacitate: " + adoptionCentre.getCapacity());

        labelProcent.setText("Occupancy: " + service.getProcentOcupare(adoptionCentre) + "%");

        List<String> types = new ArrayList<>(service.getAllTypesByCentre(adoptionCentre));
        types.add("All types");
        comboType.setItems(FXCollections.observableArrayList(types));
    }

    @FXML
    public void handleComboChanged() {
        if (comboType.getValue() == null)
            return;
        if (comboType.getValue().equals("All types"))
            model.setAll(service.getAnimaleByCentre(adoptionCentre));
        else {
            String type = comboType.getValue();
            model.setAll(service.getAnimaleByTypeByCentre(Type.valueOf(type), adoptionCentre));
        }
    }

    @FXML
    public void handleRequest() {
        if (tableAnimale.getSelectionModel().getSelectedItem() == null) {
            MessageAlert.showErrorMessage(null, "Nu ati selectat niciun animal!");
            return;
        }
        Animal animal = tableAnimale.getSelectionModel().getSelectedItem();
        if(!service.centreDinAceeasiLocatie(adoptionCentre)) {
            MessageAlert.showErrorMessage(null, "Nu mai exista centre in aceasta locatie!");
            return;
        }
        service.sendRequest(animal, adoptionCentre);
    }


    @Override
    public void update(AnimalEntityChangeEvent animalEntityChangeEvent) {
        init();
        initializeTableViews();
    }


}
