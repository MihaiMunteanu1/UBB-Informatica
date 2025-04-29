package ro.mpp2024;

import java.io.FileReader;
import java.io.IOException;
import java.util.Objects;
import java.util.Properties;

public class MainBD {
    public static void main(String[] args) {

        Properties props=new Properties();
        try {
            props.load(new FileReader("C:\\Users\\munte\\IdeaProjects\\MPP\\teme-lab-MihaiMunteanu1\\TemaLab3\\bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config "+e);
            return;
        }
        if (props.isEmpty()) {
            System.out.println("Properties file is empty or not loaded correctly.");
            return; // Exit the program if properties are not loaded
        }

        System.out.println("Adaugam o masina:");
        CarRepository carRepo=new CarsDBRepository(props);
        carRepo.add(new Car("Tesla","Model S", 2019));
        System.out.println("Toate masinile din db");
        for(Car car:carRepo.findAll())
            System.out.println(car);
        String manufacturer="Tesla";
        System.out.println("Masinile produse de "+manufacturer);
        for(Car car:carRepo.findByManufacturer(manufacturer))
            System.out.println(car);

        System.out.println("Modificam o masina:");
        Car car = new Car("Tesla","Model P", 10);
        carRepo.update(4,car);
        System.out.println("Toate masinile din db");
        for(Car car1:carRepo.findAll())
            System.out.println(car1);

        System.out.println("Cautam masini din ultimii 10 ani");
        for(Car car2:carRepo.findBetweenYears(2015,2025)){
            System.out.println(car2);
        }

        System.out.println("Afisare dupa o conditie: sa fie SEAT");
        for(Car car3:carRepo.findBetweenYears(2015,2025)){
            if(Objects.equals(car3.getManufacturer(), "Seat"))
            {
                System.out.println(car3);
            }
        }
    }
}
