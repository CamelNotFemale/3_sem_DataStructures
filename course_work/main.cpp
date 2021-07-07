#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <stack>
#include <ctime>
using namespace std;
const int MaxV = 26;
char Ch(int c) { // ���������� c-�� ������ ��������
 return c + 'a';
}
class GR {
    int n, m; // ���-�� ������ � �����
    int in_deg[MaxV] = {0}; // ������ ���������� �������� �����
    int out_deg[MaxV] = {0}; // ������ ���������� ��������� �����
    vector < list < int >> LIST; // ������ ������, �������� �������� - ������
    vector <bool> NEW; // 1 - ������� ��������, 0 - ������
    vector <int> X;
    vector <list<int>> tree; // ������������ ��������� �����
    //--��������� ������� ������������ � ��������� ��� ������������ �� ���������� ������--
    GR(const GR &);
    GR(GR &&);
    GR operator=(const GR &) const = delete;
    GR operator=(GR &&) const = delete;
public:
    GR(int, int &, int &);
    // �������� �� ������������� �������� �����
    int grow_tree(char, int); // �������� ������������ ������ �� �����
    vector <list<int>> select_root(); // ����� ����� vertice ������������� ������ � cnt ���������
    bool kosaraju(); // �������� �� ������ ���������
    bool in_out_deg(); // �������� �� ��, ��� ��� ������ ������� ����� �������� ����� ����� ��������� �����
    void Hierholzer_printCurciut(); // ����� �������� ����� ����� �������� �����������
    ~GR() = default; // ��������� ����������� �������������� ������������ ����������
};
GR::GR(int menu, int &v, int &e): n(0), m(0) {
    string s;
    int G[MaxV][MaxV]; // ������� ���������
    for (int i = 0; i < MaxV; ++i)
        for (int j = 0; j < MaxV; ++j) G[i][j] = 0;
    switch(menu)
    {
        case 1:
            // ���� ������ � ������� ���������
            cout << "\nEnter adjacency sets (strings of letters a through z)\n";
            do {
                cout << "v[" << Ch(n) << "] = ";
                cin >> s;
                for (auto i: s) // ������������ for(auto s = string.begin(); s != string.end(); ++s)
                    if (isalpha(i)) { // ���������� ������� �� ������������� ��������
                        int j = (tolower(i) - 'a'); // tolower ���������� �������� ���������� �������
                        G[n][j] = 1; // ��������������� ����
                        //G[j][n] = 1; // ����������������� ����
                        (in_deg[j])++; // ����������� ���������� �������� ����� � j �� 1
                        (out_deg[n])++;
                    }
                if (isalpha(s[0])) ++n;
            } while (isalpha(s[0]) && n < MaxV); // ���� ������ ������ ��������� ������ ����� � n �� ��������� MaxV
            break;
        case 2:
            // ��������� ��������� ������� ���������
            cout << "Enter the number of vertices in the graph\n";
            do {
                cin >> n;
                if(n < 0 || n > MaxV) cout << "The number of vertices range from 0 to " << MaxV;
            } while(n < 0 || n > MaxV);

            for (int i = 0; i < n; ++i)
                for (int j = i; j < n; ++j)
                    if (G[i][j] = rand()%2) {
                        (in_deg[j])++;
                        (out_deg[i])++;
                    }
            break;
        case 3:
            // ������������� ������
            n = 5;
            G[0][1] = 1; G[0][2] = 1; G[0][3] = 1;
            G[1][0] = 1; G[1][3] = 1;
            G[2][0] = 1; G[2][4] = 1;
            G[3][0] = 1; G[3][4] = 1;
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                    in_deg[i] += G[i][j];
                out_deg[i] = in_deg[i];
            }
            // {0, 1, 1, 1, 0},
            // {1, 0, 0, 1, 0},
            // {1, 0, 0, 0, 1},
            // {1, 1, 0, 0, 1},
            // {0, 0, 0, 0, 0},
            break;
        default:
            cout << "menu range from 0 - 3!\n";
    }
    // ������������ � ����� ������ ���������
    cout << "Graph list:";
    LIST.resize(n); // ��������� �������
    for (int i = 0; i < n; ++i) {
        int f = 0;
        cout << '\n' << Ch(i) << ": ";
        // cout << '\n' << i << ": ";
        for (int j = 0; j < n; ++j)
            if (G[i][j]) {
                ++f;
                LIST[i].push_back(j);
                cout << Ch(j) << ' ';
            }
            else cout << "- ";
        m += f;
    }
    cout << "\n|V|=" << n << " |E|="; m ? cout << m / 2 << '\n': cout << m << '\n'; // �� ������, ���� m = 1
    //cout << m << endl;
    v = n; e = m;
}
int GR::grow_tree(char vertice, int cnt) {
    /*if (!cnt) { // ����� ���������

        return 1;
    }
    else {
        //for (auto u: LIST[vertice-'a']) NEW[u]=1; // ��� ������� ������� � ��������� �������� ����������, ����� �� ����� ���� �������� � ������ ������
        for (auto u: LIST[vertice-'a']) { // ���������� ������� �������
            if (NEW[u] && rand()%3) { // ���� ������� �� ������ - ��������� ����� (vertice, u), �������� ���������� � ������������ 33%
                cout << "Add edge (" << vertice << ", " << Ch(u) << ")\n";
                tree[vertice-'a'].push_back(u);
                NEW[u] = false;
                if (grow_tree(Ch(u), cnt-1)) {
                    cout << "complete\n";
                    return 1;
                }
            }
        }
        return 0;
    }*/
}
vector <list<int>> GR::select_root() {
    // !!! ������ ������, ����� ������ ����� ����� �������� ������ !!!

    NEW.resize(n, true); // ������� ��� ������� "����������"
    tree.resize(MaxV, {}); // ������ ������ ��������� ��� ������
    X.clear();

    char vertice;
    int cnt;
    do {
        cout << "Input root of tree(char) and the desired number of vertices: "; cin >> vertice; cin >> cnt;
    } while ((!(LIST[vertice-'a'].size()) && cnt>1) || !isalpha(vertice) || cnt>n || cnt<0);
    // ���� � ����� ��� ����� ������� ��� ��������� ������� �� ������, ��� �� ����� �� �������� ���������� ������ �����

    NEW[vertice-'a']=false; // ������� ������ � ���� ������
    X.push_back(vertice-'a');
    while (X.size()<cnt) {
        int pos = rand() % X.size();
        // cout << "Verifiable vertice: " << Ch(X[pos]) << endl;
        for (auto u: LIST[X[pos]]) { // ���������� ������� ��������� �������, ������� ��� � ������
            if (NEW[u] && !(rand()%3) && X.size()<cnt) {
                NEW[u]=false;
                X.push_back(u);
                tree[X[pos]].push_back(u); // ������� ����� (X[pos], u)
                cout << "Add edge (" << Ch(X[pos]) << ", " << Ch(u) << ")\n";
            }
        }
    }
    return tree;
}

