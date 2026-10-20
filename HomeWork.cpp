#include <iostream>
#include <algorithm>
#include <stdexcept>

class DynamicArray {
    int* nachalo;
    int razmer;
public:
    DynamicArray(int r){
        if (r <= 0) {
            throw std::invalid_argument("Размер массива должен быть положительным");
        }
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
        if (index < 0 || index >= razmer) {
            throw std::out_of_range("Индекс выходит за пределы массива (set)");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100] (set)");
        }
        nachalo[index] = value;
    }
    int get(int index) {
        if (index < 0 || index >= razmer) {
            throw std::out_of_range("Индекс выходит за пределы массива (get)");
        }
        return nachalo[index];
    }
    void push_back(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100] (push_back)");
        }

        int* newArray = new int[razmer + 1];
        std::copy(nachalo, nachalo + razmer, newArray);
        delete[] nachalo;
        nachalo = newArray;
        razmer = razmer + 1;
        nachalo[razmer - 1] = value;
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
    std::cout << "=== Тест 1: выход за границы массива ===" << std::endl;
    try {
        DynamicArray arr(3);
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        arr.showArray();

        std::cout << arr.get(1) << std::endl;

        std::cout << "Попытка получить элемент по индексу 10..." << std::endl;
        std::cout << arr.get(10) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Перехвачено std::out_of_range: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 2: недопустимое значение ===" << std::endl;
    try {
        DynamicArray arr(3);
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        arr.showArray();

        std::cout << "Попытка установить значение 150..." << std::endl;
        arr.set(0, 150);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено std::invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 3: некорректный размер массива ===" << std::endl;
    try {
        std::cout << "Попытка создать массив размером -5..." << std::endl;
        DynamicArray bad(-5);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено std::invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "\n=== Корректная работа программы ===" << std::endl;
    try {
        DynamicArray arr(3);
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        arr.showArray();

        arr.push_back(40);
        arr.showArray();

        DynamicArray arr2(arr);
        arr2.showArray();

        arr.sumOrSub(arr2);
        arr.showArray();

        std::cout << "Попытка push_back(200)..." << std::endl;
        arr.push_back(200);
    }
    catch (const std::exception& e) {
        std::cout << "Перехвачено std::exception: " << e.what() << std::endl;
    }

    return 0;
}