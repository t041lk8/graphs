/***---------------------------------------****
****---------------���� ����---------------****
****---------------------------------------****
* Project Type : Win32 Console Application    *
* Project Name : SAOD_1.CPP                   *
* Language     : CPP, MSVS ver 2015 and above *
* Programmers  : Zhbanov I.A. Shorkin D.V.    *
* Modified By  : Zhbanov I.A.                 *
* Created      : 02/11/2021                   *
* Last Revision: 16/11/2021                   *
* --------------------------------------------*
* Comment      : ������ ������������ ������   *
****------------------------------------------*/
#include <iostream>
#include <iomanip>
using namespace std;
const int INF = 100;  //�������������
const int SIZE = 10;   //���������� ������

int adjacency_matrix[SIZE][SIZE] =     //������� ��������� ���������������� �����
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

int not_orient_adjacency_matrix[SIZE][SIZE] =  //������� ��������� ������������������ �����
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

void PrintMiddleOfTable(); //������� ������ ����� ����� ������� �������
void PrintTopOfTable();    //������� ������ ����� �������
void PrintBottomOfTable(); //������� ������ ��� �������
void PrintMatrix(int(&matrix)[SIZE][SIZE]); //������� ������ �������
void FloydWarshall(int(&Shortest)[SIZE][SIZE], int(&Pred)[SIZE][SIZE]);  //�������� ������-��������
void FindPath(int u, int v, int Pred[SIZE][SIZE]); //������� ������ ����������� ����
void Prim(); //�������� �����

int main() {
    setlocale(LC_ALL, "RUS");
    int Shortest[SIZE][SIZE], Pred[SIZE][SIZE];      //������� ���������� ���������� � �������
    for (int u = 0; u < SIZE; u++) 
    {
        for (int v = 0; v < SIZE; v++) 
        {
            Shortest[u][v] = adjacency_matrix[u][v]; //���������� ���������� ���������� ��� ��� ����� �� ������� ���������
            if (adjacency_matrix[u][v] < INF)        //���� ��� ����� ������ �������������
                Pred[u][v] = u;   //������� ������� � ������� �������
            else
                Pred[u][v] = -10; //����� ������ ������ ������ ��������
        }//for
    }//for
    cout << "\t�������� ������:";
    cout << "\n������� ���������:\n"; PrintMatrix(Shortest);  //������� ������� ���������
    cout << "\n������� Pred:\n"; PrintMatrix(Pred);           //������� ������� �������
    cout << '*' << setw(50) << setfill('-') << '*' << endl;
    FloydWarshall(Shortest, Pred);  //��������� �������� ������-��������
    cout << "������� ��������� � �������� ������� ��� ���������� ����������� ����: ";
    int u, v; //������� ��� ������ ����������� ����
    cin >> u >> v;
    if (Pred[u][v] > -10 && u != v) //���� ������ ������� �� ����� �������� � ������� �� ���������
    {
        cout << "���� �� " << u << " � " << v << ": " << u;
        FindPath(u, v, Pred); //���� ���������� �������
    }//if
    else
        cout << "���� �� ������!";
    cout << endl << '*' << setw(50) << setfill('-') << '*' << endl;
    Prim(); //��������� �������� �����
    return 0;
}

void FloydWarshall(int(&Shortest)[SIZE][SIZE], int(&Pred)[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) {
        for (int u = 0; u < SIZE; u++) {
            for (int v = 0; v < SIZE; v++) {
                if (Shortest[u][i] + Shortest[i][v] < Shortest[u][v])  //���� ����� ���� ����� ��������� ������ �������
                {
                    Shortest[u][v] = Shortest[u][i] + Shortest[i][v];  //������� ����� ����������
                    Pred[u][v] = Pred[i][v];  //���������� ������ ������
                    cout << "\n������� Shortest:\n"; PrintMatrix(Shortest);  //������� ������� ���������� ����������
                    cout << "\n������� Pred:\n"; PrintMatrix(Pred);          //������� ������� �������
                    cout << '*' << setw(50) << setfill('-') << '*' << endl;
                }//if
            }//for
        }//for
    }//for
}//FloydWarshall

void FindPath(int u, int v, int Pred[SIZE][SIZE]) 
{
    int temp = Pred[u][v];  //������� ������ �� ���� ��������
    if (temp != u) FindPath(u, temp, Pred); //���� �� ����� ������ �������, �� ��������� ����� ��� � ����� ��������
    cout << " -> " << v;
}//FindPath

void Prim() 
{
    int weight = 0; //��� ��������� ������
    int edges = 0;       //���-�� ���������� ������
    bool selected[SIZE]; //������ ���������� ������
    memset(selected, false, sizeof(selected));
    selected[0] = true;  //�������� ������� ������� ��� ����������
    int row, column;     //������ � �������
    cout << "������ �������� ������!\n";
    cout << "����" << " : " << "���";
    cout << endl;
    while (edges < SIZE - 1) //���� �� �������� ��� �������
    {
        int min = INF; //�� ������� ����� �������������
        row = 0;    //�������� ����� ������
        column = 0; //�������� ����� �������
        for (int i = 0; i < SIZE; i++) 
        {
            if (selected[i]) //���� ������� ��� ����������
            {
                for (int j = 0; j < SIZE; j++)
                {
                    if (!selected[j] && not_orient_adjacency_matrix[i][j]) //���� ������� �� �������� � ��� ����� ������ ����
                    {
                        if (min > not_orient_adjacency_matrix[i][j])  //���� ������� ������ ���� �����
                        {
                            min = not_orient_adjacency_matrix[i][j];  //���������� ����� �������
                            row = i; column = j; //��������� ������ ������ � �������
                        }//if
                    }//if
                }//for
            }//if
        }//for
        cout << row << " - " << column << " :  " << not_orient_adjacency_matrix[row][column];
        weight += not_orient_adjacency_matrix[row][column];
        cout << endl;
        selected[column] = true;  //�������� ������� ��� ����������
        edges++; //����������� ������� ���������� ������
    }//while
    cout << "��� ��������� ������ = " << weight << endl;
}//Prim

void PrintMatrix(int(&matrix)[SIZE][SIZE]) 
{
    PrintTopOfTable();  //�������� ������ �������
    for (int i = 0; i < SIZE; i++) 
    {
        cout << char(186) << setw(4) << setfill(' ') << i;
        for (int j = 0; j < SIZE; j++) 
        {
            cout << char(186) << setw(4) << setfill(' ');
            (matrix[i][j] == INF) ? cout << "oo" : (matrix[i][j] < 0) ? cout << "NULL" : cout << matrix[i][j]; //������� �������� �������
        }//for
        cout << char(186) << endl;
        (i < SIZE - 1) ? PrintMiddleOfTable() : PrintBottomOfTable();  //� ����������� �� ������� ������� ����� ��� ��� �������
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