//Name: Nicholas Glover
//Date: 2/15/2022

#include <Python.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("Project-3-Python");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Project-3-Python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}

	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Project-3-Python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}

	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
** Prints a menu and then receives and returns the user's input.
*/
int GetUserMenuChoice() {
	int input;

	cout << endl << setfill('-') << setw(25) << "" << " Menu " << setw(25) << "" << endl;
	cout << " 1. List Items Sold Per Day" << endl;
	cout << " 2. List Quantity Sold of a Specific Item" << endl;
	cout << " 3. List Items Sold Per Day With Histogram" << endl;
	cout << " 4. Quit" << endl << endl;
	cout << "  Please select a menu option >> ";

	cin.exceptions(istream::failbit);

	do {
		try {
			cin >> input;

			if (input < 1 || input > 4) {
				cout << "  Please enter your selection as the number: 1, 2, 3, or 4." << endl;
				cout << "   >> ";
			}
		}
		catch (ios_base::failure& fail) {
			cout << "  Please enter your selection as a number." << endl;
			cout << "   >> ";
			cin.clear();
			string tmp;
			getline(cin, tmp);
		}
	} while (input < 1 || input > 4);

	cin.ignore();

	return input;
}

/*
** Prompts the user to enter an item and calls the Python method that searches the file which returns how many times that item was bought.
** The method then prints the results with the proper grammar.
*/
void PrintSpecItem() {
	string item;
	int quant;

	cout << endl << setfill('-') << setw(21) << "" << " Item Search " << setw(22) << "" << endl;
	cout << " Please enter an item to search for >> ";
	getline(cin, item);
	cout << endl;

	quant = callIntFunc("PrintSpecItem", item);

	item.at(0) = toupper(item.at(0));

	if (item.at(item.size() - 1) == 's') {
		cout << "  " << item << " have been bought " << quant;

		if (quant == 1) {
			cout << " time." << endl << endl;
		}
		else {
			cout << " times." << endl << endl;
		}
	}
	else {
		cout << "  " << item << " has been bought " << quant;
		
		if (quant == 1) {
			cout << " time." << endl << endl;
		}
		else {
			cout << " times." << endl << endl;
		}
	}
}

/*
** Calls the Python method WriteFrequencies which will write the passed file the items purchased and their frequencies. Then this
** method will read that file and print out a histogram of the data.
*/
void WriteHistogram(string filename) {
	ifstream inFS;
	string item;
	int freq;
	vector<string> itemList;
	vector<int> freqList;
	int itemWidth;

	callIntFunc("WriteFrequencies", filename);
	
	inFS.open("..\\Release\\" + filename);
	if (!inFS.is_open()) {
		cout << "Error opening " << filename << endl;
		return;
	}

	while (inFS.good() && !inFS.eof()) {
		inFS >> item;
		inFS >> freq;

		if (!inFS.fail()) {
			itemList.push_back(item);
			freqList.push_back(freq);
		}
	}

	if (!inFS.eof()) {
		cout << " Error reading	" << filename << endl;
		return;
	}

	inFS.close();

	itemWidth = 0;
	for (int i = 0; i < itemList.size(); ++i) {
		if (itemWidth < itemList.at(i).size()) {
			itemWidth = itemList.at(i).size();
		}
	}
	itemWidth += 3;

	cout << endl << setfill('-') << setw(18) << "" << " Histogram of Items " << setw(18) << "" << endl;
	for (int i = 0; i < itemList.size(); ++i) {
		cout << setfill(' ') << setw(itemWidth) << right << itemList.at(i) << ": "
			<< setfill('*') << setw(freqList.at(i)) << left << "" << endl;
	}

	cout << endl;
}

int main() {
	system("Color 0A");

	int input;

	do {
		input = GetUserMenuChoice();

		switch (input) {
		case 1:
			cout << endl << setfill('-') << setw(20) << "" << " List of Items " << setw(21) << "" << endl;
			CallProcedure("PrintItemDict");
			break;
		case 2:
			PrintSpecItem();
			break;
		case 3:
			WriteHistogram("frequency.dat");
			break;
		default:
			break;
		}
	} while (input != 4);

	cout << endl << " Thanks for your participation!" << endl;

	return 0;
}