import numpy as np
import math
#Points
A = np.array([[1.0],[-2.0],[-8.0]])
B = np.array([[5.0],[0.0],[-2.0]])
C = np.array([[11.0],[3.0],[7.0]])

#Compute rank
r = np.linalg.matrix_rank(np.hstack((A,B,C)))

#Check collinearity
print("Points are", end=" ")
if r < 3:
    print("collinear")
else:
    print("non-collinear")

k=np.multiply((B-A),(C-B))
one=int(k[0]+k[1]+k[2])//42
q=np.linalg.norm(C-B)
two=int(q*q)//42
print("B divides AC in ratio ",one,":",two)