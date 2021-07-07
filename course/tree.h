#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Tree
{
    int n; // ���������� ������
    int root; // ������ ������
    vector <vector<int> > adj; // ������ ���������

    string dfs(int, vector<bool>&); // ����� ������ � �������
    string dfs_exec(); // �������� ������ � �������
    public:
        Tree(); // ������ ������
        Tree(char); // ������ ������� ������ (����������� 1)
        Tree(int); // ���� ������
        Tree(int, char); // ������������� ���������� ������
        bool is_isomorph(Tree*); // �������� �������� �� ������������
};

#endif

