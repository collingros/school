// Collin Gros
// 04/1/19
// CS-2365-001

class Quad
{
    public static void roots(double a, double b,
                                 double c)
    {
        System.out.printf("finding roots with a: %f\tb: %f\tc: %f%n",
                          a, b, c);

        double exp = (b * b) - (4 * a * c);
        if (exp < 0) {
            System.out.println("\troots are not real..");
            return;
        }

        exp = Math.sqrt(exp);

        double x1 = (-b + exp) / (2 * a);
        double x2 = (-b - exp) / (2 * a);

        System.out.printf("\tfound roots! x1: %f\tx2: %f\n", x1, x2);
    }


    public static void main(String[] args)
    {
        double[][] tests = {{4, 4, 2}, {1, 2, 1}, {4, 2, 0}};
        for (int i = 0; i < tests.length; i++) {
            double[] test = tests[i];
            double a = test[0];
            double b = test[1];
            double c = test[2];

            roots(a, b, c);
        }
    }
}
