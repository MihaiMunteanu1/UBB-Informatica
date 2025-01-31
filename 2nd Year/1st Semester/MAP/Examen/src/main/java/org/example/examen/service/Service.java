package org.example.examen.service;

import javafx.scene.control.Alert;
import javafx.scene.control.ButtonBar;
import javafx.scene.control.ButtonType;
import org.example.examen.domain.AdoptionCentre;
import org.example.examen.domain.Animal;
import org.example.examen.domain.Type;
import org.example.examen.repository.Repository;
import org.example.examen.utils.events.AnimalEntityChangeEvent;
import org.example.examen.utils.events.ChangeEventType;
import org.example.examen.utils.observer.Observable;
import org.example.examen.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.stream.StreamSupport;

public class Service implements Observable<AnimalEntityChangeEvent> {

    private final Repository<Long, Animal> animalRepository;
    private final Repository<Long, AdoptionCentre> adoptionCentreRepository;
    private final List<Observer<AnimalEntityChangeEvent>> observers = new ArrayList<>();

    public Service(Repository<Long, Animal> animalRepository, Repository<Long, AdoptionCentre> adoptionCentreRepository) {
        this.animalRepository = animalRepository;
        this.adoptionCentreRepository = adoptionCentreRepository;
    }

    public int getProcentOcupare(AdoptionCentre adoptionCentre) {
        int nrAnimale = 0;
        for (Animal animal : animalRepository.findAll()) {
            if (animal.getCentreId() == adoptionCentre.getId()) {
                nrAnimale++;
            }
        }
        return nrAnimale * 100 / adoptionCentre.getCapacity();
    }

    public List<Animal> getAnimaleByCentre(AdoptionCentre adoptionCentre) {
        return StreamSupport.stream(animalRepository.findAll().spliterator(), false)
                .filter(animal -> animal.getCentreId() == adoptionCentre.getId())
                .toList();
    }

    public List<AdoptionCentre> findAll() {
        return StreamSupport.stream(adoptionCentreRepository.findAll().spliterator(), false)
                .toList();
    }


    public List<String> getAllTypesByCentre(AdoptionCentre adoptionCentre) {
        return StreamSupport.stream(animalRepository.findAll().spliterator(), false)
                .filter(animal -> animal.getCentreId() == adoptionCentre.getId())
                .map(animal -> animal.getType().toString())
                .distinct()
                .toList();
    }

    public List<Animal> getAnimaleByTypeByCentre(Type type, AdoptionCentre adoptionCentre) {
        return StreamSupport.stream(animalRepository.findAll().spliterator(), false)
                .filter(animal -> animal.getType().equals(type) && animal.getCentreId() == adoptionCentre.getId())
                .toList();
    }

    public boolean centreDinAceeasiLocatie(AdoptionCentre adoptionCentre) {
        List<AdoptionCentre> centres = findAll();
        for (AdoptionCentre centre : centres) {
            if (!centre.equals(adoptionCentre) && Objects.equals(centre.getLocation(), adoptionCentre.getLocation())) {
                return true;
            }
        }
        return false;
    }

    public void sendRequest(Animal animal, AdoptionCentre adoptionCentre) {
        List<AdoptionCentre> centres = findAll();
        for (AdoptionCentre centre : centres) {
            if (!centre.equals(adoptionCentre) && centre.getCapacity()>0 && Objects.equals(centre.getLocation(), adoptionCentre.getLocation())) {
                boolean ok = showMessageBox(adoptionCentre,centre, animal);
                if (ok) {
                    Animal animalUpdate = new Animal(animal.getId(), animal.getName(), centre.getId().intValue(), animal.getType());
                    animalRepository.update(animalUpdate);
                    AnimalEntityChangeEvent event = new AnimalEntityChangeEvent(ChangeEventType.UPDATE, animalUpdate);
                    notifyObservers(event);
                    return;
                }
            }
        }

    }

    public boolean showMessageBox(AdoptionCentre mainCentre,AdoptionCentre centre, Animal animal) {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Transfer Request");
        alert.setHeaderText("Transfer pentru animalul: " + animal.getName() + ", catre centrul: " + centre.getName());
        alert.setContentText(mainCentre.getName() + " request to transfer "+ animal.getName() );


        ButtonType acceptButton = new ButtonType("Accept");
        ButtonType ignoreButton = new ButtonType("Ignore", ButtonBar.ButtonData.CANCEL_CLOSE);

        alert.getButtonTypes().setAll(acceptButton, ignoreButton);

        Optional<ButtonType> result = alert.showAndWait();
        return result.isPresent() && result.get() == acceptButton;
    }

    @Override
    public void addObserver(Observer<AnimalEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<AnimalEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(AnimalEntityChangeEvent t) {
        observers.forEach(x -> x.update(t));
    }
}
