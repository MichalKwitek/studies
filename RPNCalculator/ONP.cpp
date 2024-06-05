#include <iostream>
using namespace std;

// Single linked list node
template<typename T>
struct Node {
	T data;
	Node* next;
	Node(const T& value) : data(value), next(nullptr) {}
};

// Stack implemented as single linked list
template<typename T>
class Stack {
private:
	Node<T>* top; // Pointer to the top of the stack
	Node<T>* bottom; // Pointer to the bottom of the stack

public:
	Stack() : top(nullptr), bottom(nullptr) {}

	// Push an element onto the stack
	void push(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		if (top == nullptr) {
			top = newNode;
		}
		else {
			newNode->next = top;
			top = newNode;
		}
	}

	void pushToBottom(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		if (isEmpty()) {
			top = newNode;
			bottom = newNode;
		}
		else {
			bottom->next = newNode;
			bottom = newNode;
		}
	}

	// Pop an element from the stack
	T pop() {
		if (isEmpty()) {
			return T();
		}
		T poppedValue = top->data;
		Node<T>* temp = top;
		top = top->next;
		delete temp;
		return poppedValue;
	}

	// Return the top element of the stack
	T peek() const {
		if (isEmpty()) {
			//cerr << "Stack is empty." << endl;
			return T(); // return a default value
		}
		return top->data;
	}

	T peek_next() const {
		if (top == nullptr || top->next == nullptr) {
			// Stack is empty or there is no element next to the head
			return T(); // Return a default value or handle the empty stack case
		}
		// Return the value stored in the data member of the node next to the top
		return top->next->data;
	}

	bool isEmpty() const {
		return top == nullptr;
	}

	void printAll() const {
		if (isEmpty()) {
			cout << "Stack is empty." << endl;
			return;
		}
		Node<T>* current = top;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	void clear() {
		while (!isEmpty()) {
			pop();
		}
	}

	// Co z destruktorem?
	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}
};

class Base {
public:
	virtual void print() const = 0;
	virtual ~Base() {} // Wirtualny destruktor dla poprawnego usuwania pamięci
};

class CharObject : public Base {
private:
	char value;
public:
	CharObject() : value(' ') {}
	CharObject(char val) : value(val) {}
	CharObject(const CharObject& other) : value(other.value) {}
	void print() const override {
		std::cout << value;
	}
	CharObject& operator=(const Base* other) {
		const CharObject* derived = dynamic_cast<const CharObject*>(other);
		if (derived) {
			value = derived->value;
		}
		return *this;
	}
	char getValue() const {
		return value;
	}
	~CharObject() override {} // Destruktor
};

class IntObject : public Base {
private:
	int value;
public:
	IntObject() : value(0) {}
	IntObject(int val) : value(val) {}
	IntObject(const IntObject& other) : value(other.value) {}
	void print() const override {
		std::cout << value;
	}
	IntObject& operator=(const Base* other) {
		const IntObject* derived = dynamic_cast<const IntObject*>(other);
		if (derived) {
			value = derived->value;
		}
		return *this;
	}
	int getValue() const {
		return value;
	}
	~IntObject() override {} // Destruktor
};

class NodeSLL {
public:
	Base* data;
	NodeSLL* next;
	NodeSLL(Base* val) : data(val), next(nullptr) {}
};

class SimpleList {
private:
	NodeSLL* head; // Pointer to the first node of the list
	NodeSLL* tail; // Pointer to the last node of the list
	int size;
public:
	SimpleList() : head(nullptr), tail(nullptr), size(0) {}

