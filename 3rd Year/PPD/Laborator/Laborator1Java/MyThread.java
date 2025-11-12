

public class MyThread extends Thread {

    private int[][] F;
    private int[][] C;
    private int[][] V;
    private int startRow, endRow;
    private int startCol, endCol;
    private boolean horizontal;

    private static final int n = Main.n;
    private static final int M = Main.M;
    private static final int N = Main.N;

    public MyThread(int[][]F,int[][] C, int[][] V,
                        int startRow, int endRow, int startCol, int endCol, boolean horizontal) {
        this.F = F;
        this.C = C;
        this.V = V;
        this.startRow = startRow;
        this.endRow = endRow;
        this.startCol = startCol;
        this.endCol = endCol;
        this.horizontal = horizontal;
    }
    private static int clamp(int val, int min, int max) {
        return Math.max(min, Math.min(max, val));
    }

    @Override
    public void run() {
        if (horizontal) {
            for (int i = startRow; i < endRow; i++) {
                for (int j = 0; j < M; j++) {
                    int s = 0;
                    for (int a = 0; a < n; a++)
                        for (int b = 0; b < n; b++){
                            int r = clamp(i - n / 2 + a, 0, N - 1);
                            int c = clamp(j - n / 2 + b, 0, M - 1);
                            s += F[r][c] * C[a][b];
                        }
                    V[i][j] = s;
                }
            }
        } else {
            for (int i = 0; i < N; i++) {
                for (int j = startCol; j < endCol; j++) {
                    int s = 0;
                    for (int a = 0; a < n; a++)
                        for (int b = 0; b < n; b++){
                            int r = clamp(i - n / 2 + a, 0, N - 1);
                            int c = clamp(j - n / 2 + b, 0, M - 1);
                            s += F[r][c] * C[a][b];
                        }
                    V[i][j] = s;
                }
            }
        }
    }
}
