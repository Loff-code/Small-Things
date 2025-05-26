import java.util.Scanner;

public class bnew {
    public static void main(String[] args) {
        String[][] grid = new String[3][3];
        int moveCount = 0;
        initializeGrid(grid);
        draw(grid);

        while (true) {
            int move = getInput(moveCount, grid);
            grid[(move - 1) / 3][(move - 1) % 3] = moveCount % 2 == 0 ? "x" : "o";
            moveCount++;
            draw(grid);
            if (checkWin(grid))
                break;
        }
    }

    static void initializeGrid(String[][] grid) {
        int count = 1;
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[i].length; j++)
                grid[i][j] = Integer.toString(count++);
    }

    static boolean checkWin(String[][] grid) {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (grid[i][0].equals(grid[i][1]) && grid[i][1].equals(grid[i][2])) {
                System.out.println(grid[i][0] + " wins!");
                return true;
            }
            if (grid[0][i].equals(grid[1][i]) && grid[1][i].equals(grid[2][i])) {
                System.out.println(grid[0][i] + " wins!");
                return true;
            }
        }

        // Check diagonals
        if (grid[0][0].equals(grid[1][1]) && grid[1][1].equals(grid[2][2])) {
            System.out.println(grid[0][0] + " wins!");
            return true;
        }
        if (grid[0][2].equals(grid[1][1]) && grid[1][1].equals(grid[2][0])) {
            System.out.println(grid[0][2] + " wins!");
            return true;
        }

        return false;
    }

    static int getInput(int moveCount, String[][] grid) {
        Scanner scanner = new Scanner(System.in);
        int num;
        String player = moveCount % 2 == 0 ? "x" : "o";
        System.out.println("You are " + player);

        while (true) {
            System.out.print("Choose a number (1-9): ");
            num = scanner.nextInt();
            if (num > 0 && num < 10 && !grid[(num - 1) / 3][(num - 1) % 3].equals("x")
                    && !grid[(num - 1) / 3][(num - 1) % 3].equals("o")) {
                break;
            }
            System.out.println("Invalid choice, try again.");
        }

        return num;
    }

    static void draw(String[][] grid) {
        System.out.println("+---+---+---+");
        for (int i = 0; i < 3; i++) {
            System.out.println("| " + grid[i][0] + " | " + grid[i][1] + " | " + grid[i][2] + " |");
            System.out.println("+---+---+---+");
        }
    }
}
