#include "gcs.h"
#include <cstring>
#include <iostream>
#include <iomanip>


using namespace std;

GCS::GCS(char const * const name) :
	name(new char[strlen(name)+1])

{
	strcpy(this->name, name);
}

GCS::~GCS()
{
	delete[] name;
}

GCS& GCS::operator=(const GCS& gcs)
{
	if (this == &gcs)
		{
			return *this;
		}

		delete[] name;
		name = NULL;

		name = new char[strlen(gcs.name)+1];
		strcpy(this->name, gcs.name);


	return *this;
}

GCS::GCS(const GCS& source)
{
}

void GCS::setName(char const * const name)
{

	delete[] this->name;
	this->name = NULL;
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);

}

bool operator<(const GCS& gcs1, const GCS& gcs2)
{
	return strcmp(gcs1.getName(), gcs2.getName()) < 0;
}

bool operator==(const GCS& gcs1, const GCS& gcs2)
{
	return strcmp(gcs1.getName(), gcs2.getName()) == 0;
}

ostream& operator<<(ostream& out, const GCS& gcs)
{
	out << gcs.name;

	return out;
}
