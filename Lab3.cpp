#include <iostream>

using namespace std;

class CBase {

public:

	virtual void classname() = 0;
	virtual ~CBase() {
		cout << "~CBase()\n";
	}
};

class CDesc_1 : public CBase {

public:

	CDesc_1() {
		cout << "CDesc_1::CDesc_1()\n";
	}

	void classname() override {
		cout << "CDesc_1::classname\n";
	}
};

class CDesc_2 : public CBase {

public:

	CDesc_2() {
		cout << "CDesc_2::CDesc_2()\n";
	}

	void classname() override {
		cout << "CDesc_2::classname\n";
	}
};

class CDesc_3 : public CBase {

public:

	CDesc_3() {
		cout << "CDesc_3::CDesc_3()\n";
	}

	void classname() override {
		cout << "CDesc_3::classname\n";
	}
};

class CDesc_4 : public CBase {

public:

	CDesc_4() {
		cout << "CDesc_4::CDesc_4()\n";
	}

	void classname() override {
		cout << "CDesc_4::classname\n";
	}
};

//-----------------------

class IList {
public:
	virtual void add(CBase* obj) = 0;
	virtual void del(CBase* obj) = 0;
	virtual CBase* getObject() = 0;
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isEOL() = 0;
};

class MyStorage : public IList {

private:

	CBase** data{};
	int curr = 0;
	int size = 10;
	int count = 0;

	void resize() {

		CBase** tmp = new CBase * [size + 1]();

		for (int i = 0; i < size; i++)
			tmp[i] = data[i];

		data = tmp;

		size++;
	}

public:

	MyStorage() {
		data = new CBase * [size]();
		this->first();
	}

	void add(CBase* obj) {

		if (this->isEOL())
		{
			if (count < curr) {
				for (int i = 0; i < size; i++)
					if (data[i] == NULL) {
						data[i] = obj;
						count++;
						return;
					}
			}

			this->resize();
		}

		data[curr] = obj;
		curr++;
		count++;
	}

	void del(CBase* obj) {
		delete obj;
		data[curr] = NULL;
		count--;
	}

	CBase* getObject() {
		return data[curr];
	}

	void first() {
		curr = 0;
	}

	void next() {
		curr++;
	}

	bool isEOL() {
		return curr > size - 1;
	}

	/*void getCount() {
		cout << count << endl;
	}*/
};

//-----------------------

int main()
{
	srand(time(0));

	MyStorage* storage = new MyStorage();

	for (int i = 0; i < 14; i++)
	{

		if (rand() % 4 == 0)
			storage->add(new CDesc_1);
		else if (rand() % 4 == 1)
			storage->add(new CDesc_2);
		else if (rand() % 4 == 2)
			storage->add(new CDesc_3);
		else
			storage->add(new CDesc_4);

		cout << endl;
		//storage->getCount();
	}

	for (storage->first(); !storage->isEOL(); storage->next())
		if (storage->getObject() != NULL)
		{
			if (rand() % 2 == 0)
				storage->getObject()->classname();
			else
				storage->del(storage->getObject());
		}
		else
			cout << "NULL\n";

	for (int i = 0; i < 3; i++)
	{

		if (rand() % 4 == 0)
			storage->add(new CDesc_1);
		else if (rand() % 4 == 1)
			storage->add(new CDesc_2);
		else if (rand() % 4 == 2)
			storage->add(new CDesc_3);
		else
			storage->add(new CDesc_4);

		cout << endl;
		//storage->getCount();
	}

	for (storage->first(); !storage->isEOL(); storage->next())
		if (storage->getObject() != NULL)
			storage->getObject()->classname();
		else
			cout << "NULL\n";

	return 0;
}

