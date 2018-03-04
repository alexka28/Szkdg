#ifndef UNIFIND_H_INCLUDED
#define UNIFIND_H_INCLUDED

struct DisjointSets
{
int *parent, *rnk;
    int n;
    DisjointSets(int n);
    int find(int u);
    void merge(int,int);
    void insert(int, int);
    bool query(int, int);
};


#endif // UNIFIND_H_INCLUDED
