import java.io.*;
import java.util.Scanner;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.BrokenBarrierException;

public class Main {
    private static int p;
    private static int N, M, k;
    private static int[][] F, C;

    public static void readData(String filename) throws IOException {
        try (Scanner sc = new Scanner(new File(filename))) {
            N=sc.nextInt();
            M=N;
            F = new int[N][M];
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    F[i][j] = sc.nextInt();
            k=3;
            C = new int[k][k];
            for (int i = 0; i < k; i++)
                for (int j = 0; j < k; j++)
                    C[i][j] = sc.nextInt();
        }
    }

    public static void writeResult(boolean secv, boolean par) throws IOException {
        if (secv) {
            PrintWriter pw = new PrintWriter(new FileWriter("outputSecv.txt"));
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    pw.printf("%5d ", F[i][j]);
                }
                pw.println();
            }
            pw.close();
        }
        if (par) {
            PrintWriter pw = new PrintWriter(new FileWriter("outputPar.txt"));
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    pw.printf("%5d ", F[i][j]);
                }
                pw.println();
            }
            pw.close();
        }
    }

    public static void verifyResults() throws IOException {
        BufferedReader file1 = new BufferedReader(new FileReader("outputSecv.txt"));
        BufferedReader file2 = new BufferedReader(new FileReader("outputPar.txt"));

        String line1, line2;
        int lineNumber = 1;

        while (true) {
            line1 = file1.readLine();
            line2 = file2.readLine();

            if (line1 == null && line2 == null)
                break;

            if (line1 == null || line2 == null || !line1.equals(line2)) {
                System.out.println("Diferenta la linia " + lineNumber + ":");
                System.out.println("outputSecv: " + (line1 == null ? "EOF" : line1));
                System.out.println("outputPar : " + (line2 == null ? "EOF" : line2));
            }
            lineNumber++;
        }

        file1.close();
        file2.close();
    }

    static class MyThread extends Thread {
        private int start;
        private int end;
        private CyclicBarrier barrier;

        public MyThread(int start, int end, CyclicBarrier barrier) {
            this.start = start;
            this.end = end;
            this.barrier = barrier;
        }

        @Override
        public void run() {
            computeRows(start, end, barrier);
        }

        private void computeRows(int start, int end, CyclicBarrier barrier) {
            int[] previousLine = new int[M];
            int[] currLine = new int[M];
            int[] nextLine = new int[M];

            int previousLineNumber = start - 1;
            int nextLineNumber = end;
            if (previousLineNumber < 0) {
                previousLineNumber = 0;
            }
            if (nextLineNumber >= N) {
                nextLineNumber = N - 1;
            }

            for (int i = 0; i < N; i++) {
                previousLine[i] = F[previousLineNumber][i];
                currLine[i] = F[previousLineNumber][i];
                nextLine[i] = F[nextLineNumber][i];
            }

            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
                return;
            }

            for (int i = start; i < end; i++) {
                if (i != previousLineNumber) {
                    for (int j = 0; j < M; j++) {
                        previousLine[j] = currLine[j];
                        currLine[j] = F[i][j];
                    }
                }

                for (int j = 0; j < M; j++) {
                    applyConvolution(i, j, end, previousLine, currLine, nextLine);
                }
            }
        }
    }

    private static int clamp(int val, int min, int max) {
        return Math.max(min, Math.min(max, val));
    }
    public static void applyConvolution(int i, int j, int end, int[] prevLine, int[] currLine, int[] nextLine) {
        int s = 0;
        int diff = (k - 1) / 2;

        for (int x = 0; x < k; x++) {
            for (int y = 0; y < k; y++) {
                int ii = i - diff + x;
                int jj = j - diff + y;

                ii = clamp(ii,0,N-1);
                jj = clamp(jj,0,N-1);

                int elemCov;
                if (ii < i) {
                    elemCov = prevLine[jj];
                } else if (ii == i) {
                    elemCov = currLine[jj];
                } else if (ii >= end) {
                    elemCov = nextLine[jj];
                } else {
                    elemCov = F[ii][jj];
                }
                s += elemCov * C[x][y];
            }
        }
        F[i][j] = s;
    }

    public static void convolutionSequential() {
        int[] previousLine = new int[M];
        int[] currLine = new int[M];
        int[] nextLine = new int[M];

        for (int i = 0; i < M; i++) {
            previousLine[i] = F[0][i];
            currLine[i] = F[0][i];
            nextLine[i] = F[N - 1][i];
        }

        for (int i = 0; i < N; i++) {
            if (i != 0) {
                for (int j = 0; j < M; j++) {
                    previousLine[j] = currLine[j];
                    currLine[j] = F[i][j];
                }
            }
            for (int j = 0; j < M; j++) {
                applyConvolution(i, j, N, previousLine, currLine, nextLine);
            }
        }
    }


    public static void parallelHorizontal() throws InterruptedException {
        MyThread[] threads = new MyThread[p];
        int dimSplit = N / p;
        int r = N % p;
        int start = 0;
        int end;
        CyclicBarrier barrier = new CyclicBarrier(p);

        for (int i = 0; i < p; i++) {
            int currentNoRows = dimSplit;
            if (r > 0) {
                r--;
                currentNoRows++;
            }
            end = start + currentNoRows;
            threads[i] = new MyThread(start, end, barrier);
            threads[i].start();
            start += currentNoRows;
        }

        for (int i = 0; i < p; i++) {
            threads[i].join();
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        //p = 2;
        p=Integer.parseInt(args[0]);
        String filename = "date1.txt";

        readData(filename);

        long startTime = System.nanoTime();
        parallelHorizontal();
        convolutionSequential();
//
        long endTime = System.nanoTime();
        double ns_in_ms = 1e6;
        double duration = (endTime - startTime) / ns_in_ms;

        System.out.println("Timp: ");
        System.out.println(duration);
    }
}