/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:25:29 by tbillon           #+#    #+#             */
/*   Updated: 2022/05/09 09:32:54 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template <class T>
	class tree_iterator
	{
	public:
		typedef T 								value_type;
		typedef T 								*node_ptr;
		typedef typename T::value_type 			data;

		typedef data 							&reference;
		typedef data 							*pointer;

		typedef std::ptrdiff_t 					difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		tree_iterator() : _it(NULL), _root(NULL), _NIL(NULL) {}
		tree_iterator(node_ptr it, node_ptr root, node_ptr NIL) : _it(it), _root(root), _NIL(NIL) {}
		tree_iterator(const tree_iterator<typename std::remove_const<value_type>::type > &cpy) : _it(cpy._it), _root(cpy._root), _NIL(cpy._NIL) {}
		~tree_iterator() {}

		tree_iterator &operator=(const tree_iterator<typename std::remove_const<value_type>::type > &it)
		{
			_it = it._it;
			_root = it._root;
			_NIL = it._NIL;
			return *this;
		}

		bool operator==(const tree_iterator &it) const { return _it == it._it; }
		bool operator!=(const tree_iterator &it) const { return _it != it._it; }

		reference operator*() const { return _it->data; }
		pointer operator->() const { return &_it->data; }

		tree_iterator &operator++()
		{
			if (_it != _NIL)
				_it = _findNext();
			return *this;
		}

		tree_iterator operator++(int)
		{
			tree_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		tree_iterator &operator--()
		{
			if (_it != _NIL)
				_it = _findPrev();
			else
				_it = _findMax(_root);
			return *this;
		}

		tree_iterator operator--(int)
		{
			tree_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		node_ptr getCurrent() const { return _it; }

	private:
		node_ptr _findMin(node_ptr n)
		{
			while (n->left != _NIL)
				n = n->left;
			return n;
		}

		node_ptr _findMax(node_ptr n)
		{
			while (n->right != _NIL)
				n = n->right;
			return n;
		}

		node_ptr _findNext()
		{
			node_ptr n = _it;
			node_ptr next = _NIL;

			if (n->right != _NIL)
				return _findMin(n->right);
			next = n->parent;
			while (next != _NIL && n == next->right)
			{
				n = next;
				next = next->parent;
			}
			return next;
		}

		node_ptr _findPrev()
		{
			node_ptr n = _it;
			node_ptr prev = _NIL;

			if (n->left != _NIL)
				return _findMax(n->left);
			prev = n->parent;
			while (prev != _NIL && n == prev->left)
			{
				n = prev;
				prev = prev->parent;
			}
			return prev;
		}

		node_ptr _it;
		node_ptr _root;
		node_ptr _NIL;
	};
}