#include "myList.hpp"
using namespace std;

int main(void)
{
    myList<int> ls{11,11,11,11,33,44,11,66,11};

    ls.display();
    ls.remove(11);
    ls.display();

    return 0;
}