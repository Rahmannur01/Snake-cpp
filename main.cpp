#include <iostream>
#include "snake.cpp"

using namespace std;

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}

int main(){
    srand(static_cast<unsigned int>(time(0))); 

    Snake snake(40,20);
    hideCursor();

    bool running = true;
    while (running) {
        snake.MoveToDirection();
        snake.draw();

        if (_kbhit()) {
            char c = _getch();
            if (c == 'q') running = false;
            if (c == 'w') snake.SetDirection(UP);
            if (c == 's') snake.SetDirection(DOWN);
            if (c == 'a') snake.SetDirection(LEFT);
            if (c == 'd') snake.SetDirection(RIGHT);
        }
        if(snake.GetDirection() == UP || snake.GetDirection() == DOWN) Sleep(120);
        else Sleep(60);

        if(snake.IsDie()){
            cout<<"[!] Game Over"<<endl;
            running = false;
        }
    }

    system("pause");

    return 0;
}
