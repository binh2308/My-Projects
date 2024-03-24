#include "main.h"

template<class T>
void swap(T&& a, T&& b) {
	T temp(std::move(a));
	a = std::move(b);
	b = std::move(temp);
}

class imp_res : public Restaurant
{
public:
	class Node {
	public:	customer* cus;
		  int index;
		  Node* next;
		  Node* prev;
		  Node() :cus(nullptr), next(nullptr), prev(nullptr) {}
		  Node(customer* cus) :cus(cus), next(nullptr), prev(nullptr) {}
		  ~Node() { delete cus; next = nullptr; prev = nullptr; return; }
		  bool operator<(Node* cusnode) {
			  return (abs(this->cus->energy) == abs(cusnode->cus->energy)) ? (this->index > cusnode->index) : (abs(this->cus->energy) < abs(cusnode->cus->energy));
		  }
		  Node* operator+(int k) {
			  if (!k)return this;
			  Node* p = this;
			  while (p && k) {
				  p = p->next;
				  k--;
			  }
			  return p;
		  }
		  Node* operator-(int k) {
			  if (!k)return this;
			  Node* p = this;
			  while (p && k) {
				  p = p->prev;
				  k--;
			  }
			  return p;
		  }
	};
	struct StackNode {
	public: Node* cusnode;
		  StackNode* next;
		  StackNode(Node* cus) :cusnode(cus), next(nullptr) {}
		  ~StackNode() { cusnode = nullptr; next = nullptr; }
	};
	class stack {
	private:	StackNode* head;
	public:	stack() :head(nullptr) {}
		  ~stack() {
			  while (head)this->pop();
			  delete head;
		  }
		  void push(Node* cus) {
			  StackNode* p = new StackNode(cus);
			  if (head) {
				  p->next = head;
				  head = p;
			  }
			  else head = p;
		  }
		  void pop() {
			  if (!isEmpty()) {
				  StackNode* p = head;
				  head = head->next;
				  p->~StackNode(); delete p;
			  }
			  return;
		  }
		  Node* top()const { return head->cusnode; }
		  bool isEmpty() { return !head; }

	};
	class orgQueue {
	public: customer* head;
		  customer* tail;
		  orgQueue() :head(nullptr), tail(nullptr) {}
		  ~orgQueue() { while (head)pop(); delete head; delete tail; }
		  void enqueue(string name, int energy) {
			  customer* cus = new customer(name, energy, nullptr, nullptr);
			  if (tail) {
				  tail->next = cus; cus->prev = tail; tail = cus;
			  }
			  else head = tail = cus;
		  }
		  void pop() {
			  if (head) {
				  customer* p = head; head = head->next; if (head)head->prev = nullptr; delete p;
			  }
			  else head = tail = nullptr;
		  }
		  void remove(customer* cus) {
			  if (cus == head)pop();
			  else if (cus == tail) {
				  tail = tail->prev; if (tail)tail->next = nullptr; cus->prev = nullptr; delete cus;
			  }
			  else {
				  cus->prev->next = cus->next; cus->next->prev = cus->prev;
				  cus->prev = cus->next = nullptr; delete cus;
			  }
			  if (!head)head = tail = nullptr;
		  }
		  void removename(const string& name) {
			  for (customer* k = head; k != nullptr; k = k->next) {
				  if (k->name == name) { remove(k); break; }
			  }
		  }
		  bool betterEnergy() {
			  int sum1(0), sum2(0);
			  for (customer* k = head; k != nullptr; k = k->next) {
				  if (k->energy > 0)sum1 += k->energy;sum2 += k->energy;
			  }
			  return abs(sum1) >= abs(sum2);
		  }
		  void removefromBottom(bool check) {
			  for (customer* k = tail;k != nullptr; ) {
				  if (check && k->energy < 0) {
					  k->print(); customer* p = k->prev;
					  remove(k); k = p;
				  }
				  else if (!check && k->energy > 0) {
					  k->print(); customer* p = k->prev;
					  remove(k); k = p;
				  }
				  else k = k->prev;
			}
			  
		  }
		  bool checkName(const string& name) {
			  for (customer* k = head; k != nullptr; k = k->next) {
				  if (k->name == name)return true;
			  }
			  return false;
		  }
		  void print() {
			  for (customer* k = head; k; k = k->next) {
				  k->print();
			  }
		  }
	};
	class Queue {
	public:Node* head;
		  Node* tail;
		  int count;
		  int maxsize;
		  Queue() :head(nullptr), tail(nullptr), count(0), maxsize(0) {}
		  Queue(int maxsize) :head(nullptr), tail(nullptr), count(0), maxsize(maxsize) {}
		  ~Queue() {
			  while (head)pop();
			  count = 0; maxsize = 0;  delete head; delete tail;
		  }
		  void insert(customer* cus) {
			  customer* newcus = new customer(cus->name, cus->energy, nullptr, nullptr);
			  Node* p = new Node(newcus);
			  if (!count) { head = tail = p; head->index = 0; }
			  else if (tail) {
				  tail->next = p;
				  p->prev = tail;
				  p->index = tail->index + 1;
				  tail = p;
			  }
			  count++;
			  return;
		  }
		  void pop() {
			  Node* p = this->head; head = head->next; if (head)head->prev = nullptr;
			  delete p; count--; if (!count)head = tail = nullptr;
		  }
		  void remove(Node* cus) {
			  if (head == cus) {
				  head = head->next;
				  if (head)head->prev = nullptr;
				  delete cus;
			  }
			  else if (tail == cus) {

				  tail = tail->prev;
				  if (tail)tail->next = nullptr;
				  delete cus;
			  }
			  else {
				  cus->prev->next = cus->next;
				  cus->next->prev = cus->prev;
				  delete cus;
			  }
			  count--;if(!count)head = tail = nullptr; return;
		  }
		  void remove(string name, int energy) {
			  for (Node* p = head, *pp = tail; p && pp; p = p->next, pp = pp->prev) {
				  if (p->cus->name == name && p->cus->energy == energy) { remove(p); break; }
				  if (pp->cus->name == name && pp->cus->energy == energy) { remove(pp); break; }
			  }
		  }
		  Node* findMaxIndex(int& k) {
			  Node* max_index = this->tail;
			  k = this->count; int i = 1;
			  for (Node* p = max_index->prev; p != nullptr; p = p->prev) {
				  if (abs(max_index->cus->energy) < abs(p->cus->energy)) { max_index = p; k -= i; }
				  else { i++; continue; }
			  }
			  return max_index;
		  }
		  void insertionSort(Node* start_idx, int k, int& N) {
			  stack stck1, stck2;
			  for (Node* i = start_idx; i != nullptr; i = *i - k) {
				  Node* pCur = i;
				  if (stck1.isEmpty() || !(*pCur < stck1.top())) {
					  stck1.push(pCur); continue;
				  }
				  while (!stck1.isEmpty() && (*pCur < stck1.top())) {
					  swapCustomer(pCur->cus, stck1.top()->cus); N++;
					  stck2.push(pCur);
					  pCur = stck1.top();
					  stck1.pop();
					  if (stck1.isEmpty() || !(*pCur < stck1.top()))stck2.push(pCur);
				  }
				  while (!stck2.isEmpty()) {
					  stck1.push(stck2.top()); stck2.pop();
				  }
			  }
			  stck1.~stack(); stck2.~stack();
		  }
		  void shellSort(int& N) {
			  int k(0);
			  Node* start_idx = findMaxIndex(k); k /= 2; if (k < 1)return; if (k <= 2)k = 1;
			  Node* pK = (*start_idx) - k;
			  while (k) {
				  if (pK)
					  for (Node* p = start_idx; p->index > pK->index; p = *p - 1)insertionSort(p, k, N);
				  if (k == 1)break;
				  k /= 2;
				  if (k <= 2)k = 1;
				  pK = (*start_idx) - k;
			  }
		  }
		  void swapCustomer(customer* a, customer* b) {
			  swap<string>(a->name, b->name);
			  swap<int>(a->energy, b->energy);
		  }
		  void print() {
			  cout << "QUEUE!!!! \n";
			  for (Node* p = this->head; p != nullptr; p = p->next)p->cus->print();
		  }
		  void removeCTS_OL(bool check) {
			  for (Node* k = tail;k != nullptr; ) {
				  if (check && k->cus->energy < 0) {
					  Node* p = k->prev;
					  remove(k); k = p;
				  }
				  else if (!check && k->cus->energy > 0) {
					  Node* p = k->prev; remove(k);
					  k = p;
				  }
				  else k = k->prev;
			  }
		  }
	};
private:
	customer* x_index;
	int count;
	int MaxSize;
	Queue* queue;
	Queue* tableList;
	orgQueue orgOrder;
	bool pass;
public:
	imp_res() :x_index(nullptr), count(0), queue(nullptr), tableList(nullptr), pass(false) {}
	~imp_res() {
		orgOrder.~orgQueue();
		delete queue; delete tableList;
		while (x_index) {
			customer* p = x_index;
			remove(p);
		}
		delete x_index;
	}
	inline void IniRestaurant(const int& maxsize) {
		MaxSize = maxsize; queue = new Queue(maxsize); tableList = new Queue(maxsize);
	}
	void RED(string name, int energy);
	void BLUE(int num);
	void PURPLE();
	void REVERSAL();
	void UNLIMITED_VOID();
	void DOMAIN_EXPANSION();
	void LIGHT(int num);
	void insert(customer* addindex, customer* cus, bool prev = false) {

		if (prev) {
			cus->prev = addindex->prev; addindex->prev->next = cus;
			cus->next = addindex; addindex->prev = cus;
			x_index = cus;
		}
		else {
			cus->prev = addindex; addindex->next->prev = cus;
			cus->next = addindex->next; addindex->next = cus;
			x_index = cus;
		}
		tableList->insert(cus);
		count++; return;
	}
	void insertHead(customer* cus) {
		this->x_index = cus; x_index->next = x_index; x_index->prev = x_index; tableList->insert(cus);
		count++; return;
	}
	void remove(customer* cus) {
		x_index = (cus->energy > 0) ? cus->next : cus->prev;
		cus->prev->next = cus->next;
		cus->next->prev = cus->prev;
		cus->next = cus->prev = nullptr; delete cus;
		count--;
		if (!count)x_index = nullptr;
		return;
	}
	void swapCustomer(customer* a, customer* b) {
		swap<string>(a->name, b->name);
		swap<int>(a->energy, b->energy);
	}
	void clear() {
		for (Node* p = tableList->head; p != nullptr; p = tableList->head) {
			string name = p->cus->name; orgOrder.removename(name);
			tableList->pop();
			this->removeName(name);
		}
		tableList->head = tableList->tail = nullptr;
	}
	void removeName(const string& name) {
		for (customer* p = x_index; p; p = p->next) {
			if (p->name == name) {
				remove(p); break;
			}
			if (p->next == x_index)break;
		}
	}
	int num_CTS(int sum = 0) {
		for (customer* p = x_index; p != nullptr; p = p->prev) {
			if (p->energy > 0)sum++;
			if (p->prev == x_index)break;
		}
		return sum;
	}
	int num_OL(int sum = 0) {
		for (customer* p = x_index; p != nullptr; p = p->prev) {
			if (p->energy < 0)sum++;
			if (p->prev == x_index)break;
		}
		return sum;
	}
	void printTable(bool prev) {
		(prev) ? cout << "TABLE -1 !!\n" : cout << "TABLE 1 !!\n";
		if (prev) {
			for (customer* p = x_index; p != nullptr; p = p->prev) {
				p->print();
				if (p->prev == x_index)break;
			}
		}
		else {
			for (customer* p = x_index; p != nullptr; p = p->next) {
				p->print();
				if (p->next == x_index)break;
			}
		}
	}
	customer* findMin(customer* start, customer* end) {
		int min(start->energy); customer* minindex(start);
		for (customer* p = start->next; p != nullptr; p = p->next) {
			minindex = (p->energy < min) ? p : minindex;
			min = (p->energy < min) ? p->energy : min;
			if (p == end)break;
		}
		return minindex;
	}
	void specialPrint(customer* first, customer* min, customer* last) {
		for (customer* p = min; p != nullptr; p = p->next)
		{
			p->print(); if (p == last)break;
		}
		for (customer* p = first; p && p != min; p = p->next)p->print();

	}
	int sumOf4(customer* idx, int count = 4, int sum = 0) {
		if (!count)return sum;
		sum += idx->energy;
		return sumOf4(idx->next, count - 1, sum);
	}
	int sumOfAll(customer* first, customer* last, int sum = 0) {
		if (first == last)return sum + last->energy;
		sum += first->energy;
		return sumOfAll(first->next, last, sum);
	}
	customer* after4(customer* idx, int count = 3) {
		if (!count)return idx; return after4(idx->next, count - 1);
	}
	int lengthOf(customer* start, customer* end) {
		return (start == end) ? 1 : 1 + lengthOf(start->next, end);
	}
};