bool GR::in_out_deg() {
    for(int i = 0; i < n; i++)
        if(out_deg[i] != in_deg[i]) return false;
    return true;
}
bool GR::kosaraju() {
    int i = 0; // �������, ������� ������� ������ ����
    auto size = n;
    std::vector<bool> vis(size); // �� ��������� ��� �������� �������������� ��� ����
    vector < list < int >> t(size); // ����������������� ����
    // ��� ��������� ������������ ���� ����������� STL, �� ����� ������� ��� ���� ������ ��������� � �������
    // std::function - ����������� �������, ��������� �������, ���������� � ��������� �� ����� ������. � ��� ����� � ������-���������.
    // ����������� - ��������� ������������ ������ ������ �����
    std::function<void(int)> visit; // ������� ������� visit, ������� ������ �� ���������� � ��������� � �������� ��������� int
    // � �������
    // ������ ������-��������� � ������� visit
    // ������-��������� - ������� ����� ������ ��������� ��������� (������� - ������, ������� ����� ������������ ��� �������)
    visit = [&](int u) { // [&] - ��������� ��� ��������� ���������� �� ������. (int u) - ������������ ���������� � ���������������
        if (!vis[u]) {
            vis[u] = true;
            for (auto v : LIST[u]) {
                visit(v);
                t[v].push_back(u); // ������ �����������, �.�. ������ ����������������� ����
            }
        }
    };
    while(!out_deg[i]) i++; // ������� �� ������� � ��������� ��������
    visit(i);
    for (int j = 0; j < size; ++j)
    if(!vis[j] && out_deg[j]) return false; // ���� �������� �� ���������� �������, ������� ������� ������ 0, �� ���� �� ������ �������, � ������ �� �������� �������� �����
    // ���������� ���������� �� ������������������ �����
    std::function<void(int)> assign;
    assign = [&](int u) {
        if (vis[u]) {
            vis[u] = false;
            for (auto v : t[u]) {
                assign(v);
            }
        }
    };
    assign(i);
    for (i = 0; i < size; ++i)
    if(vis[i] && out_deg[i]) return false;

    return true;
}
// �������� �����������
// �������� ����� ��������� ������� v � ������� �� ������ �� ���� ������� ���� �� �������� � v.
// ���������� �������� �� � ����� �������, ����� v, ������ ��� ������ ������� ���� ������ �����������,
// ���, ����� �� ������ � ������ ������� w, ������ ���� �������������� �����, ��������� �� w.
// �������������� ����� ������� ���� �������� ������, �� �� ����� �� ���������� ��� ����� ��������� �����.
// (1) ������ ��������� � ������ �������, � ������� �� �������� ����������� �����.
// (2) ����� ����� ������������ � ������� u, � ������� ���� ����������� ����� � ������� �� ������ �� ���� ������� ���� �� �������� � u
// ��������� ���� (1) � (2). ���������� ������ - ����� ������������� ������� ����, �� ������?
// ����������� �������������� � �� ����� ��� � � �������� ������ �������, �� �� �������� ������ ����� �������� ���������:
// ������ ���������� ����, ���� �� �� ������� - �� �������� �� ���� ������, �� ���� �� �� ����� ����, ������� �������� ��� ������������,
// �� �� �� ������������ � ��������, ��� ���������� � ������ ��� ��������. � �������� ������������ �����, ��� ����������� ����,
// ������ ����� ����������� � ������������ ����� �������, ������� ��� ����� �������������� ����������� �����
void GR::Hierholzer_printCurciut() {
    // if (!LIST.size())
    // {
    // cout << "graph empty";
    // return; // ������ ����
    // }
    int i = 0, // ������� � ��������� ��������
    next_v,
    curr_v; // ������� �������
    // ������� ����
    stack<int> curr_path;
    // ������� ����
    vector<int> circuit;
    while(!out_deg[i]) i++;
    curr_path.push(i);
    curr_v = i;
    while (!curr_path.empty())
    {
        // ���� ���� ����������� �����, ��
        if (out_deg[curr_v])
        {
            // ��������� � ���� ��������� �������
            curr_path.push(curr_v);
            // ������� ��������� ������� ������� � curr_v
            next_v = LIST[curr_v].back();
            // � ������� ����� ������� � next_v
            out_deg[curr_v]--;
            LIST[curr_v].pop_back();
            // ��������� � ��������� �������
            curr_v = next_v;
        }
        // ���� ���, ��
        else
        {
            // ��������� ������� � ������� ����
            circuit.push_back(curr_v);
            // ������� ��������� ������� � ���� � ��� �� �� ������������� �� ��������� ����, �� ������ �� �� �����
            curr_v = curr_path.top();
            curr_path.pop();
        }
    }
    // �����
    cout << "----------------------------------------\nEuler cycle: ";
    for (int i=circuit.size()-1; i>=0; i--)
    {
        cout << Ch(circuit[i]);
        // cout << circuit[i];
        if (i)
        cout<<" -> ";
    }
    cout << "\n----------------------------------------\n";
}
int main()
{

    srand(time(nullptr));
    int menu, v, e;
    do {
        cout << "1 - Enter the graph\n";
        cout << "2 - Generate random graph\n";
        cout << "3 - Use ready example\n";
        cout << "0 - Exit\n";
        cin >> menu;
        cout << "----------------------------------------\n";
        if(menu < 4 && menu > 0) {
            GR graph(menu, v, e);
            if(!v) cout << "----------------------------------------\nThe graph has zero vertices\n----------------------------------------\n";
            else if(!e) cout << "----------------------------------------\nThe graph has zero edges\n----------------------------------------\n";
            else graph.select_root();
            system("pause");
        }
        else if(menu) cout << "Menu range from 0 to 3!\n";
    } while(menu);
 return 0;
}
