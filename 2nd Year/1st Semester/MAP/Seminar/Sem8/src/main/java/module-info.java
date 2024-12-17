module org.example.sem {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;

    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens org.example.sem8 to javafx.fxml;
    exports org.example.sem8;
}