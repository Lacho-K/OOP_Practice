#include <iostream>

struct Vector
{
    int* nums;
    size_t lenght;
};

Vector createVector(size_t size)
{
    Vector v;
    v.nums = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        int curr;
        std::cin >> curr;
        v.nums[i] = curr;
    }
    v.lenght = size;
    return v;
}

Vector* createVectors(size_t count)
{
    Vector* res = new Vector[count];

    for (size_t i = 0; i < count; i++)
    {
        res[i] = createVector(3);
    }

    return res;
}

void printVector(const Vector& v)
{
    for (size_t i = 0; i < v.lenght; i++)
    {
        std::cout << v.nums[i] << " ";
    }
    std::cout << std::endl;
}

int add(int n1, int n2)
{
   return n1 + n2;
}

int substract(int n1, int n2)
{
    return n1 - n2;
}

Vector sumOrSubstractVectors(const Vector& v1, const Vector& v2, int (*op)(int,int))
{
    size_t biggerSize = v1.lenght > v2.lenght ? v1.lenght : v2.lenght;

    Vector result;

    result.lenght = biggerSize;
    result.nums = new int[biggerSize] {};

    for (size_t i = 0; i < biggerSize; i++)
    {
        if (i < v1.lenght && i < v2.lenght)
            result.nums[i] = op(v1.nums[i], v2.nums[i]);
        else if (i > v1.lenght)
            result.nums[i] = v2.nums[i];
        else
            result.nums[i] = v1.nums[i];
    }

    return result;
}

Vector multiplyByScalar(const Vector& v, int scalar)
{
    Vector res;
    res.nums = new int[v.lenght];
    
    for (size_t i = 0; i < v.lenght; i++)
    {
        res.nums[i] = scalar * v.nums[i];
    }

    return res;
}

int dotProduct(const Vector& v1, const Vector& v2)
{
    size_t smallerSize = v1.lenght < v2.lenght ? v1.lenght : v2.lenght;

    int res = 0;

    for (size_t i = 0; i < smallerSize; i++)
    {
        res += (v1.nums[i] * v2.nums[i]);
    }

    return res;
}

bool isTherePerpendicularTriplets(Vector* vectors, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            for (size_t k = j + 1; k < n; k++)
            {
                if (dotProduct(vectors[i], vectors[j]) == 0
                    && dotProduct(vectors[j], vectors[k]) == 0
                    && dotProduct(vectors[i], vectors[k]) == 0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    //Vector v1 = createVector(5);
    //Vector v2 = createVector(3);

    //printVector(sumOrSubstractVectors(v1, v2, add));
    //printVector(sumOrSubstractVectors(v1, v2, substract));
    int n;
    std::cin >> n;
    Vector* vectors = createVectors(n);
    std::cout << isTherePerpendicularTriplets(vectors, n);
}
