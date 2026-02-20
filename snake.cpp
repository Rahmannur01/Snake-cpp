#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <vector>

using namespace std;

enum Direction {UP, DOWN, RIGHT, LEFT};

class Pos{
public:
    Pos(){
        this->x = 0;
        this->y = 0;
    }
    Pos(int x, int y){
        this->x = x;
        this->y = y;
    }

    int x,y;
};

class Eat{
    public:
        Pos pos;
        Eat(){
            alive = false;
        }
        Eat(Pos pos){
            this->pos = pos;
            this->alive = false;
        }
        Eat(int x, int y){
            this->pos.x = x;
            this->pos.y = y;
            this->alive = false;
        }

        bool alive;
};

class Snake {
    Pos pos;
    Eat eat;
    vector<Pos> tails;
    Direction direction = RIGHT;

    int borderHeight, borderWidth;
    int score;
public:
    Snake(int borderWidth, int borderHeight) {
        pos.x = borderWidth/2;
        pos.y = borderHeight/2;
        this->borderWidth = borderWidth;
        this->borderHeight = borderHeight;

        this->score = 0;

        this->SetRandPosEat();
    }

    void draw(){
        setCursor(0,0); // переместили курсор в начало
        for(int i = 0; i < borderHeight; i++){
            for(int j = 0; j < borderWidth; j++){
                if(i == pos.y && j == pos.x)
                    cout<<"o";
                else if(this->IsTailPoint(j,i)){
                    cout<<"o";
                }
                else if(i == this->eat.pos.y && j == this->eat.pos.x){
                    cout<<"+";
                }
                else if(i==0 || i==borderHeight-1 || j==0 || j==borderWidth-1)
                    cout<<".";
                else
                    cout<<" ";
            }
            cout<<"\n";
        }

        cout<<"\nScore: "<<this->score<<endl;
    }

    void MoveTo(int dx, int dy){
        for(int i = this->tails.size()-1; i >= 0; --i){
            if(i == 0){
                this->tails[i].x = this->pos.x;
                this->tails[i].y = this->pos.y;
            }else{
                this->tails[i].x = tails[i-1].x;
                this->tails[i].y = tails[i-1].y;
            }
        }
        this->pos.x += dx;
        this->pos.y += dy;
    }

    void MoveToDirection(){
        switch (this->direction)
        {
        case UP:
            this->MoveTo(0,-1);
            break;
        case DOWN:
            this->MoveTo(0,1);
            break;
        case RIGHT:
            this->MoveTo(1,0);
            break;
        case LEFT:
            this->MoveTo(-1,0);
            break;
        default:
            break;
        }

        if(this->IsEatTouch()){
            Pos pos_t = this->pos;
            if(this->tails.size() > 0){
                int size = this->tails.size();
                pos_t.x = this->tails[size-1].x;
                pos_t.y = this->tails[size-1].y;
            }
            this->tails.push_back(pos_t);
            SetRandPosEat();

            this->score++;
        }
    }

    bool IsEatTouch(){
        if(this->pos.y == this->eat.pos.y && this->pos.x == this->eat.pos.x){
            return true;
        }
        return false;
    }

    void SetRandPosEat(){
        int eatX, eatY;
        do {
            eatX = 1 + rand() % (borderWidth - 2);
            eatY = 1 + rand() % (borderHeight - 2);
        } while (IsTailPoint(eatX, eatY) || (eatX == pos.x && eatY == pos.y));
        this->eat.pos.x = eatX;
        this->eat.pos.y = eatY;
    }

    bool IsTailPoint(int x, int y){
        for(int i = 0; i < this->tails.size(); i++){
            if(x == tails[i].x && y == tails[i].y){
                return true;
            }
        }
        return false;
    }
    bool IsDie(){
        if(this->pos.x == this->borderWidth || this->pos.x == 0 || this->pos.y == this->borderHeight || this->pos.y == 0){
            return true;
        }
        for(int i = 1; i < this->tails.size(); i++){
            if(this->pos.x == this->tails[i].x && this->pos.y == this->tails[i].y){
                return true;
            }
        }

        return false;
    }

    void setCursor(int x, int y){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hConsole, pos);
    }

    void SetDirection(Direction direction){
        if(this->tails.size() > 0){
            if((direction == UP && this->direction == DOWN) || (direction == DOWN && this->direction == UP)) return;
            if((direction == LEFT && this->direction == RIGHT) || (direction == RIGHT && this->direction == LEFT)) return;
        }

        this->direction = direction;
    }
    Direction GetDirection(){
        return this->direction;
    }
};