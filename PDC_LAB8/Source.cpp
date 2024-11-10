#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

const int MAX_VERTICES = 100;
const int MAX_EDGES = 100;

int adjMatrix[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int dfsNumber[MAX_VERTICES];

void initGraph() {
    for (int i = 0; i < MAX_VERTICES; ++i) {
        visited[i] = false;
        dfsNumber[i] = 0;
        for (int j = 0; j < MAX_VERTICES; ++j) {
            adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1; 
}

void readGraphFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Помилка відкриття файлу." << endl;
        return;
    }

    int u, v;
    while (file >> u >> v) {
        addEdge(u, v);
    }
    file.close();
}

void depthFirstSearch(int start) {
    int stack[MAX_VERTICES];
    int top = -1;
    int counter = 0;

    stack[++top] = start;

    cout << "DFS\t       Номер\t       Вміст стеку" << endl;
    cout << "--------------------------------------------------" << endl;

    while (top >= 0) {
        int current = stack[top];

        if (!visited[current]) {
            visited[current] = true;
            dfsNumber[current] = ++counter;
            cout << current << "\t\t" << dfsNumber[current] << "\t\t";

            for (int i = 0; i <= top; ++i) {
                cout << stack[i] << " ";
            }
            cout << endl;
        }

        bool hasUnvisitedNeighbors = false;

        for (int i = MAX_VERTICES - 1; i >= 0; --i) {
            if (adjMatrix[current][i] && !visited[i]) {
                stack[++top] = i;
                hasUnvisitedNeighbors = true;
                break;
            }
        }

        if (!hasUnvisitedNeighbors) {
            --top;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    initGraph();

    string filename;
    int startVertex;

    cout << "Введіть назву файлу: ";
    cin >> filename;
    readGraphFromFile(filename);

    cout << "Введіть початкову вершину: ";
    cin >> startVertex;

    depthFirstSearch(startVertex);

    return 0;
}
