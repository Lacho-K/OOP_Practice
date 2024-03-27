#include <iostream>
#include <fstream>
#pragma warning(disable : 4996)

const unsigned MAX_LEN_NAME = 30;

enum Department
{
    Algebra,
    Geometry,
    ComputerScience,
    Default
};

Department convertStrToDepartment(const char* dep)
{
    if (strcmp(dep, "Algebra") == 0) return Algebra;
    if (strcmp(dep, "Geometry") == 0) return Geometry;
    if (strcmp(dep, "ComputerScience") == 0) return ComputerScience;
    return Default;
}

struct Student
{
private:
    char firstName[30];
    char lastName[30];
    unsigned fn;
    unsigned grades[32];
    unsigned gradesCount = 0;

    unsigned calcGradesSum()
    {
        unsigned sum = 0;

        for (size_t i = 0; i < gradesCount; i++)
        {
            sum += grades[i];
        }

        return sum;
    }

public:


    Student()
    {
        setFirstName("test");
        setLastName("testov");
        setFN(0);
        const unsigned grades[5] = { 2,3,4,5,6 };
        setGrades(grades, 5);
    }

    Student(const char* firstName, const char* lastName, unsigned fn, const unsigned* grades, unsigned gradesCount)
    {
        setFirstName(firstName);
        setLastName(lastName);
        setFN(fn);
        setGrades(grades, gradesCount);
    }

    const char* getFirstName()
    {
        return this->firstName;
    }

    void setFirstName(const char* value)
    {
        if(strlen(value) < MAX_LEN_NAME)
        strcpy(firstName, value);
    }
    
    const char* getLastName()
    {
        return this->lastName;
    }

    void setLastName(const char* value)
    {
        if(strlen(value) < MAX_LEN_NAME)
        strcpy(lastName, value);
    }

    const unsigned getFN()
    {
        return this->fn;
    }

    void setFN(unsigned value)
    {
        this->fn = value;
    }

    const unsigned* getGrades()
    {
        return this->grades;
    }

    void setGrades(const unsigned* newGrades, size_t gradesLen)
    {
        for (size_t i = 0; i < gradesLen; i++)
        {
            this->grades[i] = newGrades[i];
        }
        this->gradesCount = gradesLen;
    }

    const unsigned getGradesCount()
    {
        return this->gradesCount;
    }

    void setGradeCount(unsigned gradesCount)
    {
        this->gradesCount = gradesCount;
    }

    void AddGrade(unsigned grade)
    {
        this->grades[gradesCount++] = grade;
    }

    void RemoveGrade(unsigned grade)
    {
        for (size_t i = 0; i < gradesCount; i++)
        {
            if (grades[i] == grade)
            {
                for (size_t j = i; j < gradesCount-1; j++)
                {
                    grades[j] = grades[j + 1];
                }

                this->gradesCount--;
            }
        }
    }

    const double CalcAvg()
    {
        return calcGradesSum() / gradesCount;
    }
};

struct Teacher
{
private:
    char firstName[30];
    char lastName[30];
    Department department;

public:

    Teacher()
    {
        setFirstName("");
        setLastName("");
        setDepartment(Default);
    }

    Teacher(const char* firstName, const char* lastName, Department department)
    {
        setFirstName(firstName);
        setLastName(lastName);
        setDepartment(department);
    }


    const char* getFirstName() const
    {
        return this->firstName;
    }

    void setFirstName(const char* value)
    {
        if (strlen(value) < MAX_LEN_NAME)
            strcpy(firstName, value);
    }

    const char* getLastName()
    {
        return this->lastName;
    }

    void setLastName(const char* value)
    {
        if (strlen(value) < MAX_LEN_NAME)
            strcpy(lastName, value);
    }

    const char* getDepartment()
    {
        switch (this->department)
        {
            case Algebra:
                return "Algebra";
            case Geometry:
                return "Geometry";
            case ComputerScience:
                return "Computer Science";
            default:
                return "invalid";
        }
    }

    void setDepartment(Department department)
    {
        this->department = department;
    }
};

struct Subject
{
private:

    Teacher teacher;
    unsigned studentsCount = 0;
    Student students[100];

public:

    Subject()
    {
        Teacher defaultTeacher;
        setTeacher(teacher);
        Student defaultStudents[100];
        setStudents(defaultStudents, 0);
        setStudentsCount(0);
    }

    Subject(const Teacher teacher, const unsigned studentsCount, const Student* students)
    {
        setTeacher(teacher);
        setStudentsCount(studentsCount);
        setStudents(students, this->studentsCount);
    }

    const Teacher& getTeacher()
    {
        return this->teacher;
    }

    void setTeacher(const Teacher& other)
    {
        this->teacher = other;
    }

    const unsigned getStudentsCount()
    {
        return this->studentsCount;
    }

    void setStudentsCount(unsigned count)
    {
        this->studentsCount = count;
    }

    const Student* getStudents()
    {
        return this->students;
    }

    void setStudents(const Student* students, size_t studentsCount)
    {
        for (size_t i = 0; i < studentsCount; i++)
        {
            this->students[i] = students[i];
        }
        setStudentsCount(studentsCount);
    }

    void AddStudent(const Student& student)
    {
        this->students[studentsCount++] = student;
    }

    void HireTeacher(const Teacher& teacher)
    {
        setTeacher(teacher);
    }

    void serialize(const char* fileName)
    {
        std::ofstream output(fileName);

        output << this->teacher.getFirstName() << "\n";
        output << this->teacher.getLastName() << "\n";
        output << this->teacher.getDepartment() << "\n";
        output << this->studentsCount << "\n";

        for (size_t i = 0; i < this->studentsCount; i++)
        {
            output << students[i].getFirstName() << "\n";
            output << students[i].getLastName() << "\n";
            output << students[i].getFN() << "\n";
            const unsigned gradesCount = students[i].getGradesCount();
            output << gradesCount << "\n";
            const unsigned* grades = students[i].getGrades();
            for (size_t j = 0; j < gradesCount; j++)
            {
                output << grades[j] << " ";
            }
            output << "\n";
        }

    }

    void deserialize(const char* fileName)
    {
        std::ifstream input(fileName);

        char firstName[30];
        input >> firstName;
        char lastName[30];
        input >> lastName;
        char dep[16];
        input >> dep;

        Teacher teacher(firstName, lastName, convertStrToDepartment(dep));
        
        unsigned studentsCount;
        input >> studentsCount;
        for (size_t i = 0; i < studentsCount; i++)
        {
            char sFirstName[30];
            input >> sFirstName;
            char sLastName[30];
            input >> sLastName;
            unsigned fn;
            input >> fn;
            unsigned gradesCount;
            input >> gradesCount;
            unsigned grades[32]{0};

            Student student(sFirstName, sLastName, fn, grades, 0);

            for (size_t i = 0; i < gradesCount; i++)
            {
                unsigned currentGrade;
                input >> currentGrade;

                student.AddGrade(currentGrade);
            }

            this->AddStudent(student);

        }

        this->HireTeacher(teacher);

    }
};

int main()
{
    Teacher teacher("Gosho", "Goshev", Algebra);
    Student students[2];


    Subject sub;
    sub.deserialize("output.txt");
    std::cout << sub.getTeacher().getFirstName();
}
