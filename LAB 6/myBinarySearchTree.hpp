#include <fstream>
#include <iostream>
using namespace std;

template <typename Comparable>
class myBinarySearchTree{
    public:
        myBinarySearchTree( ){
            root = nullptr;
        }

        // Copy constructor
        myBinarySearchTree( const myBinarySearchTree & rhs ){
            root = clone( rhs.root );
        }

        myBinarySearchTree( myBinarySearchTree && rhs ): root{ rhs.root }{
            rhs.root = nullptr;
        }
        ~myBinarySearchTree( ){
            makeEmpty( );
        }

        const Comparable & findMin( ) const{
            BinaryNode *minNode = findMin(root);
            return minNode->element;
        }
        const Comparable & findMax( ) const{
            BinaryNode *maxNode = findMax(root);
            return maxNode->element;
        }

        // Returns true if x is found in the tree.
        bool contains( const Comparable & x ) const{
            return contains( x, root );
        }
        bool isEmpty( ) const{
            return (root == nullptr);
        }
        void printTree( ostream & out = cout ) const;

        void makeEmpty( ){
            makeEmpty(root);
        }

        // Insert x into the tree; duplicates are ignored.
        void insert( const Comparable & x ){
            insert( x, root );
        }
        void insert( Comparable && x ){
            insert( x, root );
        }

        // Remove x from the tree. Nothing is done if x is not found.
        void remove( const Comparable & x ){
            remove( x, root );
        }

        myBinarySearchTree & operator=( const myBinarySearchTree & rhs ){
            myBinarySearchTree myBST_copy = rhs;
            std::swap(*this,rhs);
            return *this;
        }
        myBinarySearchTree & operator=( myBinarySearchTree && rhs ){
            std::swap(root,rhs.root);
            return *this;
        }

        void printTreeInorder( ostream & out = cout ) const{
            printTreeInorder(root,out);
        }
        void printTreePreorder( ostream & out = cout ) const{
            printTreePreorder(root,out);
        }
        void printTreePostorder( ostream & out = cout ) const{
            printTreePostorder(root,out);
        }
    private:
        struct BinaryNode{
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt ): element{ theElement }, left{ lt }, right{ rt } { }
            BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt ): element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
        };
        BinaryNode *root;

        /**
        * Internal method to insert into a subtree.
        * x is the item to insert.
        * t is the node that roots the subtree.
        * Set the new root of the subtree.
        */
        void insert( const Comparable & x, BinaryNode * & t ){
            if( t == nullptr )
                t = new BinaryNode{ x, nullptr, nullptr };
            else if( x < t->element )
                insert( x, t->left );
            else if( t->element < x )
                insert( x, t->right );
            else
                ; // Duplicate; do nothing
        }

        /**
        * Internal method to insert into a subtree.
        * x is the item to insert by moving.
        * t is the node that roots the subtree.
        * Set the new root of the subtree.
        */
        void insert( Comparable && x, BinaryNode * & t ){
            if( t == nullptr )
                t = new BinaryNode{ std::move( x ), nullptr, nullptr };
            else if( x < t->element )
                insert( std::move( x ), t->left );
            else if( t->element < x )
                insert( std::move( x ), t->right );
            else
                ; // Duplicate; do nothing
            }

        /**
        * Internal method to remove from a subtree.
        * x is the item to remove.
        * t is the node that roots the subtree.
        * Set the new root of the subtree.
        */
        void remove( const Comparable & x, BinaryNode * & t ){
            if( t == nullptr )
                return; // Item not found; do nothing
            if( x < t->element )
                remove( x, t->left );
            else if( t->element < x )
                remove( x, t->right );
            else if( t->left != nullptr && t->right != nullptr ){ // Two children
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
            else {
                BinaryNode *oldNode = t;
                t = ( t->left != nullptr ) ? t->left : t->right;
                delete oldNode;
            }
        }

        /**
        * Internal method to find the smallest item in a subtree t.
        * Return node containing the smallest item.
        */
        BinaryNode * findMin( BinaryNode *t ) const{
            if( t == nullptr ) return nullptr;
            if( t->left == nullptr ) return t;
            return findMin( t->left );
        }

        /**
        * Internal method to find the largest item in a subtree t.
        * Return node containing the largest item.
        */
        BinaryNode * findMax( BinaryNode *t ) const{
            if( t != nullptr )
                while( t->right != nullptr )
                    t = t->right;
            return t;
        }

        /**
        * Internal method to test if an item is in a subtree.
        * x is item to search for.
        * t is the node that roots the subtree.*/
        bool contains( const Comparable & x, BinaryNode *t ) const{
            if( t == nullptr ) return false;
            else if( x < t->element ) return contains( x, t->left );
            else if( t->element < x ) return contains( x, t->right );
            else return true; // Match
        }
        void makeEmpty( BinaryNode * & t ){
            if( t != nullptr ) {
                makeEmpty( t->left );
                makeEmpty( t->right );
                delete t;
            }
            t = nullptr;
        }

        // void printTree( BinaryNode *t, ostream & out ) const;
        void printTreeInorder( BinaryNode *t, ostream & out ) const{
            if (t != nullptr){
                printTreeInorder(t->left,out);
                Comparable item = t->element;
                out<<item<<endl;
                printTreeInorder(t->right,out);
            }
        }
        void printTreePreorder( BinaryNode *t, ostream & out ) const{
            if (t != nullptr){
                Comparable item = t->element;
                out<<item<<endl;
                if (t->left != nullptr){
                    printTreePreorder(t->left,out);
                }
                if (t->right!= nullptr){
                    printTreePreorder(t->right,out);
                }
            }
        }
        void printTreePostorder( BinaryNode *t, ostream & out ) const{
            if (t != nullptr){
                if (t->left != nullptr){
                    printTreePostorder(t->left,out);
                }
                if (t->right != nullptr){
                    printTreePostorder(t->right,out);
                }
                Comparable item = t->element;
                out<<item<<endl;
            }
        }

        // Internal method to clone subtree.
        BinaryNode * clone( BinaryNode *t ) const{
            if( t == nullptr )
                return nullptr;
            else
                return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
            }
    };
