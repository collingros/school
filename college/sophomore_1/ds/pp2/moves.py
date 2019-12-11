# collin gros
# 11/7/18

# assuming the following
#   no check or stalemate
#   only kings and rooks
#   kings can die
#   columns are integers 0-8 not 'a'-'h' <-(autism)

#   also this is in python but i need to turn it in in C

#   lets see how this works out

def game_over(board):
    w_king = False
    b_king = False

    for row in range(0, 8):
        for col in range(0, 8):
            piece = board[row][col]

            piece_color = piece[0]
            if piece_color == "e":
                continue

            piece_type = piece[1]
            if piece_type == "K":
                if piece_color == "W":
                    w_king = True
                elif piece_color == "B":
                    b_king = True

    if not (w_king and b_king):
        return True

    return False


def add_moves(src, sqrs, moves):
    move = ""
    for s in sqrs:
        move = "{0}:{1}".format(src, s)
        moves.append(move)


def fill_adjacent(src, moves, board, color):
    src_row = int(src[0])
    src_col = int(src[1])
    sqrs = []
    sqr = ""

    for i in range(-1, 2):
        for j in range(-1, 2):
            new_row = src_row + i
            new_col = src_col + j

            if (new_row < 0 or new_row > 7 or
                new_col < 0 or new_col > 7 or
                (new_row == src_row and new_col == src_col)):
            # move is out of range or the same piece
                continue

            sqr = "{0}{1}".format(new_row, new_col)
            piece = board[new_row][new_col]

            if piece[0] == "e":
                sqrs.append(sqr)
            elif piece[0] != color:
                sqrs.append(sqr)

    add_moves(src, sqrs, moves)


def fill_straight(src, moves, board, color):
    rows = True
    # fill the column first

    for i in range(0, 2):
        sqrs = []
        sqr = ""
        row = int(src[0])
        col = int(src[1])
        hit_src = False

        for val in range(0, 8):
            if rows:
                row = val
            else:
                col = val

            sqr = "{0}{1}".format(row, col)
            piece = board[row][col]

            if piece[0] == "e":
                sqrs.append(sqr)

            else:
                if str(row) == src[0] and str(col) == src[1]:
                # current square is our piece
                    hit_src = True

                    continue

                if hit_src:
                # if we're above (filling col) or to the right (filling row)
                # of our piece
                    if piece[0] == color:
                        pass
                    else:
                    # we can attack the enemy
                        sqrs.append(sqr)

                    break

                else:
                # if we're below (filling col) or to the right (filling row)
                # of our piece
                    sqrs = []
                    # the piece blocks all of the previously added moves

                    if piece[0] == color:
                        pass
                    else:
                    # we can attack the enemy
                        sqrs.append(sqr)

        rows = False
        add_moves(src, sqrs, moves)


def fill_angle(src, moves, board, color):
    src_row = int(src[0])
    src_col = int(src[1])

    src_diff = abs(src_col - src_row)
    src_sum = src_col + src_row

    cur_diff = 0
    cur_sum = 0

    tl_sqrs = []
    # top left to bot right diag
    tr_sqrs = []
    # top right to bot left diag

    hit_src = False
    done = False
    for row in range(0, 8):
        if done:
            break

        for col in range(0, 8):
            sqr = "{0}{1}".format(row, col)
            piece = board[row][col]

            cur_diff = row - col
            if cur_diff != src_diff:
                continue

            if row == src_row and col == src_col:
                hit_src = True

            if ((row < src_row and col < src_col) or
                (row > src_row and col > src_col)):
            # we're looking at squares using top left to bot right diag
                if not hit_src:
                    if piece[0] == "e":
                        tl_sqrs.append(sqr)
                    else:
                        tl_sqrs = []
                        if piece[0] != color:
                            tl_sqrs.append(sqr)
                else:
                    if piece[0] == "e":
                        tl_sqrs.append(sqr)
                    else:
                        if piece[0] != color:
                            tl_sqrs.append(sqr)

                        done = True

    hit_src = False
    done = False
    for row in range(0, 8):
        if done:
            break

        for col in range(0, 8):
            sqr = "{0}{1}".format(row, col)
            piece = board[row][col]

            cur_sum = col + row
            if cur_sum != src_sum:
                continue

            if row == src_row and col == src_col:
                hit_src = True

            if ((row < src_row and col > src_col) or
                (row > src_row and col < src_col)):
            # we're looking at squares using top right to bot left diag
                if not hit_src:
                    if piece[0] == "e":
                        tr_sqrs.append(sqr)
                    else:
                        tr_sqrs = []
                        if piece[0] != color:
                            tr_sqrs.append(sqr)
                else:
                    if piece[0] == "e":
                        tr_sqrs.append(sqr)
                    else:
                        if piece[0] != color:
                            tr_sqrs.append(sqr)

                        done = True

    sqrs = tl_sqrs + tr_sqrs
    add_moves(src, sqrs, moves)


