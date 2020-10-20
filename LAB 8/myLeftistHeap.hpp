#include <iostream>
#include <algorithm>    // std::max
#include <stdexcept>
#include <math.h>
#include <cmath>  // fmod
#include <vector>
using namespace std;

template <typename Comparable>
class myLeftistHeap {
    public:
        myLeftistHeap( ){
            root = nullptr;
        }
        myLeftistHeap( const myLeftistHeap & rhs ){
            root = new LeftistNode{rhs.root->element};
            clone(rhs.root,root);
        }
        myLeftistHeap( myLeftistHeap && rhs ){
            root = rhs.root;
            rhs.root = nullptr;
        }

        ~myLeftistHeap( ){
            makeEmpty();
            delete root;
            root = nullptr;
        }

        myLeftistHeap & operator=( const myLeftistHeap & rhs ){
            myLeftistHeap copy = rhs;
            std::swap( *this, copy );
            return *this;
        }
        myLeftistHeap & operator=( myLeftistHeap && rhs ){
            std::swap( root, rhs.root );
            return *this;
        }
        bool isEmpty( ) const{
            if (root == nullptr)
                return true;
            // if ((root->left == nullptr) && (root->right == nullptr))
            //     return true;
            return false;
        }
        const Comparable & findMin( ) const{
            return root->element;
        }

        /**
        * Inserts x; duplicates allowed.
        */
        void insert( const Comparable & x ){
            root = merge( new LeftistNode{ x }, root );
        }
        void insert( Comparable && x ){
            root = merge( new LeftistNode{ x }, root );
        }

        /**
        * Remove the minimum item.
        */
        void deleteMin( ){
            if( isEmpty( ) )
                // throw underflow_error{"called deleteMin( ) while heap is empty"};
                return;
            LeftistNode *oldRoot = root;
            root = merge( root->left, root->right );
            delete oldRoot;
        }

        /**
        * Remove the minimum item and place it in minItem.
        */
        void deleteMin( Comparable & minItem ){
            minItem = findMin( );
            deleteMin( );
        }
        void makeEmpty( ){
            while (!isEmpty()){
                deleteMin();
            }
        }

        /**
        * Merge rhs into the priority queue.
        * rhs becomes empty. rhs must be different from this.
        */
        void merge( myLeftistHeap & rhs ){
            if( this == &rhs ) // Avoid aliasing problems
                return;
            root = merge( root, rhs.root );
            rhs.root = nullptr;
        }

