//boundary traversal of tree
#include<bits/stdc++.h>
using namespace std;
class Node{
	public:
		int data; 
		Node *left, *right;
};
Node* newnode(int data){
	Node* p = new Node;
	p -> left = NULL;
	p -> right = NULL;
	p -> data = data;
	return p;
}
void fun(Node* root){
	queue<Node*> q;
	q.push(root);
	q.push(NULL);
	vector<Node*> leaf;
	stack<Node*> right;
	Node *temp = NULL;
	while(!q.empty()){
		Node *p = q.front();
		q.pop();
		if(temp == NULL && p != NULL){
			cout << p -> data << "-" <<  " ";
		}
		else if(q.front() == NULL && p != NULL)
		{
			right.push(p);
		}
		if(p == NULL)
		{
			if(q.empty())
				break;
			q.push(NULL);
			temp = NULL;
			continue;
		}
		if(p -> left == NULL && p -> right == NULL && temp != NULL && q.front() != NULL)
		{
			leaf.push_back(p);
		}
		if(p -> left)
			q.push(p -> left);
		if(p -> right)
			q.push(p -> right);
		temp = p;
	}
	for(auto x : leaf)
	{
		cout << x -> data << " "; 
	}
	
	while(!right.empty()){
		cout << right.top() -> data << " ";
		right.pop();
	}
}
Node* lca(Node* root, int k1, int k2){
	if(root == NULL)
		return NULL;
	if(root -> data == k1)
		return root;
	if(root -> data == k2)
		return root;
	Node* left = lca(root -> left, k1, k2);
	Node* right = lca(root -> right, k1, k2);
	if(left && right)
	{
		return root;
	}
	return left ? left : right;	
}
void inorder(Node* root){
	if(root == NULL)
		return;
	inorder(root -> left);
	cout << root -> data << " ";
	inorder(root -> right);
}
void DLL(Node* root, Node** head_ref, Node** dll_head, Node** last_head){
	if(root == NULL){
		return;
		}
	DLL(root -> left, head_ref, dll_head, last_head);
	root -> left = (*head_ref);
	if((*head_ref)){
			(*head_ref) -> right = root;
		}
	else{
		(*dll_head) = root; 
	}
	(*head_ref) = root;
	(*last_head) = root;
	DLL(root -> right, head_ref, dll_head, last_head);
}
void show(Node** head_ref){
	Node *p = (*head_ref);
	cout << endl;
	while(p){
		cout << p -> data << " ";
		p = p -> right;
	}
	cout << endl;
}
void itrinorder(Node* root){
	stack<Node*> s;
	cout << endl;
	while(1){
		while(root)
		{
			s.push(root);
			root = root -> left;
		}
		if(s.empty())
			break;
		root = s.top();
		s.pop();
		cout << root -> data << " ";
		root = root -> right;	
	}
	cout << endl;
}
void morris(Node* root){
	if(!root)
		return;
	while(root)
	{
		if(root -> left == NULL)
		{
			cout << root -> data << " ";		
			root = root -> right;
		}
		else{
			 Node* pre = root->left; 
            while (pre->right != NULL && pre->right != root) 
                pre = pre->right; 
  			if (pre->right == NULL) { 
                pre->right = root; 
                root = root->left; 
            } 
  			else { 
                pre->right = NULL; 
                cout << root -> data << " "; 
                root = root -> right; 
            }
		}
	}
}

void kdist(Node* root, int k, int now){
	if(k < 0)
		return;
	if(root != NULL){
		if(k == now)
		{
			cout << root -> data << " ";
			return;
		}
		now++;
		kdist(root -> left, k, now);
		kdist(root -> right, k, now);
	}
}

