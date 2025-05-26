import random, os, time
sizeY = 50
sizeX = sizeY*2
def born(y,x,board):
    alive = board[y][x] == "■"
    neighbors = neighborCnt(y,x,board)
    return  "■" if ((alive and (neighbors == 2  or neighbors == 3)) or (not alive and neighbors == 3)) else " "
            
def neighborCnt(y,x,board):
    cnt= 0
    for i in range (-1,2):
        for j in range (-1,2):
            if (y+i<0 or y+i>=sizeY or x+j<0 or x+j>=sizeX or i == j == 0):
                continue
            if board[y+i][x+j] == "■":
                cnt+=1
    return cnt

def newGen(board):
    return [[born(y,x,board) for x in range(sizeX)] for y in range(sizeY)]

def printBoard(board):
    for i in board:
        for j in i:
            print(j,end="")
        print()
    
def start():
    board = [["■" if random.randint(0, 1) == 1 else " " for _ in range(sizeX)] for _ in range(sizeY)]
    gen = 0
    while board != newGen(board) and board != newGen(newGen(board)):
        gen+=1
        board = newGen(board)
        time.sleep(0.05)
        os.system("clear")
        printBoard(board)
        print("\n\n\n\n Generation",gen)

start()