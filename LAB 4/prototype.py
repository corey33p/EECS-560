

file1 = open('Instance Files/instance1.txt', 'r')
lines = file1.readlines()
class Stack:
    def __init__(self):
        self.the_stack = []
    def push(self,item):
        self.the_stack.append(item)
    def pop(self):
        return self.the_stack.pop()
    def peek(self):
        if self.empty(): return None
        else: return self.the_stack[-1]
    def empty(self):
        return len(self.the_stack) == 0
    def __str__(self):
        return str(self.the_stack)

def infix_to_postfix(line,debug=False):
    list_of_operators = ("(","*","+","-","/")
    operator_priorities = {"+":0,"-":0,"*":1,"/":1,"(":2}
    while line[len(line)-1] == " ": line = line[:len(line)-1]
    while line[len(line)-1] == "\n": line = line[:len(line)-1]
    postfix_expression = ""
    operator_stack = Stack()
    while line:
        while line[0] == " ": line = line[1:]
        space_index = line.find(" ")
        if space_index != -1: the_thing = line[:space_index]
        else: the_thing = line
        if the_thing == ")":
            next_item_in_stack = operator_stack.peek()
            while next_item_in_stack != "(" and not operator_stack.empty():
                postfix_expression += operator_stack.pop() + " "
                next_item_in_stack = operator_stack.peek()
            if not operator_stack.empty(): operator_stack.pop()
        elif the_thing in list_of_operators:
            operator_priority = operator_priorities[the_thing]
            if not operator_stack.empty():
                priority_of_next_in_stack = operator_priorities[operator_stack.peek()]
                while priority_of_next_in_stack >= operator_priority and not operator_stack.empty():
                    if operator_stack.peek() != "(":
                        postfix_expression += operator_stack.pop() + " "
                    else:
                        # operator_stack.pop()
                        break
                    if not operator_stack.empty():
                        priority_of_next_in_stack = operator_priorities[operator_stack.peek()]
                    else: break
            operator_stack.push(the_thing)
        else:
            postfix_expression += the_thing + " "
        if space_index == -1:
            line = ""
            while not operator_stack.empty():
                postfix_expression += operator_stack.pop() + " "
            while postfix_expression[len(postfix_expression)-1] == " ":
                postfix_expression = postfix_expression[:len(postfix_expression)-1]
        else: line = line[space_index:]
        if debug: print("--------------------")
        if debug: print("the_thing: '"+str(the_thing)+"'")
        if debug: print("line: '"+str(line)+"'")
        if debug: print("postfix_expression: "+postfix_expression)
        if debug: input("operator_stack: "+str(operator_stack))
    return postfix_expression

def evaluate_postfix(postfix_expression,debug=False):
    postfix_expression = postfix_expression.split(" ")
    list_of_operators = ("*","+","-","/")
    token_stack = Stack()
    for _ in range(len(postfix_expression)):
        item = postfix_expression.pop(0)
        if debug: print("\nitem: "+str(item))
        if item in list_of_operators:
            rhs = token_stack.pop()
            lhs = token_stack.pop()
            eval_str = lhs+item+rhs
            if debug: print("eval_str: "+str(eval_str))
            result = eval(eval_str)
            token_stack.push(str(result))
        else:
            token_stack.push(item)
        if debug: input("token_stack: "+str(token_stack))
    result = token_stack.pop()
    assert(token_stack.empty())
    return result


for line in lines:
    postfix_expression = infix_to_postfix(line)
    print("postfix_expression: "+str(postfix_expression))
    result = evaluate_postfix(postfix_expression)
    input("result: "+str(result))
