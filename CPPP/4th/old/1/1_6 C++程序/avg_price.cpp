#include "Sales_item.h" // 我觉得这个程序可以好好看一下子，首先注释风格
int main()              // 改了，只是因为我喜欢，注释的位置，都在要注释的头上。
{                       // 是我喜欢的风格或者短的注释在后面。
    // declare variables to hold running sum and data for the next record 
    Sales_item total, trans;
    // is there data to process?
    if (std::cin >> total) // 检测是不是正常的流输入，小括号里面是'真'不是 '>>'这个重载了的操作
	{                      // 符，返回的仍是一个输入流，看看这个流是不是正常的流。  
        // if so, read the transaction records 
        while (std::cin >> trans)
            if (total.same_isbn(trans)) 
                // match: update the running total 
                total = total + trans;
            else // no match: print & assign to total
			{   
                
                std::cout << total << std::endl;
                total = trans;
            }
        // remember to print last record
        std::cout << total << std::endl; 
    } else
	{
        // no input!, warn the user
        std::cout << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
    return 0;
}
