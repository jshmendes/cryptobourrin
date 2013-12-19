# 
# Python script to be used in sage
# sage : run coppersmith.py
# Script is adapted from 
# http://algo.epfl.ch/_media/en/projects/bachelor_semester/rapportetiennehelfer.pdf
#

def coppersmith(f, N, epsilon=0.1, debug=False):
 if epsilon>1/7.0 or epsilon<=0:
        print("invalidepsilon")
        return None
  f.change_ring(Integers(N))
 delta=f.degree()
 if debug: print delta
 m=ceil(1/(delta*epsilon))
 if debug: print m
# R.<x> = ZZ[]
 R = PolynomialRing(ZZ,'x')
 x= R.gen()
 X = x - x
 
g=[]

 for j in range(0, delta):
        g.append([])
        for i in range(1, m+1):
                g[j].append(x**j*N**(i)*f**(m-i))
 X=ceil(0.5*N**((1/Integer(delta))-epsilon))
 if debug: print("X="+str(X))
  size=m*delta
 #construct B fromg[i,j](X*x)
 B=matrix(ZZ, size , size)
 compteur=0
 for i in range(-m+1,1):
        for j in range(0, delta):
                polylist=g[j][-i](X*x).list()
                vector=[0]*size
                 vector[0:len(polylist)]=polylist
                vector.reverse()
                B.set_column(compteur , vector)
                compteur=compteur+1
 #if debug: show(B)
 if debug: print"LLLstarts"
  coeffs=[]

#computes a small combination of g[i,x](X*x) with LLL
 coeffs=B.transpose().LLL().transpose().column(0).list()

#construct g(x)
 g=0*x
 for i in range(0, size):
        g=g+Integer(coeffs[i]/X**i)*x**i
#get the roots of g(x) over the integers
 roots=g.roots(multiplicities=False)
  result=[]
#test if the roots x_i respect f(x_i)=0 mod N
 for i in range(0, len(roots)):
        if gcd(N, f(roots[i]))>=N:
                result.append(roots[i])
 return result

p = 955769
q = 650413
 n = p*q
e = 5
M = 423909
C = power_mod(M,e,n)
MA = 423919
# R.<x> = ZZ[]
R = PolynomialRing(ZZ,'x')
x= R.gen()
f = x - x
f = (MA + x)**e - C
print coppersmith(f,n,0.1,True)