def fill_knight(src, moves, board, color):
    src_row = int(src[0])
    src_col = int(src[1])

    sqrs = []

    for row in range(0, 8):
        for col in range(0, 8):
            if abs(src_row - row) == 2 and col == src_col:
                for i in range(-1, 2):
                    if i == 0:
                        continue

                    new_col = col + i
                    if new_col > 7 or new_col < 0:
                        continue

                    sqr = "{0}{1}".format(row, new_col)
                    piece = board[row][new_col]

                    if piece[0] == "e":
                        sqrs.append(sqr)
                    else:
                        if piece[0] != color:
                            sqrs.append(sqr)

            if abs(src_col - col) == 2 and row == src_row:
                for i in range(-1, 2):
                    if i == 0:
                        continue

                    new_row = row + i
                    sqr = "{0}{1}".format(new_row, col)
                    piece = board[new_row][col]

                    if piece[0] == "e":
                        sqrs.append(sqr)
                    else:
                        if piece[0] != color:
                            sqrs.append(sqr)

    add_moves(src, sqrs, moves)


def fill_pawn(src, moves, board, color):
    src_row = int(src[0])
    src_col = int(src[1])

    sqrs = []

    for row in range(0, 8):
        for col in range(0, 8):
            if color == "W":
                if src_row - row == 1:
                    sqr = "{0}{1}".format(row, col)
                    piece = board[row][col]

                    if col == src_col:
                        if piece[0] == "e":
                            sqrs.append(sqr)

                    if (col == src_col + 1 or
                        col == src_col - 1):
                        if (piece[0] != "e" and
                            piece[0] != color):
                            sqrs.append(sqr)

                if src_row == 6 and src_row - row == 2 and col == src_col:
                    prev_row = 5
                    sqr = "{0}{1}".format(row, col)

                    prev_piece = board[prev_row][col]
                    piece = board[row][col]

                    if prev_piece[0] == "e" and piece[0] == "e":
                        sqrs.append(sqr)

            if color == "B":
                if row - src_row == 1:
                    sqr = "{0}{1}".format(row, col)
                    piece = board[row][col]

                    if col == src_col:
                        if piece[0] == "e":
                            sqrs.append(sqr)

                    if (col == src_col + 1 or
                        col == src_col - 1):
                        if (piece[0] != "e" and
                            piece[0] != color):
                            sqrs.append(sqr)

                if src_row == 1 and row - src_row == 2 and col == src_col:
                    prev_row = 2
                    sqr = "{0}{1}".format(row, col)

                    prev_piece = board[prev_row][col]
                    piece = board[row][col]

                    if prev_piece[0] == "e" and piece[0] == "e":
                        sqrs.append(sqr)

    add_moves(src, sqrs, moves)


def get_attacker(enemy_moves, victim_piece, board):
    atkr_piece_str = ""

    for enemy_move in enemy_moves:
        enemy_move_substr = enemy_move.split(":")

        atkr_src = enemy_move_substr[0]
        atkr_dst = enemy_move_substr[-1]

        for row in range(0, 8):
            for col in range(0, 8):
                sqr = "{0}{1}".format(row, col)
                piece = board[row][col]

                if piece == victim_piece:
                    if atkr_dst == sqr:
                        atkr_src_row = int(atkr_src[0])
                        atkr_src_col = int(atkr_src[1])

                        atkr_piece = board[atkr_src_row][atkr_src_col]
                        atkr_piece_str = "{0}{1}".format(atkr_piece, atkr_src)

    return atkr_piece_str


def get_king(board, color):
    king_piece_str = ""

    for row in range(0, 8):
        for col in range(0, 8):
            sqr = "{0}{1}".format(row, col)
            piece = board[row][col]

            if piece[0] != "e":
                if piece[0] == color and piece[1] == "K":
                    king_piece_str = "{0}{1}".format(piece, sqr)

    return king_piece_str


