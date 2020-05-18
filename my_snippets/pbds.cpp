C++ STL: Policy based data structures

// source: https://codeforces.com/blog/entry/11080

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

// After closer inspection you may find that the last two files contained in the library

#include <ext/pb_ds/detail/standard_policies.hpp>

// Namespace, which we will have to work in newer versions of C++ is called __gnu_pbds;, earlier it was called pb_ds;

// The tree-based container has the following declaration:

template <typename Key,                      // Key type
          typename Mapped,                   // Mapped-policy
          typename Cmp_Fn = std::less<Key>,  // Key comparison functor
          typename Tag =
              rb_tree_tag,  // Specifies which underlying data structure to use
          template <typename Const_Node_Iterator, typename Node_Iterator,
                    typename Cmp_Fn_,
                    typename Allocator_> class Node_Update =
              null_node_update,  // A policy for updating node invariants
          typename Allocator = std::allocator<char> >  // An allocator type
class tree;
    
/*
Experienced participants may have already noticed that if initialize the template only the first two types, 
we obtain almost exact copy of the container map. Just say, that this container can be set, for this you just 
need to specify the second argument template type as null_type ( in older versions it is null_mapped_type).

By the way Tag and Node_Update are missing in map. Let us examine them in more detail.

Tag — class denoting a tree structure, which we will use. There are three base-classes provided in STL for this, 
it is rb_tree_tag (red-black tree), splay_tree_tag (splay tree) and ov_tree_tag (ordered-vector tree). 
Sadly, at competitions we can use only red-black trees for this because splay tree and OV-tree using linear-timed 
split operation that prevents us to use them.

Node_Update — class denoting policy for updating node invariants. By default it is set to null_node_update, ie, 
additional information not stored in the vertices. In addition, C++ implemented an update policy 
tree_order_statistics_node_update, which, in fact, carries the necessary operations. Consider them. 
*/

// Most likely, the best way to set the tree is as follows:

typedef tree<int,
             null_type,
             less<int>,
             rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;

// If we want to get map but not the set, as the second argument type must be used mapped type. 
// Apparently, the tree supports the same operations as the set (at least I haven't any problems with them before), 
// but also there are two new features — it is find_by_order() and order_of_key(). 

// The first returns an iterator to the k-th largest element (counting from zero), 
// the second — the number of items in a set that are strictly smaller than our item. Example of use:


ordered_set X;
X.insert(1);
X.insert(2);
X.insert(4);
X.insert(8);
X.insert(16);

cout << *X.find_by_order(1) << endl;             // 2
cout << *X.find_by_order(2) << endl;             // 4
cout << *X.find_by_order(4) << endl;             // 16
cout << (end(X) == X.find_by_order(6)) << endl;  // true

cout << X.order_of_key(-5) << endl;   // 0
cout << X.order_of_key(1) << endl;    // 0
cout << X.order_of_key(3) << endl;    // 2
cout << X.order_of_key(4) << endl;    // 2
cout << X.order_of_key(400) << endl;  // 5

// Usage: 

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// After this, we can define a data structure indexed_set that is like set but can be
// indexed like an array. The definition for int values is as follows:

typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

// Now we can create a set as follows:
indexed_set s;
s.insert(2);
s.insert(3);
s.insert(7);
s.insert(9);

auto x = s.find_by_order(2);
cout << *x << "\n"; // 7

cout << s.order_of_key(7) << "\n"; // 2

// If the element does not appear in the set, we get the position that the element would have in the set:
cout << s.order_of_key(6) << "\n"; // 2
cout << s.order_of_key(8) << "\n"; // 3
// Both the functions work in logarithmic time.

// For multiset:
// You need to change the comparison function from less to less_equal asn in the following:

typedef tree<
    int,
    null_type,
    less_equal<int>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_set;

// Works fine for inserts and order_of_key, find_by_order query
// Drawback of using less_equal instead of less is that lower_bound works as upper_bound and vice-versa.
// By definition of lower_bound function (according to cplusplus.com) it finds the first element not compared true 
// for less<int> comparision function

// How can i use it like multiset ?
// Main idea is to keep pairs like {elem, id}.

typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

int t = 0;

ordered_set me;
...
me.insert({x, t++});
me.erase(me.lower_bound({x, 0}));
cout << me.order_of_key({x, 0}) << "\n";

// How can I use a custom compare function in the "Key comparison functor" section for custom data types?
// Just like for regular set..

// I suppose you can overload operator and still use less<T>. 
// Also you can use functors and lambdas in the way similar as for sets:

auto cmp = [](int a, int b){return a < b;};
tree<int, null_type, decltype(cmp)> x(cmp);
tree<int, null_type, function<bool(int, int)>> y([](int a, int b) {
                                                 return a < b;});


// source: https://codeforces.com/blog/entry/10355, https://codeforces.com/blog/entry/10355?#comment-157883
// Zlobober: https://ideone.com/JlJ86R

#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
 
// we will use this class, it is able to do everything
// simple map<int, int> can do, and as we can see, much more!
typedef tree<int, int, less<int>, rb_tree_tag> Tree;
// another choice is to use splay_tree_tag for splay tree implementation
 
