
#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class Point
{
public:
    int x;
    int y;

    Point() { x = 0; y = 0; }
    Point(int a, int b) { x = a; y = b; }

    void Print()
    {
        cout << x << ":" << y << endl;
    }

    void operator++() { x++; y++; }
    void operator--() { x--; y--; }

    bool operator>(Point p)
    {
        return x * x + y * y > p.x * p.x + p.y * p.y;
    }
    bool operator<(Point p)
    {
        return x * x + y * y < p.x * p.x + p.y * p.y;
    }

    void operator!()
    {
        x = -x;
        y = -y;
    }
};

class Vector
{
    Point* points;
    int countPoint;

public:
    Vector()
    {
        points = nullptr;
        countPoint = 0;
    }

    Vector(const Vector& v)
    {
        countPoint = v.countPoint;
        points = new Point[countPoint];
        for (int i = 0; i < countPoint; i++)
            points[i] = v.points[i];
    }

    Vector(Vector&& v)
    {
        points = v.points;
        countPoint = v.countPoint;
        v.points = nullptr;
        v.countPoint = 0;
    }

    Vector& operator=(const Vector& v)
    {
        if (this != &v)
        {
            delete[] points;
            countPoint = v.countPoint;
            points = new Point[countPoint];
            for (int i = 0; i < countPoint; i++)
                points[i] = v.points[i];
        }
        return *this;
    }

    ~Vector()
    {
        delete[] points;
    }

    void Add(Point p)
    {
        Point* temp = new Point[countPoint + 1];
        for (int i = 0; i < countPoint; i++)
            temp[i] = points[i];
        temp[countPoint] = p;
        delete[] points;
        points = temp;
        countPoint++;
    }

    void Print()
    {
        for (int i = 0; i < countPoint; i++)
            points[i].Print();
    }

    void PrintXY()
    {
        for (int i = 0; i < countPoint; i++)
        {
            gotoxy(points[i].x, points[i].y);
            cout << "*";
        }
    }
};

int main()
{
    Point a(3, 4);
    Point b(1, 2);

    ++a;
    a.Print();
    --b;
    b.Print();

    if (a > b)
        cout << "a dali" << endl;
    else
        cout << "a blyzhche" << endl;

    !a;
    a.Print();

    Vector v;
    v.Add(Point(10, 5));
    v.Add(Point(15, 8));
    v.Add(Point(20, 3));
    v.Print();

    Vector v2 = v;
    Vector v3 = move(v2);
    Vector v4;
    v4 = v3;
    v4.Print();

    system("pause");
    system("cls");
    v.PrintXY();
    gotoxy(0, 15);
}
