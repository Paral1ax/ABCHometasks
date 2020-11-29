#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include "omp.h"
#include "fstream"

/*
 * Горбач Илья Вадимович
 * БПИ 194
 * Вариант №7
 * Задание:7. Вычислить прямое произведение множеств А1, А2, А3… Аn.
Входные данные: целое положительное число n, множества чисел А1, А2,
А3… Аn, мощности множеств равны между собой и мощность каждого
множества больше или равна 1. Количество потоков является входным
параметром.
 */

int main() {
    system("chcp 65001");
    std::ofstream outf("Answer/answer3.txt");
    int n = 0;
    int countUnit = 0;
    std::set<int> tempSet;
    std::set<int> :: iterator it;
    std::vector<std::set<int>> v;

    std::cout << "Введите количество множеств: ";
    std::cin >> n;
    std::cout << "Введите количество чисел во множестве (n одинаково для всех множеств): ";
    std::cin >> countUnit;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < countUnit; j++) {
            int elementSet;
            std::cin >> elementSet;
            tempSet.insert(elementSet);
        }
        v.push_back(tempSet);
        tempSet.clear();
    }

    int temp = pow(countUnit, n) / countUnit;
    int theRepeat = 0;
    int temp_i = 0;

#pragma omp parallel for private(it)
    for(int i = 0; i < n; i++) {
        it = v[i].begin();
        std::vector<int> tempV;
#pragma omp parallel for private(tempV)
        for(int k = 0; k < countUnit; k++) {
            tempV.push_back(*it);
            it++;
        }
        for(int j = 0; j < pow(countUnit, n); j++) {
            if(theRepeat == temp) {
                theRepeat = 0;
                temp_i++;
                if(temp_i == countUnit)
                    temp_i = 0;
            }
            outf << tempV[temp_i]<< " ";
            theRepeat++;
        }
        outf << std::endl;
        temp /= countUnit;
        theRepeat = 0;
        temp_i = 0;
    }
    return 0;
}