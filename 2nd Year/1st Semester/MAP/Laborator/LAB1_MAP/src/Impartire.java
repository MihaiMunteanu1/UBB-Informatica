public class Impartire extends ComplexExpression{
    public Impartire(NumarComplex[] args) {
        super(Operation.DIVISION, args);
    }
    public NumarComplex executeOneOperation(NumarComplex n1,NumarComplex n2) {
        return n1.impartire(n2);
    }
}
