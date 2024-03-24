#include "main.h"
int MAXSIZE;
long int factorial(long int n) {
	if (n <= 1)return 1;
	return n * factorial(n - 1);
}
long int combination(long int a, long int b) {
	return (factorial(a + b) / factorial(a)) / factorial(b);
}
bool theSame(const char& a, const char& b) {
	bool i = (a >= 65 && a <= 90 && b >= 65 && b <= 90) || (a >= 97 && a <= 122 && b >= 97 && b <= 122);
	return (i) ? (a > b) : (a < b);
}
bool theSame2(const char& a, const char& b) {
	return (a >= 65 && a <= 90 && b >= 65 && b <= 90) || (a >= 97 && a <= 122 && b >= 97 && b <= 122);
}
struct comp {
	static bool prior(const pair<int, char>& a, const pair<int, char>& b) { return (a.first == b.first) ? (theSame2(a.second, b.second) ? (a.second < b.second) : (a.second > b.second)) : (a.first < b.first); }
};
long long dfs(vector<int>& nums, vector<vector<long long>>& table, long long mod) {
	int n = nums.size();
	if (n <= 2)return 1;
	vector<int> left, right;
	for (unsigned int i = 1; i < nums.size(); i++) {
		if (nums[i] < nums[0])left.push_back(nums[i]);
		else right.push_back(nums[i]);
	}
	long long left_res = dfs(left, table, mod) % mod;
	long long right_res = dfs(right, table, mod) % mod;
	int left_len = left.size();
	return (((table[n - 1][left_len] * left_res) % mod) * right_res) % mod;
}
int ways(vector<int>& nums) {
	int n = nums.size();
	vector<vector<long long>> table(n + 1);
	long long mod = MAXSIZE;
	for (int i = 0; i < n + 1; i++)
	{
		table[i] = vector<long long>(i + 1, 1);
		for (int j = 1; j < i; j++)
		{
			table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % mod;
		}
	}
	long long ans = dfs(nums, table, mod);
	return (ans % mod) % mod;
}
// Heap class
//template <typename E, typename Comp, typename Comp1> class heap {
//private:
//	E* Heap; // Pointer to the heap array
//	int maxsize; // Maximum size of the heap
//	int n; // Number of elements now in the heap
//	// Helper function to put element in its correct place
//	void siftdown(int pos) {
//		while (!isLeaf(pos)) { // Stop if pos is a leaf
//			int j = leftchild(pos); int rc = rightchild(pos);
//			if ((rc < n) && Comp::prior(Heap[rc], Heap[j]))
//				j = rc; // Set j to greater child’s value
//			if (Comp1::prior(Heap[pos], Heap[j])) return; // Done
//			std::swap(Heap[pos], Heap[j]);
//			pos = j; // Move down
//		}
//	}
//public:
//	heap(E* h, int num, int max) // Constructor
//	{
//		Heap = h; n = num; maxsize = max; buildHeap();
//	}
//	int size() const // Return current heap size
//	{
//		return n;
//	}
//	bool isLeaf(int pos) const // True if pos is a leaf
//	{
//		return (pos >= n / 2) && (pos < n);
//	}
//	int leftchild(int pos) const
//	{
//		return 2 * pos + 1;
//	} // Return leftchild position
//	int rightchild(int pos) const
//	{
//		return 2 * pos + 2;
//	} // Return rightchild position
//	int parent(int pos) const // Return parent position
//	{
//		return (pos - 1) / 2;
//	}
//	void buildHeap() // Heapify contents of Heap
//	{
//		for (int i = n / 2 - 1; i >= 0; i--) siftdown(i);
//	}
//	// Insert "it" into the heap
//	void insert(const E& it) {
//		assert(n < maxsize, "Heap is full");
//		int curr = n++;
//		Heap[curr] = it; // Start at end of heap
//		// Now sift up until curr’s parent > curr
//		while ((curr != 0) &&
//			(Comp::prior(Heap[curr], Heap[parent(curr)]))) {
//			std::swap(Heap[curr], Heap[parent(curr)]);
//			curr = parent(curr);
//		}
//	}
//	// Remove first value
//	E removefirst() {
//		assert(n > 0, "Heap is empty");
//		std::swap(Heap[0], Heap[--n]);
//		// Swap first with last value
//		if (n != 0) siftdown(0); // Siftdown new root val
//		return Heap[n]; // Return deleted value
//	}
//	// Remove and return element at specified position
//	E remove(int pos) {
//		assert((pos >= 0) && (pos < n), "Bad position");
//		if (pos == (n - 1)) n--; // Last element, no work to do
//		else
//		{
//			std::swap(Heap[pos], Heap[--n]); // Swap with last value
//			while ((pos != 0) &&
//				(Comp::prior(Heap[pos], Heap[parent(pos)]))) {
//				std::swap(Heap[pos], Heap[parent(pos)]); // Push up large key
//				pos = parent(pos);
//			}
//			if (n != 0) siftdown(pos); // Push down small key
//		}
//		return Heap[n];
//	}
//	E valAt(int pos)const { return Heap[pos]; }
//};
// Huffman tree node abstract base class
class Gojo {
	class ZoneTree;
private: vector<ZoneTree> TableZone;
	   int maxsize;
public: Gojo(int maxsize) :maxsize(maxsize) { TableZone = vector<ZoneTree>(this->maxsize); }
	  ~Gojo() {
		  TableZone.clear();
	  }
	  void insertZoneTable(int result) {
		  int ID = result % maxsize;
		  TableZone[ID].insert(result);
	  }
	  void Kokusen() {
		  for (unsigned int i = 0; i < TableZone.size(); i++) {
			  int Y = TableZone[i].permutations();
			  TableZone[i].REMOVE(Y);
		  }
	  }
	  void Limitless(int num) {
		  if (num < 0 || num >= maxsize)return;
		  TableZone[num].print();
	  }
private: class ZoneTree {
	class Node;
private: Node* root;
	   queue<int> orderQueue;
	   vector<int> list;
public: ZoneTree() :root(nullptr) {}
	  ~ZoneTree() { REMOVE(orderQueue.size()); }
	  int size()const { return orderQueue.size(); }
	  void insert(Node*& root, int result) {
		  if (!root) { root = new Node(result); orderQueue.push(result); }
		  else if (result < root->result)insert(root->left, result);
		  else insert(root->right, result);
	  }
	  void insert(int result) { insert(this->root, result); }
	  void remove(Node*& root, int value) {
		  if (!root)return;
		  if (value < root->result)remove(root->left, value);
		  else if (value > root->result)remove(root->right, value);
		  else {
			  if (!root->left && !root->right) {
				  delete root; root = nullptr;
			  }
			  else if (!root->left) {
				  Node* temp = root;
				  root = root->right;
				  delete temp;
			  }
			  else if (!root->right) {
				  Node* temp = root;
				  root = root->left;
				  delete temp;
			  }
			  else {
				  Node* minRight = root->right;
				  while (minRight->left)minRight = minRight->left;
				  root->result = minRight->result;
				  remove(root->right, minRight->result);
			  }
		  }
	  }
	  void remove(int val) { remove(this->root, val); }
	  void REMOVE(long int num) {
		  int size = orderQueue.size();
		  if (num >= size) {
			  while (!orderQueue.empty()) {
				  orderQueue.pop();
			  }
			  while (root)remove(root->result);
		  }
		  else {
			  while (num) {
				  int value = orderQueue.front();
				  orderQueue.pop();
				  remove(value);
				  num--;
			  }
		  }
	  }
	  void print(Node* root) {
		  if (!root)return;
		  print(root->left);
		  cout << root->result << endl;
		  print(root->right);
	  }
	  void print() { print(this->root); }
	  void createVec(Node* root) {
		  if (!root)return;
		  list.push_back(root->result);
		  createVec(root->left);
		  createVec(root->right);
	  }
	  int permutations() {
		  createVec(this->root); if (!this->list.size())return this->list.size();
		  int result = ways(this->list);
		  this->list.clear();
		  return result;
	  }
private: class Node {
private: int result;
	   Node* left;
	   Node* right;
	   friend class ZoneTree;
public: Node(int result) :result(result), left(nullptr), right(nullptr) {}
};
};
};
template <typename E>
class HuffNode {
public:
	E getData()const { return it; }
	HuffNode<E>* left() const { return lc; }
	void setLeft(HuffNode<E>* b)
	{
		lc = b;
	}
	HuffNode<E>* right() const { return rc; }
	void setRight(HuffNode<E>* b)
	{
		rc = b;
	}
	virtual ~HuffNode() {}// Base destructor
	virtual int weight() = 0; // Return frequency
	virtual bool isLeaf() = 0; // Determine type
	virtual int getHeight() = 0;
	virtual HuffNode<E>* rotateLeft() = 0;
	virtual HuffNode<E>* rotateRight() = 0;
	virtual HuffNode<E>* BalanceLeft() = 0;
	virtual HuffNode<E>* BalanceRight() = 0;
	virtual HuffNode<E>* reBalance(int& i) = 0;
	void InOrderTraverse() {
		if (this->isLeaf()) { cout << this->getData() << "\n"; return; }
		this->lc->InOrderTraverse();
		cout << this->weight() << "\n";
		this->rc->InOrderTraverse();
	}
	string toBinary(string s, const E& ch) {
		if (this->isLeaf()) {
			if (this->it == ch)return s;
			else return "";
		}
		string s_l = s + '0'; s_l = this->left()->toBinary(s_l, ch);
		string s_r = s + '1'; s_r = this->right()->toBinary(s_r, ch);
		return (s_l.length() > 0) ? s_l : s_r;
	}

protected: E it;
		 HuffNode<E>* lc; // Left child
		 HuffNode<E>* rc; // Right child
};
template <typename E> // Leaf node subclass
class LeafNode : public HuffNode<E> {
private:
	// Value
	int wgt; // Weight
public:
	LeafNode(const E& val, int freq) // Constructor
	{
		this->it = val; wgt = freq; this->lc = this->rc = nullptr;
	}
	~LeafNode() { }
	int weight() { return wgt; }
	int getHeight() { return 0; }
	bool isLeaf() { return true; }
	HuffNode<E>* rotateLeft() { return this; }
	HuffNode<E>* rotateRight() { return this; }
	HuffNode<E>* BalanceLeft() { return this; }
	HuffNode<E>* BalanceRight() { return this; }
	HuffNode<E>* reBalance(int& i) { return this; }
};
template <typename E> // Internal node subclass
class IntlNode : public HuffNode<E> {
private:
	int wgt; // Subtree weight
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r)
	{
		wgt = l->weight() + r->weight(); this->lc = l; this->rc = r;
		this->it = '-';
	}
	~IntlNode() {
		if (this->lc)delete this->lc;
		if (this->rc)delete this->rc;
	}
	int weight() { return wgt; }
	bool isLeaf() { return false; }
	int getHeight() {
		int max_l = 1 + this->left()->getHeight();
		int max_r = 1 + this->right()->getHeight();
		return (max_r > max_l) ? max_r : max_l;
	}
	HuffNode<E>* rotateLeft() {
		HuffNode<E>* pR = this->right();
		this->setRight(pR->left());
		pR->setLeft(this);
		return pR;
	}
	HuffNode<E>* rotateRight() {
		HuffNode<E>* pR = this->left();
		this->setLeft(pR->right());
		pR->setRight(this);
		return pR;
	}
	HuffNode<E>* BalanceLeft() {
		int lH = this->left()->left()->getHeight(); int rH = this->left()->right()->getHeight();
		if (lH >= rH)return this->rotateRight();
		else {
			this->setLeft(this->left()->rotateLeft());
			return this->rotateRight();
		}
	}
	HuffNode<E>* BalanceRight() {
		int lH = this->right()->left()->getHeight(); int rH = this->right()->right()->getHeight();
		if (rH >= lH)return this->rotateLeft();
		else {
			this->setRight(this->right()->rotateRight());
			//this->InOrderTraverse(); system("pause");
			//HuffNode<E>* result = this->rotateLeft();
			return this->rotateLeft();
		}
	}
	HuffNode<E>* reBalance(int& i) {
		HuffNode<E>* root = this; if (i == 3)return root;
		int left = root->left()->getHeight(), right = root->right()->getHeight();
		while (i < 3 && (abs(left - right) > 1)) {
			if (left > right)root = root->BalanceLeft();
			else root = root->BalanceRight();
			++i;
			left = root->left()->getHeight();
			right = root->right()->getHeight();
		}
		root->setLeft(root->left()->reBalance(i));
		root->setRight(root->right()->reBalance(i));
		return root;
	}
};

