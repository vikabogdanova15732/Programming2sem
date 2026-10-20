#include <iostream>
#include <algorithm>

class DynamicArray {
    int* nachalo;
    int razmer;
public:
    DynamicArray(int r){
        razmer = r;
        nachalo = new int[r];
    }
    DynamicArray(const DynamicArray& other) : razmer(other.razmer) {
        nachalo = new int[razmer];
        std::copy(other.nachalo, other.nachalo + razmer, nachalo);
    }
    ~DynamicArray(){
        delete [] nachalo;
    }
    void showArray() {
        for (int i = 0; i < razmer; i++) {
            std::cout << nachalo[i] << " ";
        }
        std::cout << std::endl;
    }
    void set(int index, int value){
        if (0 <= index && index < razmer && -100 <= value && value <= 100){
            nachalo[index] = value;
        }
    }
    int get(int index) {
        if (index >= 0 && index < razmer) {
            return nachalo[index];
        }
        return 0;
    }
    bool push_back(int value) {
        if (value < -100 || value > 100) {
            return false;
        }

        int* newArray = new int[razmer + 1];
        std::copy(nachalo, nachalo + razmer, newArray);
        delete[] nachalo;
        nachalo = newArray;
        razmer = razmer + 1;
        nachalo[razmer - 1] = value;

        return true;
    }
    void sumOrSub(const DynamicArray& arr2) {
        for (int i = 0; i < razmer; i++) {
            int element = 0;

        if (i < arr2.razmer) {
            element = arr2.nachalo[i];
        }

        nachalo[i] += element;
        }
    }
};

int main() {
    DynamicArray arr(3);

    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);
    arr.showArray();

    std::cout << arr.get(1) << std::endl;

    arr.push_back(40);
    arr.showArray();

    DynamicArray arr2(arr); // Копирование
    arr2.showArray();

    arr.sumOrSub(arr2);
    arr.showArray();

    return 0;
}