def is_check(enemy_moves, our_moves, board, color):
    for enemy_move in enemy_moves:
        enemy_move_substr = enemy_move.split(":")
        atkr_dst = enemy_move_substr[-1]

        for row in range(0, 8):
            for col in range(0, 8):
                sqr = "{0}{1}".format(row, col)
                piece = board[row][col]

                if piece[0] == color and piece[1] == "K":
                    if atkr_dst == sqr:
                        return True

    return False


def strip_piece(piece, board, color):
    for row in range(0, 8):
        for col in range(0, 8):
            if board[row][col] == "{0}{1}".format(color, piece):
                print("stripped piece")
                board[row][col] = "e"


def replace_piece(target_piece, target_sqr, replacement_piece, board):
    for row in range(0, 8):
        for col in range(0, 8):
            piece = board[row][col]
            sqr = "{0}{1}".format(row, col)
            if piece[0] != "e":
                if piece == target_piece and sqr == target_sqr:
                    board[row][col] = replacement_piece
                elif piece == replacement_piece:
                    board[row][col] = "e"


def fill_moves(piece, moves, board, color, row, col):
    piece_type = piece[1]
    src = "{0}{1}".format(row, col)

    if piece_type == "K":
        fill_adjacent(src, moves, board, color)
    elif piece_type == "Q":
        fill_straight(src, moves, board, color)
        fill_angle(src, moves, board, color)
    elif piece_type == "R":
        fill_straight(src, moves, board, color)
    elif piece_type == "B":
        fill_angle(src, moves, board, color)
    elif piece_type == "N":
    # N is for knight
        fill_knight(src, moves, board, color)
    elif piece_type == "P":
        fill_pawn(src, moves, board, color)


def get_moves(board, color):
    moves = []

    for row in range(0, 8):
        for col in range(0, 8):
            piece = board[row][col]

            piece_color = piece[0]
            if piece_color == "e":
                continue
            elif piece_color == color:
                fill_moves(piece, moves, board, color, row, col)

    return moves


def copy_board(board):
    new_board = []
    for row in range(0, 8):
        new_board.append([])
        for col in range(0, 8):
            new_board[row].append(board[row][col])

    return new_board


def defend(enemy_moves, our_moves, board, color):
    check = is_check(enemy_moves, our_moves, board, color)
    if not check:
        return our_moves


    danger_sqrs = get_danger(enemy_moves, our_moves, board, color)
    king_escapes = get_king_escapes(danger_sqrs)
    blocking_moves = get_blocking_moves()
    killing_moves = get_killing_moves()

    check_moves(danger_zone, king_escapes, blocking_moves, killing_moves)


def check_moves():
    # combine all the check moves in one
    # filter out the moves that we used to be able to make, but now
    # we can't since we're in check
    pass

    return None
    # return the array of moves we can make while in check


def get_killing_moves(our_moves, atkr_sqr, board):
    # extract the moves that we can make to kill the attacker without
    # putting the king back in check
    kill_moves = []

    for move in our_moves:
        move_sub = move.split(":")
        move_piece = move_sub[0]
        move_sqr = move_sub[-1]

        if (move_sqr == atkr_sqr and
            move_piece[1] != "K"):
            modified_board = copy_board(board)
            strip_piece(move_piece[1], modified_board, color)

            if color == "W":
                enemy_color = "B"
            else:
                enemy_color = "W"

            new_enemy_moves = get_moves(board, enemy_color)
            will_check = is_check(new_enemy_moves, our_moves,
                                  modified_board, color)
            if not will_check:
                kill_moves.append(move)

    return kill_moves
    # return the array of moves we can make to kill the atkr


def get_blocking_moves(danger_sqrs, our_moves, enemy_moves, color):
    # extract the moves that we can make to block the atkr, without
    # putting the king in check
    blocks = []

    for move in our_moves:
        move_sub = move.split(":")
        move_piece = move_sub[0]
        move_sqr = move_sub[-1]

        for danger_sqr in danger_sqrs:
            if (move_sqr == danger_sqr and
                move_piece != "K"):
                kingless_board = copy_board(board)
                strip_piece("K", kingless_board, color)

                will_check = is_check(enemy_moves, our_moves,
                                      kingless_board, color)
                if not will_check:
                    blocks.append(move)

    return blocks
    # return the array of moves we can make to block the atkr


