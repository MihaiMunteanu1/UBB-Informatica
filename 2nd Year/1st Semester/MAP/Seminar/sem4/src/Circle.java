public class Circle {
    private double raza;

    public Circle(double raza) {
        this.raza = raza;
    }

    public double getRaza() {
        return raza;
    }

    public void setRaza(double raza) {
        this.raza = raza;
    }

    @Override
    public String toString() {
        return "Circle{" +
                "raza=" + raza +
                '}';
    }
}
