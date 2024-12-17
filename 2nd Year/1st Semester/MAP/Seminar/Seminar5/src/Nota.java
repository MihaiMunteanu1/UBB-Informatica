public class Nota {
    private Student student;
    private Tema tema;
    private double nota;
    private String professor;

    public Nota(Student student, Tema tema, double nota, String professor) {
        this.student = student;
        this.tema = tema;
        this.nota = nota;
        this.professor = professor;
    }

    public Student getStudent() {
        return student;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public Tema getTema() {
        return tema;
    }

    public void setTema(Tema tema) {
        this.tema = tema;
    }

    public double getNota() {
        return nota;
    }

    public void setNota(double nota) {
        this.nota = nota;
    }

    public String getProfessor() {
        return professor;
    }

    public void setProfessor(String professor) {
        this.professor = professor;
    }
}
