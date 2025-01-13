package ubb.scs.map.sem13map.domain;

public class Angajat extends Entity<String> {
    private float venitPeOra;
    private String nume;
    private Nivel nivel;

    public Angajat(String id, float venitPeOra, String nume, Nivel nivel) {
        this.venitPeOra = venitPeOra;
        this.nume = nume;
        this.nivel = nivel;
        setId(id);
    }

    public float getVenitPeOra() {
        return venitPeOra;
    }

    public void setVenitPeOra(float venitPeOra) {
        this.venitPeOra = venitPeOra;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public Nivel getNivel() {
        return nivel;
    }

    public void setNivel(Nivel nivel) {
        this.nivel = nivel;
    }

    @Override
    public String toString(){
        return getId() + " " + nume + " " + venitPeOra  + " " + nivel;
    }
}
