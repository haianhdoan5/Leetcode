#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define max 9
#define Max 100

// Cấu trúc đồ thị
struct node {
    int data;
    int w;
    node *link;
};

void init(node *head[], int n) {
    for (int i = 0; i < n; i++) {
        head[i] = nullptr;
    }
}

node* create(int key, int weight) {
    node *p = new node;
    p->data = key;
    p->w = weight;
    p->link = nullptr;
    return p;
}

void addLast(node* &head, int x, int weight) {
    if (head == nullptr) {
        head = create(x, weight);
    }
    else {
        node *p = head;
        while (p->link != nullptr) {
            p = p->link;
        }
        p->link = create(x, weight);
    }
}
void display(node* head[], int n) {
    for (int i = 0; i < n; i++) {
        node *p = head[i];
        cout << i << ": ";
        while (p != nullptr) {
            cout << p->data << "(" << p->w << ") ";
            p = p->link;
        }
        cout << endl;
    }
}

void docFile(node* head[], int &n) {
    ifstream inF("/Users/rolandtran/Documents/GitHub/DSA2/DSA2/DSA2/CHAPTER 3/OpenUniversity/MatrixInputLaDoi.txt");
    if (inF.is_open()) {
        inF >> n;
        while (!inF.eof()) {
            int pre, next, weight;
            inF >> pre >> next >> weight;
            addLast(head[pre], next, weight);
            addLast(head[next], pre, weight);
        }
        inF.close();
    }
}

// Lớp hàng đợi
class Queue {
private:
    node *front;
    node *rear;
public:
    Queue() {
        front = rear = nullptr;
    }

    void enQueue(int data) {
        node* p = create(data, 0);
        if (rear == nullptr) {
            front = rear = p;
            return;
        }
        rear->link = p;
        rear = p;
    }

    node* deQueue() {
        if (front == nullptr) return nullptr;
        node* p = front;
        front = front->link;
        if (front == nullptr) rear = nullptr;
        return p;
    }

    bool is_empty() {
        return front == nullptr;
    }
};

// Hàm BFS
void BFS(node *head[], int n, int v) {
    Queue temp;
    vector<bool> visited(n, false);
    visited[v] = true;
    temp.enQueue(v);

    while (!temp.is_empty()) {
        node* u = temp.deQueue();
        cout << u->data << " ";
        node* p = head[u->data];
        while (p != nullptr) {
            if (!visited[p->data]) {
                visited[p->data] = true;
                temp.enQueue(p->data);
            }
            p = p->link;
        }
        //delete u;
    }
}

// Cấu trúc stack
struct Stack {
    int a[Max];
    int top;
};

void init(Stack &s) {
    s.top = -1;
}

void push(Stack &s, int x) {
    s.a[++s.top] = x;
}

int pop(Stack &s) {
    return s.a[s.top--];
}

bool isEmpty(Stack s) {
    return s.top == -1;
}

// Hàm DFS
void DFS(node *head[], int n, int v) {
    Stack s;
    init(s);
    vector<bool> visited(n, false);
    //visited[v] = true;
    push(s, v);
    int sodinh=0;
    while (!isEmpty(s)) {
        int u = pop(s);
        if(sodinh<n){
            if(!visited[u]) {
                cout << u << " ";
                visited[u] = true;
                sodinh++;
            }
            node* p = head[u];
            while (p != nullptr) {
                if (!visited[p->data]) {
                    //visited[p->data] = true;
                    //cout << p->data<<" ";
                    push(s, u);
                    push(s, p->data);
                    break;
                }
                p = p->link;
            }

        }
    }
}

int main() {
    node *head[max];
    int n;
    init(head, max);
    docFile(head, n);
    display(head, n);

    cout << "===== BFS =====\n";
    BFS(head, n, 0);

    cout << endl << "===== DFS =====\n";
    DFS(head, n, 0);


    for (int i = 0; i < n; i++) {
        node* p = head[i];
        while (p != nullptr) {
            node* temp = p;
            p = p->link;
            delete temp;
        }
    }
    cout << endl;
    return 0;
}
