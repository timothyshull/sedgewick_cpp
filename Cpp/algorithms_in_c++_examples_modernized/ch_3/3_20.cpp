#include<cmath>
#include<iostream>
#include<cstdlib>
#include"Point.h"

using std::cin;
using std::cout;

struct Node {
    Point p;
    Node* next;

    Node(Point pt, Node* t) : p{pt}, next{t} {}
};

using Link = Node *;

static Link** grid;

static int G, cnt = 0;

static float d;

void grid_insert(float x, float y)
{
    int X = x * G + 1;
    int Y = y * G + 1;
    Point p;
    p.x = x;
    p.y = y;
    Link s;
    Link t = new Node(p, grid[X][Y]);
    for (int i = X - 1; i <= X + 1; i++) {
        for (int j = Y - 1; j <= Y + 1; j++) {
            for (s = grid[i][j]; s != 0; s = s->next) {
                if (distance(s->p, t->p) < d) { cnt++; }
            }
        }
    }
    grid[X][Y] = t;
}

int main(int argc, char* argv[])
{
    int i, N = atoi(argv[1]);
    d = atof(argv[2]);
    G = 1 / d;
    grid = malloc2d(G + 2, G + 2);
    for (i = 0; i < G + 2; i++) {
        for (int j = 0; j < G + 2; j++) {
            grid[i][j] = 0;
        }
    }
    for (i = 0; i < N; i++) {
        grid_insert(randFloat(), randFloat());
    }
    cout << cnt << " pairs within " << d << "\n";
    return 0;
}

