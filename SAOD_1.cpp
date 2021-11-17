/***---------------------------------------****
****---------------Курс САОД---------------****
****---------------------------------------****
* Project Type : Win32 Console Application    *
* Project Name : SAOD_1.CPP                   *
* Language     : CPP, MSVS ver 2015 and above *
* Programmers  : Zhbanov I.A. Shorkin D.V.    *
* Modified By  : Zhbanov I.A.                 *
* Created      : 02/11/2021                   *
* Last Revision: 16/11/2021                   *
* --------------------------------------------*
* Comment      : Первая лабораторная работа   *
****------------------------------------------*/
#include <iostream>
#include <iomanip>
using namespace std;
const int INF = 100;  //бесконечность
const int SIZE = 10;   //количество вершин

int adjacency_matrix[SIZE][SIZE] =     //матрица смежности ориентированного графа
{
    INF, 3, INF, INF, INF, INF, INF, INF, INF, INF,
    INF, INF, INF, INF, 2, INF, 1, INF, INF, INF,
    INF, 2, INF, 2, INF, INF, INF, INF, INF, INF,
    INF, INF, INF, INF, 1, INF, INF, INF, INF, INF,
    INF, INF, INF, INF, INF, 3, INF, INF, INF, INF,
    INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,
    INF, INF, INF, INF, INF, 4, INF, INF, INF, 7,
    INF, INF, INF, INF, INF, INF, 1, INF, INF, INF,
    INF, INF, INF, INF, INF, INF, INF, 1, INF, 4,
    5, INF, INF, INF, INF, INF, INF, INF, INF, INF,
}; //adjacency_matrix

int not_orient_adjacency_matrix[SIZE][SIZE] =  //матрица смежности неориентированного графа
{
    INF, 3, INF, INF, INF, INF, INF, INF, INF, 5,
    3, INF, 2, INF, 2, INF, 1, INF, INF, INF,
    INF, 2, INF, 2, INF, INF, INF, INF, INF, INF,
    INF, INF, 2, INF, 1, INF, INF, INF, INF, INF,
    INF, 2, INF, 1, INF, 3, INF, INF, INF, INF,
    INF, INF, INF, INF, 3, INF, 4, INF, INF, INF,
    INF, 1, INF, INF, INF, 4, INF, 1, INF, 7,
    INF, INF, INF, INF, INF, INF, 1, INF, 1, INF,
    INF, INF, INF, INF, INF, INF, INF, 1, INF, 4,
    5, INF, INF, INF, INF, INF, 7, INF, 4, INF,
}; //not_orient_adjacency_matrix

void PrintMiddleOfTable(); //функция печати линии между строчек таблицы
void PrintTopOfTable();    //функция печати шапки таблицы
void PrintBottomOfTable(); //функция печати дна таблицы
void PrintMatrix(int(&matrix)[SIZE][SIZE]); //функция печати матрицы
void FloydWarshall(int(&Shortest)[SIZE][SIZE], int(&Pred)[SIZE][SIZE]);  //алгоритм Флойда-Уоршелла
void FindPath(int u, int v, int Pred[SIZE][SIZE]); //функция поиска кратчайшего пути
void Prim(); //алгоритм Прима

int main() {
    setlocale(LC_ALL, "RUS");
    int Shortest[SIZE][SIZE], Pred[SIZE][SIZE];      //матрицы кратчайших расстояний и предков
    for (int u = 0; u < SIZE; u++) 
    {
        for (int v = 0; v < SIZE; v++) 
        {
            Shortest[u][v] = adjacency_matrix[u][v]; //изначально кратчайшее расстояние это вес ребра из матрицы смежности
            if (adjacency_matrix[u][v] < INF)        //если вес ребра меньше бесконечности
                Pred[u][v] = u;   //заносим вершину в таблицу предков
            else
                Pred[u][v] = -10; //иначе вместо предка делаем заглушку
        }//for
    }//for
    cout << "\tИсходные данные:";
    cout << "\nТаблица смежности:\n"; PrintMatrix(Shortest);  //выводим матрицу смежности
    cout << "\nТаблица Pred:\n"; PrintMatrix(Pred);           //выводим матрицу предков
    cout << '*' << setw(50) << setfill('-') << '*' << endl;
    FloydWarshall(Shortest, Pred);  //выполняем алгоритм Флойда-Уоршелла
    cout << "Введите начальную и конечную вершины для нахождения кратчайшего пути: ";
    int u, v; //вершины для поиска кратчайшего пути
    cin >> u >> v;
    if (Pred[u][v] > -10 && u != v) //если вместо впредка не стоит заглушка и вершины не совпадают
    {
        cout << "Путь из " << u << " в " << v << ": " << u;
        FindPath(u, v, Pred); //ищем кратчайший маршрут
    }//if
    else
        cout << "Путь не найден!";
    cout << endl << '*' << setw(50) << setfill('-') << '*' << endl;
    Prim(); //выполняем алгоритм Прима
    return 0;
}

