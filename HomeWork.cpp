#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <cmath>
#include <typeinfo>


template <typename T>
class DynamicArray {
    T* nachalo;
    int razmer;
public:
    DynamicArray(int r){
        razmer = r;
        nachalo = new T[r];
    }
    DynamicArray(const DynamicArray& other) : razmer(other.razmer) {
        nachalo = new T[razmer];
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
    void set(int index, T value){
        if (index < 0 || index >= razmer) {
            throw std::out_of_range("Индекс выходит за пределы массива (set)");
        }
        if constexpr (std::is_integral_v<T>) {
            if (value < -100 || value > 100) {
                throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100] (set)");
            }
        }
    }
    T get(int index) {
        if (index < 0 || index >= razmer) {
            throw std::out_of_range("Индекс выходит за пределы массива (get)");
        }
        return 0;
    }
    int getSize() const { return razmer; }
    T getElement(int index) const { return nachalo[index]; }
    void push_back(T value) {
        if constexpr (std::is_integral_v<T>) {
            if (value < -100 || value > 100) {
                throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100] (push_back)");
            }
        }

        T* newArray = new T[razmer + 1];
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
    double distanceTo(const DynamicArray& arr2) const {
        if constexpr (std::is_arithmetic_v<T>) {
            if (razmer != arr2.razmer) {
                throw std::invalid_argument("Размеры массивов должны быть одинаковыми");
            }
            double sum = 0.0;
            for (int i = 0; i < razmer; i++) {
                double diff = static_cast<double>(nachalo[i]) - static_cast<double>(arr2.nachalo[i]);
                sum += diff * diff;
            }
            return std::sqrt(sum);
        } else {
            throw std::bad_typeid();
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const DynamicArray<T>& arr)
{
    for (int i = 0; i < arr.getSize(); i++) {
        stream << arr.getElement(i) << " ";
    }
    return stream;
}

int main() {
    std::cout << "=== Тест 1: выход за границы массива ===" << std::endl;
    try {
        DynamicArray<int> arr(3);
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        std::cout << arr << std::endl;

        std::cout << arr.get(1) << std::endl;

        std::cout << "Попытка получить элемент по индексу 10..." << std::endl;
        std::cout << arr.get(10) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Перехвачено std::out_of_range: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 2: недопустимое значение ===" << std::endl;
    try {
        DynamicArray<int> arr(3);
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        std::cout << arr << std::endl;

        std::cout << "Попытка установить значение 150..." << std::endl;
        arr.set(0, 150);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено std::invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 3: некорректный размер массива ===" << std::endl;
    try {
        std::cout << "Попытка создать массив размером -5..." << std::endl;
        DynamicArray<int> bad(-5);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено std::invalid_argument: " << e.what() << std::endl;
    }
    std::cout << "\n=== Корректная работа программы ===" << std::endl;
    try {
        DynamicArray<int> arr(3);
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        std::cout << arr << std::endl;

        arr.push_back(40);
        std::cout << arr << std::endl;

        DynamicArray<int> arr2(arr);
        std::cout << arr2 << std::endl;

        arr.sumOrSub(arr2);
        std::cout << arr << std::endl;

    arr.sumOrSub(arr2);
    arr.showArray();

    std::cout << "\n=== Пример использования переопределения оператора << ===" << std::endl;
    try {
        DynamicArray<int> first(3);
        first.set(0, 1);
        first.set(1, 2);
        first.set(2, 3);

        DynamicArray<int> second(2);
        second.set(0, 100);
        second.set(1, -100);

        std::cout << "Вывод первого массива: ";
        std::cout << first << std::endl;

        std::cout << "Вывод второго массива: ";
        std::cout << second << std::endl;

        std::cout << "Демонстрация цепочки вызовов: " << std::endl;
        std::cout << "Массив 1: " << first << "| Массив 2: " << second << std::endl;

        DynamicArray<double> dblArr(3);
        dblArr.set(0, 1.5);
        dblArr.set(1, 2.25);
        dblArr.set(2, 3.75);
        std::cout << "Вывод массива типа double: ";
        std::cout << dblArr << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Перехвачено std::exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Задание 3: Расстояние между массивами ===" << std::endl;
    try {
        DynamicArray<int> vec1(3);
        vec1.set(0, 1);
        vec1.set(1, 2);
        vec1.set(2, 3);

        DynamicArray<int> vec2(3);
        vec2.set(0, 4);
        vec2.set(1, 5);
        vec2.set(2, 6);

        std::cout << "Вектор 1: " << vec1 << std::endl;
        std::cout << "Вектор 2: " << vec2 << std::endl;
        std::cout << "Расстояние: " << vec1.distanceTo(vec2) << std::endl;

        std::cout << "\nПопытка найти расстояние между массивами разного размера..." << std::endl;
        DynamicArray<int> vec3(2);
        vec3.set(0, 1);
        vec3.set(1, 2);
        std::cout << "Расстояние: " << vec1.distanceTo(vec3) << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено std::invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "\nПопытка найти расстояние для нечислового типа..." << std::endl;
    try {
        DynamicArray<std::string> strArr1(2);
        strArr1.set(0, "A");
        strArr1.set(1, "B");

        DynamicArray<std::string> strArr2(2);
        strArr2.set(0, "C");
        strArr2.set(1, "D");

        std::cout << "Расстояние: " << strArr1.distanceTo(strArr2) << std::endl;
    }
    catch (const std::bad_typeid& e) {
        std::cout << "Перехвачено std::bad_typeid: нечисловой тип данных" << std::endl;
    }

    return 0;
}