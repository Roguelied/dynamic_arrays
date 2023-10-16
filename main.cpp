#include "dynamic_arrays.h"
using namespace std;


int main() {

    Array<int> arr(10, 99);
    cout << arr << '\n';
    arr.erase();
    cout << arr <<'\n';
    for (int i = 0; i < 10; i++) {arr.add(i);}
    cout << arr << '\n';
    arr.erase(2);
    arr.erase(18);
    cout << arr << '\n';
    cout << arr.index(arr.min()) << ' ';
    cout << arr.index(arr.max()) << '\n';
    cout << arr << '\n';
    arr.add(101, 17);
    cout << arr << '\n';
    Array<int> arr1(10, 9);
    cout << arr1 << '\n';
    arr = arr1;
    cout << arr << '\n';
    return 0;
}
