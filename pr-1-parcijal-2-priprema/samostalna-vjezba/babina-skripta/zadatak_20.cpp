#include<iostream>
#include<cmath>

constexpr unsigned int SECONDS_TO_COUNT_TO { 20u };
constexpr float GRAVITY { 9.81 };

[[nodiscard]] float calcSpeedOfFreeFall(const unsigned int);
[[nodiscard]] float calcDistanceTraveled(const unsigned int);

int main() {
    for (unsigned int time = 3; time <= SECONDS_TO_COUNT_TO; time += 3) {
        std::cout<<"Situacija u "<<time<<"-oj sekundi je:\n";
        std::cout<<"Brzina: "<<calcSpeedOfFreeFall(time)<<std::endl;
        std::cout<<"Predjeni put: "<<calcDistanceTraveled(time)<<std::endl;
    }

    return 0;
}

float calcSpeedOfFreeFall(const unsigned int time) {
    return GRAVITY * time;
}

float calcDistanceTraveled(const unsigned int time) {
    return (GRAVITY / 2) * std::pow(time, 2); 
}