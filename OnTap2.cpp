#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
#define max 50
int vertex;
int degrees[max];
int parent[max];
int parent_dfs[max];
int result_dfs[max];
int ndfs = 0;

// struct_data
struct edge
{
    int x, y, w;
};

struct node
{
    edge val;
    node *link;
};

void init(node *head[], int n)
{
    for (int i = 0; i < n; i++)
        head[i] = NULL;
}

node *newNode(edge u)
{
    node *p = new node;
    p->val = u;
    p->link = NULL;
    return p;
}

void addLast(node *&head, edge data)
{
    if (head == NULL)
        head = newNode(data);
    else
    {
        node *p = head;
        while (p->link != NULL)
            p = p->link;
        p->link = newNode(data);
    }
}

void delNode(node *&head, int x)
{
    if (head != NULL)
    {
        node *p = head;
        if (p->val.y == x)
        {
            head = head->link;
            p->link = NULL;
        }
        else
        {
            node *pre_q = NULL;
            while (p != NULL && p->val.y != x)
            {
                pre_q = p;
                p = p->link;
            }
            if (p != NULL)
            {
                pre_q->link = p->link;
            }
        }
        delete p;
    }
}

// readfile

void readFile(node *head[])
{
    ifstream myFile("input2.txt");
    if (myFile.is_open())
    {
        myFile >> vertex;
        for (int i = 0; i < vertex; i++)
            myFile >> degrees[i];
        for (int i = 0; i < vertex; i++)
        {
            for (int j = 0; j < degrees[i]; j++)
            {
                edge e;
                e.x = i;
                myFile >> e.y;
                myFile >> e.w;
                addLast(head[i], e);
            }
        }
        myFile.close();
    }
}

void displayList(node *head[])
{
    for (int i = 0; i < vertex; i++)
    {
        if (head[i] != NULL)
        {
            cout << char(65 + i) << ":";
            node *p = head[i];
            while (p != NULL)
            {
                cout << p->val.y << "(" << p->val.w << ")\t";
                p = p->link;
            }
        }
        cout << endl;
    }
}

void freeMemory(node *head[], int n)
{
    for (int i = 0; i < n; i++)
    {
        node *p = head[i];
        while (p != NULL)
        {
            node *temp = p;
            p = p->link;
            delete temp;
        }
        head[i] = NULL;
    }
}

// DFS
class Stack
{
private:
    int a[max];
    int top;

public:
    Stack()
    {
        top = -1;
    }
    void push(int x)
    {
        if (top >= max - 1)
        {
            cout << "Bo nho tran, ko the them " << x << endl;
            return;
        }
        a[++top] = x;
    }
    bool isEmpty()
    {
        return top == -1;
    }
    int pop()
    {
        if (isEmpty())
        {
            cout << "Da het phan tu" << endl;
            return -1;
        }
        return a[top--];
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack rong" << endl;
            return;
        }
        cout << "Phan tu: ";
        for (int i = 0; i <= top; i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
};
vector<bool> visit(max, false);
void dfs_dequy(node *head[], int x, int y = -1)
{
    visit[x] = true;
    cout << x << " ";
    if (x == y)
        return;
    for (node *p = head[x]; p != NULL; p = p->link)
    {
        if (visit[p->val.y] == false)
        {
            parent_dfs[p->val.y] = x;
            dfs_dequy(head, p->val.y);
        }
    }
}

void dfs(node *head[], int x, int y = -1)
{
    vector<bool> visit(max, false);
    for (int i = 0; i < vertex; i++)
    {
        parent[i] = -1;
    }
    ndfs = 0;
    Stack s;
    s.push(x);
    while (!s.isEmpty())
    {
        int temp = s.pop();
        if (ndfs < vertex)
        {
            if (!visit[temp])
            {
                result_dfs[ndfs++] = temp;
                visit[temp] = true;
            }
            if (temp == y)
                break;
            node *p = head[temp];
            while (p != nullptr)
            {
                if (!visit[p->val.y])
                {
                    s.push(temp);
                    s.push(p->val.y);
                    parent[p->val.y] = temp;
                    break;
                }
                p = p->link;
            }
        }
    }
}
void display_dfs()
{
    for (int i = 0; i < ndfs; i++)
    {
        cout << result_dfs[i] << " ";
    }
    cout << endl;
}

// prim
void prim(node *head[], int x)
{
    int size = 0;
    vector<bool> tree(vertex, false);
    vector<edge> T(vertex);
    tree[x] = true;
    while (size < vertex - 1)
    {
        int min_w = INT_FAST16_MAX, X = -1, Y = -1;
        for (int i = 0; i < vertex; i++)
        {
            if (tree[i] == true)
            {
                node *p = head[i];
                while (p != NULL)
                {
                    if (tree[p->val.y] == false && min_w > p->val.w)
                    {
                        X = i, Y = p->val.y, min_w = p->val.w;
                    }
                    p = p->link;
                }
            }
        }
        if (Y != -1)
        {
            edge e;
            e.x = X;
            e.y = Y;
            e.w = min_w;
            T[size++] = e;
            tree[Y] = true;
        }
    }
    int d = 0;
    for (int i = 0; i < size; i++)
    {
        cout << "(" << char(65 + T[i].x) << ", " << char(65 + T[i].y) << ") = " << T[i].w << endl;
        d += T[i].w;
    }
    cout << "Tong trong so nho nhat = " << d << endl;
}

// kruskal
int find(int parent[], int dinh)
{
    if (dinh != parent[dinh])
        parent[dinh] = find(parent, parent[dinh]);
    return parent[dinh];
}
edge setE[max];
int nE = 0;
edge setT[max];
int nT = 0;

void createE(node *head[])
{
    for (int i = 0; i < vertex; i++)
    {
        if (head[i] != NULL)
        {
            node *p = head[i];
            while (p != NULL)
            {
                if (i < p->val.y)
                    setE[nE++] = p->val;
                p = p->link;
            }
        }
    }
}
void swap(edge &e1, edge &e2)
{
    edge temp = e1;
    e1 = e2;
    e2 = temp;
}
void sortE()
{
    for (int i = 0; i < nE - 1; i++)
    {
        for (int j = i + 1; j < nE; j++)
        {
            if (setE[i].w > setE[j].w)
                swap(setE[i], setE[j]);
        }
    }
}
void kruskal()
{
    int parentMST[max];
    for (int i = 0; i < vertex; i++)
        parentMST[i] = i;
    for (int i = 0; i < nE; i++)
    {
        int X = setE[i].x;
        int Y = setE[i].y;
        int root_X = find(parentMST, X);
        int root_Y = find(parentMST, Y);
        if (root_X != root_Y)
        {
            setT[nT++] = setE[i];
            parentMST[root_Y] = root_X;
        }
        if (nT == vertex - 1)
            return;
    }
}
void printMST()
{
    int total_weight = 0;
    for (int i = 0; i < nT; i++)
    {
        cout << "(" << char(65 + setT[i].x) << ", " << char(65 + setT[i].y) << ") = " << setT[i].w << endl;
        total_weight += setT[i].w;
    }
    cout << "Tong trong so nho nhat = " << total_weight << endl;
}

int main()
{
    node *head[max];
    init(head, max);
    readFile(head);
    displayList(head);
    // dfs(head,3);
    // cout<<endl;
    // dfs_dequy(head,3);
    // display_dfs();
    prim(head, 3);
    cout << endl;
    createE(head);
    sortE();
    kruskal();
    printMST();
    freeMemory(head, vertex);
    return 0;
}
