import java.io.*;
import java.util.*;

public class Main {

    private static final int MAX_VAL = 100;
    private static final int MAX_DIM = 10000;
    public static int N;
    public static int M;
    public static int n;
    private static int P;
    private static double finalTime;

    private static int[][] F = new int[MAX_DIM][MAX_DIM];
    private static int[][] C = new int[MAX_DIM][MAX_DIM];
    private static int[][] V = new int[MAX_DIM][MAX_DIM];
    private static int[][] V_Secv = new int[MAX_DIM][MAX_DIM];

    public static void main(String[] args) throws Exception {
        if (args.length > 0) {
            try {
                P = Integer.parseInt(args[0]);
            } finally {

            }
        }
        else{
            P=4;
        }

        N=10;
        M=10;
        n=3;

        generareDate();
        readDate();

        convolutieSecventiala();
        //parallelHorizontal();
        //parallelVertical();

        //writeResult(V_Secv,V);
        //verifyResults();

        System.out.println(finalTime);


    }

    private static void generareDate() throws IOException {
        Random rand = new Random();
        try (PrintWriter pw = new PrintWriter("date.txt")) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    pw.print(rand.nextInt(MAX_VAL) + " ");
                }
                pw.println();
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    pw.print(rand.nextInt(2) + " ");
                }
                pw.println();
            }
        }
    }

    private static void readDate() throws IOException {
        try (Scanner sc = new Scanner(new File("date.txt"))) {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    F[i][j] = sc.nextInt();

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    C[i][j] = sc.nextInt();
        }


    }
    private static int clamp(int val, int min, int max) {
        return Math.max(min, Math.min(max, val));
    }

    private static void convolutieSecventiala() {
        long start_time_secv=System.nanoTime();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int s = 0;
                for (int a = 0; a < n; a++)
                    for (int b = 0; b < n; b++){
                        int r = clamp(i - n / 2 + a, 0, N - 1);
                        int c = clamp(j - n / 2 + b, 0, M - 1);
                        s += F[r][c] * C[a][b];
                    }
                V_Secv[i][j] = s;
            }
        }

        long end_time_secv=System.nanoTime();
        double ns_in_ms = 1e6;
        long secv_time = end_time_secv - start_time_secv;
        double secv_ms = secv_time / ns_in_ms;
        System.out.printf("Secv time: %10.3fms\n",secv_ms);

        finalTime = secv_ms;
    }

    private static void parallelHorizontal() throws InterruptedException {
        int dim_split = N / P;
        int r = N % P;

        MyThread[] threads = new MyThread[P];
        int startRow = 0;
        int endRow = dim_split;

        long start_time_par_H =  System.nanoTime();

        for (int i = 0; i < P; i++) {
            if (r > 0) {
                endRow++;
                r--;
            }
            threads[i] = new MyThread(F, C, V, startRow, endRow, -1,  -1, true);
            threads[i].start();
            startRow = endRow;
            endRow += dim_split;
        }

        for (MyThread t : threads)
            t.join();

        long end_time_par_H =  System.nanoTime();

        double ns_in_ms = 1e6;
        long par_time = end_time_par_H - start_time_par_H;
        double par_ms =  par_time / ns_in_ms;
        System.out.printf("Par time H: %10.3fms\n",par_ms);


        finalTime = par_ms;

    }

    private static void parallelVertical() throws InterruptedException {
        int dim_split = M / P;
        int r = M % P;

        MyThread[] threads = new MyThread[P];
        int startCol = 0;
        int endCol = dim_split;

        long start_time_par_V =  System.nanoTime();
        for (int i = 0; i < P; i++) {
            if (r > 0) {
                endCol++;
                r--;
            }
            threads[i] = new MyThread(F, C, V, -1,  -1, startCol, endCol, false);
            threads[i].start();
            startCol = endCol;
            endCol += dim_split;
        }

        for (MyThread t : threads)
            t.join();

        long end_time_par_V =  System.nanoTime();

        double ns_in_ms = 1e6;
        long par_time = end_time_par_V - start_time_par_V;
        double par_ms =  par_time / ns_in_ms;
        System.out.printf("Par time V: %10.3fms\n",par_ms);


        finalTime = par_ms;

    }

    private static void verifyResults() throws FileNotFoundException {
        String file1 = "outputSecv.txt";
        String file2 = "outputPar.txt";

        try (BufferedReader br1 = new BufferedReader(new FileReader(file1));
             BufferedReader br2 = new BufferedReader(new FileReader(file2))) {

            String line1, line2;
            int lineNumber = 1;

            while ((line1 = br1.readLine()) != null | (line2 = br2.readLine()) != null) {
                if (line1 == null || line2 == null || !line1.equals(line2)) {
                    System.out.println("Diferenta la linia " + lineNumber + ":");
                    System.out.println("outputSecv: " + line1);
                    System.out.println("outputPar : " + line2);
                }
                lineNumber++;
            }


        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }



    private static void writeResult(int[][] ResSecv,int[][] ResPar) throws IOException {
        try (PrintWriter pw = new PrintWriter("outputSecv.txt")) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    pw.printf("%5d ", ResSecv[i][j]);
                }
                pw.println();
            }
        }
        try (PrintWriter pw = new PrintWriter("outputPar.txt")) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    pw.printf("%5d ", ResPar[i][j]);
                }
                pw.println();
            }
        }
    }
}
