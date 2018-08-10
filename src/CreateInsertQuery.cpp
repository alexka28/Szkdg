#include "CreateInsertquery.h"
#include <time.h>
#include <stdlib.h>
/*
iq: insert or query. 0 = insert, 1 query
a: a node which will be inserted
b: the other node
*/
IQ::IQ(int iq, int a, int b)
{
    this->iq = iq;
    this->a = a;
    this->b = b;
}
/*
n: number of nodes
numInserts: number of inserts and queries
*/
std::list<struct IQ> createIQ(int n, int numInserts)
{
    /*
    rnd: random number the chance we make an insert or query
    count_i: counts how much insert we made
    count_q: same as count_i with querys
    node1: a generated node
    node2: same as node1
    */
    int rnd, count_i=0, count_q=0, node1, node2;
    std::list<struct IQ> iqList;
    srand (time(NULL));

    while(count_i != numInserts )
    {
        /* generate a number between 1 and 10, which decides it will be an insert or a query */
        rnd = rand() % 10 + 1;
        /*
        generate 2 nodes and check equality
        */
        node1 = rand() % (n+1);
        node2 = rand() % (n+1);
        while(node1 == node2)
        {
            node1 = rand() % (n+1);
            node2 = rand() % (n+1);
        }
        /*
        make an insert
        */
        if(rnd > 3 || count_i < count_q)
        {

            /*
            check the list, if it contains insert with node1 and node2 regenerate nodes
            */
            if(count_i != 0)
            {
                std::list <struct IQ> :: iterator it;
                /*
                iterate over the list and check nodes
                */
                for(it = iqList.begin(); it != iqList.end(); ++it)
                {
                    /*
                    check: is it an insert? If its not an insert just increment the iterator
                    these if's can be merged into one if statement
                    */
                    if(it->iq == 0)
                    {
                        /*
                        if the nodes equals with an insert, we generate new nodes, and start the iteration again
                        */
                        if((it->a == node1 && it->b == node2) || (it->a == node2 && it->b == node1) )
                        {
                            node1 = rand() % (n+1);
                            node2 = rand() % (n+1);
                            it = iqList.begin();
                        }
                    }

                }
                IQ iq(0,node1,node2);
                iqList.push_back(iq);
            }
            /*
            if we haven't got any insert, we have to do at least one
            */
            else
            {
                IQ iq(0,node1,node2);
                iqList.push_back(iq);
            }
            ++count_i;
        }
        /*
        make a query
        */

        else
        {
            if(count_q != 0)
            {
                std::list <struct IQ> :: iterator it;
                for(it = iqList.begin(); it != iqList.end(); ++it)
                {
                    /*
                    check: is it a query? If its not a query just increment the iterator
                    these if's can be merged into one if statement
                    */
                    if(it->iq == 1)
                    {
                        /*
                        if the nodes equals with a query, we generate new nodes, and start the iteration again
                        */
                        if((it->a == node1 && it->b == node2) || (it->a == node2 && it->b == node1) )
                        {
                            node1 = rand() % (n+1);
                            node2 = rand() % (n+1);
                            it = iqList.begin();
                        }
                    }
                }
                IQ iq(1,node1,node2);
                iqList.push_back(iq);
            }
            /*
            if we havent got any query, we have to do at least one
            */
            else
            {
                IQ iq(1,node1,node2);
                iqList.push_back(iq);
            }
            ++count_q;
        }

    }
    /*
    we return the list
    */
    return iqList;
}
