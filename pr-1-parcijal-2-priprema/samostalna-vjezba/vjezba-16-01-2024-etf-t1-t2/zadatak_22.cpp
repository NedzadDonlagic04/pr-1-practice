#include<iostream>
#include<limits>
#include<optional>

constexpr std::size_t STUDENT_SIZE { 3 };

void clearBuffer();
void enterNum(float &, const char * const, const std::optional<float> = std::nullopt, const std::optional<float> = std::nullopt);

void enterStudentPoints(float &, const char * const);

[[nodiscard]] unsigned int getStudentGrade(const float);
[[nodiscard]] unsigned int howManyStudentsPassed(float (&)[STUDENT_SIZE]);
[[nodiscard]] const char* howManyStudentsPassedMessage(const unsigned int);

[[nodiscard]] unsigned int howManyStudentsHaveSameGrade(float (&)[STUDENT_SIZE]);
[[nodiscard]] const char* howManyStudentsHaveSameGradeMessage(const unsigned int);

int main() {
    float studentPoints[STUDENT_SIZE] { 0 };

    enterStudentPoints(studentPoints[0], "Unesite bodove za Tarika:\n");
    enterStudentPoints(studentPoints[1], "Unesite bodove za Bojana:\n");
    enterStudentPoints(studentPoints[2], "Unesite bodove za Mirzu:\n");

    // Debugging
/*     std::cout<<std::endl;
    std::cout<<studentPoints[0]<<' '<<studentPoints[1]<<' '<<studentPoints[2];
    std::cout<<std::endl; */

    const unsigned int studentsPassedCount { howManyStudentsPassed(studentPoints) };
    const unsigned int studentsWithSameGradeCount { howManyStudentsHaveSameGrade(studentPoints) };

    std::cout<<howManyStudentsPassedMessage(studentsPassedCount)<<std::endl;
    std::cout<<howManyStudentsHaveSameGradeMessage(studentsWithSameGradeCount)<<std::endl;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(float &num, const char * const outputText, const std::optional<float> min, const std::optional<float> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::cout<<"Uneseni broj treba biti veci od "<<min.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::cout<<"Uneseni broj treba biti manji od "<<max.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterStudentPoints(float &totalPoints, const char * const outputText) {
    float tempPoints {};

    std::cout<<outputText;
    enterNum(tempPoints, "I parcijalni ispit: ", 0, 20);
    totalPoints += tempPoints;

    enterNum(tempPoints, "II parcijalni ispit: ", 0, 20);
    totalPoints += tempPoints;

    enterNum(tempPoints, "Prisustvo: ", 0, 10);
    totalPoints += tempPoints;

    enterNum(tempPoints, "Zadace: ", 0, 10);
    totalPoints += tempPoints;

    enterNum(tempPoints, "Zavrsni ispit: ", 0, 40);
    totalPoints += tempPoints;

    std::cout<<std::endl;
}

unsigned int getStudentGrade(const float points) {
    if (points < 55) {
        return 5;
    } else if (points < 65) {
        return 6;
    } else if (points < 75) {
        return 7;
    } else if (points < 85) {
        return 8;
    } else if (points < 92) {
        return 9;
    }
    return 10;
}

unsigned int howManyStudentsPassed(float (&studentPoints)[STUDENT_SIZE]) {
    unsigned int stundetsPassedCounter { 0 };

    if (getStudentGrade(studentPoints[0]) != 5) {
        stundetsPassedCounter++;
    }
    if (getStudentGrade(studentPoints[1]) != 5) {
        stundetsPassedCounter++;
    }
    if (getStudentGrade(studentPoints[2]) != 5) {
        stundetsPassedCounter++;
    }

    return stundetsPassedCounter;
}

const char* howManyStudentsPassedMessage(const unsigned int count) {
    if (count == 0) {
        return "Nijedan student nije položio.";
    } else if (count == 1) {
        return "Jedan student je položio.";
    } else if (count == 2) {
        return "Dva studenta su položila.";
    }

    return "Sva tri studenta su položila.";
}

unsigned int howManyStudentsHaveSameGrade(float (&studentPoints)[STUDENT_SIZE]) {
    unsigned int studentsWithSameGrade { 0 };

    const unsigned int grade0 { getStudentGrade(studentPoints[0]) };    
    const unsigned int grade1 { getStudentGrade(studentPoints[1]) };    
    const unsigned int grade2 { getStudentGrade(studentPoints[2]) };    

    if (grade0 == grade1) {
        studentsWithSameGrade++;
    }
    if (grade1 == grade2) {
        studentsWithSameGrade++;
    }
    if (grade0 == grade2) {
        studentsWithSameGrade++;
    }

    return studentsWithSameGrade;
}

const char* howManyStudentsHaveSameGradeMessage(const unsigned int count) {
    if (count == 0) {
        return "Svaki student ima različitu ocjenu.";
    } else if (count == 1) {
        return "Dva od tri studenta imaju istu ocjenu.";
    }

    return "Sva tri studenta imaju istu ocjenu";
}