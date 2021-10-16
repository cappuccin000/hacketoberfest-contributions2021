def gcd_rec(a,b):
    if(a%b==0):
        return b
    return gcd_rec(b,a%b)


a=int(input("First Num: "))
b=int(input("Second Num: "))

if a>b:
    a1=gcd_rec(a,b)
else:
    a1=gcd_rec(b,a)

a2=(a*b)//a1
print("HCF: ",a1,"LCM: ",a2)





