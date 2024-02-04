#include<iostream>
#include<limits>
#include<optional>

constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] int getRandomNum();
[[nodiscard]] unsigned int getSumOfNumDivisors(const int);
[[nodiscard]] bool isPerfectNum(const int);

[[nodiscard]] float getPercentPerfectNumAppearance(const int);

int main() {
    std::srand(time(NULL));

    int n {};

    enterNum(n, "Unesi broj (n): ", 10, 1000);

    std::cout<<"Nakon n ("<<n<<") simulacija slucajnih vrijednosti savrsen broj se pojavio samo ";
    std::cout<<getPercentPerfectNumAppearance(n)<<"%\n";

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

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};
    char errorMsg[BUFFER_SIZE];

    do {
        repeatLoop = false; 

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti manji od %d\n", min.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti veci od %d\n", max.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

int getRandomNum() {
    return std::rand() % 1000 + 1;
}

unsigned int getSumOfNumDivisors(const int num) {
    unsigned int sum { 1 };

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;

            if (i != (num / i)) {
                sum += (num / i);
            }
        }
    }

    // Debuggin
    // std::cout<<sum<<std::endl;

    return sum;
}

bool isPerfectNum(const int num) {
    if (num <= 1) {
        return false;
    }

    return num == getSumOfNumDivisors(num);
}

float getPercentPerfectNumAppearance(const int num) {
    int counter { 0 };
    int randomNum {};

    for (int i = 0; i < num; i++) {
        randomNum = getRandomNum();

        if (isPerfectNum(randomNum)) {
            // Debugging
            // std::cout<<randomNum<<' ';
            counter++;
        }
    }

    return (counter)? (counter / static_cast<float>(num)) * 100 : 0.0f;
}