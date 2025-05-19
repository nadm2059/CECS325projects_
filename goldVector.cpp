/*
Program name: goldVector.cpp
Author: Steve Gold
Date: April 14, 2025
Purpose: Demo Drive for assignment
*/
#include "goldNamespace.cpp" // uncomment for submission
#include <iostream>
//#include <vector> // comment for submission
using namespace std;
using namespace gold; // uncomment for submission
class can
{
private:
    string contents;
    int volume;
public:
    can()
    {
        contents="empty";
        volume = 0;
    }
    can(int n, string name)
    {
        contents = name;
        volume = n;
    }
    friend ostream & operator<<(ostream & out, const can & c)
    {
        cout << c.contents << ':'<< c.volume;
        return out;
    }
};

template <typename T>
void vectorStat(string name, vector<T> v)
{
    cout << "Stats on vector "<<name<<endl;
    cout << "Size:"<<v.size()<<endl;
    //cout << "Capacity:"<<v.capacity()<<endl;
    cout << "Contents:";
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << ',';
    }
    cout << endl<<endl;
}


int main()
{
    vector<int> v1, v2(10), v3(4,20);
    vector<can> cans;
    cans.push_back(can(24, "Monster"));
    cans.push_back(can(20, "Baked Beans"));
    cout << "--- section 1 (here are my cans)\n";
    for (int i=0; i<cans.size(); i++)
        cout << cans[i]<<endl;

    cout << "----- section 2 (inital vectors)------\n";
    vectorStat("v1",v1);
    vectorStat("v2",v2);
    vectorStat("v3",v3);
    vectorStat("cans",cans);

    for (int i=0; i<5; i+=2)
    {
        v1.push_back(i);
        v2.push_back(i);
        v3.push_back(i);
        v3[v3.size()-1] = 42;
    }

    cout << "----- section 3 (push_back)-----\n";
    vectorStat("v1",v1);
    vectorStat("v2",v2);
    vectorStat("v3",v3);

    cout << "----- section 4 (pop_back)------\n";
    for (int i=0; i<3; i+=2)
    {
        v1.pop_back();
        v2.pop_back();
        v3.pop_back();
    }
    vectorStat("v1",v1);
    vectorStat("v2",v2);
    vectorStat("v3",v3);

    cout << "----- section 5 (capacity)------\n";
    cout << "v1 Capacity:"<<v1.capacity()<<endl;
    cout << "v2 Capacity:"<<v2.capacity()<<endl;
    cout << "v3 Capacity:"<<v3.capacity()<<endl;
    cout << "cans Capacity:"<<cans.capacity()<<endl;
    cout << endl;

    v1.clear();
    v2.clear();
    v3.clear();

    cout << "----- all vectors are cleared------\n";
    vectorStat("v1",v1);
    vectorStat("v2",v2);

    vectorStat("v3",v3);

    vector<int> v4;

    for(int i=1; i<=10; i++)
        v4.push_back(i);

    cout << "testing [ ] - should not throw exception\n";
    for(int i=0; i<=10; i++)
        cout << v4[i]<<','<<flush;
    cout << endl<<endl;

    cout << "v4.size():"<<v4.size()<<endl;
    v4.pop_back();
    v4.pop_back();
    v4.pop_back();
    cout << "v4.size():"<<v4.size()<<endl;

    cout << "v4.front():"<< v4.front()<<endl;
    cout << "v4.back():"<<v4.back()<<endl;
    cout << endl;

    cout << "testing at( ) - should throw out_of_range exception\n";
    
    for(int i=0; i<= 10; i++)
        cout << v4.at(i)<<','<<flush;
    

    

    cout << "you should never see this line\n";
}

