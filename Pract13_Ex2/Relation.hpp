#pragma once
#pragma warning (disable:4996)
template<class T>
class Relation
{
	T subject;
	T object;
	char* relation = nullptr;
	void copyFrom(const Relation& rel)
	{
		subject = rel.subject;
		object = rel.object;
		this->relation = new char[strlen(rel.relation) + 1];
		strcpy(relation, rel.relation);
	}
	void free()
	{
		delete[] relation;
	}

public:
	Relation() = default;

	Relation(const Relation& rel)
	{
		copyFrom(rel);
	}

	Relation(T subject, T object, const char* relation)
	{
		this->subject = subject;
		this->object = object;
		this->relation = new char[strlen(relation) + 1];
		strcpy(this->relation, relation);
	}

	Relation& operator=(const Relation& rel)
	{
		if (this != &rel)
		{
			free();
			copyFrom(rel);
		}
		return *this;
	}

	void print()
	{
		std::cout << subject << " " << relation << " " << object;
	}


	~Relation()
	{
		free();
	}
};
