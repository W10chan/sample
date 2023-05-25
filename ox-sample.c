#include <stdio.h> // scanf/printf
#include <stdlib.h> // rand/srand
#include <time.h> // time

#define NUM 3 // マス数
#define true 1
#define false 0

//新しい型の定義
typedef int bool;

//列挙型(enum)の定数定義
typedef enum {
    RESULT_WIN, // プレイヤーの勝ち
    RESULT_LOSE, // プレイヤーの負け
    RESULT_DRAW, // 引き分け
    RESULT_NONE // つづく
} RESULT;

typedef enum {
    TURN_PLAYER, // プレイヤーのターン
    TURN_COM, // コンピューターのターン
} TURN;

char board[NUM][NUM];

//初期化処理(srand 関数の実行と前述の board への ' ' の格納)
void init(void){
    srand(time(NULL));

    for(int x = 0; x < NUM; x++){
        for(int y = 0; y < NUM; y++){
            board[x][y] = ' ';
        }
    }
}

//①○×を記入する位置を決める
void myTarget(int *x, int *y){
    printf("どこに印を記入しますか？(x,y)\n");
    printf("xの入力(0 ~ %d):", NUM - 1);
    scanf("%d", x);
    printf("yの入力(0 ~ %d):", NUM - 1);
    scanf("%d", y);
}

void comTarget(int *x, int *y) {
    *x = rand() % NUM;//0~2の値がランダムに生成される
    *y = rand() % NUM;
}

//0以下、3以上は不正
bool ableMark(int x, int y) {
    if (x < 0 || x > NUM - 1 || y < 0 || y > NUM - 1) {
        printf("入力した値は使えません\n");
        return 0;
    }

//記入済みかどうかの判定
    if (board[x][y] != ' ') {
        printf("その場所は選択出来ません\n");
        return 0;
    }

    return 1;
}

void decidePosition(int *x, int *y, TURN turn) {
    while (1) {
        if (turn == TURN_PLAYER) {
            myTarget(x, y);
        } else {
            comTarget(x, y);
        }
        if (ableMark(*x, *y)) {
            break;
        }
    }
}

//2.〇☓記入
void writeMark(int x, int y, TURN turn) {

    if (turn == TURN_PLAYER) {
        board[x][y] = 'o';
    }
    else {
        board[x][y] = 'x';
    }
}
// 3.3x3のマスを表示する
void printBoard(void) {
    printf(" ");
///x軸(012)
    for (int x = 0; x < NUM; x++) {
        printf("%2d", x);
    }
    printf("\n");

///y軸（012,|）
    for (int y = 0; y < NUM; y++) {
        printf("%d", y);
        for (int x = 0; x < NUM; x++) {//x方向
            printf("|%c", board[x][y]);
        }
        printf("|\n");//改行指定
    }
    printf("\n");
}

bool judgeFull(void) {
    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            if (board[x][y] == ' ') {
                return 0;
            }
        }
    }

    return 1;
}

// 4.勝負の結果を判断する
RESULT checkWin(TURN turn){

int count;
char mark;

//記入された印の取得
if(turn == TURN_PLAYER){
    mark = 'o';
}
else{
    mark = 'x';
}
//横方向のチェック
for(int y = 0; y < NUM; y++){
    //記入された値が横方向に三つ並んでいるかどうか？
    count = 0;
    for(int x =0; x < NUM; x++){
        if(board[x][y]  == mark){
            count++;
        }
    }
    if (count == 3) {
            return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
        }

    }
//縦方向のチェック
    for (int x = 0; x < NUM; x++) {

        // 記入された印が縦方向に３つ並んでいるかを確認
        count = 0;
        for (int y = 0; y < NUM; y++) {
            if (board[x][y] == mark) {
                count++;
            }
        }
        if (count == 3) {
            return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
        }

    }
//斜め方向のチェック
    // 記入された印が右下方向に３つ並んでいるかを確認
    count = 0;
    for (int k = 0; k < NUM; k++) {
        if (board[k][k] == mark) {
            count++;
        }
    }
    ///
    if (count == 3) {
        return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
    }

    // 記入された印が左下方向に３つ並んでいるかを確認
    count = 0;
    for (int k = 0; k < NUM; k++) {
        if (board[NUM - 1 - k][NUM - 1 - k] == mark) {
            count++;
        }
    }
    if (count == 3) {
        return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
    }

//引き分けの判定
    // マスが全て埋まったかどうかを確認
    if (judgeFull()) {
        return RESULT_DRAW;
    }

    // まだ勝敗が決定していない
    return RESULT_NONE;
}

// ⑤ターンを進める
TURN nextTurn(TURN now){
    return now == TURN_PLAYER ? TURN_COM : TURN_PLAYER;
}

// ⑥勝負の結果を表示する
void printResult(RESULT result){

    if (result == RESULT_WIN) {
        printf("You are win!\n");
    }
    else if (result == RESULT_LOSE) {
        printf("Yor are loser・・・\n");
    }
    else if (result == RESULT_DRAW) {
        printf("DRAW\n");
    }
}

int main(void){

int x, y;
RESULT result = RESULT_NONE;
TURN turn = TURN_PLAYER;

//初期表示
init();

printBoard();

do {

     // ①⚪︎×を記入する位置を決める関数の呼び出し
    decidePosition(&x, &y, turn);

    // ②○× を記入する関数・・・scanf
    writeMark(x, y , turn);

     // ③3x3のマスを表示する関数
    printBoard();

    // ④勝敗判定関数
    result = checkWin(turn);

    //⑤ターンを進める関数
    turn = nextTurn(turn);

    } while (result == RESULT_NONE);

    //⑦勝負の結果を表示する
    printResult(result);

}

