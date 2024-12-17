public class Main {
    public static void main(String[] args) {

        if(args.length == 0){
            System.out.println("Nu sunt argumente!\n");
        }

        ExpressionParser parser = new ExpressionParser(args);
        ComplexExpression expr = parser.parse();
        NumarComplex result = expr.execute();
        System.out.println(result);
    }

}