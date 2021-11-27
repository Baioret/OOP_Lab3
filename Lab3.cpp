#include <iostream>

using namespace std;

class IArray {
public:
	virtual void set_value(int index, float value) = 0;
	virtual float get_value(int index) = 0;
	virtual int get_lenght() = 0;
};

class Array : public IArray {
public:
	float data[10];
	virtual void set_value(int index, float value) {
		data[index] = value;
	}
	virtual float get_value(int index) {
		return data[index];
	}
	virtual int get_lenght() {
		return 10;
	}
};

//-----------------------

class IList {
public:
	virtual float get_value() = 0;
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isEOL() = 0;
};

class MyStorage : public IList {

private:

	float data[10];
	int curr;

public:

	float get_value() {
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

class CDesc_1_2 : public CDesc_1 {
public:

	CDesc_1_2() {
		cout << "CDesc_1_2::CDesc_1_2()\n";
	}

	void classname() override {
		cout << "CDesc_1_2::classname\n";
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

int main()
{
	


    return 0;
}
