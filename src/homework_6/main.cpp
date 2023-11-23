#include "array.h"
#include "single_list.h"
#include "dual_list.h"
#include <iostream>

using namespace std;

int main() {
    Array<int> box;
    //SingleList<int> box;
    //DualList<int> box;

    for (int i = 0; i < 10; i++) {
        box.push_back(i);
    }
    cout << box << endl;
    cout << box.size() << endl;

    box.erase(2);
    box.erase(3);
    box.erase(4);
    cout << box << endl;

    box.insert(0, 10);
    cout << box << endl;

    box.insert(box.size() / 2, 20);
    cout << box << endl;

    box.push_back(30);
    cout << box << endl;
    

    
    

    

    
    


    return 0;
}