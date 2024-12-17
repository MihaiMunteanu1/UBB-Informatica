public class ExpressionFactory {

    private static final ExpressionFactory instance = new ExpressionFactory();

    private ExpressionFactory() {
    }

    public static ExpressionFactory getInstance() {
        return instance;
    }

    public ComplexExpression createExpression(Operation operation, NumarComplex[] args) {
        return switch (operation) {
            case ADDITION -> new Adunare(args);
            case DIVISION -> new Impartire(args);
            case MULTIPLICATION -> new Inmultire(args);
            case SUBSTRACT -> new Scadere(args);
        };
    }
}
