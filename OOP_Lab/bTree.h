#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

namespace LAB
{
	template <typename cType>
	class srchTree
	{
	public:
		template <typename cType>
		class tNode
		{
			friend class srchTree<cType>;
			tNode<cType>* parent;
			tNode<cType>* left;
			tNode<cType>* right;
			cType key;

			tNode(cType key = cType(), tNode<cType>* parent = nullptr, tNode<cType>* left = nullptr, tNode<cType>* right = nullptr) : key(key), parent(parent), left(left), right(right) {};
			~tNode() {}

			int maxDepth() const
			{
				int left_depth;
				if (left != nullptr)
				{
					left_depth = left->maxDepth();
				}
				else
				{
					left_depth = 0;
				}

				int right_depth;
				if (right != nullptr)
				{
					right_depth = left->maxDepth();
				}
				else
				{
					right_depth = 0;
				}

				return (left_depth > right_depth ? left_depth : right_depth) + 1;
			}

		public:
			tNode(tNode<cType>* source) : key(source->key), parent(source->parent), left(source->left), right(source->right) {}

			tNode* Left() { return left; };
			tNode* Right() { return right; };
			tNode* Parent() { return parent; };
			cType Key() { return key; };
		};

	private:
		//Tree starts here
		tNode<cType>* root = nullptr;

		static void push(cType& what, tNode<cType>* _where)
		{
			if (what < _where->key)
			{
				if (_where->left == nullptr)
				{
					_where->left = new tNode<cType>{ what, _where };
				}
				else
				{
					push(what, _where->left);
				}
			}
			else if (what > _where->key)
			{
				if (_where->right == nullptr)
				{
					_where->right = new tNode<cType>{ what, _where };
				}
				else
				{
					push(what, _where->right);
				}
			}
		}

		static void eliminate(tNode<cType>* deletable)
		{
			if (deletable->parent != nullptr)
			{
				if (deletable->key < deletable->parent->key)
				{
					deletable->parent->left = nullptr;
				}
				else
				{
					deletable->parent->right = nullptr;
				}
			}

			if (deletable->left != nullptr)
			{
				eliminate(deletable->left);
			}

			if (deletable->right != nullptr)
			{
				eliminate(deletable->right);
			}

			delete deletable;
			deletable = nullptr;
		}

		static void buildArrayIn(tNode<cType>* from, std::vector<cType>& receiver)
		{
			if (from->left != nullptr)
			{
				buildArrayIn(from->left, receiver);
			}
			
			receiver.push_back(from->key);
			

			if (from->right != nullptr)
			{
				buildArrayIn(from->right, receiver);
			}
		}

		static void buildArrayPre(tNode<cType>* from, std::vector<cType>& receiver)
		{
			receiver.push_back(from->key);

			if (from->left != nullptr)
			{
				buildArrayPre(from->left, receiver);
			}

			if (from->right != nullptr)
			{
				buildArrayPre(from->right, receiver);
			}
		}

		static void buildArrayPost(tNode<cType>* from, std::vector<cType>& receiver)
		{
			if (from->left != nullptr)
			{
				buildArrayPre(from->left, receiver);
			}

			if (from->right != nullptr)
			{
				buildArrayPre(from->right, receiver);
			}

			receiver.push_back(from->key);
		}

		static void copyRec(tNode<cType>* src, tNode<cType>* dest)
		{
			if (src->left != nullptr)
			{
				dest->left = new tNode<cType>{ src->left->key, dest };
				copyRec(src->left, dest->left);
			}

			if (src->right != nullptr)
			{
				dest->right = new tNode<cType>{ src->right->key,dest };
				copyRec(src->right, dest->right);
			}

		}

		static tNode<cType>* FindRec(cType key, tNode<cType>* _where)
		{
			if (key < _where->key)
			{
				if (_where->left == nullptr)
				{
					return nullptr;
				}
				else
				{
					return FindRec(key, _where->left);
				}
			}
			else if (key > _where->key)
			{
				if (_where->right == nullptr)
				{
					return nullptr;
				}
				else
				{
					return FindRec(key, _where->right);
				}
			}
			else
			{
				return _where;
			}
		}

		tNode<cType>* minValueNode(tNode<cType>* node)
		{
			if (node != nullptr)
			{
				while (node->left != nullptr)
					node = node->left;
			}
			return node;
		}

	public:

		srchTree() {}
		srchTree(cType initializer) : root(new tNode<cType>{ initializer }) {}
		srchTree(std::initializer_list<cType> list)
		{
			for (cType initializer : list)
			{
				add(initializer);
			}
		}
		srchTree(srchTree<cType>& source)
		{
			Copy(source);
		}

		srchTree(tNode<cType>& source)
		{
			if (source.root != nullptr)
			{
				root = new tNode<cType>{ source.root->key };
				copyRec(source.root, root);
			}
		}

		~srchTree()
		{
			Clear();
		}

		int getMaxDepth()
		{
			if (root != nullptr)
			{
				return root->maxDepth();
			}
			else
			{
				return 0;
			}
		}

		void add(cType element)
		{
			if (root == nullptr)
			{
				root = new tNode<cType>{ element };
			}
			else
			{
				push(element, root);
			}
		}

		void add(tNode<cType>* node)
		{
			add(node->key);

			if (node->left != nullptr)
			{
				add(node->left);
			}

			if (node->right != nullptr)
			{
				add(node->right);
			}
		}

		void add(srchTree<cType>& source) 
		{
			add(source.root);
		}

