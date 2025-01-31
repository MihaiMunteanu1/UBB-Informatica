package org.example.examen;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.examen.controller.MainController;
import org.example.examen.domain.AdoptionCentre;
import org.example.examen.domain.validators.AnimalValidator;
import org.example.examen.repository.AdoptionCentreDbRepository;
import org.example.examen.repository.AnimalDbRepository;
import org.example.examen.service.Service;

import java.io.IOException;
import java.util.List;

public class HelloApplication extends Application {
    Service service;

    @Override
    public void start(Stage primaryStage) throws IOException {

        String url = "jdbc:postgresql://localhost:5432/examen";
        String username = "postgres";
        String password = "postgres";


        AnimalDbRepository animalDbRepository = new AnimalDbRepository(url, username, password, new AnimalValidator());
        AdoptionCentreDbRepository adoptionCentreDbRepository = new AdoptionCentreDbRepository(url, username, password);


        service = new Service(animalDbRepository, adoptionCentreDbRepository);

        System.out.println(animalDbRepository.findAll());

        System.out.println(adoptionCentreDbRepository.findAll());

        initView();
        primaryStage.setWidth(800);
        primaryStage.show();


    }

    private void initView() throws IOException {

        for (AdoptionCentre adoptionCentre : service.findAll()) {
            try {
                FXMLLoader loader = new FXMLLoader();
                loader.setLocation(getClass().getResource("/org/example/examen/main-view.fxml"));
                AnchorPane root = loader.load();
                Stage stage = new Stage();
                stage.initModality(Modality.WINDOW_MODAL);
                stage.setScene(new Scene(root));
                stage.setTitle(adoptionCentre.getName()+", "+adoptionCentre.getLocation()+", "+adoptionCentre.getCapacity());

                MainController mainController = loader.getController();
                mainController.setService(service, stage, adoptionCentre);

                stage.show();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    public static void main(String[] args) {
        launch();
    }
}