#include <iostream>

template <class T>
class PriceTag
{
	unsigned double _price = 0;
	T _product;

public:
	PriceTag() = default;
	PriceTag(double price, const T& product);

	const double getPrice() const;
	void setPrice(double price);

	const T& getProduct() const;
	void setProduct(const T& product);

	friend std::istream& operator >> (std::istream is, const PriceTag& pt);
	friend std::ostream& operator << (std::ostream os, const PriceTag& pt);

	void discount(unsigned double discountAmount);
};

template <class T>
PriceTag<T>::PriceTag(double price, const T& product) : _price(price), _product(product) {}

template <class T>
const double PriceTag<T> :: getPrice() const
{
	return _price
}

template <class T>
void PriceTag<T> ::setPrice(double price)
{
	if (price < 0)
		throw std::exception("price must be > 0");

	_price = price;
}

template <class T>
const T& PriceTag<T>::getProduct() const
{
	return _product;
}

template <class T>
std::istream& operator>> (std::istream& is, const PriceTag<T>& pt)
{
	
}

template <class T>
std::ostream& operator<< (std::ostream& os, const PriceTag<T>& pt)
{
	return os << pt._price << pt._product;
}