void print_tree(Tree::node_iterator it, Tree::node_iterator null, int indent = 0)
{
    if (it == null)
        return;
    // that's how we can access left child and right child
    // as I understand, there is no way to access parent node
    print_tree(it.get_l_child(), null, indent + 1);
    for (int i = 0; i < indent; i++)
        printf("    ");
    printf("(%d %d)\n", (**it).first, (**it).second);
    // of course this is equal to:
    // printf("(%d %d)\n", (*it)->first, (*it)->second);
    print_tree(it.get_r_child(), null, indent + 1);
}
 
int main()
{
    Tree X;
    // we can use X like usual map container
    for (int i = 0; i < 15; i++)
        X[i * i] = i ^ (i + 1);
    // we can iterate over it using iterators, begin() and end()
    for (Tree::iterator it = X.begin(); it != X.end(); it++)
        printf("%d %d\n", it->first, it->second);
    /* output:
     * 0 1
     * 1 3
     * 4 1
     * 9 7
     * 16 1
     * 25 3
     * 36 1
     * 49 15
     * 64 1
     * 81 3
     * 100 1
     * 121 7
     * 144 1
     * 169 3
     * 196 1
     */
    // but implementation gives us cool interface to access nodes of the tree!
    Tree::node_iterator root = X.node_begin();
    // for example we can print value at the root of the tree
    // root has type node_iterator
    // *root has type point_iterator == iterator (these two types are synonimic for trees)
    // **root has containing type (pair<int, int> in our case)
    printf("%d %d\n", (**root).first, (**root).second);
    // output: 9 7 
    // let's traverse the tree using methods get_l_node() and get_r_node()
    print_tree(root, X.node_end()); // X.node_end() defines null (leaf terminator) for this tree
    /* output:
     *         (0 1)
     *     (1 3)
     *         (4 1)
     * (9 7)
     *            (16 1)
     *         (25 3)
     *             (36 1)
     *     (49 15)
     *             (64 1)
     *         (81 3)
     *                 (100 1)
     *             (121 7)
     *                     (144 1)
     *                 (169 3)
     *                     (196 1)
     */
    Tree Y;
    // Now we are going to split by the key 42 
    // (42 and greater are moving to the right operand Y, other keys remain in X tree)
    X.split(42, Y);
    print_tree(X.node_begin(), X.node_end());
    /* output:
     *         (0 1)
     *     (1 3)
     *         (4 1)
     * (9 7)
     *         (16 1)
     *     (25 3)
     *         (36 1)
     */
    print_tree(X.node_begin(), X.node_end());
    /* output:
     *         (0 1)
     *     (1 3)
     *         (4 1)
     * (9 7)
     *         (16 1)
     *     (25 3)
     *         (36 1)
     */
    // notice that both parts are absolutely balanced!
    // we can merge them back
    X.join(Y);
    printf("%d\n", (int)X.size());
    // output: 15 
    // we can find lower bound for a key in this tree
    Tree::iterator it = (X.lower_bound(42));
    // it returns a usual iterator, not a node_iterator
    // it's easy to understand that it is more formally correct: one can possibly
    // use this tree as usual map, and it will be a big surprise, that lower_bound
    // returns some strange node_iterator type instead of usual iterator
    printf("%d %d\n", it->first, it->second);
    // output: 49 15 
    // but now some strange effect: we can simply cast node_iterator to iterator
    // with dereferensing (*node_iterator = iterator), but I didn't found
    // any other way to do the reverse cast (from iterator to node_iterator) except this:
    Tree::node_iterator n_it = it.m_p_nd;
    printf("%d %d\n", (*n_it)->first, (*n_it)->second);
    // output: 49 15
    // .m_p_nd field is left public, that is strange for c++-library style, but
    // I don't know other ways to convert iterator to node_iterator. Any ideas?
 
    return 0;
}

// source: https://ideone.com/jOxlgl

#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
 
template<typename node_const_iterator, typename node_iterator, typename cmp_fn,
	   typename _Alloc>
struct tree_max
{
    typedef int metadata_type;
 
    tree_max(){}
 
    inline void operator() (node_iterator it, node_const_iterator null) const
    {
        int mx = (*it)->second;
        if (it.get_l_child() != null)
            mx = max(mx, it.get_l_child().get_metadata());
        if (it.get_r_child() != null)
            mx = max(mx, it.get_r_child().get_metadata());
        (int&)(it.get_metadata()) = mx;
    }
};
 
typedef tree<int, int, less<int>, splay_tree_tag, tree_max> Tree;
 
Tree A; 
 
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int t;
        scanf("%d", &t);
        A.insert(make_pair(i, t));
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char t;
        int x, y;
        scanf(" %c %d %d", &t, &x, &y);
        if (t == 'u')
        {
            A.erase(x);
            A.insert(make_pair(x, y));
        }
        else
        {
            Tree B, C;
            A.split(y, C);
            A.split(x - 1, B);
            printf("%d ", B.node_begin().get_metadata());
            A.join(B);
            A.join(C);
        }
    }
}
