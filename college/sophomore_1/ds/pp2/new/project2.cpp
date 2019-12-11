/*
Collin Gros
11/17/18
DS CS-2413-501
*/

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cmath>
#include "project2.h"

using namespace std;

vector<string> vector_cat(vector<string> tl_sqrs,
                          vector<string> tr_sqrs)
{
    tl_sqrs.insert(tl_sqrs.end(), tr_sqrs.begin(), tr_sqrs.end());

    return tl_sqrs;
}


struct mov cvt_move(struct mov move)
{
    struct mov new_move;
    new_move.src = "";
    new_move.dst = "";

    string old_src = move.src;
    string old_dst = move.dst;

    int src_row = int(old_src.at(0)) - '0';
    int src_col = int(old_src.at(1)) - '0';

    char new_row = 8 - src_row + '0';
    char new_col = src_col + 'a';

    string new_row_str(1, new_row);
    string new_col_str(1, new_col);

    new_move.src = new_row_str + new_col_str;

    int dst_row = int(old_dst.at(0)) - '0';
    int dst_col = int(old_dst.at(1)) - '0';

    char new_dst_row = 8 - dst_row + '0';
    char new_dst_col = dst_col + 'a';

    string new_dst_row_str(1, new_dst_row);
    string new_dst_col_str(1, new_dst_col);

    new_move.dst = new_dst_row_str + new_dst_col_str;

    return new_move;
}


set<mov> cvt_moves(set<mov> moves)
{
    set<mov> cvted_moves;

    for (auto move : moves) {
        struct mov new_move = cvt_move(move);
        cvted_moves.insert(new_move);
    }

    return cvted_moves;
}


void print_move(struct mov move)
{
    cout << move.src << ":" << move.dst;
}


void print_set(set<mov> moves)
{
    for (struct mov move : moves) {
        print_move(move);
        cout << "\t";
    }
    cout << endl << endl;
}

void print_board(position board)
{
    for (int i = 0; i < 8; i++) {
        cout << "\n\n";
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << "\t";
        }
    }
    cout << "\n";
}

/*
void load_board(position &board, string puzzle)
{
    int cur_row, cur_column;
    string color_w_type;
    char cur_char;

    int char_place = 0;
    int count = 0;
    while (count <= puzzle.size()) {
        cur_char = puzzle[count];

        if (char_place > 3) {
            board[cur_row][cur_column] = color_w_type;
            char_place = 0;

            continue;
        }

        if (cur_char == ' ') {
            char_place = 0;
            count++;

            continue;
        }

        if (char_place == 3) {
            cur_column = int(cur_char) - 48;
        }
        else if (char_place == 2) {
            cur_row = int(cur_char) - 48;
        }
        else if (char_place == 1) {
            color_w_type = "";

            color_w_type += puzzle[count - 1];
            color_w_type += puzzle[count];
        }

        char_place++;
        count++;
    }
}
*/

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
            cur_row = abs(cur_row - 7);
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


void fill_default(position &board)
{
    string def_pos = "Wb1a WK7e Bp7g Bp7h BK8h Wk6h";
    board = readPosition(def_pos);
}


position create_board()
{
    row rows(8, "e");
    position board(8, rows);

    return board;
}


string get_color(string piece)
{
    string piece_color(1, piece.at(0));
    if (piece_color == "e")
        return "e";

    return piece_color;
}


string get_type(string piece)
{
    string piece_color(1, piece.at(0));
    if (piece_color == "e")
        return "e";

    string piece_type(1, piece.at(1));
    if (piece.length() > 1)
        return piece_type;
}


string get_our_color(char color)
{
    if (color == 'W')
        return "W";
    else
        return "B";
}


string get_enemy_color(string color)
{
    string enemy_color = "";
    if (color == "W") {
        enemy_color = "B";
    }
    else {
        enemy_color = "W";
    }

    return enemy_color;
}


void add_moves(string src, vector<string> sqrs, set<mov> &moves)
{
    for (auto sqr : sqrs) {
        struct mov move;
        move.src = src;
        move.dst = sqr;

        moves.insert(move);
    }
}


string get_king(position board, string color)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            string sqr = to_string(i) + to_string(j);

            string piece = board[i][j];
            string piece_type = get_type(piece);
            string piece_color = get_color(piece);

            if (piece_type == "K" && piece_color == color)
                return sqr;
        }
    }
    return "";
}


string get_piece(position board, string src)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            string piece = board[i][j];

            string sqr = to_string(i) + to_string(j);

            if (sqr == src) {
                return piece;
            }
        }
    }

    return "";
}





