#ifndef CREATEINSERTQUERY_H_INCLUDED
#define CREATEINSERTQUERY_H_INCLUDED
#include<list>
struct IQ
{
    int iq, a, b;
    IQ(int iq, int a, int b);
};
std::list<struct IQ> createIQ(int n, int numIQ);


#endif // CREATEINSERTQUERY_H_INCLUDED
