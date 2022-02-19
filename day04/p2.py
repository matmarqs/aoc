import sys


def get_input():
    numbers = []
    boards = []
    # recebendo todo input
    block = []
    for line in sys.stdin:
        if ',' in line:
            numbers = [int(i) for i in line.strip('\n').split(',')]
        else:
            if line == '\n':
                if block:
                    boards.append(block)
                block = []
            else:
                block.append([[0, int(i)] for i in line.split()])
    # ultimo bloco, pq nao tem um '\n' na ultima linha
    boards.append(block)
    return numbers, boards


def update(boards, n):
    for b in range(len(boards)):
        for i in range(len(boards[b])):
            for j in range(len(boards[b])):
                if (boards[b][i][j][1] == n):
                    boards[b][i][j][0] = 1


def check(boards, board_index):
    # board_index[i] = 0 ou 1, se ele nao ganhou ou ja ganhou
    for b in range(len(boards)):
        # checando linhas
        for i in range(len(boards[b])):
            checklin = []
            for j in range(len(boards[b])):
                checklin.append(boards[b][i][j][0])
            if every_element(checklin, 1):
                board_index[b] = 1
        # checando colunas
        for j in range(len(boards[b])):
            checkcol = []
            for i in range(len(boards[b])):
                checkcol.append(boards[b][i][j][0])
            if every_element(checkcol, 1):
                board_index[b] = 1


def every_element(L, n):
    for e in L:
        if (e != n):
            return False
    return True


def score(board):
    N = len(board)
    sum = 0
    for i in range(N):
        for j in range(N):
            if (board[i][j][0] == 0):
                sum += board[i][j][1]
    return sum


# returns position of first zero, or -1 if there is not a zero
def firstzero(L):
    N = len(L)
    for i in range(N):
        if L[i] == 0:
            return i
    return -1


def main():
    numbers, boards = get_input()
    board_index = [0 for i in boards]
    k = 0
    everyone_won = False
    while not everyone_won and k < len(numbers):
        ultimo = firstzero(board_index)
        update(boards, numbers[k])
        check(boards, board_index)
        everyone_won = every_element(board_index, 1)
        k += 1
    print("O score do ultimo ganhador eh", numbers[k-1]*score(boards[ultimo]))
    print("O ultimo ganhador foi o", ultimo+1)


if __name__ == '__main__':
    main()
