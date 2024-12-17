import java.util.Objects;

public class ExpressionParser {
    private final String[] args;

    public ExpressionParser(String[] args) {
        this.args = args;
    }

    public ComplexExpression parse() {
        NumarComplex[] argss = new NumarComplex[(args.length + 1) / 2];
        String op = null;
        int index = 0;

        for (int i = 0; i < args.length; i++) {
            if (i % 2 == 0) {
                NumarComplex nr = getNumarComplex(i);
                argss[index++] = nr;
            } else {
                op = args[i];
                if (!Objects.equals(op, "+") && !Objects.equals(op, "-") && !Objects.equals(op, "*") && !Objects.equals(op, "/")) {
                    return null;
                }
            }
        }

        return switch (op) {
            case "+" -> ExpressionFactory.getInstance().createExpression(Operation.ADDITION, argss);
            case "-" -> ExpressionFactory.getInstance().createExpression(Operation.SUBSTRACT, argss);
            case "*" -> ExpressionFactory.getInstance().createExpression(Operation.MULTIPLICATION, argss);
            case "/" -> ExpressionFactory.getInstance().createExpression(Operation.DIVISION, argss);
            default -> null;
        };
    }

    private NumarComplex getNumarComplex(int i) {
        String[] el = args[i].split("[+]", 2);
        double re = 0;
        double im = 0;
        if (el.length > 0 && !el[0].contains("i")) {
            re = Double.parseDouble(el[0]);
        }
        if (el.length == 2 || (el.length == 1 && el[0].contains("i"))) {
            String imPart;
            if (el.length == 2) {
                imPart = el[1];
            } else {
                imPart = el[0];
            }
            imPart = imPart.replace("*i", "").replace("i", "");
            if (imPart.isEmpty() || imPart.equals("+")) {
                im = 1;
            } else if (imPart.equals("-")) {
                im = -1;
            } else {
                im = Double.parseDouble(imPart);
            }
        }
        return new NumarComplex(re, im);
    }
}
