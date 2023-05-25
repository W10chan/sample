#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 3
#define PLAYER_MARK 'o'
#define COMPUTER_MARK 'x'

char masu[NUM][NUM];

// 1.盤面の初期化用の関数
void init(){
    int x, y;
    for(x = 0; x < NUM; x++){
        for(y = 0; y < NUM; y++){
            masu[x][y] = ' ';
        }
    }
}

// 2.3x3のマスを表示する用の関数
void printMasu(){
    printf(" ");
    for (int x = 0; x < NUM; x++) {
        printf("%2d", x);
    }
    printf("\n");

    for (int y = 0; y < NUM; y++) {
        printf("%d", y);
        for (int x = 0; x < NUM; x++) {
            printf("|%c", masu[x][y]);
        }
        printf("|\n");
    }
    printf("\n");
}

// 3.プレイヤーの手
void playerTurn() {
    int row, col;

    while (1) {
        printf("プレイヤーの番です。\n");
        printf("行 (0-%d): ", 2);
        scanf("%d", &row);
        printf("列 (0-%d): ", 2);
        scanf("%d", &col);

        //row--;
        //col--;

        if (row < 0 || row >= NUM || col < 0 || col >= NUM || masu[row][col] != ' ') {
            printf("無効な位置です。もう一度入力してください。\n");
            continue;
        }

        masu[row][col] = PLAYER_MARK;
        break;
    }
}

// 4.コンピューターの手
void computerTurn() {
    int row, col;

    printf("コンピュータの番です。\n");

    while (1) {
        row = rand() % NUM;
        col = rand() % NUM;

        if (masu[row][col] == ' ') {
            masu[row][col] = COMPUTER_MARK;
            break;
        }
    }
}

//5．勝敗判定
int judgeWin() {
    int x;

    for (x = 0; x < NUM; x++) {
        if (masu[x][0] == masu[x][1] && masu[x][1] == masu[x][2] && masu[x][0] != ' ') {
            return 1;
        }
    }

    for (x = 0; x < NUM; x++) {
        if (masu[0][x] == masu[1][x] && masu[1][x] == masu[2][x] && masu[0][x] != ' ') {
            return 1;
        }
    }

    if ((masu[0][0] == masu[1][1] && masu[1][1] == masu[2][2] && masu[0][0] != ' ') ||
        (masu[0][2] == masu[1][1] && masu[1][1] == masu[2][0] && masu[0][2] != ' ')) {
        return 1;
    }

    return 0;
}

int judgeDraw(){
    int x, y;
    for (x = 0; x < NUM; x++) {
        for (y = 0; y < NUM; y++) {
            if (masu[x][y] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    srand(time(0));

    init();
    printMasu();

    printf("三目並べゲームを開始します。\n");

    while (1) {
        playerTurn();
        printMasu();

        if (judgeWin()) {
            printf("プレイヤーの勝利です！\n");
            break;
        }

        if (judgeDraw()) {
            printf("引き分けです。\n");
            break;
        }

        computerTurn();
        printMasu();

        if (judgeWin()) {
            printf("コンピュータの勝利です。\n");
            break;
        }

        if (judgeDraw()) {
            printf("引き分けです。\n");
            break;
        }
    }

    return 0;
}
