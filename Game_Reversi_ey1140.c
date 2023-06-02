#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define NUM 8
#define PLAYER_MARK 'O'
#define COMPUTER_MARK 'X'

char masu[NUM][NUM];

// 盤面の初期化
void init() {
    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            masu[x][y] = ' ';
        }
    }
    masu[3][3] = PLAYER_MARK;
    masu[3][4] = COMPUTER_MARK;
    masu[4][3] = COMPUTER_MARK;
    masu[4][4] = PLAYER_MARK;
}

// 盤面の表示
void printMasu() {
    printf("  ");
    for (int x = 0; x < NUM; x++) {
        printf("%2d", x);
    }
    printf("\n");

    for (int y = 0; y < NUM; y++) {
        printf("%d ", y);
        for (int x = 0; x < NUM; x++) {
            printf("|%c", masu[x][y]);
        }
        printf("|\n");
    }
}

// プレイヤーの手
void playerTurn() {
    int row, col;

    while (1) {
        printf("プレイヤーの番です。\n");
        printf("行 (0-%d): ", NUM - 1);
        if (scanf("%d", &row) != 1) {
            printf("無効な入力です。もう一度入力してください。\n");
            fflush(stdin);
            continue;
        }
        printf("列 (0-%d): ", NUM - 1);
        if (scanf("%d", &col) != 1) {
            printf("無効な入力です。もう一度入力してください。\n");
            fflush(stdin);
            continue;
        }

        if (row < 0 || row >= NUM || col < 0 || col >= NUM || masu[row][col] != ' ') {
            printf("無効な位置です。もう一度入力してください。\n");
            continue;
        }

        int flag = 0;
        // 上下左右および斜めの8方向をチェック
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                // 自身の位置や範囲外はスキップ
                if (dx == 0 && dy == 0) {
                    continue;
                }
                int x = col + dx;
                int y = row + dy;
                int count = 0;
                // 相手の石を挟んでいるかチェック
                while (x >= 0 && x < NUM && y >= 0 && y < NUM && masu[y][x] != ' ' && masu[y][x] != PLAYER_MARK) {
                    count++;
                    x += dx;
                    y += dy;
                }
                // 挟んでいる場合は裏返す
                if (x >= 0 && x < NUM && y >= 0 && y < NUM && masu[y][x] == PLAYER_MARK && count > 0) {
                    x = col + dx;
                    y = row + dy;
                    while (masu[y][x] != PLAYER_MARK) {
                        masu[y][x] = PLAYER_MARK;
                        x += dx;
                        y += dy;
                    }
                    flag = 1;
                }
            }
        }
        if (flag) {
            masu[row][col] = PLAYER_MARK;
            break;
        } else {
            printf("挟める相手の石がありません。もう一度入力してください。\n");
        }
    }
}

// コンピューターの手
void computerTurn() {
    int validMoves[NUM * NUM][2];
    int validMoveCount = 0;

    // 空きマスを探索し、挟むことができる場所を記録
    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            if (masu[y][x] == ' ') {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) {
                            continue;
                        }
                        int tx = x + dx;
                        int ty = y + dy;
                        int count = 0;
                        while (tx >= 0 && tx < NUM && ty >= 0 && ty < NUM && masu[ty][tx] != ' ' && masu[ty][tx] != COMPUTER_MARK) {
                            count++;
                            tx += dx;
                            ty += dy;
                        }
                        if (tx >= 0 && tx < NUM && ty >= 0 && ty < NUM && masu[ty][tx] == COMPUTER_MARK && count > 0) {
                            validMoves[validMoveCount][0] = x;
                            validMoves[validMoveCount][1] = y;
                            validMoveCount++;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (validMoveCount > 0) {
        // ランダムに選んだ有効な手を実行
        int index = rand() % validMoveCount;
        int x = validMoves[index][0];
        int y = validMoves[index][1];
        masu[y][x] = COMPUTER_MARK;

        // 挟める相手の石を裏返す
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                int tx = x + dx;
                int ty = y + dy;
                int count = 0;
                while (tx >= 0 && tx < NUM && ty >= 0 && ty < NUM && masu[ty][tx] != ' ' && masu[ty][tx] != COMPUTER_MARK) {
                    count++;
                    tx += dx;
                    ty += dy;
                }
                if (tx >= 0 && tx < NUM && ty >= 0 && ty < NUM && masu[ty][tx] == COMPUTER_MARK && count > 0) {
                    tx = x + dx;
                    ty = y + dy;
                    while (masu[ty][tx] != COMPUTER_MARK) {
                        masu[ty][tx] = COMPUTER_MARK;
                        tx += dx;
                        ty += dy;
                    }
                }
            }
        }
    }
}

// 勝利判定
int judgeWin() {
    int playerCount = 0;
    int computerCount = 0;
    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            if (masu[y][x] == PLAYER_MARK) {
                playerCount++;
            } else if (masu[y][x] == COMPUTER_MARK) {
                computerCount++;
            }
        }
    }
    if (playerCount == 0 || computerCount == 0 || playerCount + computerCount == NUM * NUM) {
        return 1;
    }
    return 0;
}

int main() {
    srand(time(0));

    setlocale(LC_ALL, "");

    init();
    printMasu();

    printf("オセロゲームを開始します。\n");

    while (1) {
        playerTurn();
        printMasu();

        if (judgeWin()) {
            int playerCount = 0;
            int computerCount = 0;
            for (int x = 0; x < NUM; x++) {
                for (int y = 0; y < NUM; y++) {
                    if (masu[y][x] == PLAYER_MARK) {
                        playerCount++;
                    } else if (masu[y][x] == COMPUTER_MARK) {
                        computerCount++;
                    }
                }
            }
            printf("プレイヤー: %d, コンピューター: %d\n", playerCount, computerCount);
            if (playerCount > computerCount) {
                printf("プレイヤーの勝利です！\n");
            } else if (playerCount < computerCount) {
                printf("コンピューターの勝利です！\n");
            } else {
                printf("引き分けです。\n");
            }
            break;
        }

        computerTurn();
        printMasu();

        if (judgeWin()) {
            int playerCount = 0;
            int computerCount = 0;
            for (int x = 0; x < NUM; x++) {
                for (int y = 0; y < NUM; y++) {
                    if (masu[y][x] == PLAYER_MARK) {
                        playerCount++;
                    } else if (masu[y][x] == COMPUTER_MARK) {
                        computerCount++;
                    }
                }
            }
            printf("プレイヤー: %d, コンピューター: %d\n", playerCount, computerCount);
            if (playerCount > computerCount) {
                printf("プレイヤーの勝利です！\n");
            } else if (playerCount < computerCount) {
                printf("コンピューターの勝利です！\n");
            } else {
                printf("引き分けです。\n");
            }
            break;
        }
    }

    return 0;
}