void FloydWarshall(int(&Shortest)[SIZE][SIZE], int(&Pred)[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) {
        for (int u = 0; u < SIZE; u++) {
            for (int v = 0; v < SIZE; v++) {
                if (Shortest[u][i] + Shortest[i][v] < Shortest[u][v])  //если новый путь между вершинами короче старого
                {
                    Shortest[u][v] = Shortest[u][i] + Shortest[i][v];  //считаем новое расстояние
                    Pred[u][v] = Pred[i][v];  //записываем нового предка
                    cout << "\nТаблица Shortest:\n"; PrintMatrix(Shortest);  //выводим таблицу кратчайших расстояний
                    cout << "\nТаблица Pred:\n"; PrintMatrix(Pred);          //выводим таблицу предков
                    cout << '*' << setw(50) << setfill('-') << '*' << endl;
                }//if
            }//for
        }//for
    }//for
}//FloydWarshall

void FindPath(int u, int v, int Pred[SIZE][SIZE]) 
{
    int temp = Pred[u][v];  //находим предка по двум вершинам
    if (temp != u) FindPath(u, temp, Pred); //если не нашли нужную вершину, то запускаем поиск уже с новой вершиной
    cout << " -> " << v;
}//FindPath

void Prim() 
{
    int weight = 0; //вес остовного дерева
    int edges = 0;       //кол-во посещенных вершин
    bool selected[SIZE]; //массив посещенных вершин
    memset(selected, false, sizeof(selected));
    selected[0] = true;  //отмечаем нулевую вершину как посещенную
    int row, column;     //строка и столбец
    cout << "Строим остовное дерево!\n";
    cout << "Путь" << " : " << "Вес";
    cout << endl;
    while (edges < SIZE - 1) //пока не посетили все вершины
    {
        int min = INF; //за минимум берем бесконечность
        row = 0;    //обнуляем номер строки
        column = 0; //обнуляем номер столбца
        for (int i = 0; i < SIZE; i++) 
        {
            if (selected[i]) //если вершина уже посещенная
            {
                for (int j = 0; j < SIZE; j++)
                {
                    if (!selected[j] && not_orient_adjacency_matrix[i][j]) //если вершина не посещена и вес ребра больше нуля
                    {
                        if (min > not_orient_adjacency_matrix[i][j])  //если минимум больше веса ребра
                        {
                            min = not_orient_adjacency_matrix[i][j];  //запоминаем новый минимум
                            row = i; column = j; //обновляем номера строки и столбца
                        }//if
                    }//if
                }//for
            }//if
        }//for
        cout << row << " - " << column << " :  " << not_orient_adjacency_matrix[row][column];
        weight += not_orient_adjacency_matrix[row][column];
        cout << endl;
        selected[column] = true;  //отмечаем вершину как посещенную
        edges++; //увеличиваем счетчик посещенных вершин
    }//while
    cout << "Вес остовного дерева = " << weight << endl;
}//Prim

void PrintMatrix(int(&matrix)[SIZE][SIZE]) 
{
    PrintTopOfTable();  //печатаем шапкку таблицы
    for (int i = 0; i < SIZE; i++) 
    {
        cout << char(186) << setw(4) << setfill(' ') << i;
        for (int j = 0; j < SIZE; j++) 
        {
            cout << char(186) << setw(4) << setfill(' ');
            (matrix[i][j] == INF) ? cout << "oo" : (matrix[i][j] < 0) ? cout << "NULL" : cout << matrix[i][j]; //выводим значение матрицы
        }//for
        cout << char(186) << endl;
        (i < SIZE - 1) ? PrintMiddleOfTable() : PrintBottomOfTable();  //в зависимости от строчки выводим линию или дно таблицы
    }//for
}//PrintMatrix

void PrintBottomOfTable() 
{
    cout << char(200) << setw(5) << setfill(char(205)) << char(202);
    for (int i = 0; i < SIZE; i++) 
    {
        cout << setw(5) << setfill(char(205));
        (i < SIZE - 1) ? cout << char(202) : cout << char(188);
    }//for
    cout << endl;
    setlocale(LC_ALL, "RUS");
}//PrintBottomOfTable

void PrintTopOfTable() 
{
    setlocale(0, "C");
    cout << char(201) << setw(5) << setfill(char(205)) << char(203);
    for (int i = 0; i < SIZE; i++) 
    {
        cout << setw(5) << setfill(char(205));
        (i < SIZE - 1) ? cout << char(203) : cout << char(187);
    }//for
    cout << endl << char(186) << setw(5) << setfill(' ');
    for (int i = 0; i < SIZE; i++) 
    {
        cout << char(186) << setw(4) << setfill(' ') << i;
    }//for
    cout << char(186) << endl;
    PrintMiddleOfTable();
}//PrintTopOfTable

void PrintMiddleOfTable() 
{
    cout << char(204);
    for (int i = 0; i < SIZE + 1; i++) 
    {
        cout << setw(5) << setfill(char(205));
        (i < SIZE) ? cout << char(206) : cout << char(185);
    }//for
    cout << endl;
}//PrintMiddleOfTable
/*--------End of SAOD_1.CPP file---------- */