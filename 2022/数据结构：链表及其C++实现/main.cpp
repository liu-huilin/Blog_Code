#include<iostream>
#include"list.hpp"

using namespace std;

int main()
{
    list<int> l;
    for(int i = 0; i < 10; i++)
    {
        l.push_back(i);
    }
    cout << "list length: " << l.get_length() << endl;
    list<int> l2 = l;
    list<int> l3(l);
    cout << "l: ";
    for(int i = 0; i < l.get_length(); i++)
    {
        cout << l.get_node(i) << ' '; 
    }
    cout << endl;

    l2.insert_node(5, 999); 
    cout << "l2: ";
    cout << "list length: " << l2.get_length() << endl;
    for(int i = 0; i < l2.get_length(); i++)
    {
        cout << l2.get_node(i) << ' '; 
    }
    cout << endl;
    

    l3.del_node(7);
    cout << "l3: ";
    cout << "list length: " << l2.get_length() << endl;
    for(int i = 0; i < l3.get_length(); i++)
    {
        cout << l3.get_node(i) << ' '; 
    }
    cout << endl;

    cout << l3.find(999) << endl;
    cout << l2.find(999) << endl;
    

    return 0;
}
