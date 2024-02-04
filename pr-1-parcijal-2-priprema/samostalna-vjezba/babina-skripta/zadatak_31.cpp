#include<iostream>
#include<cmath>
#include<limits>

void clearBuffer();
void printErrorMsg(const char * const);

void enterNum(int &, const char * const);
[[nodiscard]] float getGeometricAverage(const int);

int main() {
    int n {};

    enterNum(n, "Unesi cijeni broj (N): ");
    std::cout<<"U intervalu [1, "<<n<<"] geometrijska sredina brojeva je: "<<getGeometricAverage(n)<<std::endl;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

float getGeometricAverage(const int n) {
    float sum { 1.0f };

    for (int i = 1; i <= n; i += 2) {
        if (i % 5 == 0) {
            continue;
        }

        sum *= i; 
    }

    return std::pow(sum, 1.0f / n);
}