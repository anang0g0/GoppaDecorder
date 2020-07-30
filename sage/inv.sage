G=GF(16,'a')
#F.<a> = GF(2^4)
#R.<Y> = PolynomialRing(F)
#K.<a>=GF(2**4)
R.<x> = PolynomialRing(G,implementation='NTL')





def inv(a, n):
 d = n
 x = 0
 s = 1
 while (a != 0):
    q = d // a
    r = d % a
    d = a
    a = r
    t = x - q * s
    x = s
    s = t
    print(a)
 gcd = d  # $\gcd(a, n)$

 print("d=",d)

 return ((x + n) % (n // d))




g0=x^6+x^4+1
g1=x^2+1
e=x^6+x^4+x^3+x+1
s=G('a^12')*x^5+G('a^6')*x^4+G('a')*x^3+G('a^7')*x^2+G('a^9')*x+G('a')
v=inverse_mod(s,e)
v=v+x
T1=G('a^4')*x^4+x^2+G('a^7')
T0=G('a^12')*x^4+G('a^3')*x^2+G('a^7')
#T1=G('a^11')*x^4+G('a^9')*x^2+G('a^14')
#T0=G('a^3')*x^4+G('a^6')*x^2+1
g0=sqrt(g0)
g1=sqrt(g1)
inv_g=inverse_mod(g1,e)
T0=sqrt(T0)
T1=sqrt(T1)
r=T0+g0*inv_g*T1
r=r%e
#V=(T0^2+(g0*inv_g*T1)^2)%e
#w=(g0*inv_g)^2%e

d1=G('a^4')*x^4+x^2+G('a^7')
d0=G('a^12')*x^4+G('a^3')*x^2+G('a^7')
d1=sqrt(d1)
d0=sqrt(d0)