	void push_back(Base* obj) {
		NodeSLL* newNode = new NodeSLL(obj);
		if (!head) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	void push_back(char c) {
		push_back(new CharObject(c));
	}

	void push_back(int i) {
		push_back(new IntObject(i));
	}

	void push_back(const CharObject& obj) {
		push_back(new CharObject(obj));
	}

	void push_back(const IntObject& obj) {
		push_back(new IntObject(obj));
	}

	Base* pop() {
		if (isEmpty()) {
			return nullptr; // Return nullptr if the list is empty
		}
		NodeSLL* temp = head;
		Base* poppedData = temp->data;
		head = head->next;
		delete temp;
		size--;
		return poppedData;
	}

	// Check if the list is empty
	bool isEmpty() const {
		return head == nullptr;
	}

	void printAll() const {
		NodeSLL* current = head;
		while (current) {
			current->data->print();
			std::cout << "  ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	void clear() {
		while (head) {
			NodeSLL* temp = head;
			head = head->next;
			delete temp->data;
			delete temp;
		}
		size = 0; // Reset the size after clearing the list
	}

	friend void printRPN(const SimpleList& rpn, Stack<int>& MinMaxArgs);

	~SimpleList() {
		while (head) {
			NodeSLL* temp = head;
			head = head->next;
			delete temp->data;
			delete temp;
		}
	}
};

void printRPN(const SimpleList& rpn, Stack<int>& MinMaxArgs)
{
	Stack<int> temp;
	NodeSLL* current = rpn.head;
	// loop until current == nullptr
	while (current) {
		CharObject* token_ptr = dynamic_cast<CharObject*>(current->data);
		if (token_ptr)
		{
			CharObject token = *token_ptr;
			if (token.getValue() == 'F')
				std::cout << "IF";
			else if (token.getValue() == 'X') {
				int count = MinMaxArgs.pop();
				std::cout << "MAX" << count;
				temp.push(count);
			}
			else if (token.getValue() == 'n') {
				int count = MinMaxArgs.pop();
				std::cout << "MIN" << count;
				temp.push(count);
			}
			else
				current->data->print();
		}
		else current->data->print();

		std::cout << " ";
		current = current->next;
	}
	while (!temp.isEmpty())
	{
		int count = temp.pop();
		MinMaxArgs.push(count);
	}
	std::cout << std::endl;
}

bool isOperator(const char& token)
{
	//CharObject token = token_pointer;
	if (token == '+' || token == '-' ||
		token == '*' || token == '/' ||
		token == 'N' || token == 'F' ||
		token == 'X' || token == 'n' ||
		token == '(' || token == ')')
		return true;
	else
		return false;
}

int get_priority(char& token)
{
	if (token == '-' || token == '+')
		return 1;
	if (token == '*' || token == '/')
		return 2;
	if (token == 'N')
		return 3;
	if (token == 'F' || token == 'X' || token == 'n')
		return 4;
	if (token == '(' || token == ')')
		return 0;
	return 0;
}

int do_calc(char& token, int& op1, int& op2)
{
	switch (token) {
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	default:
		return -1;
	}
}

int calc_N(int& op1)
{
	return -1 * op1;
}

int calc_F(int& op1, int& op2, int& op3)
{
	if (op1 > 0)
		return op2;
	else
		return op3;
}

int MAX(const int* args, int count) {
	if (count <= 0) {
		std::cerr << "Error: No arguments provided." << std::endl;
		return 0; // Return some default value or handle error as appropriate
	}
	int max = args[0];
	for (int i = 0; i < count; ++i) {
		if (args[i] > max) {
			max = args[i];
		}
	}
	return max;
}

int MIN(const int* args, int count) {
	if (count <= 0) {
		std::cerr << "Error: No arguments provided." << std::endl;
		return 0; // Return some default value or handle error as appropriate
	}
	int min = args[0];
	for (int i = 0; i < count; ++i) {
		if (args[i] < min) {
			min = args[i];
		}
	}
	return min;
}

int rpn_calc(SimpleList& rpn, Stack<int>& MinMaxArgs, bool& zeroDivision)
{
	int op1, op2, op3, result;
	Stack<int> stack;

	while (!rpn.isEmpty())
	{
		Base* ptr;
		ptr = rpn.pop();

		IntObject* isoperand = dynamic_cast<IntObject*>(ptr); // to można wrzucić do waruku

		if (isoperand)
		{
			const IntObject Operand = *isoperand;
			int token = Operand.getValue();
			stack.push(token);
			delete isoperand;
		}
		else
		{
			CharObject* isoperator = dynamic_cast<CharObject*>(ptr);
			const CharObject Operator = *isoperator;
			char token = Operator.getValue();
			if (token == 'N') {

				std::cout << token << " ";
				stack.printAll();

				op1 = stack.pop();
				result = calc_N(op1);
				stack.push(result);
			}
			else if (token == 'F') {

				std::cout << "IF" << " ";
				stack.printAll();

				op3 = stack.pop();
				op2 = stack.pop();
				op1 = stack.pop();
				result = calc_F(op1, op2, op3);
				stack.push(result);
			}
			else if (token == 'X' || token == 'n') {

				int count = MinMaxArgs.pop();

				if (token == 'X')
					std::cout << "MAX" << count << " ";
				else
					std::cout << "MIN" << count << " ";
				stack.printAll();

				int* arguments = new int[count];
				for (int j = 0; j < count; ++j) {
					arguments[j] = stack.pop(); // Example arguments, you need to adjust this as per your requirement
				}
				if (token == 'X')
					result = MAX(arguments, count);
				else if (token == 'n')
					result = MIN(arguments, count);
				stack.push(result);
				delete[] arguments;
			}
			else {

				std::cout << token << " ";
				stack.printAll();

				op2 = stack.pop();
				op1 = stack.pop();

				if (token == '/' && op2 == 0)
				{
					zeroDivision = true;
					return -1;
				}
				else {
					result = do_calc(token, op1, op2);
					stack.push(result);
				}
			}
			delete isoperator;
		}
	}
	result = stack.pop();
	return result;
}

void procedure(SimpleList& rpn, Stack<char>& stack, Stack<int>& MinMaxArgs, bool& zeroDivision)
{
	int args = 1;

	char current_token;
	while (cin >> current_token && !isspace(current_token) && !zeroDivision)
	{
		int priority;
		char top;

		if (current_token == 'M')
		{
			char I_A, N_X;
			cin >> I_A;
			if (I_A == 'A')
				stack.push('X');
			else if (I_A == 'I')
				stack.push('n');
			cin >> N_X;
			//isInsideMinMax = true;
			procedure(rpn, stack, MinMaxArgs, zeroDivision);
			if (zeroDivision == true)
				return;
		}
		else if (isdigit(current_token)) {
			int operand = 0;
			while (isdigit(current_token))
			{
				// pobieram nastęny znak
				// jeśli jest to liczba, to zostaję w pętli i dodaję na koniec budowanego operandu
				// jeśli nie jest to liczba, to wychodzę z pętli w wstawiam dotychczasowy operand na lisę rpn 
				// jeśli nie jest to liczba, pobrany w tym miejscu token zostanie przetworzony przez następne instrukcje warunkowe
				operand = (operand * 10 + current_token - '0');
				cin.get(current_token);
			}
			rpn.push_back(operand);
		}							// to można wykasować (',')
		else if (isOperator(current_token) || current_token == ',') {
			if (current_token == '(')
				stack.push(current_token);
			else if (current_token == ')')
			{
				while (!stack.isEmpty())
				{
					current_token = stack.pop();
					if (current_token == '(')
					{
						if (stack.peek() == 'F')
						{
							current_token = stack.pop();
							rpn.push_back(current_token);
							break;
						}
						if (stack.peek() == 'X' || stack.peek() == 'n')
						{
							MinMaxArgs.pushToBottom(args);
							current_token = stack.pop();
							rpn.push_back(current_token);
							return;
						}
						else break;
					}
					else rpn.push_back(current_token);
				}
			}
			else if (current_token == ',')
			{
				args++;
				while (!stack.isEmpty())
				{
					top = stack.pop();
					if (top == '(')
					{
						stack.push(top);
						break;
					}
					rpn.push_back(top); // żeby można było opuścić nawiasy w MinMax
				}
			}
			else
			{
				priority = get_priority(current_token);
				while (!stack.isEmpty())
				{
					// pull top stack token
					top = stack.pop();

					//if top stack token has lower prority
					//put back the token to stack and break the loop 
					//w sumie nie wiem czy trzeba sprawdzać top == '(' // ten fragment jest do obsłużenia wielokrotnej negacji
					if (top == '(' || (get_priority(top) < priority) || (current_token == 'N' && top == 'N'))
					{
						stack.push(top);
						break;
					}

					// put top stack token to output
					// if top is MIN or MAX, save number of arguments
					// dzieki temu brak nawiasu nie psuje
					if (top == 'X' || top == 'n')
						MinMaxArgs.pushToBottom(args);
					rpn.push_back(top);
				}

				// push token to stack
				stack.push(current_token);

				// if token is IF then substract 2 from args (IF takes 2 operands)
				if (current_token == 'F')
					args -= 2;
			}
		}
		else if (current_token == '.')
			break;
		else if (current_token != 'M' && current_token != 'A' && current_token != 'I') {
			std::cout << "ERROR";
			MinMaxArgs.clear();
			stack.clear();
			rpn.clear();
			return;
		}
	}

	//when all the elements are processed write all stack to output
	while (!stack.isEmpty())
	{
		char item = stack.pop();
		rpn.push_back(item);
	}

	printRPN(rpn, MinMaxArgs);
	int result = rpn_calc(rpn, MinMaxArgs, zeroDivision);
	if (zeroDivision == false)
		std::cout << result << "\n\n";
	else
		std::cout << "ERROR\n\n";

	MinMaxArgs.clear();
	stack.clear();
	rpn.clear();
	return;
}

int main(int argc, char* argv[])
{
	int amount;
	cin >> amount;
	for (int i = 1; i <= amount; i++)
	{
		SimpleList rpn;
		Stack<char> stack;
		Stack<int> MinMaxArgs;
		bool zeroDivision = false;
		procedure(rpn, stack, MinMaxArgs, zeroDivision);
	}
	return 0;
}