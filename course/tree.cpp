#include "tree.h"
// ���������� ������ �������� c'�� �� �������
char name(char c) {return c+'a';}

// ��������� ����� (��� ����������)
bool cmp(const string &lhs, const string &rhs)
{
    return lhs < rhs;
}
// ������������� ������ ������
Tree :: Tree()
{
    root = 0;
    n = 9;
    adj.resize(n);

    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[0].push_back(7);
    adj[1].push_back(5);
    adj[1].push_back(6);
    adj[2].push_back(3);
    adj[2].push_back(4);
    adj[7].push_back(8);

    cout << "������ ������ 1\n������ ���������:\n";
    cout << "a: -bc----h-\n";
    cout << "b: -----fg--\n";
    cout << "c: ---de----\n";
    cout << "d: ---------\n";
    cout << "e: ---------\n";
    cout << "f: ---------\n";
    cout << "g: ---------\n";
    cout << "h: --------i\n";
    cout << "i: ---------\n";
    cout << "������ - " << name(root) << "\n";
    cout << "|V| = 9\n\n";
}

// ������ ������� ������. (��������� 1)
Tree :: Tree(char c)
{

    root = 2;
    n = 9;
    adj.resize(n);
    adj[2].push_back(0);
    adj[2].push_back(5);
    adj[2].push_back(3);
    adj[0].push_back(1);
    adj[0].push_back(4);
    adj[3].push_back(7);
    adj[3].push_back(8);
    adj[5].push_back(6);

    cout << "������ ������ 2\n������ ���������:\n";
    cout << "a: -b--e----\n";
    cout << "b: ---------\n";
    cout << "c: a--d-f---\n";
    cout << "d: -------hi\n";
    cout << "e: ---------\n";
    cout << "f: ------g--\n";
    cout << "g: ---------\n";
    cout << "h: ---------\n";
    cout << "i: ---------\n";
    cout << "������ - " << name(root) << "\n";
    cout << "|V| = 9\n\n";
}

// ���� ������ �������� ���������
Tree :: Tree(int maxV): n(maxV)
{
    string s;
    char r;
    cout << "\n������� ������ ������ (�����): ";
    cin >> r;
    root = (int)(tolower(r) - 'a');

    adj.resize(n);
    cout << "\n������� ������ ��������� (������ ���� a �� z)\n";

    for (int k = 0; k < n; ++k)
    {
        cout << "v[" << name(k) << "] = ";
        cin >> s;
        for (auto u: s)
            if (isalpha(u))
            {
                int j = tolower(u) - 'a';
                adj[k].push_back(j); // ������
            }
    }
}

// ��������� ���������� ������ (��� �������� ������ ����� ������� �������)
Tree :: Tree(int maxV, char c): n(maxV), root(0)
{
    int G[n][n];

    // ��������� �������
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            G[i][j] = 0;

    // ��������� ��������� ������� ���������
    for (int i = n - 1; i > 0; i--)
        G[rand() % i][i] = 1;

    cout << "\n��������������� ����\n������ ���������:";
    // ���������� ������ ���������
    adj.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cout << '\n' << name(i) << ": ";
        for (int j = 0; j < n; ++j)
            if (G[i][j])
            {
                adj[i].push_back(j);
                cout << name(j);
            }
            else cout << '-';
    }
    cout << "\n������ - " << name(root) << "\n";
    cout << "|V| = " << n << "\n\n";
}

// �������� �������� �� ������������. ��������� ����� ��������.
// ���������� ������, ���� ����� ���������
bool Tree :: is_isomorph(Tree *other)
{
    // cout << dfs_exec() << "\n" << other.dfs_exec() << "\n";
    if (dfs_exec() == other->dfs_exec())
        return true;
    else
        return false;
}

// ������� �������� ��� ������ ������ � �������
// ���������� ��� ������
string Tree :: dfs_exec()
{
    string code;
    vector<bool> used;
    used.resize(n);
    code = dfs(root, used);
    return code;
}

// ����� ������ � ������� � ������������ ���� ������.
// ���������� ��� ������
string Tree :: dfs(int node, vector<bool> &used)
{
    used[node] = true;
    vector<string> tmp;
    string str;

    if (adj[node].empty()) // ���� ������� �������� ������
        return "10";

    for (vector<int>::iterator i = adj[node].begin(); i != adj[node].end(); ++i)
        if (!used[*i])
            tmp.push_back(dfs(*i, used));

    sort(tmp.begin(), tmp.end(), cmp);

    for (int j = 0; j < tmp.size(); ++j)
        str += tmp[j];

    return '1' + str + '0';
}

