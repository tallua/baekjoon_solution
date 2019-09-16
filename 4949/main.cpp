#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>


bool is_stable(const std::string& str)
{
    const size_t len = str.length();
    
    std::vector<char> stack;
    for(size_t indx = 0; indx < len; ++indx)
    {
        switch(str[indx])
        {
        case '(':
            {
                stack.push_back('(');

                break;
            }
        case ')':
            {
                if(stack.size() == 0)
                    return false;
                if(stack.back() == '(')
                    stack.pop_back();
                else
                    return false;
                break;
            }
        case '[':
            {
                stack.push_back('[');
                break;
            }
        case ']':
            {
                if(stack.size() == 0)
                    return false;
                if(stack.back() == '[')
                    stack.pop_back();
                else
                    return false;
                break;
            }
        case '.':
            {
                break;
            }
        }
    }

    if(stack.size() == 0)
        return true;
    return false;
}


int main(int argc, char** argv)
{
    std::string buff;
    bool eof = false;
    do {
        getline(std::cin, buff);

        size_t len = buff.length();
        if(len == 1 && buff[0] == '.')
        {
            eof = true;
        }
        else if(len == 0)
        {
            continue;
        }
        else
        {
            bool stable = is_stable(buff);
            if(stable)
            {
                printf("yes\n");
            }
            else
            {
                printf("no\n");
            }
        }
        
    } while(!eof);

    return 0;
}