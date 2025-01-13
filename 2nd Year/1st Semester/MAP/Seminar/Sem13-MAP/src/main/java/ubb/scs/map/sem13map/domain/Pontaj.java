package ubb.scs.map.sem13map.domain;

import java.time.LocalDateTime;

public class Pontaj extends  Entity<Tuple<String>> {
    private LocalDateTime data;
    private Angajat angajat;
    private Sarcina sarcina;

    public Pontaj(LocalDateTime data, Angajat angajat, Sarcina sarcina) {
        this.data = data;
        this.angajat = angajat;
        this.sarcina = sarcina;
        setId(new Tuple<>(angajat.getId(), sarcina.getId()));
    }

    public LocalDateTime getData() {
        return data;
    }

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    public Angajat getAngajat() {
        return angajat;
    }

    public void setAngajat(Angajat angajat) {
        this.angajat = angajat;
    }

    public Sarcina getSarcina() {
        return sarcina;
    }

    public void setSarcina(Sarcina sarcina) {
        this.sarcina = sarcina;
    }

    @Override
    public String toString() {
        return "Pontaj{" +
                "data=" + data +
                ", angajat=" + angajat +
                ", sarcina=" + sarcina +
                '}';
    }
}
