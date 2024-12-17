package org.example.sem8.domain;

public class NotaDTO {
    private String temaId;
    private double nota;
    private String studentName;
    private String profesor;

    public NotaDTO(String studentName, String temaId, double nota, String profesor) {
        this.studentName = studentName;
        this.temaId = temaId;
        this.nota = nota;
        this.profesor=profesor;
    }

    public String getTemaId() {
        return temaId;
    }

    public void setTemaId(String temaId) {
        this.temaId = temaId;
    }

    public double getNota() {
        return nota;
    }

    public void setNota(double nota) {
        this.nota = nota;
    }

    public String getStudentName() {
        return studentName;
    }

    public void setStudentName(String studentName) {
        this.studentName = studentName;
    }

    public String getProfesor() {
        return profesor;
    }

    public void setProfesor(String profesor) {
        this.profesor = profesor;
    }

    @Override
    public String toString() {
        return "NotaDTO{" +
                "temaId='" + temaId + '\'' +
                ", nota=" + nota +
                ", studentName='" + studentName + '\'' +
                ", profesor='" + profesor + '\'' +
                '}';
    }
}
