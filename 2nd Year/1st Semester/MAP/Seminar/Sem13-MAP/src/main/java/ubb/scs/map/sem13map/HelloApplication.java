package ubb.scs.map.sem13map;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import ubb.scs.map.sem13map.controller.Controller;
import ubb.scs.map.sem13map.domain.Angajat;
import ubb.scs.map.sem13map.domain.Pontaj;
import ubb.scs.map.sem13map.domain.Sarcina;
import ubb.scs.map.sem13map.domain.Tuple;
import ubb.scs.map.sem13map.repository.InMemoryRepository;
import ubb.scs.map.sem13map.repository.Repository;
import ubb.scs.map.sem13map.service.Service;


import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;

import static ubb.scs.map.sem13map.domain.Dificultate.MEDIE;
import static ubb.scs.map.sem13map.domain.Dificultate.USOARA;
import static ubb.scs.map.sem13map.domain.Nivel.*;


public class HelloApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("view/GUI.fxml"));
        AnchorPane root = loader.load();
        Controller ctrl = loader.getController();
        List<Sarcina> Sarcinas = generateSarcinas();
        List<Angajat> Angajats = generateAngajats();
        Repository<String, Sarcina> SarcinaRepository = new InMemoryRepository<>();
        for (Sarcina Sarcina : Sarcinas) {
            SarcinaRepository.save(Sarcina);
        }
        Repository<String, Angajat> AngajatRepository = new InMemoryRepository<>();
        for (Angajat Angajat : generateAngajats()) {
            AngajatRepository.save(Angajat);
        }
        Repository<Tuple<String>, Pontaj> PontajRepository = new InMemoryRepository<>();
        for (Pontaj Pontaj : generatePontajs(Angajats, Sarcinas)) {
            PontajRepository.save(Pontaj);
        }
        ctrl.setService(new Service(AngajatRepository, PontajRepository, SarcinaRepository));
        primaryStage.setScene(new Scene(root));
        primaryStage.setTitle("Hello World");
        primaryStage.show();
    }

    public List<Sarcina> generateSarcinas() {
        return Arrays.asList(new Sarcina("1", 1,  USOARA, "T1"), new Sarcina("2", 2,  MEDIE, "T2"), new Sarcina("3", 1, USOARA, "T3"));
    }

    public List<Angajat> generateAngajats() {
        return Arrays.asList(new Angajat("1", 100,"E1", SENIOR), new Angajat("2", 50,"E2", JUNIOR), new Angajat("3", 50,"E3", JUNIOR));
    }

    public List<Pontaj> generatePontajs(List<Angajat> Angajats, List<Sarcina> Sarcinas) {
        return Arrays.asList(new Pontaj(LocalDateTime.of(2025, 1, 1, 0, 0, 0), Angajats.get(0), Sarcinas.get(0)), new Pontaj(LocalDateTime.of(2025, 1, 2, 0, 0, 0), Angajats.get(0), Sarcinas.get(1)), new Pontaj(LocalDateTime.of(2025, 1, 1, 0, 0, 0), Angajats.get(1), Sarcinas.get(2)));
    }

    public static void main(String[] args) {
        launch(args);
    }
}