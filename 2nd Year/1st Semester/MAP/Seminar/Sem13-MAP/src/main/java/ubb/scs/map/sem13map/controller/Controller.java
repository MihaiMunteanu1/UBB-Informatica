package ubb.scs.map.sem13map.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import ubb.scs.map.sem13map.domain.Angajat;
import ubb.scs.map.sem13map.service.Service;

import java.time.YearMonth;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Controller {
    @FXML
    private ListView<String> listView;
    @FXML
    ComboBox<Integer> monthComboBox;
    private ObservableList<String> items;
    private Service service;

    @FXML
    public void initialize() {
        items = FXCollections.observableArrayList();
        listView.setItems(items);
        monthComboBox.getItems().setAll(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
    }

    public void handleReport1() {
        items.setAll(service.getEmployeesOrderedByLevelAndRatePerHour().stream().map(Angajat::toString).collect(Collectors.toList()));
    }

    public void handleReport2() {
        items.setAll(service.getAverageTaskTime().entrySet().stream().map(e -> e.getKey() + " " + e.getValue()).collect(Collectors.toList()));
    }

    public void handleReport3() {
        items.setAll(service.getTopBestPaidEmployees(2, 2025).stream().map(p -> p.getLeft() + " " + p.getRight()).collect(Collectors.toList()));
    }

    public void handleReport4() {
        Integer month = monthComboBox.getValue();
        if (month == null) {
            return;
        }
        items.setAll(service.getEmployeeSalaries(YearMonth.of(2025, monthComboBox.getValue())).stream().map(p -> p.getLeft() + " " + p.getRight()).collect(Collectors.toList()));
    }

    public void setService(Service service) {
        this.service = service;
    }
}
