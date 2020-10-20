# include "myLeftistHeap.hpp"
# include <iostream>
# include <vector>
# include <fstream>
# include <string>
using namespace std;

void parseInstance(const std::string& line, std::vector<std::string> & res)
{
    int p = 0, q = 0;
    while(q < (int) line.size())
    {
        if(line[q] ==',')
        {
            res.push_back(line.substr(p,q-p));
            p=q+1;
        }
        q++;
    }
}


int main(int argc, char* argv[])
{
    // std::cerr<<"test-3"<<endl;
    // int a = 0;
    // int b = 1/a;
    // cerr<<"test-2"<<endl;
    if(argc != 2)
    {
        std::cout << "You have to provide one test instance file to run the test main!\n";
        return 0;
    }
    // cerr<<"test-1"<<endl;
    std::ifstream fin;
    std::vector<std::string> data;
    fin.open(argv[1]);	    // open file
    if (!fin.is_open())	    // fail to open
    {
        std::cout << "Can't open the test instance file!\n";
        return 0;
    }
    else
    {
        std::string line;
        while(std::getline(fin, line))
        {
            parseInstance(line,data);
        }
    }

    // Declear three new leftist heap object
    myLeftistHeap<int>* mlh  = new myLeftistHeap<int>();
    myLeftistHeap<int>* mlh1 = new myLeftistHeap<int>();
    myLeftistHeap<int>* mlh_tem = new myLeftistHeap<int>();
    // cerr<<"test"<<endl;
    /*
    @Pre  New leftist heap has been decleared but no element has been put into it
    @Post Test your implementation of isEmpty function to tell if the heap is empty
    */
    // cout<<"Test your implementation of isEmpty function to tell if the heap is empty"<<endl;
    if(mlh->isEmpty())	std::cout << 1 << "\n";
    else                std::cout << 0 << "\n";

    for(int i = 0; i < (int) data.size(); ++i)
    {
        int it = std::stoi(data[i]);
        /*
        @Pre  Load a new element
        @Post Insert the new element to mlh. Insert the new element to mlh_tem if
        the index of the element is odd. Note that a single element will be
        treated as a single-node leftist heap.
        */
        mlh->insert(it);
        if(i%2==1) mlh_tem->insert(it);
    }
    // cerr<<"test1.5"<<endl;
    // mlh->printNice();
    mlh->printInOrder();      // Test your implementation of in-order traversal
    // cerr<<"\ntest1.6"<<endl;
    *mlh1 = *mlh;             // Test your implementation of assign operator
    // cerr<<"test1.7"<<endl;
    // Test your implementation of copy constructor
    myLeftistHeap<int>* mlh2 = new myLeftistHeap<int>(*mlh);
    // cerr<<"test1.8"<<endl;
    /*
    @Pre  mlh1 and mlh2 should be exactly the same as mlh
    @Post Print the in-order of mlh1, print the level-order traversal of mlh2.
    you should be able to reconstruct the tree-structure of mlh now.
    */
    // cout<<"printInOrder"<<endl;
    mlh1->printInOrder();
    // cout<<"printLevelOrder"<<endl;
    mlh2->printLevelOrder();

    // cerr<<"test1"<<endl;
    if(mlh1->isEmpty())	std::cout << 1 << "\n";
    else                std::cout << 0 << "\n";
    mlh1->makeEmpty();        // Test your implementation of makeEmpty
    if(mlh1->isEmpty())	std::cout << 1 << "\n";
    else                std::cout << 0 << "\n";
    /*
    Test your implementation of deleteMin, boundary case when you try to deleteMin
    from empty heap.
    */
    mlh1->deleteMin();
    // cerr<<"test2"<<endl;

    // cout<<"Test your implementation of findMin"<<endl;
    std::cout << mlh->findMin() << "\n";    // Test your implementation of findMin
    // cerr<<"test2.1"<<endl;
    // cout<<"Test your implementation of deleteMin, where you return the to-be-delete \nelement by reference. This is a combination of findMin and deleteMin."<<endl;
    for(int i = 0; i < 5; i++)
    {
        int a;
        /*
        Test your implementation of deleteMin, where you return the to-be-delete
        element by reference. This is a combination of findMin and deleteMin.
        */
        // cerr<<"test2.3"<<endl;
        mlh->deleteMin(a);
        // cerr<<"test2.6"<<endl;
        std::cout << a << "\n";
    }
    // cerr<<"test3"<<endl;
    // Now check if your leftist heap is correct
    // cout<<"printLevelOrder"<<endl;
    mlh->printLevelOrder();
    // cerr<<"test3.1"<<endl;
    // cout<<"printInOrder"<<endl;
    mlh->printInOrder();
    // cerr<<"test3.2"<<endl;

    for(int i = 0; i < 5; i++)
    {
        // Test your implementation of deleteMin, this time you discard the min element.
        mlh->deleteMin();
    }
    // Now check if your leftist heap is correct
    // cout<<"printLevelOrder"<<endl;
    mlh->printLevelOrder();
    // cout<<"printInOrder"<<endl;
    mlh->printInOrder();
    // cerr<<"test4"<<endl;
    // Test the merge routine of your leftist heap by merging mlh_tem with mlh
    // cout<<"printInOrder"<<endl;
    mlh_tem->printInOrder();
    mlh->merge(*mlh_tem);
    // cout<<"printLevelOrder"<<endl;
    mlh->printLevelOrder();

    delete mlh;
    delete mlh_tem;
    delete mlh1;
    delete mlh2;
    // cerr<<"test5"<<endl;
    return 0;
}
