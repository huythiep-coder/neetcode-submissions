public class Solution
{
    public bool IsValidSudoku(char[][] board)
    {
        // HashSet để track các số đã thấy
        var rows = new HashSet<char>[9];
        var cols = new HashSet<char>[9];
        var boxes = new HashSet<char>[9];

        for (int i = 0; i < 9; i++)
        {
            rows[i] = new HashSet<char>();
            cols[i] = new HashSet<char>();
            boxes[i] = new HashSet<char>();
        }

        for (int r = 0; r < 9; r++)
        {
            for (int c = 0; c < 9; c++)
            {
                char val = board[r][c];

                // Bỏ qua ô trống
                if (val == '.') continue;

                // Index của box 3x3
                int boxIndex = (r / 3) * 3 + (c / 3);

                // Kiểm tra trùng lặp
                if (!rows[r].Add(val)) return false;
                if (!cols[c].Add(val)) return false;
                if (!boxes[boxIndex].Add(val)) return false;
            }
        }

        return true;
    }
}