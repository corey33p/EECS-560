#include "myStack_corey33p.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class myInfixPostfix{
    public:
        myInfixPostfix () {}
        virtual ~myInfixPostfix(){}
        int getPriority(std::string op){
            if      (op == "+") return 0;
            else if (op == "-") return 0;
            else if (op == "*") return 1;
            else if (op == "/") return 1;
            else if (op == "(") return 2;
            cout<<"op: "<<op<<endl;
            throw std::invalid_argument("Bad input to getPriority function.");
            return -1;
        }
        bool isOperator(std::string item){
            if      (item == "(") return true;
            else if (item == "*") return true;
            else if (item == "/") return true;
            else if (item == "+") return true;
            else if (item == "-") return true;
            return false;
        }
        float eval(float lhs,std::string op,float rhs){
            if      (op == "*") return lhs*rhs;
            else if (op == "/") return lhs/rhs;
            else if (op == "+") return lhs+rhs;
            else if (op == "-") return lhs-rhs;
            cout<<"op: "<<op<<endl;
            throw std::invalid_argument("Bad input to eval function.");
            return 0;
        }
        std::string getPostfix(std::string str){
            str.erase(str.find_last_not_of(" \n\r\t")+1);
            std::string postfixExpression = "";
            myStack<std::string> operatorStack;
            while (!str.empty()){
                str = str.substr(str.find_first_not_of(" \n\r\t"));
                int spaceIndex = str.find_first_of(" ");
                std::string theThing;
                if (spaceIndex != (int) std::string::npos){
                    theThing = str.substr(0,spaceIndex);
                } else {
                    theThing = str;
                }
                if (theThing == ")"){
                    std::string nextItemInStack = operatorStack.top();
                    while ((nextItemInStack != "(") && (!operatorStack.empty())){
                        postfixExpression = postfixExpression.append(operatorStack.pop());
                        nextItemInStack = operatorStack.top();
                    }
                    if (!operatorStack.empty()) operatorStack.pop();
                } else if (isOperator(theThing)){
                    int operatorPriority = getPriority(theThing);
                    if (!operatorStack.empty()){
                        int priorityOfNextInStack = getPriority(operatorStack.top());
                        while ((priorityOfNextInStack >= operatorPriority) && (!operatorStack.empty())){
                            if (operatorStack.top() != "(") postfixExpression.append(operatorStack.pop());
                            else break;
                            if (!operatorStack.empty()) priorityOfNextInStack = getPriority(operatorStack.top());
                            else break;
                        }
                    }
                    operatorStack.push(theThing);
                } else postfixExpression.append("("+theThing + ")");
                if (spaceIndex == (int) std::string::npos) {
                    str = "";
                    while (!operatorStack.empty()) postfixExpression.append(operatorStack.pop());
                    postfixExpression.erase(postfixExpression.find_last_not_of(" \n\r\t")+1);
                } else str = str.substr(spaceIndex+1,-1);
            }
            return postfixExpression;
        }
        float PostfixCalculator(std::string exp){
            int counter = 0;
            myStack<float> tokenStack;
            exp = exp.substr(exp.find_first_not_of(" \n\r\t")); // trim left
            exp.erase(exp.find_last_not_of(" \n\r\t")+1); // trim right
            while (!exp.empty()){
                counter++;
                if (counter > 50) throw std::runtime_error("counter exceeded 50.");
                std::string firstCharacter = exp.substr(0,1);
                std::string item;
                if ((isOperator(firstCharacter))&&(firstCharacter!="(")) {
                    item = firstCharacter;
                    if (exp.length() == 1)  exp = "";
                    else exp = exp.substr(1,-1);
                } else {
                    int endParenthesisIndex = exp.find_first_of(")");
                    item = exp.substr(1,endParenthesisIndex);
                    exp = exp.substr(endParenthesisIndex+1,-1);
                }
                if (isOperator(item)){
                    float rhs = tokenStack.pop();
                    float lhs = tokenStack.pop();
                    float result = eval(lhs,item,rhs);
                    tokenStack.push(result);
                } else {
                    item = item.substr(item.find_first_not_of(" \n\r\t")); // trim left
                    item.erase(item.find_last_not_of(" \n\r\t")+1); // trim right
                    tokenStack.push(std::stof(item));
                }
            }
            float finalResult = tokenStack.pop();
            if (!tokenStack.empty()) throw std::runtime_error("PostfixCalculator stack not emptied.");
            return finalResult;
        }
    };
