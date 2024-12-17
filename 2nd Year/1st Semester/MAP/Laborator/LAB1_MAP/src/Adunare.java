
public class Adunare extends ComplexExpression{
    public Adunare(NumarComplex[] args) {
        super(Operation.ADDITION, args);
    }
    public NumarComplex executeOneOperation(NumarComplex n1,NumarComplex n2) {
        return n1.adunare(n2);
    }
}
