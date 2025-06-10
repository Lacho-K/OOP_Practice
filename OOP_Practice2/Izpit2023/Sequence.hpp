#pragma once
#include <stdexcept>

template<typename T>
class Sequence
{
public:
    T operator[](unsigned index) const;

    class SequenceIter;

    Sequence(T firstEl, unsigned countEls, T(*nextFunc)(T el));

    SequenceIter begin() const;
    SequenceIter end() const;

private:
    T startEl;
    unsigned countElements;
    T(*nextFunc)(T el);

    class SequenceIter
    {
    public:
        SequenceIter(const Sequence<T>* parent, unsigned index);
        bool operator!=(const SequenceIter& other) const;
        T operator*() const;
        SequenceIter& operator++();

    private:
        const Sequence<T>* parent;
        unsigned index;
    };
};

template<typename T>
inline T Sequence<T>::operator[](unsigned index) const
{
    if (index >= countElements) {
        throw std::out_of_range("Index out of bounds for Sequence.");
    }

    T res = startEl;
    for (unsigned i = 0; i < index; ++i)
    {
        res = nextFunc(res);
    }
    return res;
}

template<typename T>
inline Sequence<T>::Sequence(T firstEl, unsigned countEls, T(*nextFunc)(T el))
    : startEl(firstEl), countElements(countEls), nextFunc(nextFunc)
{}

template<typename T>
inline typename Sequence<T>::SequenceIter Sequence<T>::begin() const
{
    return SequenceIter(this, 0);
}

template<typename T>
inline typename Sequence<T>::SequenceIter Sequence<T>::end() const
{
    return SequenceIter(this, countElements);
}

template<typename T>
Sequence<T>::SequenceIter::SequenceIter(const Sequence<T>* parent, unsigned index)
    : parent(parent), index(index)
{}

template<typename T>
bool Sequence<T>::SequenceIter::operator!=(const SequenceIter& other) const
{
    return index != other.index;
}

template<typename T>
T Sequence<T>::SequenceIter::operator*() const
{
    return (*parent)[index];
}

template<typename T>
typename Sequence<T>::SequenceIter& Sequence<T>::SequenceIter::operator++()
{
    index++;
    return *this;
}