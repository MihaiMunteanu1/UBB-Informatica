module org.example.examen {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    opens org.example.examen to javafx.fxml;
    exports org.example.examen;
}