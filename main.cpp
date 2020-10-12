#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

constexpr unsigned int MB256BT = 256 * 1024 * 1024; // количество байт в 256 Мб
constexpr unsigned int NUMELEMENT64 = MB256BT / 8; //Количество элементов в памяти

uint64_t convertCharToUInt64(const unsigned char* buf) {
    uint64_t num(0);
    for (int i = 7; i > 0; i--) {
        num += buf[i];
        num = num << 8;
    }
    num += buf[0];
    return num;
}

void bubbleSort(uint64_t* arr, size_t &size) {
    for (size_t i = 0; i < size; i++)
        for (size_t y = 0; y < size; y++)
            if (arr[y] > arr[y + 1])
                std::swap(arr[y], arr[y + 1]);
}

void mysort(uint64_t* beg, uint64_t* end) {
    if (beg == end)
        return;
    uint64_t* l = beg;
    uint64_t* r = end;
    uint64_t* piv = l++;
    while (l != r) {
        if (*l < *piv)
            l++;
        else {
            while ((l != --r) && (*piv < *r));
            std::swap(l, r);
        }
    }
    --l;
    std::swap(l, r);
    mysort(beg, l);
    mysort(r, end);
}

int main(int argc, char** argv) {
    //if (argc != 3) {
    //    std::cout << "Error input parametrs";
    //    return 1;
    //}
    //char* fileInputName = argv[1];
    //char* fileOutputName = argv[2];

    const std::string fileInputName = "D:\\temp\\bigFile\\myfile";
    const std::string fileOutputName = "D:\\temp\\bigFile\\outfile";
    const std::string fileTempName = "file_temp";

    std::ifstream fileInput(fileInputName, std::ios::in | std::ios::binary);
    std::ofstream fileOutput(fileOutputName, std::ios::out | std::ios::binary);

    if (!fileInput.is_open()) {
        std::cout << "Error open input file";
        return 2;
    }
    uint64_t* buff = new uint64_t[NUMELEMENT64];
    size_t countFiles(0);
    while (!fileInput.eof()) {
        fileInput.read((char*)buff, MB256BT);
       // std::sort(buff, (buff + NUMELEMENT64));
        std::ofstream partFile(fileTempName + std::to_string(countFiles), std::ios::out | std::ios::binary);
        partFile.write((char*)buff, MB256BT);
        partFile.close();
        countFiles++;
    }
    fileInput.close();
    delete[] buff;
    
    std::vector<uint64_t> vec(countFiles);
    std::ifstream* files = new std::ifstream[countFiles];
    uint64_t* ch = new uint64_t;

    for (int i = 0; i <= countFiles; i++) {
        *(fl+i).(fileTempName + std::to_string(countFiles), std::ios::in | std::ios::binary);
        fl.seekp(vec[i].second, std::ios::beg);
        fl.read((char*)ch, sizeof(uint64_t));
        it.second += sizeof(uint64_t);
        auto ds = std::distance(lstFiles.firbegin(), it);
        vec[ds] = ch;
    }




    return 0;
}