////////////////////////// IMPLEMENT COLOUR METHODS ////////////////////////////////////
void imp_res::RED(string name, int energy) {
	//cout << "RED!!\n";
	if (!queue && !tableList)IniRestaurant(MAXSIZE); if (pass)goto accept;
	if (!energy || this->queue->count >= MaxSize)return;
	if (this->orgOrder.checkName(name))return;
	else {
	accept:	customer* cus = new customer(name, energy, nullptr, nullptr);
		if (this->count < MaxSize) {
			if (this->count >= MaxSize / 2) {
				customer* maxindex = x_index;
				for (customer* p = maxindex->next; p != x_index; p = p->next)
					maxindex = (abs(cus->energy - maxindex->energy) < abs(cus->energy - p->energy)) ? p : maxindex;
				bool prev = (cus->energy < maxindex->energy) ? true : false;
				insert(maxindex, cus, prev);
			}
			else {
				if (x_index) {
					bool prev = (cus->energy < x_index->energy) ? true : false;
					insert(x_index, cus, prev);
				}
				else insertHead(cus);
			}
		}
		else this->queue->insert(cus); 
		if(!this->orgOrder.checkName(name))orgOrder.enqueue(name, energy);
		pass = false;
	}
}
void imp_res::BLUE(int num) {
	//cout << "BLUE!!!\n";
	if (num <= 0 || !count)return;
	if (num >= tableList->count || num >= MaxSize)this->clear();
	else for (Node* p = tableList->head; p != nullptr && num > 0; p = tableList->head) {
			string name = p->cus->name; orgOrder.removename(name);
			tableList->pop(); 
			this->removeName(name);
			num--;
		}
	while (count < MaxSize && queue->count > 0) {
		string name(queue->head->cus->name); int energy(queue->head->cus->energy); pass = true;
		queue->pop(); RED(name, energy);
	}


}
void imp_res::PURPLE() {
	cout << "PURPLE!!!\n";
	if (!this->queue || this->queue->count <= 1)return;
	int N(0);
	queue->shellSort(N);
	cout << N << "\n\n";
	BLUE(N % MaxSize);
}
void imp_res::REVERSAL() {
	cout << "REVERSAL!!!\n";
	if (!this->tableList || this->tableList->count <= 1)return;
	customer* start_idx = x_index; int k1 = this->num_CTS(), k2 = this->num_OL();
	customer* pNguoc1(start_idx), * pThuan1(start_idx->next), * pNguoc2(start_idx), * pThuan2(start_idx->next);
	while (k1 > 1) {
		for (; pNguoc1 != start_idx->next; pNguoc1 = pNguoc1->prev) {
			if (pNguoc1->energy > 0)break; else continue;
		}
		for (; pThuan1 != start_idx; pThuan1 = pThuan1->next) {
			if (pThuan1->energy > 0)break; else continue;
		}
		if (x_index == pThuan1) {
			swapCustomer(pThuan1, pNguoc1); x_index = pNguoc1;
		}
		else if (x_index == pNguoc1) {
			swapCustomer(pThuan1, pNguoc1); x_index = pThuan1;
		}
		else swapCustomer(pThuan1, pNguoc1);
		k1 -= 2;
		pThuan1 = pThuan1->next; pNguoc1 = pNguoc1->prev;
	}
	while (k2 > 1) {
		for (; pNguoc2 != start_idx->next; pNguoc2 = pNguoc2->prev) {
			if (pNguoc2->energy < 0)break; else continue;
		}
		for (; pThuan2 != start_idx; pThuan2 = pThuan2->next) {
			if (pThuan2->energy < 0)break; else continue;
		}
		if (x_index == pThuan2) {
			swapCustomer(pThuan2, pNguoc2); x_index = pNguoc2;
		}
		else if (x_index == pNguoc2) {
			swapCustomer(pThuan2, pNguoc2); x_index = pThuan2;
		}
		else swapCustomer(pThuan2, pNguoc2);
		k2 -= 2;
		pThuan2 = pThuan2->next; pNguoc2 = pNguoc2->prev;
	}

}
void imp_res::UNLIMITED_VOID() {
	cout << "Unlimited void!!!\n";
	customer* start = x_index, * end = x_index->prev, * min = findMin(start, end);
	int minsum = sumOfAll(start, end), maxlen(lengthOf(start, end)), len(0);
	if (this->count < 4)return;
	
	else {
		for (customer* p = x_index;; p = p->next) {
			int sum = sumOf4(p); customer* pR = after4(p); len = 4;
			if (sum < minsum) {
				minsum = sum; start = p; end = pR; maxlen = len;
			}
			if (sum == minsum && len >= maxlen) {
				minsum = sum; start = p; end = pR; maxlen = len;
			}
			for (pR = pR->next; pR != p; pR = pR->next) {
				sum += pR->energy; len++;
				if (sum <= minsum) {
					minsum = sum; start = p; end = pR; maxlen = len;
				}
				if (sum == minsum && len >= maxlen) {
					minsum = sum; start = p; end = pR; maxlen = len;
				}
			}
			if (p->next == x_index)break;
		}
		min = findMin(start, end);
		specialPrint(start, min, end);
	}

}
void imp_res::DOMAIN_EXPANSION() {
	cout << "DOMAIN_EXPANSION!!!\n";
	if (this->count <= 1)return;
	bool check = orgOrder.betterEnergy();
	orgOrder.removefromBottom(check);
	this->queue->removeCTS_OL(check);
	int CTS = num_CTS(), OL = num_OL();
	for (Node* k = tableList->head; CTS && OL; ) {
		if (check && k->cus->energy < 0) {
			Node* p = k->next; this->removeName(k->cus->name);
			tableList->remove(k); k = p; OL--;
		}
		else if (!check && k->cus->energy > 0) {
			Node* p = k->next; this->removeName(k->cus->name);
			tableList->remove(k); CTS--;
			k = p;
		}
		else k = k->next;
	}
	while (count < MaxSize && queue->count > 0) {
		string name(queue->head->cus->name); int energy(queue->head->cus->energy); pass = true;
		queue->pop(); RED(name, energy);
	}
	//if (orgOrder.head)cout << "Co org!!!"; else cout << "MAT ROI!!!\n";

}
void imp_res::LIGHT(int num) {
	//cout << "LIGHT !!!\n";
	//if (num == 2) { orgOrder.print(); return; }
	if (!num)queue->print();
	else if (num < 0)this->printTable(true);
	else this->printTable(false);
}