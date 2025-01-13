package ubb.scs.map.sem13map.domain;

public class Sarcina extends Entity<String>{
    private Dificultate dificultate;
    private int nrOreEstimate;
    private String denumire;

    public Sarcina(String id, int nrOreEstimate, Dificultate dificultate, String denumire) {
        this.nrOreEstimate = nrOreEstimate;
        this.dificultate = dificultate;
        this.denumire = denumire;
        setId(id);
    }

    public String getDenumire() {
        return denumire;
    }

    public void setDenumire(String denumire) {
        this.denumire = denumire;
    }

    public Dificultate getDificultate() {
        return dificultate;
    }

    public void setDificultate(Dificultate dificultate) {
        this.dificultate = dificultate;
    }

    public int getNrOreEstimate() {
        return nrOreEstimate;
    }

    public void setNrOreEstimate(int nrOreEstimate) {
        this.nrOreEstimate = nrOreEstimate;
    }

    @Override
    public String toString() {
        return denumire + " " + nrOreEstimate + " " + dificultate;
    }
}