// HuffTree is a template of two parameters: the element
// type being coded and a comparator for two such elements.
template <typename E>
class HuffTree {
private:
	HuffNode<E>* Root; // Tree root
	int index;
public:
	HuffTree(E& val, int freq, int idx) :index(idx) // Leaf constructor
	{
		Root = new LeafNode<E>(val, freq);
	}
	// Internal node constructor
	HuffTree(HuffTree<E>* l, HuffTree<E>* r, int idx) :index(idx)
	{
		Root = new IntlNode<E>(l->root(), r->root());
	}
	~HuffTree() { delete Root; }; // Destructor
	HuffNode<E>* root() { return Root; } // Get root
	int weight() { return Root->weight(); } // Root weight
	void reBalance(int& i, int idx) {
		int h(0);
		while (i < 3) {
			h = i;
			this->Root = this->Root->reBalance(i);
			if (i == h)break;
		}
		//this->Root = this->Root->reBalance(i);
		index = idx;
	}
	int Index()const { return index; }
	void Hand() { this->Root->InOrderTraverse(); }
};
template <typename E>
HuffTree<E>** treeArray(vector<pair<int, E>>& v) {
	const int n = v.size();
	HuffTree<E>** TreeArray = new HuffTree<E>*[n];
	for (int i = 0; i < n; i++)TreeArray[i] = new HuffTree<E>(v[i].second, v[i].first, i);
	return TreeArray;
}
template<typename E>
vector<HuffTree<E>*> treeVector(vector<pair<int, E>>& v) {
	const int n = v.size();
	vector<HuffTree<E>*> TreeVec(n);
	for (int i = 0; i < n; i++)TreeVec[i] = new HuffTree<E>(v[i].second, v[i].first);
	return TreeVec;
}
template <typename E>
struct HuffComp {
	bool operator()(HuffTree<E>*& a, HuffTree<E>*& b) { return (a->weight() == b->weight()) ? (a->Index() > b->Index()) : (a->weight() > b->weight()); }
};
template <typename E>
struct HuffComp1 {
	static bool prior(HuffTree<E>*& a, HuffTree<E>*& b) { return a->weight() <= b->weight(); }
};
// Build a Huffman tree from a collection of frequencies
template <typename E>
HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count) {
	priority_queue<HuffTree<E>*, vector<HuffTree<E>* >, HuffComp<E>> p;
	for (int i = 0; i < count; i++)p.push(TreeArray[i]); 
	int maxidx = TreeArray[count - 1]->Index();
	if (p.size() == 1)return p.top();
	HuffTree<E>* temp1, * temp2, * temp3 = NULL;
	while (p.size() > 1) {
		temp1 = p.top(); p.pop(); // Pull first two trees
		temp2 = p.top(); p.pop();  // off the list
		temp3 = new HuffTree<E>(temp1, temp2, ++maxidx); int i = 0;
		temp3->reBalance(i, maxidx);
		p.push(temp3); // Put the new tree back on list
		temp1 = nullptr;
		temp2 = nullptr;
	}
	return p.top();
}
template <typename E>
void printHuffmanTree(HuffNode<E>* root, string str) {
	if (root) {
		cout << root->getData() << "(" << root->weight() << ")" << endl;
		if (root->left() || root->right()) {
			cout << str << "|-- Left: ";
			printHuffmanTree(root->left(), str + "|   ");
			cout << str << "|__ Right: ";
			printHuffmanTree(root->right(), str + "    ");
		}
	}
}
class Sukuna {
private:	class Node {
private: int index;
	   int ID;
	   list<int> List;
	   friend class Sukuna;
public: Node(int ID) :ID(ID) {}
	  int size()const { return List.size(); }
	  int Index()const { return index; }
	  void insert(int result, int& idx) { List.push_front(result); index = ++idx; }
	  void remove(int num, int& idx) {
		  if (num > size())num = size();
		  while (num) { cout << *(--List.end()) << "-" << ID << endl; List.pop_back(); num--; }; index = ++idx;
	  }
	  void print(int num) {
		  for (list<int>::iterator i = List.begin(); num > 0 && i != List.end(); ++i, --num) {
			  cout << ID << "-" << *i << endl;
		  }
	  }
	  bool operator<(const Node& b) {
		  return (this->size() == b.size()) ? (this->index < b.index) : (this->size() < b.size());
	  }
	  static bool comp(const Node& a, const Node& b) {
		  return (a.size() == b.size()) ? (a.index < b.index) : (a.size() < b.size());
	  }
};
private: vector<Node> ZoneTable;
private:
	int count() const { return ZoneTable.size(); }
	void reHeapDown(int idx) {
		while (idx < this->count()) {
			int leftchild = idx * 2 + 1;
			if (leftchild >= this->count())return;
			if (leftchild + 1 < this->count() && ZoneTable[leftchild + 1] < ZoneTable[leftchild])leftchild++;
			if (ZoneTable[idx] < ZoneTable[leftchild])return;
			std::swap(ZoneTable[idx], ZoneTable[leftchild]);
			idx = leftchild;
		}
	};
	void reHeapUp(int idx) {
		while (idx) {
			int parent = (idx - 1) / 2;
			if (parent < 0)return;
			if (ZoneTable[parent] < ZoneTable[idx])return;
			std::swap(ZoneTable[parent], ZoneTable[idx]);
			idx = parent;
		}
	}
	int getIndex(int ID) {
		for (unsigned int i = 0; i < ZoneTable.size(); i++) {
			if (ZoneTable[i].ID == ID)return i;
		}
		return -1;
	}
private: int maxindex = 0;
	   int maxsize = 0;
public: Sukuna(int maxsize) { this->maxsize = maxsize; maxindex = 0; }
	  ~Sukuna() {
		  ZoneTable.clear();
	  }
	  void insertZoneTable(int result) {
		  int ID = result % maxsize + 1;
		  int index = getIndex(ID);
		  if (index == -1) {
			  ZoneTable.push_back(Node(ID));
			  index = ZoneTable.size() - 1;
			  ZoneTable[index].insert(result, maxindex);
			  this->reHeapUp(index);
		  }
		  else {
			  ZoneTable[index].insert(result, maxindex);
			  this->reHeapDown(index);
		  }

	  }
	  void Keiteiken(int num) {
		  if (this->count() <= 0)return; 
		  int numZone = (num > this->count()) ? this->count() : num;
		  vector<Node> DeleteList = ZoneTable;
		  std::sort(DeleteList.begin(), DeleteList.end(), Node::comp);
		  for (int i = 0; i < numZone; i++) {
			  int deleteindex = getIndex(DeleteList[i].ID);
			  ZoneTable[deleteindex].remove(num, maxindex);
			  if (ZoneTable[deleteindex].size() > 0)this->reHeapUp(deleteindex);
			  else {
				  std::swap(ZoneTable[this->count() - 1], ZoneTable[deleteindex]);
				  ZoneTable.pop_back();
				  this->reHeapDown(deleteindex);
			  }
		  }
	  }
	  void preOrderPrint(int index, int num) {
		  if (index >= this->count())return;
		  this->ZoneTable[index].print(num);
		  preOrderPrint(index * 2 + 1, num);
		  preOrderPrint(index * 2 + 2, num);
	  }
	  void Cleave(int num) {
		  preOrderPrint(0, num);
	  }
};
char CeasarEncode(char a, int num) {
	num = num % 26;
	if (a >= 'a' && a <= 'z') {
		return ((a + num) > 'z') ? (('a' - 1) + (a + num) % 'z') : (a + num);
	}
	if (a >= 'A' && a <= 'Z') {
		return ((a + num) > 'Z') ? (('A' - 1) + (a + num) % 'Z') : (a + num);
	}
	return '!';
}
vector<pair<int, char>> frequencySort(string& s) {
	vector<pair<int, char>> vec(123), vec1(123), result; int n = s.size();
	for (auto i : s) {
		vec[i].second = i;
		vec[i].first++;
	}
	for (int i = 0; i < n; i++)s[i] = CeasarEncode(s[i], vec[s[i]].first);
	vec.clear();
	for (auto i : s) {
		vec1[i].second = i;
		vec1[i].first++;
	}
	std::sort(vec1.begin(), vec1.end(), comp::prior);
	for (auto i : vec1)if (i.first)result.push_back(i);
	vec1.clear();
	return result;
}
int toDecimal(const string& s) {
	int result = 0; int j = 0;
	for (unsigned int i = (s.length() > 10) ? (s.length() - 10) : 0; i < s.length(); i++) {
		if (s[i] == '1') {
			result += pow(2, j);
		}
		j++;
	}
	return result;
}
int getResult(string& s, HuffTree<char>*& tree) {

	string tmp = "";
	vector<pair<int, char>> vp = frequencySort(s);
	//for (unsigned int i = 0; i < vp.size(); i++)cout << vp[i].first << vp[i].second << " ";
	//system("pause"); cout << endl << s; system("pause");
	//for (unsigned int i = 0; i < vp.size(); i++)cout << vp[i].second << vp[i].first << " ";
	tree = buildHuff<char>(treeArray<char>(vp), vp.size());
	if (tree->root()->isLeaf())return 0;
	for (unsigned int i = 0; i < s.size(); i++)tmp += tree->root()->toBinary("", s[i]);
	return toDecimal(tmp);
}
bool checkName(string& s) {
	map<char, int> count;
	for (unsigned int i = 0; (i < s.size()) && (count.size() < 3); i++) {
		count[s[i]]++;
	}
	return (count.size() >= 3);
}
class Run {
private: Gojo* gojo;
	   Sukuna* sukuna;
	   HuffTree<char>* lastCustomer;
	   int MAXSIZE;
public: Run(int maxsize) :MAXSIZE(maxsize) {
	gojo = new Gojo(MAXSIZE);
	sukuna = new Sukuna(MAXSIZE);
	lastCustomer = nullptr;
}
	  ~Run() { delete gojo; delete sukuna; if(lastCustomer)delete lastCustomer; }
	  void LAPSE(string& s) {
		  if (!checkName(s))return;
		  if (lastCustomer)delete lastCustomer;
		  int result = getResult(s, lastCustomer);
		  (result % 2) ? gojo->insertZoneTable(result) : sukuna->insertZoneTable(result);
		  return;
	  }
	  void KOKUSEN() {
		  gojo->Kokusen();
	  }
	  void KEITEIKEN(int NUM) {
		  sukuna->Keiteiken(NUM);
	  }
	  void HAND() {
		  if (lastCustomer)lastCustomer->Hand();
	  }
	  void LIMITLESS(int NUM) {
		  gojo->Limitless(NUM);
	  }
	  void CLEAVE(int NUM) {
		  sukuna->Cleave(NUM);
	  }
};
void simulate(string filename)
{
	ifstream ss(filename); Run* run = nullptr;
	string str, maxsize, name, num;
	while (ss >> str)
	{
		if (str == "MAXSIZE")
		{
			ss >> maxsize; MAXSIZE = stoi(maxsize);
			run = new Run(stoi(maxsize));
		}
		else if (str == "LAPSE")
		{
			ss >> name; //cout << str << endl;
			run->LAPSE(name);
		}
		else if (str == "KOKUSEN")
		{
			//cout << str << endl;
			run->KOKUSEN();
		}
		else if (str == "KEITEIKEN")
		{
			ss >> num; //cout << str << num << endl;
			run->KEITEIKEN(stoi(num));
		}
		else if (str == "HAND")
		{
			//cout << str << endl;
			run->HAND();
		}
		else if (str == "LIMITLESS")
		{
			ss >> num; //cout << str << num << endl;
			run->LIMITLESS(stoi(num) - 1);
		}
		else if (str == "CLEAVE")
		{
			ss >> num; //cout << str << num << endl;
			run->CLEAVE(stoi(num));
		}
	}
	delete run;
	return;
}


