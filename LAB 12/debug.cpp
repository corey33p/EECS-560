# include "mySorting.hpp"
# include <iostream>
# include <vector>
# include <fstream>
# include <string>
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
    bool debug = false;
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
    std::vector<int> data2;
    for(auto x : data) data2.push_back(std::stoi(x));

    // if (debug) cout<<"unsorted data: "<<endl;
    // for(auto x : data2) std::cout << x << " ";
    // std::cout << "\n";
    if (debug) cout<<"performing quickSort: "<<endl;
    quickSort(data2);
    if (debug) cout<<"sorted data: "<<endl;
    for(auto x : data2) std::cout << x << " ";
    std::cout << "\n";
    // if (debug) cout<<"performing reverse quickSort: "<<endl;
    // quickSort(data2, true);
    // if (debug) cout<<"reverse sorted data: "<<endl;
    // for(auto x : data2) std::cout << x << " ";
    // std::cout << "\n";
    //
    // if (debug) cout<<"unsorted data: "<<endl;
    // for(auto x : data) std::cout << x << " ";
    // std::cout << "\n";
    // if (debug) cout<<"performing quickSort: "<<endl;
    // quickSort(data);
    // if (debug) cout<<"sorted data: "<<endl;
    // for(auto x : data) std::cout << x << " ";
    // std::cout << "\n";
    // if (debug) cout<<"performing reverse quickSort: "<<endl;
    // quickSort(data, true);
    // if (debug) cout<<"reverse sorted data: "<<endl;
    // for(auto x : data) std::cout << x << " ";
    // std::cout << "\n";

    return 0;
}