public class Inmultire extends ComplexExpression{
    public Inmultire(NumarComplex[] args) {
        super(Operation.MULTIPLICATION, args);
    }
    public NumarComplex executeOneOperation(NumarComplex n1,NumarComplex n2) {
        return n1.inmultire(n2);
    }
}
