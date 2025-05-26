import java.util.Scanner;

public class working {
    public static void main(String[] args) {
        String grid[][] = new String[3][3];
        initGrid(grid);
        int cnt = 0;
        boolean done = false;
        draw(grid);

        while (!done) {
            int num = input(cnt, grid);
            grid[(num - 1) / 3][(num - 1) % 3] = (cnt % 2 == 0 ? "x" : "o");
            cnt++;
            draw(grid);
            done = checkWin(grid);
        }

    }

    static void initGrid(String[][] grid) {
        int cnt = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                grid[i][j] = Integer.toString(++cnt);
            }
        }
    }

    static boolean checkWin(String grid[][]) {
        String strH = "", strV = "", strX = "", strY = "";
        boolean xWin = false, oWin = false;
        for (int i = 0; i < grid.length; i++) {
            strX += grid[i][i];
            strY += grid[2 - i][i];

            for (int j = 0; j < grid[i].length; j++) {
                strH += grid[i][j];
                strV += grid[j][i];
            }

            xWin = strH.equals("xxx") || strV.equals("xxx") || strY.equals("xxx") || strX.equals("xxx");
            oWin = strH.equals("ooo") || strV.equals("ooo") || strY.equals("ooo") || strX.equals("ooo");
            if (xWin || oWin) {
                System.out.println((xWin ? "X" : "O") + " wins!");
                return true;
            }

            strH = "";
            strV = "";
        }

        return false;
    }

    static int input(int cnt, String grid[][]) {
        Scanner scanner = new Scanner(System.in);
        int num = 0;
        boolean check = false;
        int attemt = 0;
        System.out.println("You are " + (cnt % 2 == 0 ? "x" : "o"));
        while (!check) {
            if (attemt > 0) {
                System.out.print("Invalid, try again");
                for (int i = 0; i < attemt; i++) {
                    System.out.print("!");
                }
                System.out.println();
            }
            attemt++;
            System.out.print("Choose number from 1 to 9: ");
            num = scanner.nextInt();
            check = num > 0 && num < 10 && !grid[(num - 1) / 3][(num - 1) % 3].equals("x")
                    && !grid[(num - 1) / 3][(num - 1) % 3].equals("o");
        }

        return num;
    }

    static void draw(String grid[][]) {
        String draw[][] = new String[7][7];
        String res = "";
        int cnt = 0;

        for (int i = 0; i < draw.length; i++) {
            for (int j = 0; j < draw[i].length; j++) {
                boolean check = (i + 1) % 2 == 0 && (j + 1) % 2 == 0;
                if (check) {
                    res = grid[cnt / 3][cnt % 3] != null ? grid[cnt / 3][cnt % 3] : " ";
                    cnt++;
                }
                draw[i][j] = check ? res // Intersection (space)
                        : (i + 1) % 2 == 0 ? "|" // Vertical lines for even rows
                                : (j + 1) % 2 == 0 ? "-" // Horizontal lines for odd rows
                                        : "+"; // Corners
            }
        }

        for (String[] strings : draw) {
            for (String strings2 : strings) {
                System.out.print(strings2);
            }
            System.out.println();
        }
    }
}
