#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#define max 100

struct matrix {
	int a[max][max] = {0};
	int n;
};

struct arrE {
	int e1[max];
	int e2[max];
	int we[max];
	int ne = 0;
};

struct arrT {
	int t1[max];
	int t2[max];
	int wt[max];
	int nt = 0;
};

void TaoArrE(matrix &a, arrE &E) {
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.a[i][j] != 0) {
				E.e1[E.ne] = i;
				E.e2[E.ne] = j;
				E.we[E.ne] = a.a[i][j];
				E.ne++;
				a.a[i][j] = 0;
				a.a[j][i] = 0;
			}
		}
	}
}

void SapXepE(arrE &E) {
	for (int i = 0; i < E.ne - 1; i++) {
		for (int j = i + 1; j < E.ne; j++) {
			if (E.we[i] > E.we[j]) {
				swap(E.we[i], E.we[j]);
				swap(E.e1[i], E.e1[j]);
				swap(E.e2[i], E.e2[j]);
			}
			if (E.we[i] == E.we[j]&&E.e1[i]>E.e1[j]) {
				swap(E.we[i], E.we[j]);
				swap(E.e1[i], E.e1[j]);
				swap(E.e2[i], E.e2[j]);
			}
		}
	}
}

void docFile(matrix &a) {
	ifstream inF("Data.txt");
	if (inF.is_open()) {
		inF >> a.n;
		int x1, x2, w;
		while (inF >> x1 >> x2 >> w) {
			a.a[x1][x2] = w;
			a.a[x2][x1] = w;
		}
		inF.close();
	}
}

void displayMatrix(matrix a) {
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			cout << a.a[i][j] << "\t";
		}
		cout << endl;
	}
}

void displayT(arrT T) {
	cout << "ket qua kruskal:\n";
	int tong = 0;
	for (int i = 0; i < T.nt; i++) {
		cout << endl << "(" << T.t1[i] << "," << T.t2[i] << ") = " << T.wt[i];
		tong += T.wt[i];
	}
	cout << "\n" << "Tong trong so la:" << tong << endl;
}

// Cấu trúc dữ liệu Union-Find
struct UnionFind {
	int parent[max];   // Mảng cha
	int rank[max];     // Mảng rank (hoặc size)

					   // Khởi tạo Union-Find
	void init(int n) {
		for (int i = 0; i < n; i++) {
			parent[i] = i;  // Mỗi đỉnh là cha của chính nó
			rank[i] = 0;     // Khởi tạo rank = 0
		}
	}

	// Tìm đại diện của nhóm chứa đỉnh x
	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);  // Path compression
		}
		return parent[x];
	}

	// Kết hợp hai nhóm
	void unionSets(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);

		// Nếu hai đỉnh đã cùng nhóm, không cần kết hợp
		if (rootX != rootY) {
			// Union by rank (hoặc size)
			if (rank[rootX] > rank[rootY]) {
				parent[rootY] = rootX;
			}
			else if (rank[rootX] < rank[rootY]) {
				parent[rootX] = rootY;
			}
			else {
				parent[rootY] = rootX;
				rank[rootX]++;
			}
		}
	}

	// Kiểm tra xem x và y có tạo thành chu trình không
	bool isCycle(int x, int y) {
		return find(x) == find(y);
	}
};


void kruskal(matrix a, arrE E, arrT &T, UnionFind &uf) {
	uf.init(a.n);
	for (int i = 0; i < E.ne; i++) {
		if (uf.isCycle(E.e1[i], E.e2[i])) {
			continue;  // Nếu tạo chu trình thì bỏ qua cạnh này
		}
		// Nếu không tạo chu trình, thêm vào cây khung
		T.t1[T.nt] = E.e1[i];
		T.t2[T.nt] = E.e2[i];
		T.wt[T.nt] = E.we[i];
		T.nt++;
		uf.unionSets(E.e1[i], E.e2[i]);  // Kết hợp các nhóm lại với nhau

		if (T.nt == a.n - 1) break;  // Cây khung tối tiểu đã đầy đủ
	}
}

void displayE(arrE E) {
	for (int i = 0; i < E.ne; i++) {
		cout << endl << "(" << E.e1[i] << "," << E.e2[i] << ") = " << E.we[i];
	}
}

int main() {
	arrE E;
	arrT T;
	matrix a;
	UnionFind uf;
	docFile(a);
	displayMatrix(a);
	TaoArrE(a, E);
	SapXepE(E);
	displayE(E);
	kruskal(a, E, T,uf);
	displayT(T);
	system("pause");
	return 0;
}