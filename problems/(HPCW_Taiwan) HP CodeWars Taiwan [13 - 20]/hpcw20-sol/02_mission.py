import re

"""
:type l1: List
:type l2: List
:rtype: List        
"""
def solution(l1, l2):
    #l1, l2 = re.split(' ', numbers)
    carry_num = 0
    l_sum = []
    max_len = max(len(l1), len(l2))    
    tmp_sum = 0

    if max_len == 0:
        return [0]

    for i in range(max_len):
        
        if len(l1) > i and len(l2) > i:
            tmp_sum = l1[i] + l2[i] + carry_num
        elif len(l1) <= i and len(l2) > i:
            tmp_sum = l2[i] + carry_num
        else:
            tmp_sum = l1[i] + carry_num

        if tmp_sum > 9:
            carry_num = tmp_sum // 10
            l_sum.append(tmp_sum % 10)
        else:
            carry_num = 0
            l_sum.append(tmp_sum)

    if carry_num > 0:
        l_sum.append(carry_num)
    
    print(l_sum)
    #return l_sum
    
    

if __name__ == '__main__':
    lnum1 = []
    lnum2 = []
    
    n = int(input("Enter number of elements for list 1: ")) 
      
    # iterating till the range 
    for i in range(0, n): 
        ele = int(input())       
        lnum1.append(ele)
        
    n = int(input("Enter number of elements for list 2: "))       
    
    for i in range(0, n): 
        ele = int(input())      
        lnum2.append(ele)
    
    solution(lnum1, lnum2)
        
