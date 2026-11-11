#include <iostream>

using namespace std;

int main() {

    //challenge: shift array to the left by one.

    int array[] = {1,2,3,4,5,6,7,8,9};
    int arrayLength = std::size(array);

    int first = array[0];

    for(int i = 0; i < arrayLength; i++) {
        array[i] = array[i+1];
    }
    array[arrayLength-1] = first;

    for(int i = 0; i < arrayLength; i++){
        cout<< array[i];
        if(i != (arrayLength-1)){
            cout<< ", ";
        }else{
            cout<< ".\n";
        }
    }

    return 0;
}