void fill_adjacent(string src, set<mov> &moves, position board,
                   string color)
{
    int src_row = int(src.at(0)) - '0';
    int src_col = int(src.at(1)) - '0';

    vector<string> sqrs = {};

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int new_row = src_row + i;
            int new_col = src_col + j;

            if (new_row < 0 || new_row > 7 ||
                new_col < 0 || new_col > 7 ||
                (new_row == src_row &&
                 new_col == src_col)) {
                continue;
            }

            string sqr = to_string(new_row) + to_string(new_col);
            string piece = board[new_row][new_col];
            string piece_type = get_type(piece);
            string piece_color = get_color(piece);

            if (piece_color != color)
                sqrs.push_back(sqr);
        }
    }

    add_moves(src, sqrs, moves);
}


void fill_straight(string src, set<mov> &moves, position board,
                   string color)
{
    int src_row = int(src.at(0)) - '0';
    int src_col = int(src.at(1)) - '0';
    bool rows = true;
    for (int i = 0; i < 2; i++) {
        vector<string> sqrs = {};
        int row = src_row;
        int col = src_col;
        bool hit_src = false;

        for (int j = 0; j < 8; j++) {
            if (rows)
                row = j;
            else
                col = j;

            string sqr = to_string(row) + to_string(col);
            string piece = board[row][col];
            string piece_type = get_type(piece);
            string piece_color = get_color(piece);

            if (piece_type == "e")
                sqrs.push_back(sqr);
            else {
                if (row == src_row and col == src_col) {
                    hit_src = true;
                    continue;
                }

                if (hit_src) {
                    if (piece_color != color)
                        sqrs.push_back(sqr);
                    break;
                }
                else {
                    sqrs.clear();
                    if (piece_color != color)
                        sqrs.push_back(sqr);
                }
            }

        }
        rows = false;
        add_moves(src, sqrs, moves);
    }
}


void fill_diag(string src, set<mov> &moves, position board,
                   string color)
{
    int src_row = int(src.at(0)) - '0';
    int src_col = int(src.at(1)) - '0';

    int src_diff = abs(src_col - src_row);
    int src_sum = src_col + src_row;
    int cur_diff = 0;
    int cur_sum = 0;

    vector<string> tl_sqrs = {};
    vector<string> tr_sqrs = {};

    bool hit_src = false;
    bool done = false;
    for (int i = 0; i < 8; i++) {
        if (done)
            break;

        for (int j = 0; j < 8; j++) {
            string sqr = to_string(i) + to_string(j);
            string piece = board[i][j];
            string piece_type = get_type(piece);
            string piece_color = get_color(piece);

            cur_diff = i - j;
            if (cur_diff != src_diff)
                continue;

            if (i == src_row && j == src_col)
                hit_src = true;


            if ((i < src_row && j < src_col) ||
                (i > src_row && j > src_col)) {
                if (!hit_src) {
                    if (piece_color == "e")
                        tl_sqrs.push_back(sqr);
                    else {
                        tl_sqrs.clear();
                        if (piece_color != color)
                            tl_sqrs.push_back(sqr);
                    }
                }
                else {
                    if (piece_color == "e")
                        tl_sqrs.push_back(sqr);
                    else {
                        if (piece_color != color)
                            tl_sqrs.push_back(sqr);
                        done = true;
                    }
                }
            }
        }
    }

    hit_src = false;
    done = false;
    for (int i = 0; i < 8; i++) {
        if (done)
            break;

        for (int j = 0; j < 8; j++) {
            string sqr = to_string(i) + to_string(j);
            string piece = board[i][j];
            string piece_type = get_type(piece);
            string piece_color = get_color(piece);

            cur_sum = j + i;
            if (cur_sum != src_sum)
                continue;

            if (i == src_row && j == src_col)
                hit_src = true;

            if ((i < src_row && j > src_col) ||
                (i > src_row && j < src_col)) {
                if (!hit_src) {
                    if (piece_color == "e")
                        tr_sqrs.push_back(sqr);
                    else {
                        tr_sqrs.clear();
                        if (piece_color != color)
                            tr_sqrs.push_back(sqr);
                    }
                }
                else {
                    if (piece_color == "e")
                        tr_sqrs.push_back(sqr);
                    else {
                        if (piece_color != color)
                            tr_sqrs.push_back(sqr);
                        done = true;
                    }
                }
            }
        }
    }

    vector<string> sqrs = vector_cat(tl_sqrs, tr_sqrs);
    add_moves(src, sqrs, moves);
}