        void printInOrder(){
            inOrderTraversal(root);
        }
        void printLevelOrder(){
            levelOrderTraversal(root);
        }
        void printNice(){
            cerr<<"root->element: "<<root->element<<endl;
            //
            cerr<<"root->left->element: "<<root->left->element<<endl;
            cerr<<"root->right->element: "<<root->right->element<<endl;
            //
            cerr<<"root->left->left->element: "<<root->left->left->element<<endl;
            cerr<<"root->left->right->element: "<<root->left->right->element<<endl;
            cerr<<"root->right->left->element: "<<root->right->left->element<<endl;
            cerr<<"root->right->right->element: "<<root->right->right->element<<endl;
            //
            cerr<<"root->left->left->left->element: "<<root->left->left->left->element<<endl;
            cerr<<"root->left->left->right->element: "<<root->left->left->right->element<<endl;
            cerr<<"root->left->right->left->element: "<<root->left->right->left->element<<endl;
            cerr<<"root->left->right->right->element: "<<root->left->right->right->element<<endl;
            cerr<<"root->right->left->left->element: "<<root->right->left->left->element<<endl;
            cerr<<"root->right->left->right->element: "<<root->right->left->right->element<<endl;
            cerr<<"root->right->right->left->element: "<<root->right->right->left->element<<endl;
            cerr<<"root->right->right->right->element: "<<root->right->right->right->element<<endl;
            //
            cerr<<"(root->left->left->left->left==nullptr): "<<(root->left->left->left->left==nullptr)<<endl;
            cerr<<"(root->left->left->left->right==nullptr): "<<(root->left->left->left->right==nullptr)<<endl;
            cerr<<"(root->left->left->right->left==nullptr): "<<(root->left->left->right->left==nullptr)<<endl;
            cerr<<"(root->left->left->right->right==nullptr): "<<(root->left->left->right->right==nullptr)<<endl;
            cerr<<"(root->left->right->left->left==nullptr): "<<(root->left->right->left->left==nullptr)<<endl;
            cerr<<"(root->left->right->left->right==nullptr): "<<(root->left->right->left->right==nullptr)<<endl;
            cerr<<"(root->left->right->right->left==nullptr): "<<(root->left->right->right->left==nullptr)<<endl;
            cerr<<"(root->left->right->right->right==nullptr): "<<(root->left->right->right->right==nullptr)<<endl;
            cerr<<"root->right->left->left->left->element: "<<root->right->left->left->left->element<<endl;
            cerr<<"root->right->left->left->righ->elementt: "<<root->right->left->left->right->element<<endl;
            cerr<<"root->right->left->right->left->element: "<<root->right->left->right->left->element<<endl;
            cerr<<"root->right->left->right->right->element: "<<root->right->left->right->right->element<<endl;
            cerr<<"(root->right->right->left->left==nullptr): "<<(root->right->right->left->left==nullptr)<<endl;
            cerr<<"(root->right->right->left->right==nullptr): "<<(root->right->right->left->right==nullptr)<<endl;
            cerr<<"root->right->right->right->left->element: "<<root->right->right->right->left->element<<endl;
            cerr<<"(root->right->right->right->right==nullptr): "<<(root->right->right->right->right==nullptr)<<endl;
            vector<Comparable> treeVec = treeAsVector();
            cerr<<"\n-------------------------";
            int currentSize = treeVec.size();
            if (isEmpty()){ return; }

            int height = 1+(log(currentSize)/log(2));
            int maxVal = treeVec[0];
            int counter = 0;
            for (int i = 0;i<currentSize;i++) {
                if (treeVec[i] > maxVal){
                    maxVal = treeVec[i];
                }
                counter ++;
            }
            std::string max = std::to_string(maxVal);
            int spacing = max.length()+1;
            if (spacing % 2 == 1){ spacing++; }
            std::string the_str = "";
            int space_locations_len = spacing*pow(2,height-2)-2;
            int space_locations[space_locations_len];
            for (int i=0; i<space_locations_len; i++) {
                space_locations[i]=0;
            }
            int i = 0;
            for (int j=pow(2,height-1)-1; j<pow(2,height)-1; j++) {
                space_locations[j]=i*spacing;
                i++;
            }

            for (int row=height-1; row>-1; row--){
                cerr<<endl;
                std::string row_str = "";
                int line_location = 0;
                for (int entry = pow(2,row)-1;entry<pow(2,row+1)-1;entry++){
                    if (entry < currentSize) {
                        Comparable value = treeVec[entry];
                        int len_entry = std::to_string(value).length();
                        if (row == (height-1)){
                            for (int i = 0; i < (spacing - len_entry);i++){
                                row_str = row_str + " ";
                                line_location++;
                            }
                            row_str = row_str + std::to_string(value);
                            line_location=line_location + len_entry;
                        } else {
                            int child_1_pos = space_locations[entry*2+1];
                            int child_2_pos = space_locations[entry*2+2];
                            int new_pos = (child_1_pos + child_2_pos) / 2;
                            space_locations[entry] = new_pos;
                            int line_location_static = line_location;
                            for (int i = 0;i<(new_pos - line_location_static);i++){
                                row_str = row_str + " ";
                                line_location++;
                            }
                            for (int i = 0; i < (spacing - len_entry);i++){
                                row_str = row_str + " ";
                                line_location++;
                            }
                            row_str = row_str + std::to_string(value);
                            line_location+=len_entry;
                        }
                    }
                }
                row_str = row_str + "\n";
                the_str = row_str + the_str;
            }
            cerr<<the_str<<"\n-------------------------\n";
        }

    private:
        struct LeftistNode {
            Comparable element;
            LeftistNode *left = nullptr;
            LeftistNode *right = nullptr;
            int npl; // shortest null path length

            LeftistNode( const Comparable & e, LeftistNode *lt = nullptr,
                         LeftistNode *rt = nullptr, int np = 0 )
                         : element{ e }, left{ lt }, right{ rt }, npl{ np } { }

            LeftistNode( Comparable && e, LeftistNode *lt = nullptr,
                         LeftistNode *rt = nullptr, int np = 0 )
                         : element{ std::move( e ) }, left{ lt }, right{ rt }, npl{ np } { }
        };

        LeftistNode *root;

        /**
        * Internal method to merge two roots.
        * Deals with deviant cases and calls recursive merge1.
        */
        LeftistNode * merge( LeftistNode *h1, LeftistNode *h2 ){
            if( h1 == nullptr )
                return h2;
            if( h2 == nullptr )
                return h1;
            if( h1->element < h2->element )
                return merge1( h1, h2 );
            else
                return merge1( h2, h1 );
        }

