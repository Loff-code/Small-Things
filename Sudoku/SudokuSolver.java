import java.util.Arrays;

public class j {
    public static void main(String[] args) {
        int[][] fixPlaces = { { 0, 0 }, { 0, 1 }, { 0, 4 }, { 1, 0 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 1 },
                { 2, 2 }, { 2, 7 }, { 3, 0 }, { 3, 4 }, { 3, 8 }, { 4, 0 }, { 4, 3 }, { 4, 5 }, { 4, 8 }, { 5, 0 },
                { 5, 4 }, { 5, 8 }, { 6, 1 }, { 6, 6 }, { 6, 7 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 8 }, { 8, 4 },
                { 8, 7 }, { 8, 8 } };
        int[] fixNums = {
                5, 3, 7, 6, 1, 9, 5, 9, 8, 6, 8, 6,
                3, 4, 8, 3, 1, 7, 2, 6, 6, 2, 8, 4,
                1, 9, 5, 8, 7, 9
        };

        int[][] board = initBoard(fixPlaces, fixNums);

        solveSudoku(board);

        printBoard(board);
    }

    static boolean solveSudoku(int[][] board) {
        int[] empty = findEmpty(board);
        if (empty == null) {
            return true; // No empty cells, puzzle is solved
        }

        int row = empty[0];
        int col = empty[1];

        for (int num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                board[row][col] = num;

                if (solveSudoku(board)) {
                    return true;
                }

                board[row][col] = 0; // Backtrack
            }
        }

        return false; // Trigger backtracking
    }

    static boolean isValid(int[][] board, int row, int col, int num) {
        // Check row
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num) {
                return false;
            }
        }

        // Check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num) {
                return false;
            }
        }

        // Check 3x3 block
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    static int[] findEmpty(int[][] board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) {
                    return new int[] { row, col };
                }
            }
        }
        return null;
    }

    static void printBoard(int[][] board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                System.out.print(board[row][col] + " ");
                if ((col + 1) % 3 == 0 && col != 8) {
                    System.out.print("| ");
                }
            }
            System.out.println();
            if ((row + 1) % 3 == 0 && row != 8) {
                System.out.println("------+-------+------");
            }
        }
    }

    static int[][] initBoard(int[][] fixPlaces, int[] fixNums) {
        int[][] board = new int[9][9];
        for (int i = 0; i < fixPlaces.length; i++) {
            board[fixPlaces[i][0]][fixPlaces[i][1]] = fixNums[i];
        }
        return board;
    }
}