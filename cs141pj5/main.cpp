// to test whether my code is valid
// UIC changjae han 2021 computer science.UIC
// 

#include <iostream>
#include "list.h"
#include <fstream>
#include "pqueue.h"
using namespace std;

//int pq_search(List L, int pos);



int main()
{
        
    
    List L;
    init_list(L);
    
    NodeData d;
    d.ID = 5;
    d.Priority = 6;
    
    push_back_list(L, d);
    
    d.ID = 6;
    d.Priority = 9;
    
    push_back_list(L, d);
    
    
    d.ID = 8;
    d.Priority = 17;
    
    push_back_list(L,d);
    //pq_enqueue(L, 1, 3);
    pq_print(L);
    
    cout << "6,17 추가: ";
    pq_enqueue(L, 6, 17);
    
    
    pq_print(L);
    
    cout << "8,1 추가: ";
    pq_enqueue(L, 8, 1);
    
    pq_print(L);
    
    cout << "4,6 추가: ";
    pq_enqueue(L, 4, 6);
    
    pq_print(L);
    
   // cout << "4,7 추가: ";
    //pq_enqueue(L, 4, 7);
    
    pq_print(L);
    
    pq_enqueue(L, 2, 6);
    
    pq_print(L);
    
    pq_clear(L);
    
    pq_print(L);
    
    d.ID = -1;
    d.Priority = -12;
    
    push_back_list(L, d);
    
    d.ID = 1;
    d.Priority = -11;
    
    push_back_list(L, d);
    
    d.ID = 0;
    d.Priority = -10;
    
    push_back_list(L, d);
    
    d.ID = 2;
    d.Priority = 0;
    
    push_back_list(L, d);
    
    pq_print(L);
    
    pq_enqueue(L, 100, 4);
    
    pq_enqueue(L, 101, 4);
    pq_enqueue(L, 102, 4);
    pq_enqueue(L, 103, 1);
    pq_enqueue(L, 104, 10);
    
    pq_enqueue(L, 105, 2);
    
    pq_enqueue(L, 106, 6);
    
    pq_enqueue(L, 107, 3);
    
    pq_enqueue(L, 108, 7);
    pq_enqueue(L, 109, 2);
    pq_enqueue(L, 110, 5);
    pq_enqueue(L, 111, 9);
    pq_enqueue(L, 112, 2);
    pq_enqueue(L, 113, 2);
    pq_enqueue(L, 114, 7);
    pq_enqueue(L, 115, 2);
    pq_enqueue(L, 116, 10);
    pq_enqueue(L, 117, 8);
    pq_enqueue(L, 118, 7);
    pq_enqueue(L, 119, 4);
    pq_enqueue(L, 120, 7);
    pq_enqueue(L, 121, 6);
    pq_enqueue(L, 122, 10);
    pq_enqueue(L, 123, 2);
    pq_enqueue(L, 124, 7);
    pq_print(L);
    
   /* pq_clear(L);
    
    
    d.ID = 10;
    d.Priority = 20;
    push_back_list(L, d);
    
    d.ID = 11;
    d.Priority = 20;
    push_back_list(L, d);
    
    d.ID = 12;
    d.Priority = 20;
    push_back_list(L, d);
    
    pq_print(L);*/
    
    
    pq_nudge(L, 105);
    pq_print(L);
    //pq_nudge(L, 11);
    
    
    
   // pq_nudge(L, 4);
    //pq_print(L);
    
    //pq_nudge(L, 6);
    //pq_print(L);
    
    //pq_nudge(L, 6);
    //pq_print(L);
    
   // //pq_nudge(L, 2);
   // pq_print(L);
    
   // List newlist = pq_duplicate(L);
   // cout << "복사된 리스트: ";
   // pq_print(L);
    
    pq_nudge(L, 112);
    pq_print(L);
    
    List vvv = pq_duplicate(L);
    cout << "복사된 리스트: ";
    pq_print(vvv);
   // int z = pq_search(L, 20);
   // cout << z << endl;
    //int w = pq_search(L, 18); 
   // cout << "과연 9 " << w << endl;
   // cout << "insert 2, 5" << endl;
   // pq_enqueue(L, 2, 5);
    //pq_print(L);
    
    
    
    return 0;
} 