        /**
        * Internal method to merge two roots.
        * Assumes trees are not empty, and h1’s root contains smallest item.
        */
        LeftistNode * merge1( LeftistNode *h1, LeftistNode *h2 ){
        if( h1->left == nullptr ) // Single node
            h1->left = h2; // Other fields in h1 already accurate
        else {
            h1->right = merge( h1->right, h2 );
            if( h1->left->npl < h1->right->npl )
                swapChildren( h1 );
            h1->npl = h1->right->npl + 1;
            }
            return h1;
        }

        void swapChildren( LeftistNode *t ){
            std::swap(t->left,t->right);
        }
        void reclaimMemory( LeftistNode *t );

        void clone( LeftistNode *t, LeftistNode *newT ) {
            if (t->left != nullptr){
                int newElement = t->left->element;
                newT->left = new LeftistNode{newElement};
                clone(t->left,newT->left);
            }
            if (t->right != nullptr){
                newT->right = new LeftistNode{t->right->element};
                clone(t->right,newT->right);
            }
        }

        void inOrderTraversal( LeftistNode *node){
            if (node == nullptr)
                return;
            if (node->left != nullptr)
                inOrderTraversal(node->left);
            cout<<node->element<<endl;
            if (node->right != nullptr)
                inOrderTraversal(node->right);
        }

        // level order traversal algorithm adapted from explanation at
        // https://www.geeksforgeeks.org/level-order-tree-traversal/
        int getTreeHeight(LeftistNode *tree){
            if ((tree->left == nullptr)&&(tree->right == nullptr))
                return 1;
            else {
                int leftHeight = 0;
                int rightHeight = 0;
                if (tree->left != nullptr)
                    leftHeight = getTreeHeight(tree->left);
                if (tree->right != nullptr)
                    rightHeight = getTreeHeight(tree->right);
                int maxChildHeight = max(leftHeight,rightHeight);
                return 1 + maxChildHeight;
            }
            return 0;
        }
        void printLevel(LeftistNode *tree, int levelNumber){
            if (tree == nullptr)
                return;
            if (levelNumber == 1)
                cout<<tree->element<<endl;
            else {
                printLevel(tree->left,levelNumber-1);
                printLevel(tree->right,levelNumber-1);
            }
        }
        void levelOrderTraversal( LeftistNode *tree){
            if (tree == nullptr)
                return;
            int treeHeight = getTreeHeight(tree);
            for (int levelIndex = 1;levelIndex <= treeHeight;levelIndex++)
                printLevel(tree,levelIndex);
        }
        //
        // takes a path through the tree as a series of lefts and rights
        // and returns the value at the end of that path
        //
        Comparable getByPath(LeftistNode *tree,vector<bool> path){
            if (tree == nullptr)
                return Comparable(-3);
            bool right = path[0];
            if (right){
                if (tree->right==nullptr){
                    return Comparable(-1);
                }
                if (path.size() == 1){
                    return tree->right->element;
                } else {
                    vector<bool> subPath = path;
                    subPath.erase(subPath.begin());
                    return getByPath(tree->right,subPath);
                }
            }else{
                if (tree->left==nullptr){
                    return Comparable(-1);
                }
                if (path.size() == 1){
                    return tree->left->element;
                } else {
                    vector<bool> subPath = path;
                    subPath.erase(subPath.begin());
                    return getByPath(tree->left,subPath);
                }
            }
            return Comparable(-2);
        }
        // returns a vector containing the items in the tree
        // with negative values indicating empty slots
        vector<Comparable> treeAsVector(){
            vector<Comparable> theVector;
            if (root == nullptr)
                return theVector;
            theVector.push_back(root->element);
            int treeHeight = getTreeHeight(root);
            int treeSize = pow(2,treeHeight)-1;
            for (int i = 2;i <= treeSize;i++){
                vector<bool> positionAsBinary;
                double x = i;
                while (x > 0){
                    x/=2;
                    if (fmod(x,1)==0.0)
                        positionAsBinary.push_back(false);
                    else {
                        positionAsBinary.push_back(true);
                        x-=.5;
                    }
                }
                std::reverse(positionAsBinary.begin(), positionAsBinary.end()); // reverse vector to correct binary
                positionAsBinary.erase(positionAsBinary.begin()); // remove first digit for this implementation
                Comparable item = getByPath(root,positionAsBinary);
                theVector.push_back(item);
            }
            return theVector;
        }
};