int kdist(Node* root, int target, int k, int now, stack<Node*>& s){
	if(root == NULL)
		return 0;
	if(root -> data == target || now != 0){
		now++;
	}
	if(now == k + 1){
		cout << root -> data << " ";
		return 0;
	}
	s.push(root);
	int np1 = kdist(root -> left, target, k, now,  s);
	int np2 = kdist(root -> right, target, k, now, s);
	
	if(root -> data == target){
		Node* prev = s.top();
		s.pop();

			int c = 1;
		while(!s.empty()){
			Node* x = s.top();
			s.pop();
			if(x -> left == prev)
				kdist(x -> right, k - c - 1, 0);
			else if(x -> right == prev)
				kdist(x -> left, k - c - 1, 0);
			prev = x;
			if(c == k)
				cout <<  x -> data << " ";
			c++;
		}
	}
	if(!s.empty())
	s.pop();
	return 0;
}
int search(int inorder[], int ins, int ine, int e){
	for(int i = ins; i <= ine; i++){
		if(inorder[i] == e)
			return i;
	}
	return -1;
}
Node* fun(int inorder[], int preorder[], int ins, int ine){
	static int pi = 0;
	if(ins > ine)
		return NULL;
	Node *p = new Node;
	p -> data = preorder[pi];
	pi++;
	if(ins == ine)
		return p;
	int inorderindex = search(inorder, ins, ine, p -> data);
	p -> left = fun(inorder, preorder, ins, inorderindex - 1);
	p -> right = fun(inorder, preorder, inorderindex + 1, ine);
	return p;
}
int searchh(int inorder[], int ins, int ine, int e){
	for(int i = ins; i <= ine; i++){
		if(inorder[i] == e)
			return i;
	}
	return 1;
}
Node* build(int inorder[], int postorder[], int ins, int ine){
	static int pi = 5;
	if(ins > ine)
		return NULL;
	Node *p = new Node;
	if(!p)
	{
		cout << "Memory error";
		exit(0);
	}
	p -> data = postorder[pi];
	pi--;
	if(ins == ine)
		return p;
	int inorderindex = searchh(inorder, ins, ine, p -> data);
	p -> right = build(inorder, postorder, inorderindex + 1, ine);
	p -> left = build(inorder, postorder, ins, inorderindex - 1);
	return p;
}
Node* funnn(int inorder[], int level[], int ins, int ine, int lsize){
	if(ins < ine) return NULL;
	Node *p = new Node;
	if(!p){
		cout << "Memory error";
		exit(0);
	}
	p -> data = level[0];
	set<int> s;  int index;
	for(int i = ins; i <= ine; i++){
		if(inorder[i] == p -> data){
			index = p -> data;
			break;
		}
		s.insert(inorder[i]);
	}
	int ll = 0, rl = 0, llevel[s.size()], rlevel[ine - ins - s.size()];
	for(int i = 0; i <= lsize; i++){
		if(s.find(level[i]) != s.end())
			llevel[ll++] = level[i];
		else
			rlevel[rl++] = level[i];
	}
	p -> left = funnn(inorder, llevel, ins, index - 1, ll);
	p -> right = funnn(inorder, rlevel, index + 1, ine, rl);
	return p;
}

void leftt(Node *root, vector<int>& left){
	if(root == NULL)
		return;
	left.push_back(root -> data);
	leftt(root -> left, left);
}
void rightt(Node *root, vector<int>& left){
	if(root == NULL)
		return;
	left.push_back(root -> data);
	rightt(root -> right, left);
}
void leaff(Node *root, vector<int>& leaf){
	if(!root)
		return;
	leaff(root -> left, leaf);
	if(root -> left == NULL && root -> right == NULL)
	{
		leaf.push_back(root -> data);
		return;
	}
	leaff(root -> right, leaf);
}
void boundary(Node *root){
	vector<int> left;
	leftt(root -> left, left);
	vector<int> right;
	rightt(root -> right, right);
	vector<int> leaf;
	leaff(root, leaf);
	reverse(right.begin(), right.end());
	cout << root -> data << " ";
	for(auto x : left)
		cout << x << " ";
	for(int i = 1; i < leaf.size() - 1; i++){
		cout << leaf[i] << " ";
	}
	for(auto x : right)
		cout << x << " ";
}
int sumtree(Node* root){
	if(!root){
		return 0;
	}
	int left = sumtree(root -> left);
	int right = sumtree(root -> right);
	return root -> data + left + right;
}
int even(Node* root, int sum, bool *res){
	if(!root){
		return 0;
	}
	int left = even(root -> left, sum, res);
	int right = even(root -> right, sum, res);
	if(root -> data + left + right == sum / 2){
		*res = true;
	}
	return root -> data + left + right;
}

int main(){
	Node *root = newnode(1);
	root -> left = newnode(2);
	root -> right = newnode(3);
	root -> left -> left = newnode(4);
	root -> left -> right = newnode(5);
	root -> left -> right -> left = newnode(6);
	root -> left -> right -> right = newnode(7);
	root -> right -> left = newnode(8);
	root -> right -> right = newnode(9);
	root -> right -> left -> right = newnode(10);
	cout << endl;
	/*
	int sum = sumtree(root);
	cout << sum << endl;
	bool res = false;
	even(root, sum, &res);
	cout << res << endl;
	inorder(root);
	cout << endl;
	boundary(root);
	int nowpre = 0;
	stack<Node*> s;
	kdist(root, 3, 2, 0, s);
	cout << endl;
	morris(root);
	Node *prev = NULL;
	Node* dll = NULL;
	Node* last = NULL;
	DLL(root, &prev, &dll, &last);
	show(&dll);
	dll -> left = last;
	last -> right = dll;
	//show(&dll);
	//cout << dll -> right -> data;
	cout << endl << dll -> left -> left -> left -> data << endl;
	//itrinorder(root);
*/	return 0;
}
