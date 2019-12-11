// Name: Collin Gros
// Lab501


#include "project_1.h"


position readPosition(string s)
{
    row r(8, "e");
    position p(8, r);

    int cur_row, cur_column;
    string color_w_type;
    char cur_char;

    int char_place = 0;
    int count = 0;
    while (count <= s.size()) {
        cur_char = s[count];

        if (char_place > 3) {
            p[cur_row][cur_column] = color_w_type;
            char_place = 0;

            continue;
        }

        if (cur_char == ' ') {
            char_place = 0;
            count++;

            continue;
        }

        if (char_place == 3) {
            cur_column = int(cur_char) - 97;
        }
        else if (char_place == 2) {
            cur_row = int(cur_char) - 49;
        }
        else if (char_place == 1) {
            color_w_type = "";

            color_w_type += s[count - 1];
            color_w_type += s[count];
        }

        char_place++;
        count++;
    }

    return p;
}

