#include<iostream>
using namespace std;

template<class K>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode<K>* _left;
	BinarySearchTreeNode<K>* _right;
	K _key;
	BinarySearchTreeNode(const K& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K> BSNode;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	BinarySearchTree( BinarySearchTree<K>& BSTree)
	{
		 _root = _BinarySearchTree(BSTree._root);
	}

	BSNode*& operator=( BinarySearchTree<K> BSTree)
	{
		swap(_root,BSTree._root);
	}

	~BinarySearchTree()                               //�����ڶ�������������ķ�ʽ
	{
		if (_root != NULL)
		{
			_MakeEmptyTree(_root);
			_root = NULL;
		}
	}

public:

	bool  Insert(const K& key )   //�����������_root, key�Ѿ����ڣ� key������
	{
		if (_root == NULL)
		{
			 _root = new BSNode(key);
			return  true;
		}
		else 
		{
			BSNode* cur = _root;
			BSNode* parent = NULL;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else  if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
					return false;
			}
			if (parent->_key > key)
			{
				parent->_left = new BSNode(key);
			}
			else
			{
				parent->_right = new BSNode(key);
			}

			return true;
		}
	}

	bool Find(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		BSNode* cur = _root;
		BSNode* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return true;
		}
		return false;
	}

	bool Remove(const K& key)
		//���������һ��dst�ڵ����ҽڵ㶼Ϊ�գ�
		//����dst�ڵ���ڵ�Ϊ�գ��丸�ڵ�ָ��dst�ڵ���ҽڵ� �����ҽڵ�Ϊ�գ��丸�ڵ�ָ��dst�ڵ����ڵ㣨��һ����������ڵڶ��������
		//��ɾ���Ľڵ��������ӽڵ㶼��ΪNULL ����ý������˼�룺dst�ڵ����������ڵ㽻������������С�ڵ㽻���� 
	{
		if (_root == NULL)
		{
			return false;
		}
		else
		{
			BSNode *cur = _root;
			BSNode *parent = NULL;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					if (cur->_left == NULL)   //��ǰ�ڵ����ΪNULL
					{
						if (parent->_key > key) //�ӽڵ�Ҫôȫ���ȸ��ڵ��Ҫô��ȫ���ȸ��ڵ�С
						{
							parent->_left = cur->_right;
							delete cur;
						}
						else
						{
							parent->_right = cur->_right;
							delete cur;
						}
						return true;
					}
					else if (cur->_right == NULL)             //��ΪNULL  �˴��������Ҷ�ΪNULL�Ľڵ�
					{
						if (parent->_key > key)
						{
							parent->_left = cur->_left;
							delete cur;

						}
						else
						{
							parent->_right = cur->_left;
							delete cur;
						}
						return true;
					}
					else                    
					{
						//���Ҳ�ΪNULL�����,ɾ��ĳ���ڵ㣺Ҫô�����ýڵ����һ���ҽڵ㣬<���ȿ���>Ҫô�����ýڵ����һ���ҽڵ�������ӽڵ㣬�����ɴ�֪if�ĳ�������

						BSNode* Tmp = cur;
						
						cur = cur->_right;
						if (cur->_left==NULL)//�˴�������һ��ΪNULL
						{
							swap(Tmp->_key, cur->_key);
							Tmp->_right = cur->_right;
							delete cur;
						}
						else
						{
							while (cur->_left)
							{
								parent = cur;
								cur = cur->_left;
							}
							swap(Tmp->_key, cur->_key);

							delete cur;
							parent->_left = NULL;
							return true;
						}
					}
				}

			}
			return false;
		}
	}


	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}
protected:


	BSNode*  _BinarySearchTree( BSNode*& root)
	{
		if (root == NULL)
			return NULL;
		BSNode* cur = root;
		BSNode* head = new BSNode(root->_key);
		head->_left = _BinarySearchTree(cur->_left);
		head->_right = _BinarySearchTree(cur->_right);
		return head;
	}

	void _MakeEmptyTree(BSNode*& root)
	{
		if (root == NULL)
			return;
		else
		{
			BSNode *cur = root;
			_MakeEmptyTree(cur->_left);
			_MakeEmptyTree(cur->_right);
			
			delete cur;
			cur = NULL;
			return;
		}

	}

	void _Inorder(BSNode* root)
	{
		if (root == NULL)
		{
			return;
		}
		BSNode* cur = root;
		_Inorder(cur->_left);
		cout << cur->_key << " ";
		_Inorder(cur->_right);
	}
protected:
	BSNode* _root;
};


void test()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BinarySearchTree<int> bs;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]);i++)
	{
		bs.Insert(a[i]);
	}

	bs.Inorder();
	cout << endl;
	cout << "Find: "<<bs.Find(3) << endl;
	cout << "Find: " << bs.Find(20) << endl;
	cout << "Remove<5>:"  ;
	bs.Remove(5);
	bs.Inorder();
	bs.Insert(a[0]);
	cout << "Remove<7>:";
	bs.Remove(7);
	bs.Inorder();

	BinarySearchTree<int> bs1(bs);
	cout << endl;
	cout << "bs1 & bs2:" << endl;
	bs1.Inorder();
	BinarySearchTree<int> bs2 = bs1;
	bs2.Inorder();


}