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


def check(boards):
    # retornar -1 significa que nao encontrou
    # retornar b >= 0 eh o board encontrado
    for b in range(len(boards)):
        # checando linhas
        for i in range(len(boards[b])):
            checklin = []
            for j in range(len(boards[b])):
                checklin.append(boards[b][i][j][0])
            if every_element(checklin, 1):
                return b
        # checando colunas
        for j in range(len(boards[b])):
            checkcol = []
            for i in range(len(boards[b])):
                checkcol.append(boards[b][i][j][0])
            if every_element(checkcol, 1):
                return b
    return -1


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


def main():
    numbers, boards = get_input()
    winboard = -1
    k = 0
    while winboard == -1 and k < len(numbers):
        update(boards, numbers[k])
        winboard = check(boards)
        k += 1
    if (winboard == -1):
        print("Nao existe ganhador")
    else:
        print("O score do ganhador eh", numbers[k-1]*score(boards[winboard]))


if __name__ == '__main__':
    main()
