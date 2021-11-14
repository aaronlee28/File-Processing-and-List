#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Final Output Class
class salary {
	string name;
	double salaryAmount;

public:
	salary() : name(""), salaryAmount(0) {}
	salary(string name, double salaryAmount) : name(name), salaryAmount(salaryAmount) {}
	string getName() const { return name; }
	double getSalaryAmount() const { return salaryAmount; }
};

//File 1 Class
class employee {
	int id;
	double hourlyWage;
	string name;

public:
	employee() : id(0), hourlyWage(0), name("") {}
	employee(int id, double hourlyWage, string name, double payroll = 0) : id(id), 
		hourlyWage(hourlyWage), name(name) {}
	int getId() const { return id; }
	double getHourlyWage() const { return hourlyWage; }
	string getName() const { return name; }
	/*friend ifstream& >> */
};

//File 2 Class
class employeeHours {
	int id;
	int hours;
public:
	employeeHours() : id(0), hours(0) {}
	employeeHours(int id, int hours) : id(id), hours(hours) {}
	int getEmployeeHoursId() { return id; }
	int getEmployeeHoursHours() { return hours; }
};

//Linked Lists
template <class T>
class LList;

template <class T>
class LListNode {
	T data;
	LListNode<T>* next;
	LListNode<T>* prev;
public:
	LListNode(const T& newdata = T(), LListNode<T>* newnext = nullptr, 
		LListNode<T>* newprev = nullptr)
		:data(newdata), next(newnext), prev(newprev) {}
	friend class LList<T>;

	T& getData() { return data; }

	LListNode<T>* getNext() { return next; }
	LListNode<T>* getPrev() { return prev; }
};

template <class T>
class LList {
	LListNode<T>* head;
	LListNode<T>* tail;

public:

	LList() {
		head = new LListNode<T>;
		tail = new LListNode<T>;
		head->next = tail;
		tail->prev = head;
	}

	LList(const LList<T>& rhs) {
		head = new LListNode<T>;
		tail = new LListNode<T>;
		head->next = tail;
		tail->prev = head;
		*this = rhs;
	}

	virtual ~LList() {
		clear();
		delete head;
		delete tail;
	}

	LList<T>& operator=(const LList<T>& rhs) {
		if (this == &rhs)
			return *this;
		clear();
		LListNode<T>* ptr = rhs.head->next;
		while (ptr != rhs.tail) {
			push(ptr->data);
			ptr = ptr->next;
		}
		return *this;
	}

	T pop_back() {
		if (tail->prev == head) //empty list!
			return T(); //not sure what to do here?  User did something dumb.
		T retval = tail->prev->data;
		LListNode<T>* nodeToDelete = tail->prev;
		tail->prev = nodeToDelete->prev;
		nodeToDelete->prev->next = nodeToDelete->next;
		delete nodeToDelete;
		return retval;
	}

	void clear() { while (!isEmpty()) pop_back(); }

	void push(const T& data) {
		tail->prev = new LListNode<T>(data, tail, tail->prev);
		tail->prev->prev->next = tail->prev;
	}

	int size();

	bool isEmpty() { return head->next == tail; }

	LListNode<T>* getHead() { return head->next; }

	LListNode<T>* getEnd() { return tail; }

	void swap() {
	}
};

//Free Functions

void txtToList_1(LList<employee>& txt1, ifstream& inFile1) {
	int m_id;
	double m_hourlyWage;
	string m_name;

	inFile1.open("file_1.txt");
	while (!inFile1) {
		cout << "File_1 failed to open" << endl;
	}
	while (inFile1 >> m_id >> m_hourlyWage) {
		inFile1.ignore(1, '\n');
		getline(inFile1, m_name);
		txt1.push(employee(m_id, m_hourlyWage, m_name));
	}
}