		void Copy(srchTree<cType>& source)
		{
			if (root != nullptr)
			{
				Clear();
			}

			if (source.root != nullptr)
			{
				root = new tNode<cType>{ source.root->key };
				copyRec(source.root, root);
			}
		}

		static void Copy(srchTree<cType>& source, srchTree<cType>& destination)
		{
			if (destination.root != nullptr)
			{
				destination.Clear();
			}

			if (source.root != nullptr)
			{
				destination.root = new tNode<cType>{ source.root.key };
				copyRec(source.root, destination.root);
			}
		}

		void Clear()
		{
			if (root != nullptr)
			{
				eliminate(root);
			}
			root = nullptr;
		}

		static void killBranch(tNode<cType>* element)
		{
			if (element != nullptr)
			{
				eliminate(element);
			}
		}

		static void In_order(std::vector<cType>& receiver, tNode<cType>* from)
		{
			if (from != nullptr)
			{
				buildArrayIn(from, receiver);
			}
		}

		void In_order(std::vector<cType>& receiver)
		{
			if (root != nullptr)
			{
				buildArrayIn(root, receiver);
			}
		}

		static void Pre_order(std::vector<cType>& receiver, tNode<cType>* from)
		{
			if (from != nullptr)
			{
				buildArrayPre(from, receiver);
			}
		}

		void Pre_order(std::vector<cType>& receiver)
		{
			if (root != nullptr)
			{
				buildArrayPre(root, receiver);
			}
		}

		static void Post_order(std::vector<cType>& receiver, tNode<cType>* from)
		{
			if (from != nullptr)
			{
				buildArrayPost(from, receiver);
			}
		}

		void Post_order(std::vector<cType>& receiver)
		{
			if (root != nullptr)
			{
				buildArrayPost(root, receiver);
			}
		}

		tNode<cType>* Root() { return root; };

		void Balance()
		{
			std::vector<cType> tmp;
			this->In_order(tmp);
			size_t size = tmp.size();

			if (size)
			{
				cType median = tmp[size / 2];
				this->Clear();
				this->add(median);
				for (cType& element : tmp)
				{
					this->add(element);
				}
			}
			//Might be improved
		}

		void Delete(tNode<cType>* deletable)
		{
			if (deletable != nullptr)
			{
				tNode<cType>** replaceable;
				if (deletable->parent != nullptr)
				{
					if (deletable == deletable->parent->left)
					{
						replaceable = &(deletable->parent->left);
					}
					else
					{
						replaceable = &(deletable->parent->right);
					}
				}
				else
				{
					replaceable = &root;
				}

				if (deletable != nullptr)
				{
					if (deletable->left == nullptr && deletable->right == nullptr)
					{
						*replaceable = nullptr;
						delete deletable;
						deletable = nullptr;
					}
					else if (deletable->left == nullptr)
					{
						*replaceable = deletable->right;
						deletable->right->parent = deletable->parent;
						delete deletable;
						deletable = nullptr;
					}
					else if (deletable->right == nullptr)
					{
						*replaceable = deletable->left;
						deletable->left->parent = deletable->parent;
						delete deletable;
						deletable = nullptr;
					}
					else
					{
						tNode<cType>* tmp = minValueNode(deletable->right);
						*replaceable = new tNode<cType>{ tmp->key, deletable->parent };
						delete deletable;
						if (tmp->right != nullptr)
						{
							tmp->parent->left = tmp->right;
							tmp->right->parent = tmp->parent;
						}
						else
						{
							tmp->parent->left = nullptr;
						}
						delete tmp;
					}
				}
			}
		}

		static tNode<cType>* Find(cType what, tNode<cType>* _where)
		{
			if (_where == nullptr)
			{
				return nullptr;
			}
			else
			{
				return FindRec(what, _where);
			}
		}

		tNode<cType>* Find(cType what)
		{
			if (root == nullptr)
			{
				return nullptr;
			}
			else
			{
				return FindRec(what, root);
			}
		}

		srchTree<cType>* operator= (srchTree<cType>& source)
		{
			Clear();
			if (source.root != nullptr)
			{
				root = new tNode<cType>{ source.root->Key() };
				copyRec(source.root, root);
			}
			return this;
		}

		srchTree<cType>* operator= (tNode<cType>* source)
		{
			Clear();
			if (source != nullptr)
			{
				root = new tNode<cType>{ source.Key() };
				copyRec(source, root);
			}
			return this;
		}

		tNode<cType>& operator-> () const
		{
			return(root);
		}

		srchTree<cType>& operator()(srchTree<cType>& src)
		{
			add(src);

			return *this;
		}

		srchTree<cType>& operator()(tNode<cType>* src)
		{
			add(src);

			return *this;
		}

		srchTree<cType>& operator()(std::initializer_list<cType> list)
		{
			for (cType elem : list)
			{
				add(elem);
			}
			
			return *this;
		}

		template <typename cType>
		friend std::ostream& operator<< (std::ostream& str, srchTree<cType>& tree)
		{
			std::vector<cType> tmp;
			tree.In_order(tmp);

			for (uint32_t i = 0; i < tmp.size(); ++i)
			{
				str << tmp[i] << ", ";
			}

			return str;
		}

		template <typename cType>
		friend std::istream& operator>> (std::istream& str, srchTree<cType>& tree)
		{
			cType tmp;
			str >> tmp;
			tree.add(tmp);
			return str;
		}
	};
}