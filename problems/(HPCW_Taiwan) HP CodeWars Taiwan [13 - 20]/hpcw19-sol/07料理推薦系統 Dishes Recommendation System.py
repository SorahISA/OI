n = input()
name_l = []
price_l = []
for i in range(int(n)):
    line = input()
    name = line.split(",")[1]
    price= int(line.split(",")[2])
    name_l.append(name)
    price_l.append(price)
key = input().split()


wct_l = []
cor_l = []
for j in range(len(name_l)):
    wct = 0
    name = name_l[j].split()

    for k in name:
        for i in key:
            if i == k:
                wct += 1
    wct_l.append(wct)

for i in range(len(wct_l)):
    cor = -1
    if int(wct_l[i]) == len(name_l[i].split()):
        cor = 9
    elif int(wct_l[i]) < len(name_l[i].split()) and int(wct_l[i])!= 0:
        cor = 6
    elif int(wct_l[i]) == 0:
        cor = 0
    cor_l.append(cor)


if max(cor_l) == 9:
    ind = cor_l.index(9)
    print(ind+1,9, sep = " ", end='')

elif max(cor_l) == 6:
    ct = 0
    w_max_l = []
    wct_m = max(wct_l)
    for i in range(len(wct_l)):
        if wct_l[i] == wct_m:
            w_max_l.append(i)
            ct += 1
    if ct > 1:
        p_min = 1000000
        for j in w_max_l:
            if price_l[j] < p_min:
                p_min = price_l[j]
        ind = price_l.index(p_min)
        print(ind+1,6, sep = " ", end='')
    else:
        ind = wct_l.index(wct_m)
        print(ind+1,6, sep = " ", end='')
elif max(cor_l) == 0:
    p_min = min(price_l)
    ind = price_l.index(p_min)
    print(ind+1,0, sep = " ", end='')
            
    

    

 
            
    
