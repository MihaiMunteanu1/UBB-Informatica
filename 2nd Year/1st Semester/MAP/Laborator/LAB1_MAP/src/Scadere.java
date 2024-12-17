public class Scadere extends ComplexExpression{
    public Scadere(NumarComplex[] args) {
        super(Operation.SUBSTRACT, args);
    }
    public NumarComplex executeOneOperation(NumarComplex n1,NumarComplex n2) {
        return n1.scadere(n2);
    }
}