def get_king_escapes(danger_sqrs, board, color):
    # extract the moves that we can make using the king to escape
    # from ALL enemy moves
    escapes = []
    safe = True

    for danger_sqr in danger_sqrs:
        for king_sqr in king_sqrs:
            if danger_sqr == king_sqr:
                safe = False

        if safe = True:
            escapes.append(king_sqr)

    return escapes
    # return the array of moves that we can make to make the king
    # escape without getting back in check


def get_sqrs(moves):
    sqrs = []
    for move in moves:
        move_sub = move.split(":")
        move_sqr = move_sub[-1]

        sqrs.append(move_sqr)

    return sqrs


def get_danger(enemy_moves, our_moves, board, color):
    # return the array of enemy_moves' SQRS that include the king's square
    kingless_board = copy_board(board)
    strip_piece("K", kingless_board, color)

    danger_moves = []

    if color == "W":
        enemy_color = "B"
    else:
        enemy_color = "W"

    danger_moves = get_moves(kingless_board, enemy_color)
    danger_sqrs = get_sqrs(danger_moves)

    return danger_sqrs


def legal_moves(board, color):
    moves = []

    if game_over(board):
        return moves

    enemy_color = ""
    if color == "W":
        enemy_color = "B"
    else:
        enemy_color = "W"

    defr_moves = get_moves(board, color)
    atkr_moves = get_moves(board, enemy_color)

    moves = defend(atkr_moves, defr_moves, board, color)

    return moves


board = [
    ["e", "e", "e", "e", "e", "e", "e", "BK"],
    ["e", "e", "e", "e", "e", "e", "e", "e"],
    ["e", "e", "e", "e", "e", "e", "e", "e"],
    ["e", "e", "e", "e", "e", "e", "e", "e"],
    ["e", "e", "e", "e", "e", "e", "e", "e"],
    ["e", "e", "BB", "e", "e", "e", "e", "e"],
    ["e", "e", "e", "BB", "e", "e", "e", "e"],
    ["e", "e", "e", "e", "WK", "e", "e", "e"],
]

color = "W"


moves = legal_moves(board, color)
print(moves)


'''
def get_overlap(atkr, atkr_moves, defr, atkr_sqr, defr_sqr, overlap,
                board, color):
# assuming that atkr_moves and defr_moves are the piece's moves themselves
# (attacker and king)
    clone = "{0}{1}".format(color, atkr[1])
    # convert to our color wololo
    clone_sqr = defr_sqr
    clone_piece = "{0}{1}".format(clone, clone_sqr)

    clone_moves = []
    fill_moves(clone_piece, clone_moves, board, color,
               clone_sqr[0], clone_sqr[1])

    for atkr_move in atkr_moves:
        atkr_move_substr = atkr_move.split(":")
        atkr_move_sqr = atkr_move_substr[-1]

        for clone_move in clone_moves:
            clone_move_substr = clone_move.split(":")
            clone_move_sqr = clone_move_substr[-1]

            if atkr_move_sqr == clone_move_sqr:
                overlap.append(clone_move_sqr)

    return overlap
'''
'''
def block_overlap(our_moves, king_moves, enemy_moves, overlap, board):
    block_moves = []

    for move in our_moves:
    # move available pieces to block the path of the attacker
        move_substr = move.split(":")
        move_src = move_substr[0]
        move_dst = move_substr[-1]

        move_src_row = int(move_src[0])
        move_src_col = int(move_src[1])

        move_piece = board[move_src_row][move_src_col]

        for overlap_sqr in overlap:
            if move_piece[0] != "e":
                if move_piece[1] != "K":
                    if move_dst == overlap_sqr:
                        block_moves.append(move)

    # get king out of check by moving him
    for king_move in king_moves:
        add_move = True
        king_move_substr = king_move.split(":")
        king_move_dst = king_move_substr[-1]

        for enemy_move in enemy_moves:
            enemy_move_substr = enemy_move.split(":")
            enemy_move_src = enemy_move_substr[0]
            enemy_move_dst = enemy_move_substr[-1]

            if king_move_dst == enemy_move_dst:
                add_move = False

        if add_move:
            block_moves.append(king_move)

    return block_moves


'''