void fill_knight(string src, set<mov> &moves, position board,
                   string color)
{
    int src_row = int(src.at(0)) - '0';
    int src_col = int(src.at(1)) - '0';

    vector<string> sqrs = {};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (abs(src_row - i) == 2 && j == src_col) {
                for (int x = -1; x < 2; x++) {
                    if (x == 0)
                        continue;

                    int new_col = j + x;
                    if (new_col > 7 || new_col < 0)
                        continue;

                    string sqr = to_string(i) + to_string(new_col);
                    string piece = board[i][new_col];
                    string piece_type = get_type(piece);
                    string piece_color = get_color(piece);

                    if (piece_color == "e")
                        sqrs.push_back(sqr);
                    else {
                        if (piece_color != color)
                            sqrs.push_back(sqr);
                    }
                }
            }
            if (abs(src_col - j) == 2 && i == src_row) {
                for (int x = -1; x < 2; x++) {
                    if (x == 0)
                        continue;

                    int new_row = i + x;
                    if (new_row > 7 || new_row < 0)
                        continue;

                    string sqr = to_string(new_row) + to_string(j);
                    string piece = board[new_row][j];
                    string piece_type = get_type(piece);
                    string piece_color = get_color(piece);

                    if (piece_color == "e")
                        sqrs.push_back(sqr);
                    else {
                        if (piece_color != color)
                            sqrs.push_back(sqr);
                    }
                }
            }
        }
    }
    add_moves(src, sqrs, moves);
}


void fill_pawn(string src, set<mov> &moves, position board,
                   string color)
{

    int src_row = int(src.at(0)) - '0';
    int src_col = int(src.at(1)) - '0';

    vector<string> sqrs = {};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (color == "W") {
                if (src_row - i == 1) {
                    string sqr = to_string(i) + to_string(j);
                    string piece = board[i][j];
                    string piece_type = get_type(piece);
                    string piece_color = get_color(piece);

                    if (j == src_col) {
                        if (piece_color == "e")
                            sqrs.push_back(sqr);
                    }

                    if (j == src_col + 1 || j == src_col - 1) {
                        if (piece_color != "e" &&
                            piece_color != color)
                            sqrs.push_back(sqr);
                    }
                }

                if (src_row == 6 && src_row - i == 2 && j == src_col) {
                    int prev_row = 5;
                    string prev_piece = board[prev_row][j];
                    string prev_piece_color = get_color(prev_piece);

                    string sqr = to_string(i) + to_string(j);
                    string piece = board[i][j];
                    string piece_type = get_type(piece);
                    string piece_color = get_color(piece);

                    if (prev_piece_color == "e" && piece_color == "e")
                        sqrs.push_back(sqr);
                }
            }
            if (color == "B") {
                if (i - src_row == 1) {
                    string sqr = to_string(i) + to_string(j);
                    string piece = board[i][j];
                    string piece_type = get_type(piece);
                    string piece_color = get_color(piece);

                    if (j == src_col) {
                        if (piece_color == "e")
                            sqrs.push_back(sqr);
                    }

                    if (j == src_col + 1 || j == src_col - 1) {
                        if (piece_color != "e" &&
                            piece_color != color)
                            sqrs.push_back(sqr);
                    }
                }

                if (src_row == 1 && i - src_row == 2 && j == src_col) {
                    int prev_row = 2;
                    string prev_piece = board[prev_row][j];
                    string prev_piece_color = get_color(prev_piece);

                    string sqr = to_string(i) + to_string(j);
                    string piece = board[i][j];
                    string piece_type = get_type(piece);
                    string piece_color = get_color(piece);

                    if (prev_piece_color == "e" && piece_color == "e")
                        sqrs.push_back(sqr);
                }
            }
        }
    }

    add_moves(src, sqrs, moves);
}


void fill_moves(set<mov> &moves, position board, string color,
                string piece_type, string src)
{
    if (piece_type == "K") {
        fill_adjacent(src, moves, board, color);
    }
    else if (piece_type == "Q") {
        fill_straight(src, moves, board, color);
        fill_diag(src, moves, board, color);
    }
    else if (piece_type == "r") {
        fill_straight(src, moves, board, color);
    }
    else if (piece_type == "b") {
        fill_diag(src, moves, board, color);
    }
    else if (piece_type == "k") {
        fill_knight(src, moves, board, color);
    }
    else if (piece_type == "p") {
        fill_pawn(src, moves, board, color);
    }

}


set<mov> get_moves(position board, string color)
{
    set<mov> moves;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            string piece = board[i][j];

            string piece_color(1, piece.at(0));
            if (piece_color == "e")
                continue;

            string piece_type(1, piece.at(1));
            string cur_sqr = to_string(i) + to_string(j);

            if (piece_color == color) {
                fill_moves(moves, board, color, piece_type, cur_sqr);
            }
        }
    }

    return moves;
}


void fast_forward(position &board, struct mov move)
{
    int src_row = int(move.src.at(0)) - '0';
    int src_col = int(move.src.at(1)) - '0';
    int dst_row = int(move.dst.at(0)) - '0';
    int dst_col = int(move.dst.at(1)) - '0';

    string piece = board[src_row][src_col];

    board[src_row][src_col] = "e";
    board[dst_row][dst_col] = piece;
}


