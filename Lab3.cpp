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

class CBaseFactory {
public:
	virtual CBase* createDesc() = 0;
	virtual ~CBaseFactory() {}
};

class CDesc_1Factory : public CBaseFactory {
public:
	CDesc_1Factory() {
		cout << "CDesc_1Factory::CDesc_1Factory()\n";
	}
	CBase* createDesc() override {
		cout << "CDesc_1Factory::createDesc()\n";
		return new CDesc_1();
	}
};

class CDesc_2Factory : public CBaseFactory {
public:
	CDesc_2Factory() {
		cout << "CDesc_2Factory::CDesc_2Factory()\n";
	}
	CBase* createDesc() override {
		cout << "CDesc_2Factory::createDesc()\n";
		return new CDesc_2();
	}
};

class CDesc_3Factory : public CBaseFactory {
public:
	CDesc_3Factory() {
		cout << "CDesc_3Factory::CDesc_3Factory()\n";
	}
	CBase* createDesc() override {
		cout << "CDesc_3Factory::createDesc()\n";
		return new CDesc_3();
	}
};

class CDesc_4Factory : public CBaseFactory {
public:
	CDesc_4Factory() {
		cout << "CDesc_4Factory::CDesc_4Factory()\n";
	}
	CBase* createDesc() override {
		cout << "CDesc_4Factory::createDesc()\n";
		return new CDesc_4();
	}
};

//-----------------------

class IList {
public:
	virtual void add(CBase* obj) = 0;
	virtual CBase* get_value() = 0;
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isEOL() = 0;
};

class MyStorage : public IList {

private:

	CBase* data[10]{};
	int curr{};

public:

	MyStorage() {
		curr = 0;
	}

	void add(CBase* obj) {
		data[curr] = obj;
		curr++;
	}

	CBase* get_value() {
		return data[curr];
	}
	void first() {
		curr = 0;
	}
	void next() {
		curr++;
	}
	bool isEOL() {
		return curr > 9;
	}
};

//-----------------------

int main()
{
	srand(time(0));

	MyStorage* storage = new MyStorage();

	for (int i = 0; i < 10; i++)
	{

		CBaseFactory* factory{};

		if (rand() % 4 == 0)
			factory = new CDesc_1Factory();
		else if (rand() % 4 == 1)
			factory = new CDesc_2Factory();
		else if (rand() % 4 == 2)
			factory = new CDesc_3Factory();
		else
			factory = new CDesc_4Factory();

		storage->add(factory->createDesc());

		cout << endl;
	}

	for (storage->first(); !storage->isEOL(); storage->next())
		storage->get_value()->classname();

    return 0;
}
