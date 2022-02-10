from fractions import Fraction
from math import gcd
import math

t = 1
N = t*t + t + 4
Xp = -4*(t*t+t+1)*(t*t+t+1)
Yp = 4*(2*t+1)*(t*t+t+1)*(3*t*t+3*t+7)

Xq = 0
Yq = 0

a3 = 1
a2 = 4*N*N + 12*N - 3
a1 = 32*(N+3)

# y^2 = a3*x^3 + a2*x^2 + a1*x
# Given two points P(Xp, Yp) and Q(Xq, Yq) on the graph
# M() calculates the slope of PQ
def M(Xp, Yp, Xq, Yq, a2, a1):
    if Xp == Xq and Yp == Yq:
        f1 = 3*Xp*Xp + 2*a2*Xp + a1
        f2 = 2*Yp
        return Fraction(f1, f2)
    else:
        f1 = Yq - Yp
        f2 = Xq - Xp
        return Fraction(f1, f2)

# y^2 = a3*x^3 + a2*x^2 + a1*x
# Given two points P(Xp, Yp) and Q(Xq, Yq) on the graph
# R() returns the point R=p+Q and the corresponding (a,b,c) of R point
def R(Xp, Yp, Xq, YQ, a2, a1):
    m = M(Xp, Yp, Xq, Yq, a2, a1)
    Xr = m*m - a2 - Xp - Xq
    Yr = m*(Xp-Xr) - Yp

    a = Fraction(8*(N+3)-Xr+Yr, 2*(4-Xr)*(N+3))
    b = Fraction(8*(N+3)-Xr-Yr, 2*(4-Xr)*(N+3))
    c = Fraction(-4*(N+3)-(N+2)*Xr, (4-Xr)*(N+3))

    return a,b,c,Xr,Yr


round = 1
while True:
    round = round+1
    #print("round =", round)
    a, b, c, Xr, Yr = R(Xp, Yp, Xq, Yq, a2, a1)
    if (a>0) and (b>0) and (c>0):
        break
    else:
        Xq = Xr
        Yq = Yr

def verify(a,b,c,Xr,Yr):
    print("Xr =", Xr)
    print("Yr =", Yr)
    print("")

    print("Verify 0:")
    v1 = N*(a+b)*(b+c)*(c+a)
    v2 = a*(a+b)*(a+c) + b*(b+a)*(b+c) + c*(c+a)*(c+b)
    print("v1 =", v1)
    print("v2 =", v2)
    print("")

GCD1 = gcd(a.denominator, b.denominator)
LCM1 = a.denominator * b.denominator // GCD1
GCD = gcd(LCM1, c.denominator)
LCM = LCM1 * c.denominator // GCD
a = a*LCM
b = b*LCM
c = c*LCM
#verify(a,b,c,Xr,Yr)
sum = a+b+c
#print(sum)

n = input()
div = 1000 ** int(n)
out = sum//div % 1000

print("%03d" % out)