bool check(position board, string color, set<mov> atkr_moves)
{
    string king_src = get_king(board, color);
    for (auto move : atkr_moves) {
        if (move.dst == king_src) {
            return true;
        }
    }

    return false;
}


bool checkmate(position board, string color,
               set<mov> defr_moves, set<mov> atkr_moves)
{
    string enemy_color = get_enemy_color(color);

    if (!check(board, color, atkr_moves))
        return false;

    for (auto move : defr_moves) {
        position new_board = board;
        fast_forward(new_board, move);

        set<mov> new_atkr_moves = get_moves(new_board, enemy_color);
        if (!check(new_board, color, new_atkr_moves))
            return false;
    }

    return true;
}


bool stalemate(position board, string color,
               set<mov> defr_moves, set<mov> atkr_moves)
{
    string enemy_color = get_enemy_color(color);
    bool stale = true;

    if (!check(board, color, atkr_moves)) {
        for (auto move : defr_moves) {
            position new_board = board;
            fast_forward(new_board, move);

            set<mov> new_atkr_moves = get_moves(new_board, enemy_color);
            if (!check(new_board, color, new_atkr_moves))
                stale = false;
        }
    }
    else
        stale = false;

    return stale;
}


void add_castle(string src, set<mov> &moves, position board,
                   string color, set<mov> atkr_moves)
{
    if (src == "")
        return;

    int master_row;
    if (color == "W")
        master_row = 7;
    else
        master_row = 0;

    bool queen = true;
    bool king = true;

    string color_rook = color + "r";
    string color_king = color + "K";

    string req_src = to_string(master_row) + src.at(1);
    if (src != req_src) {
        return;
    }

    if (board[master_row][0] != color_rook)
        queen = false;
    if (board[master_row][7] != color_rook)
        king = false;
    if (!(king || queen)) {
        return;
    }

    for (int j = 1; j < 7; j++) {
        string piece = board[master_row][j];
        string piece_color = get_color(piece);
        if (j < 4) {
            if (piece_color != "e")
                queen = false;
        }
        if (j > 4) {
            if (piece_color != "e")
                king = false;
        }
    }

    position castled = board;
    for (int j = 0; j < 8; j++) {
        if (queen && j <= 4) {
            if (j != 2 && j != 3)
                castled[master_row][j] = "e";
            else if (j == 2)
                castled[master_row][j] = color_king;
            else if (j == 3)
                castled[master_row][j] = color_rook;
        }
        if (king && j >= 4) {
            if (j != 5 && j != 6)
                castled[master_row][j] = "e";
            else if (j == 5)
                castled[master_row][j] = color_rook;
            else if (j == 6)
                castled[master_row][j] = color_king;
        }
    }

    string cvted_master = to_string(master_row);
    if (queen && !check(castled, color, atkr_moves)) {
        struct mov move;
        move.src = src;
        move.dst = cvted_master + "2";

        moves.insert(move);
    }

    if (king && !check(castled, color, atkr_moves)) {
        struct mov move;
        move.src = src;
        move.dst = cvted_master + "6";

        moves.insert(move);
    }

}


set<mov> filter_check(position board, string color,
                  set<mov> moves, set<mov> atkr_moves)
{
    string enemy_color = get_enemy_color(color);
    set<mov> filtered_set;

    for (auto move : moves) {
        position new_board = board;
        fast_forward(new_board, move);


        set<mov> new_atkr_moves = get_moves(new_board, enemy_color);
        if (!check(new_board, color, new_atkr_moves)) {
            filtered_set.insert(move);
        }
    }

    return filtered_set;
}


set<mov> filter_king(position board, string color, set<mov> moves)
{
    string enemy_color = get_enemy_color(color);
    string enemy_king_src = get_king(board, enemy_color);

    set<mov> kingless;
    for (auto move : moves) {
        if (move.dst != enemy_king_src)
            kingless.insert(move);
    }

    return kingless;
}


set<mov> legalMoves(position p, color c)
{
    set<mov> moves;
    string our_color = get_our_color(c);
    string enemy_color = get_enemy_color(our_color);

    set<mov> defr_moves = get_moves(p, our_color);
    set<mov> atkr_moves = get_moves(p, enemy_color);

    bool mate = checkmate(p, our_color, defr_moves, atkr_moves);
    if (mate)
        return moves;
    mate = stalemate(p, our_color, defr_moves, atkr_moves);
    if (mate)
        return moves;

    moves = defr_moves;

    string king_src = get_king(p, our_color);
    add_castle(king_src, moves, p, our_color, atkr_moves);

    set<mov> filtered_moves = filter_check(p, our_color, moves,
                                           atkr_moves);
    set<mov> kingless = filter_king(p, our_color, filtered_moves);

    set<mov> cvted_moves = cvt_moves(kingless);
    return cvted_moves;
}

