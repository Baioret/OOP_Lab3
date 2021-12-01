#include <iostream>
#include <ctime>

using namespace std;

class CBase {

public:

	virtual void classname() = 0;
	virtual ~CBase() {
		cout << "~CBase()\n\n";
	}
};

class CDesc_1 : public CBase {

public:

	CDesc_1() {
		cout << "CDesc_1::CDesc_1()\n";
	}

	~CDesc_1() {
		cout << "CDesc_1::~CDesc_1()\n";
	}

	void classname() override {
		cout << "CDesc_1::classname\n";
	}

	virtual void mew()
	{
		cout << "CDesc_1::mew()\n";
	}
};

class CDesc_2 : public CDesc_1 {

public:

	CDesc_2() {
		cout << "CDesc_2::CDesc_2()\n";
	}

	~CDesc_2() {
		cout << "CDesc_2::~CDesc_2()\n";
	}

	void classname() override {
		cout << "CDesc_2::classname\n";
	}

	void mew() override
	{
		cout << "CDesc_2::mew2()\n";
	}
};

class CDesc_3 : public CBase {

public:

	CDesc_3() {
		cout << "CDesc_3::CDesc_3()\n";
	}

	~CDesc_3() {
		cout << "CDesc_3::~CDesc_3()\n";
	}

	void classname() override {
		cout << "CDesc_3::classname\n";
	}

	virtual void bark()
	{
		cout << "CDesc_3::bark()\n";
	}
};

class CDesc_4 : public CDesc_3 {

public:

	CDesc_4() {
		cout << "CDesc_4::CDesc_4()\n";
	}

	~CDesc_4() {
		cout << "CDesc_4::~CDesc_4()\n";
	}

	void classname() override {
		cout << "CDesc_4::classname\n";
	}

	void bark() override
	{
		cout << "CDesc_4::bark2()\n";
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

		size++;

		CBase** tmp = new CBase * [size]();

		for (int i = 0; i < size - 1; i++)
			tmp[i] = data[i];

		data = tmp;
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
};

//-----------------------

void addition(MyStorage& storage) {

	if (rand() % 4 == 0)
		storage.add(new CDesc_1);
	else if (rand() % 4 == 1)
		storage.add(new CDesc_2);
	else if (rand() % 4 == 2)
		storage.add(new CDesc_3);
	else
		storage.add(new CDesc_4);

	cout << endl;
}

void cycle(MyStorage& storage, int count) {

	storage.first();

	int t1 = clock();

	for (int i = 0; i < count; i++)
		if (!storage.isEOL())
		{
			if (storage.getObject() != NULL)
			{
				if (rand() % 4 == 0) {
					storage.del(storage.getObject());
					storage.next();
				}
				else if (rand() % 4 == 1) {
					storage.getObject()->classname();
					storage.next();
				}
				else if (rand() % 4 == 2)
				{
					if (dynamic_cast<CDesc_1*>(storage.getObject()) != NULL)
						dynamic_cast<CDesc_1*>(storage.getObject())->mew();
					else if (dynamic_cast<CDesc_3*>(storage.getObject()) != NULL)
						dynamic_cast<CDesc_3*>(storage.getObject())->bark();

					storage.next();
				}
				else addition(storage);
			}
			else addition(storage);
		}
		else
			storage.first();

	int t2 = clock();

	int t = t2 - t1;
	cout << "\nTIME = " << t / 1000.0;
}

int main()
{
	srand(time(0));

	MyStorage storage;

	for (int i = 0; i < 10; i++)
		addition(storage);

	cout << "THE FIRST 10 ELEMENTS: " << endl << endl;

	for (storage.first(); !storage.isEOL(); storage.next())
		storage.getObject()->classname();

	cout << "\nCYCLE 100!" << endl << endl;
	cycle(storage, 100);

	cout << "\nCYCLE 1000!" << endl << endl;
	//cycle(storage, 1000);

	cout << "\nCYCLE 10000!" << endl << endl;
	//cycle(storage, 10000);

	return 0;
}