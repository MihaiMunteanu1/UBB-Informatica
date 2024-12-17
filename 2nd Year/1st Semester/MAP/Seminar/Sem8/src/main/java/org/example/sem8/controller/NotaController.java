package org.example.sem8.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import org.example.sem8.domain.NotaDTO;
import org.example.sem8.domain.Tema;
import org.example.sem8.service.ServiceManager;

import java.util.List;
import java.util.Objects;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class NotaController {

    ServiceManager service;
    ObservableList<NotaDTO> modelGrade = FXCollections.observableArrayList();
    List<String> modelTema;
    @FXML
    TableColumn<NotaDTO, String> tableColumnName;
    @FXML
    TableColumn<NotaDTO, String> tableColumnTema;
    @FXML
    TableColumn<NotaDTO, Double> tableColumnNota;
    @FXML
    TableView<NotaDTO> tableViewNote;

    @FXML
    TextField numeStudent;

    @FXML
    TextField notaMaiMareDecat;

    @FXML
    TextField tema;

    @FXML
    ComboBox<String> comboBox;


    @FXML
    void initialize() {
        tableColumnName.setCellValueFactory(new PropertyValueFactory<>("studentName"));
        tableColumnTema.setCellValueFactory(new PropertyValueFactory<>("temaId"));
        tableColumnNota.setCellValueFactory(new PropertyValueFactory<>("nota"));

        tableViewNote.setItems(modelGrade);

        numeStudent.textProperty().addListener(o -> handleFitler());
        tema.textProperty().addListener(o -> handleFitler());
        notaMaiMareDecat.textProperty().addListener(o -> handleFitler());

        comboBox.getSelectionModel().selectedItemProperty().addListener(
                (x, y, z) -> handleFitler()
        );
    }


    public void setService(ServiceManager service) {
        this.service = service;
        modelGrade.setAll(getNotaDTOList());
        modelTema = service.findAllHomeWorks()
                .stream()
                .map(Tema::getId)
                .collect(Collectors.toList());

        comboBox.getItems().setAll(modelTema);
    }

    private List<NotaDTO> getNotaDTOList(){
        return service.findAllGrades()
                .stream()
                .map(n -> new NotaDTO(n.getStudent().getName(), n.getTema().getId(), n.getValue(), n.getProfesor()))
                .collect(Collectors.toList());
    }

    @FXML
    private void handleFitler(){

        String selection = comboBox.getSelectionModel().getSelectedItem();

        String idTema="";
        if(!selection.isEmpty()){
            idTema = comboBox.getSelectionModel().getSelectedItem();
            System.out.println(idTema);
        }


        String name = numeStudent.getText();
        String temaa = tema.getText();
        String nota = notaMaiMareDecat.getText();

        Predicate<NotaDTO> verifyName = o -> o.getStudentName().startsWith(name);
        Predicate<NotaDTO> verifyTema = o -> o.getTemaId().startsWith(temaa);
        Predicate<NotaDTO> verifyNota = o -> {
            if (!Objects.equals(nota, "")) {
                return o.getNota() > Double.parseDouble(nota);
            } else return true;
        };

        List<NotaDTO> multipleFilter = getNotaDTOList()
                .stream()
                .filter(verifyName.and(verifyTema).and(verifyNota))
                .toList();

        multipleFilter = multipleFilter
                .stream()
                .filter(o -> o.getStudentName().startsWith(name))
                .toList();

        multipleFilter = multipleFilter
                .stream()
                .filter(o -> o.getTemaId().startsWith(temaa))
                .toList();


        if (!Objects.equals(nota, "")) {
            multipleFilter = multipleFilter
                    .stream()
                    .filter(o -> o.getNota() > Double.parseDouble(nota))
                    .toList();
        }

        if(!idTema.isEmpty()){
            multipleFilter = multipleFilter
                    .stream()
                    .filter(o -> o.getTemaId().equals(selection))
                    .toList();
        }

        modelGrade.setAll(multipleFilter);
    }

}
