
# MIGHT BE POINTLESS
#def filter_bounds(dsts):
#    for i, dst in enumerate(dsts):
#        cur_row = dst[0]
#        cur_col = dst[1]

#        if cur_row < "1" or cur_row > "8" or
#           cur_col < "a" or cur_col > "h":
#            del dsts[i]


def add_cols(src, dsts, board, color):
# traverse rows down -> up
    row = src[0]
    col = src[1]

    hit_piece = False
    hit_enemy = False
    hit_src = False

    rows = ["1", "2", "3", "4", "5", "6", "7", "8"]
    available_dsts = []
    for new_row in rows:
        cur_sqr = "{0}{1}".format(new_row, col)
        cur_piece = board[new_row][col]

        if new_row == row:
        # if we hit our piece
            hit_src = True

        if cur_piece[0] != "e":
        # if we hit a square with a piece on it
            hit_piece = True

            if color != cur_piece[0]:
            # if the piece is an enemy piece
                hit_enemy = True

        if hit_piece and not hit_src:
        # if the piece we hit was not the source piece
            available_dsts = []

            if hit_enemy:
            # if the piece we hit was an enemy
                available_dsts.append(cur_sqr)

        if hit_piece and hit_src:
            if hit_enemy:
            # if we hit an enemy after we hit ours
                available_dsts.append(cur_sqr)

            break

    dsts = dsts + available_dsts


def add_rows(src, dsts, board, color):
# traverse cols left -> right
    row = src[0]
    col = src[1]

    hit_piece = False
    hit_enemy = False
    hit_src = False

    cols = ["a", "b", "c", "d", "e", "f", "g", "h"]
    available_dsts = []
    for new_col in cols:
        cur_sqr = "{0}{1}".format(row, new_col)
        cur_piece = board[row][new_col]

        if new_col == col:
        # if we hit our piece
            hit_src = True

        if cur_piece[0] != "e":
        # if we hit a square with a piece on it
            hit_piece = True

            if color != cur_piece[0]:
            # if the piece is an enemy piece
                hit_enemy = True

        if hit_piece and not hit_src:
        # if the piece we hit was not the source piece
            available_dsts = []

            if hit_enemy:
            # if the piece we hit was an enemy
                available_dsts.append(cur_sqr)

        if hit_piece and hit_src:
        # if the piece we hit was after we hit ours
            if hit_enemy:
            # if we hit an enemy after we hit ours
                available_dsts.append(cur_sqr)

            break

    dsts = dsts + available_dsts



def add_adjacent(src, dsts, board, color):
    row = src[0]
    col = src[1]
    # getting ascii of col val

    for i in range(-1, 2):

        for j in range(-1, 2):
            cur_piece = board[i][j]

            new_row = int(row) + i
            new_col = chr(ord(col) + j)

            if new_row != row and new_col != col:
            # if the square is not our current piece's square
                if cur_piece[0] == color:
                # if the square has a piece of our color (but not our piece)
                    continue

                dst = "{0}{1}".format(new_row, new_col)
                dsts.append(dst)


def add_moves(cur_piece, all_moves, board, color):
    # modifies the piece_moves arr to include all possible moves in
    # the format (OFFICIAL)[("src", "dst_1"), ("src", "dst_2") ... etc]
    src_r = cur_piece[2]
    src_c = cur_piece[3]
    src = "{0}{1}".format(src_r, src_c)

    dsts = []
    # get all possible moves based on piece type
    piece_type = cur_piece[1]
    # cur_piece: "WK4a" -> piece_type = "K"
    if piece_type == "K":
        add_adjacent(src, dsts, board, color)
    elif piece_type == "R":
        add_cols(src, dsts, board, color)
        add_rows(src, dsts, board, color)
    # filter the possible moves by doing bounds checks
    # POINTLESS
    #filter_bounds(dsts)
    # filter the possible moves by doing block checks
    # also POINTLESS
    #filter_moves(dsts, board)
    # filter the possible moves by doing game over checks
    filter_game_over(dsts)
    # add every possible move (destinations) to src
    for dst in dsts:
        add_moves.append((src, dst))


def legal_moves(board, color):
    # returns all legal moves color can make on the board
    all_moves = []

    rows = ["1", "2", "3", "4", "5", "6", "7", "8"]
    cols = ["a", "b", "c", "d", "e", "f", "g", "h"]
    for row in rows:

        for col in cols:
            cur_piece = board[row][color]

            if cur_piece[0] == "e":
                # cur_sqr is empty
                continue

            piece_color = cur_piece[0]
            # cur_sqr = "WK4a" white king at row 4 col a

            if piece_color == color:
            # if the current square is color's square (we can move it)
                add_moves(cur_piece, all_moves, board, color)

    return all_moves


# should look like this:

# OFFICIAL
# {
#  ("1a","2b"),("1a","3c"),("1a","4d"),("1a","5e"),("1a","6f"),
#  ("1a","7g"),("7e","8d"),("7e","8e"),("7e","8f"),("7e","7d"),     
#  ("7e","7f"),("7e","6d"),("7e","6e"),("6h","4g"), 
#  ("6h","5f"),("6h","7f"),("6h","8g")
# }

# ACTUAL
# [
#   ("1a", "2b"), (etc)
# ]





















