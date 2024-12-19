#pragma once
#include <string>

template <typename T>
class IteratorVector;

template<typename T>
class MyVector {
friend class IteratorVector<T>;

private:
	size_t cap;
	size_t lg;
	T* elems;
	void resize();
public:
	//Constructor care creeaza vector cu capacitate default = 1
	MyVector() : cap{ 1 }, lg{ 0 }, elems{ new T[cap] } {};
	//Constructor care creeaza vector cu capacitate initiala data
	MyVector(const size_t initialCapacity) : cap{ initialCapacity }, lg{ 0 }, elems{ new T[initialCapacity]} {};
	//copy constructor
	//apelat cand avem:
	// MyVector v = v2, v2 vector existent, initializat
	// MyVector v{v2}
	// transmitere prin valoare
	// returnare prin valoare
	MyVector(const MyVector& v);
	//apelat cand avem:
	//v1, v2 vectori existenti, initializati
	//v1 = v2
	MyVector& operator=(const MyVector& v);


	//Adauga elementul dat in vector
	void push_back(T elem);

	//subscript operator - varianta non-const
	T& operator[](size_t index);
	//subscript operator - varianta const
	//folosita pentru vectori const
	//adaugata ulterior seminarului dupa 
	//inlocuirea std::vector cu myVector
	const T& operator[](size_t index) const;

	//returneaza numarul de elemente din vector
	size_t size() const { return this->lg; };

	//returneaza iterator setat la inceputul vectorului - varianta const
	const IteratorVector<T> begin() const { return IteratorVector<T>(*this); };
	//returneaza iterator setat la sfarsitul vectorului - varianta const
	const IteratorVector<T> end() const {
		return IteratorVector<T>(*this, this->lg);
	};

	//returneaza iteratori setati la inceputul, respectiv sfarsitul vectorului
	//variantele non-const

	IteratorVector<T> begin() { return IteratorVector<T>(*this); };
	IteratorVector<T> end() { return IteratorVector<T>(*this, this->lg); };
	~MyVector();
};
template<typename T>
class IteratorVector {
private:
	const MyVector<T>& v;
	size_t current_index;
public:
	IteratorVector(const MyVector<T>& vecToIterate) :v{ vecToIterate } {
		this->current_index = 0;
	}

	IteratorVector(const MyVector<T>& vecToIterate, const size_t poz) :v{ vecToIterate }, current_index{ poz } {};
	
	const T& element() const;
	
	void next();
	bool valid() const noexcept;

	//*it
	const T& operator*();

	//++it
	IteratorVector& operator++();
	//it++
	IteratorVector& operator++(int);

	//necesari, spre exemplu, 
	//pentru compararea unui iterator cu cel returnat de 
	//v.begin(), v.end() in rang for
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;

};

template<typename T>
inline void MyVector<T>::resize()
{
	size_t newCapacity = this->cap * 2;
	T* newElems = new T[newCapacity];
	for (int i = 0; i < this->lg; i++)
		newElems[i] = this->elems[i];
	delete[] elems;
	this->elems = newElems;
	this->cap = newCapacity;
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector& v)
{
	if (this == &v)
		return;
	this->cap = v.cap;
	this->lg = v.lg;
	this->elems = new T[this->cap];
	for (int i = 0; i < this->lg; i++)
		this->elems[i] = v[i];
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector& v)
{
	if (this == &v)
		return *this;
	this->cap = v.cap;
	this->lg = v.lg;
	delete[] this->elems;
	this->elems = new T[this->cap];
	for (int i = 0; i < this->lg; i++)
		this->elems[i] = v[i];
	return *this;
}


template<typename T>
inline void MyVector<T>::push_back(T elem)
{
	if (this->lg == this->cap)
		resize();
	this->elems[this->lg++] = elem;
}

template<typename T>
inline T& MyVector<T>::operator[](size_t index)
{
	//poate fi implementat cu ajutorul variantei const
	//si folosirea const-cast/as_const pentru a evita duplicarea
	// codului
	//return const_cast<T&>(std::as_const(*this)[index]);
	if (index >= this->lg)
		throw std::out_of_range("Index out of bounds: " + std::to_string(index));
	return this->elems[index];

}

template<typename T>
inline const T& MyVector<T>::operator[](size_t index) const
{
	if (index >= this->lg)
		throw std::out_of_range("Index out of bounds: " + std::to_string(index));
	return this->elems[index];
}

template<typename T>
inline MyVector<T>::~MyVector()
{
	delete[] this->elems;
}

template<typename T>
inline const T& IteratorVector<T>::element() const
{
	return this->v[current_index];
}

template<typename T>
inline void IteratorVector<T>::next()
{
	if (this->current_index > this->v.lg)
		throw std::out_of_range("Invalid iterator.");
	this->current_index++;

}

template<typename T>
inline bool IteratorVector<T>::valid() const noexcept
{
	return (this->current_index < this->v.lg);
}

template<typename T>
inline const T& IteratorVector<T>::operator*()
{
	return this->element();
}

template<typename T>
inline IteratorVector<T>& IteratorVector<T>::operator++()
{
	this->next();
	return *this;
}

template<typename T>
inline IteratorVector<T>& IteratorVector<T>::operator++(int )
{
	this->next();
	return *this;
}

template<typename T>
inline bool IteratorVector<T>::operator==(const IteratorVector& ot) noexcept
{
	return this->current_index == ot.current_index;
}

template<typename T>
inline bool IteratorVector<T>::operator!=(const IteratorVector& ot) noexcept
{
	return !(*this == ot);
	//sau 	return this->current_index != ot.current_index;

}