void txtToList_2(LList<employeeHours>& txt2, ifstream& inFile2) {
	int m_id;
	int m_hours;
	inFile2.open("file_2.txt");
	while (!inFile2) {
		cout << "File_2 failed to open" << endl;
	}
	while (inFile2 >> m_id >> m_hours) {
		txt2.push(employeeHours(m_id, m_hours));
	}
}

LList<employeeHours> hoursCombined(LList<employee>& txt1List, LList<employeeHours>& txt2List) {
	LList<employeeHours> hoursCombinedList;
	LListNode<employeeHours>* current;
	current = txt2List.getHead();
	while (current->getNext() != nullptr) {
		int m_id = 0;
		int m_hours = 0;

		while (current->getData().getEmployeeHoursId() == current->getNext()->getData().getEmployeeHoursId())
		{
			m_id = current->getData().getEmployeeHoursId();
			m_hours += current->getData().getEmployeeHoursHours();
			current = current->getNext();
		}
		m_id = current->getData().getEmployeeHoursId();
		m_hours += current->getData().getEmployeeHoursHours();
		hoursCombinedList.push(employeeHours(m_id, m_hours));
		current = current->getNext();
	}
	return hoursCombinedList;
}

LList<salary> totalSalary(LList<employee>& txt1List, LList<employeeHours>& hoursCombinedList) {
	string m_name;
	double m_totalSalary;
	LList<salary> m_salaryList;
	LListNode<employee>* txt1Pointer;
	LListNode<employeeHours>* txt2Pointer;
	txt1Pointer = txt1List.getHead();
	txt2Pointer = hoursCombinedList.getHead();

	while (txt1Pointer->getNext() != nullptr) {
		m_name = "";
		m_totalSalary = 0;
		if (txt1Pointer->getData().getId() == txt2Pointer->getData().getEmployeeHoursId()) {
			m_name = txt1Pointer->getData().getName();
			m_totalSalary = txt1Pointer->getData().getHourlyWage() * txt2Pointer->getData().getEmployeeHoursHours();
			m_salaryList.push(salary(m_name, m_totalSalary));
		}
		txt1Pointer = txt1Pointer->getNext();
		txt2Pointer = txt2Pointer->getNext();
	}
	return m_salaryList;
}
void printEmployee(LList<salary>& m_salaryList) {
	LListNode<salary>* current;
	current = m_salaryList.getHead();
	while (current->getNext() != nullptr) {
		cout << "        " << current->getData().getName() << ", $" << current->getData().getSalaryAmount() << endl;
		current = current->getNext();
	}
}

LList<salary> sort(LList<salary>& m_salaryList) {
	LListNode<salary>* current;
	LListNode<salary>* index;
	current = nullptr; index = nullptr;
	salary temp;
	if (m_salaryList.getHead() == nullptr) {
		return m_salaryList;
	}
	else {
		for (current = m_salaryList.getHead(); current->getNext() != nullptr; current = current->getNext()) {
			for (index = current->getNext(); index != nullptr; index = index->getNext()) {
				if (current->getData().getSalaryAmount() < index->getData().getSalaryAmount()) {
					temp = index->getData();
					index->getData() = current->getData();
					current->getData() = temp;
				}
			}
		}
	}
	return m_salaryList;
}
int main()
{
	LList<salary> finalList;
	LList<salary> finalListSorted;
	LList<employee> txt1List;
	LList<employeeHours> txt2List, hoursCombinedList;
	ifstream inFile1, inFile2;

	txtToList_1(txt1List, inFile1);

	txtToList_2(txt2List, inFile2);

	hoursCombinedList = hoursCombined(txt1List, txt2List);
	//in the assignment operator, this is the lhs and hoursCombined function is the rhs
	finalList = totalSalary(txt1List, hoursCombinedList);
	finalListSorted = sort(finalList);
	cout << "*********Payroll Information********" << endl;
	cout << endl;
	printEmployee(finalListSorted);
	cout << endl;
	cout << "************End payroll*************" << endl;
}