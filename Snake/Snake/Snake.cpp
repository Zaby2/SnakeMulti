
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;




void hide_cursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}
int score1;
int score2;
class Map {
public:
    char map[30][30];
    int curRow;
    int curCol;
void clear(int row, int col) {
    SetCursor(NULL);
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 || i == row - 1) {
                map[i][j] = '#';
            } 
            else if (j == 0 || j == col - 1 ) {
                map[i][j] = '#';
            }
            else if (map[i][j] == '*' || map[i][j] == '"') {

            }
            else {
                map[i][j] = ' ';
            }            
        }
    }
}
void randomFoodGeneration(int maxRow, int maxCol, char (&curp)[30][30]) {
    int x = 0, y = 0;
    int k = 0;
    int k2 = 0;
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            if (curp[i][j] == ' ') {
                k++;
            }
        }
    }
    if (k >= 4) {
        do {           
            x = (rand() % (maxRow - 2)) + 1;
            y = (rand() % (maxCol - 2)) + 1;
        } while (curp[x][y] != ' ' );
        curp[x][y] = '*';
    }
    else {
        for (int i = 0; i < maxRow; i++) {
            for (int j = 0; j < maxCol; j++) {
                if (curp[i][j] == ' ' && k2 == 0) {
                    curp[i][j] = '*';
                    k2++;
                }
            }
        }
    }
 
    
}
void show(int row, int col, int user) {
    printStuff();
    //map[row][col] = '\0';
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");      
    }
    if (user == 0) {
        printf("Score = %d", score1);
    }
    else {
        printf("Score1 = %d\n", score1);
        printf("Score2 = %d", score2);
    }
    
}
void printStuff() {
   Sleep(95);
    HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cd;
    cd.X = 0;
    cd.Y = 0;
    SetConsoleCursorPosition(hd, cd);
}
};
bool fl = false;
struct TAIL {
    int x, y;
};
class Snake {
public:
    int dir = 0;
    int row, col;
    TAIL tail[1000];
    Map mp = Map();
void putOnMap(int row, int col, char(&curMap)[30][30], int *len, int user) {
    if (user == 0) {
        curMap[row][col] = '@';
    }
    else if (user == 1) {
        curMap[row][col] = '$';
    }
    else if (user == 2) {
        curMap[row][col] = '%';
    }
       
        for (int i = 0; i < *len; i++) {
            curMap[tail[i].x][tail[i].y] = '+';
        }    
}
void control(char w, char s, char a, char d, int *row, int *col, int curRow,int curCol, char(&curMap)[30][30], int *len, int *code, int player) {
    int fl2 = 0;
    TAIL oldPos;
    oldPos.x = *row;
    oldPos.y = *col;
    //if (player == 1) {
    //    dir = 4;
    //}
   // if (player == 2) {
   //     dir = 2;
   // }
    if (GetAsyncKeyState(w) != 0) { dir = 1; fl2++; }
    if (GetAsyncKeyState(a) != 0) { dir = 2; fl2++;}
    if (GetAsyncKeyState(s) != 0) { dir = 3; fl2++; }
    if (GetAsyncKeyState(d) != 0) { dir = 4; fl2++; }
    if (dir == 1) { (*row) -= 1; }
    if (dir == 2) { (*col) -= 1; }
    if (dir == 3) { (*row) += 1; }
    if (dir == 4) { (*col) += 1; }
    if (fl2 == 1 && *len == 0) {
        *len = 1;
    }
    if (player == 1) {
        if (curMap[*row][*col] == '%') {
            *code = 6;
            return;
        }
    }
    if (player == 2) {
        if (curMap[*row][*col] == '$') {
            *code = 6;
            return;
        }
    }
    if ((*row <= 0 || *row >= curRow-1) || (*col <= 0 || *col >= curCol-1) || (curMap[*row][*col] == '+') || (curMap[*row][*col] == '"')) {
        if (player == 1) {
            *code = 3;
            return;
        }
        else if (player == 2 && *code!=0) {
            if (curMap[*row][*col] == '+') {
                *code = 6;
            }
            else {
                 *code = 5;
            }
           
            return;
        }
        else if (player == 2) {
                *code = 4;
                return;
        }
        else if (player == 0) {
            *code = 1;
            return;
        }
      
    }
    if (curMap[*row][*col] == '*') {
        addTail(oldPos.x, oldPos.y, len);
        if (player == 0 || player == 1) {
            score1++;
        }
        else {
            score2++;
        }
        mp.randomFoodGeneration(curRow, curCol, curMap);
    }
    else {      
        moveTail(oldPos.x, oldPos.y, len);     
    }      
}
void moveTail(int x, int y, int * len) {  
     for (int i = ( * len) - 1; i >= 0; i--) {
        tail[i + 1] = tail[i];
    }
    tail[0].x = x;
    tail[0].y = y;    
}
void addTail(int x, int y, int *len) {
    moveTail(x, y, len);
    (* len)++;
    if ((*len) >= 1000) {
        *len = 999;
    }
}
void check(char(&curMap)[30][30], int row, int col, int *code) {
    int check = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (curMap[i][j] == ' ' || curMap[i][j] == '*') {
                check += 1;
            }
        }
    }
    if (check == 0) {
        *code = 2;
    }
}
};
class MainMenu {
public:
    int key;
    int k = 0;
    int num = 0;
    Map mp = Map();
    int code = 0;  
    int row = 3;
    int col = 3;
    TAIL block[5];
    void mainMenu() {
        key = 15;
        num = 1;
        // printf("key = %d", key);
        system("cls");
        do {
            if (key == 13) {
                if (num == 1) {
                   // code = 0;
                    fl = false;
                    start(row+2, col+2, 1);
                    //key = 15;
                    system("cls");
                }
                if (num == 2) {
                    fl = false;
                    start(row+2, col+2, 2);
                    //key = 15;
                    system("cls");
                }
                if (num == 3) {                   
                    do {
                        input(&row, 1);
                    } while (row < 3 || row > 20);
                    do {
                        input(&col, 2);
                    } while (col < 3 || col > 20);
                    cleanBlock(mp.map, row+2, col+2);
                }
           
            if (num == 4) {
                k = 0;
               constructor(mp.map, row+2, col+2);
               for (int i = 0; i < 5;i++) {
                   block[i].x = 0;
                   block[i].y = 0;
               }
               for (int i = 0; i < row + 2; i++) {
                   for (int j = 0; j < col + 2; j++) {
                       if (mp.map[i][j] == '"') {
                           block[k].x = i;
                           block[k].y = j;
                           k++;
                       }
                   }
                }
              
;            }
            if (num == 5) {
                cleanBlock(mp.map, row+2, col+2);
            }
            if (num == 6) {
                exit(0);
            } 
            }
            if (code == 1) {
                printf("Вы проиграли Score = %d\n", score1);
                system("pause");
                code = 0;
                system("cls");
            }
            if (code == 2) {
                printf("Вы победили Score = %d\n", score1);
                system("pause");
                code = 0;
                system("cls");
            }
            if (code == 3) {
              
                printf("Победил игрок, управляющий стрелочками Score1 = %d Score2 = %d\n", score1, score2);
                system("pause");
                code = 0;
                system("cls");
            }
            if (code == 4) {
                printf("Победил игрок, управляющий клавишами Score1 = %d Score2 = %d\n", score1, score2);;
                system("pause");
                code = 0;
                system("cls");
            }
            if (code == 5) {
                if (score1 > score2) {
                    printf("Победил игрок, управляющий клавишами Score1 = %d Score2 = %d\n", score1, score2);
                    system("pause");
                    code = 0;
                    system("cls");
                }
                else if (score1 < score2) {
                    printf("Победил игрок, управляющий стрелочками Score1 = %d Score2 = %d\n", score1, score2);
                    system("pause");
                    code = 0;
                    system("cls");
                }
                else {
                    printf("Ничья Score1 = %d Score2 = %d\n", score1, score2);
                    system("pause");
                    code = 0;
                    system("cls");
                }
             }
            if (key >= 49 and key <= 54) {
                printf("1) Начать игру (1 игрок)");
                if (key == 49) {
                    printf(" <-");
                    num = 1;
                }
                printf("\n2) Начать игру (2 игрока)");;
                if (key == 50) {
                    printf(" <-");
                    num = 2;
                }
                printf("\n3) Ввести размеры поля %d x %d", row, col);
                if (key == 51) {
                    printf(" <-");
                    num = 3;
                }
                printf("\n4) Установить стенки на поле");
                if (key == 52) {
                    printf(" <-");
                    num = 4;
                }
                printf("\n4) Удалить стенки с поля");
                if (key == 53) {
                    printf(" <-");
                    num = 5;
                }
                printf("\n5) Выход");
                if (key == 54) {
                    printf(" <-");
                    num = 6;
                }
                printf("\nДля выбора нажмите ENTER\n");
            }
            if (key == 0 or key == 224)
            {
                switch (_getch())
                {
                case 72:
                    num -= 1;
                    if (num < 1) {
                        num = 6;
                    }
                    break;

                case 80:
                    num += 1;
                    if (num > 6) {
                        num = 1;
                    }
                    break;
                }
                printf("1) Начать игру (1 игрок)");
                if (num == 1) {
                    printf(" <-");
                }
                printf("\n2) Начать игру (2 игрока)");;
                if (num == 2) {
                    printf(" <-");
                }
                printf("\n3) Ввести размеры поля %d x %d", row, col);
                if (num == 3) {
                    printf(" <-");
                }
                printf("\n4) Установить стенки на поле");
                if (num == 4) {
                    printf(" <-");
                }
                printf("\n4) Удалить стенки с поля");
                if (num == 5) {
                    printf(" <-");
                    
                }
                printf("\n5) Выход");
                if (num == 6) {
                    printf(" <-");
                   
                }
                printf("\nДля выбора нажмите ENTER\n");
            }

            if ((key < 49 or key > 53) and (key != 80 or key != 72) and key != 224 and key != 0) {
                key = 15;
            }
            if (key == 15) {
                printf("1) Начать игру (1 игрок)");
                if (num == 1) {
                    printf(" <-");
                }
                printf("\n2) Начать игру (2 игрока)");;
                if (num == 2) {
                    printf(" <-");
                }
                printf("\n3) Ввести размеры поля %d x %d", row, col);
                if (num == 3) {
                    printf(" <-");
                }
                printf("\n4) Установить стенки на поле");
                if (num == 4) {
                    printf(" <-");
                }
                printf("\n4) Удалить стенки с поля");
                if (num == 5) {
                    printf(" <-");

                }
                printf("\n5) Выход");
                if (num == 6) {
                    printf(" <-");

                }
                printf("\nДля выбора нажмите ENTER\n");

            }
           
            key = _getch();
            system("cls");
           
        } while (true);
    }
    void start(int row, int col, int userNum) {
        clean(mp.map, row, col);
        blockInint(mp.map);
        system("cls");
        score1 = 1;
        score2 = 1;
        //Map mp = Map();
        Snake snake1 = Snake();
        Snake snake2 = Snake();
        snake1.row = 2;
        snake1.col = 1;
        snake2.row = 2;
        snake2.col = col - 2;
        int user = userNum;
        int playerNum;
        int len1 = 0;
        int len2 = 0;
        system("pause");
        GetAsyncKeyState('W');
        GetAsyncKeyState('A');
        GetAsyncKeyState('S');
        GetAsyncKeyState('D');
        GetAsyncKeyState(VK_UP);
        GetAsyncKeyState(VK_DOWN);
        GetAsyncKeyState(VK_LEFT);
        GetAsyncKeyState(VK_RIGHT);
        system("cls");
        while (true) {
            Sleep(400);
             
            if (code != 0) {
                if (code == 2 && user == 2) {
                    code = 5;
                    return;

                }
                else {
                    return;
                }
                
            }
            if (user == 1) {
                snake1.control('W', 'S', 'A', 'D', &snake1.row, &snake1.col, row, col, mp.map, &len1,&code, 0 );
            }
            
            if (user == 2) {
                snake1.control('W', 'S', 'A', 'D', &snake1.row, &snake1.col, row, col, mp.map, &len1, &code, 1);
                snake2.control(VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, &snake2.row, &snake2.col, row, col, mp.map, &len2, &code,2);
            }
            if (code == 6) {
                code = 5;
                if (code == 2 && user == 2) {
                    code = 5;
                    return;

                }
                else {
                    return;
                }

            }
            mp.clear(row, col);
            if (user == 1) {
                snake1.putOnMap(snake1.row, snake1.col, mp.map, &len1, 0);
                mp.show(row, col, 0);
            }
            
            if (user == 2) {
                snake1.putOnMap(snake1.row, snake1.col, mp.map, &len1, 1);
                snake2.putOnMap(snake2.row, snake2.col, mp.map, &len2, 2);
                mp.show(row, col,2);
            }
            if (fl == false) {
                for (int i = 0; i < 4; i++) {
                    mp.randomFoodGeneration(row, col, mp.map);
                }
                fl = true;
                
            }
            snake1.check(mp.map, row, col, &code);
        }
    }
    void input(int* input, int cur) {
        int key1 = 0;
        int  len = 0;
        *input = 0;
        while (key1 != 13) {
            if (key1 == 8 and len != 0) {
                *input = *input / 10;
                len -= 1;
            }
            if (key1 >= 48 and key1 <= 57 and len < 2) {
                *input = *input * 10 + (key1 - 48);
                len += 1;
                printf("Число%d = %d", cur, *input);
            }
            else {
                printf("Число%d = %d", cur, *input);
            }
            key1 = _getch();
            system("cls");
        }     
    }
    void constructor(char(&curMap)[30][30], int row, int col) {
        int x = 3, y = 3;
        int key2 = 5;
        int count = 0;
        
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (i == 0 || i == row - 1) {
                    curMap[i][j] = '#';
                }
                else if (j == 0 || j == col - 1) {
                    curMap[i][j] = '#';
                }
                else if (curMap[i][j] != '"') {
                    curMap[i][j] = ' ';
                }
                else if (curMap[i][j] == '"') {
                    count++;
                }
            }
        }
        do {
            printf("Для установки стена нажмите Enter\n");
            printf("Чтобы убрать стену наведитесь на нее и повторно нажмите Enter\n");
            printf("Чтобы выйти в меню нажмите Escape \n");
            
            if ((key2 == 0 or key2 == 224))
            {
                switch (_getch())
                {
                case 72:
                    x -= 1;
                    if (x <= 0) {
                        x = row - 2;
                    }
                    break;

                case 80:
                    x += 1;
                    if (x > row - 2) {
                        x = 1;
                    }
                    break;
                case 75:
                    y -= 1;
                    if (y <= 0) {
                        y = col - 2;
                    }
                    break;
                case 77:
                    y += 1;
                    if (y > col - 2) {
                        y = 1;
                    }
                    break;
                }
            }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {   
                if(i != x || j != y)
                    printf("%c ",curMap[i][j]);

                if (i == x && j == y) {
                    printf("%c ", '"');
                }
                
            }
            printf("\n");
        }
        if (key2 == 13) { 
            if (curMap[x][y] == '"') {
                curMap[x][y] = ' ';
                count--;
            }
            else if (count < 5) {
                    if ((x != 2 || y != 1) && (x != 2 || y != col - 2)) {                      
                            curMap[x][y] = '"';
                            count++;                        
                    }
                    else {
                        printf("Сюда нельзя ставить стену");
                    }
                }
            
        }
        key2 = _getch();
        system("cls");
        } while (key2 != 27);
    }
    void blockInint(char(&curMap)[30][30]) {
        for (int i = 0; i < 5; i++) {
            curMap[block[i].x][block[i].y] = '"';
        }
    }
    void clean(char(&curMap)[30][30], int row, int col) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (curMap[i][j] != '"') {
                    
                    curMap[i][j] = ' ';
                }
            }
        }
    }
    void cleanBlock(char(&curMap)[30][30], int row, int col) {
        for (int i = 0; i < 5; i++) {
            block[i].x = 0;
            block[i].y = 0;
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (curMap[i][j] == '"') {
                    curMap[i][j] = ' ';
                }
            }
        }
    }
    
};

int main() {
    setlocale(LC_ALL, "Russian");
    hide_cursor();
    MainMenu mn = MainMenu();
    mn.mainMenu();
}