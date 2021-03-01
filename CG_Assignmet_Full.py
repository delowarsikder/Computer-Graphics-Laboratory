import hashlib
import math
from math import *
from operator import *
import numpy as np
roll=input("Enter your Roll : ")
# roll = "1607094"
# initial কারিসমা
hash = hashlib.md5(roll.encode())
out = hash.hexdigest()
print("Roll : "+"md5 hash is: ")
print(roll, " : ", out)
# check roll even or odd
Roll = int(roll)
if Roll % 2 == 0:
    # print ("even")
    d0 = int(out[-1], 16)
    d1 = int(out[-2], 16)
    d2 = int(out[-3], 16)
    d3 = int(out[-4], 16)
    d4 = int(out[-5], 16)
    d5 = int(out[-6], 16)
else:
    # print("odd")
    d0 = int(out[5], 16)
    d1 = int(out[4], 16)
    d2 = int(out[3], 16)
    d3 = int(out[2], 16)
    d4 = int(out[1], 16)
    d5 = int(out[0], 16)

# # # solution of question no 1.
print("d0 is :", d0)
print("d1 is :", d1)
print("d2 is :", d2)
print("d3 is :", d3)
print("d4 is :", d4)
print("d5 is :", d5)

x1 = max((d0+d3) % (max(d0, d1, d2)), 2)
y1=max((d1+d4)%(max(d2,d3)),2) 
z1 = max((d2+d5) % (max(d4, d5)), 2)
x0 = x1+1
y0 = y1+1
z0 = min(3*z1, z1+9)
x2 = x1+1
y2 = 0
z2 = z1+1
x3 = x1-1
y3 = 0
z3 = z1+1
x4=x1
y4 = 0
z4 = z1-1.4
xr = math.ceil(.8*x1)
yr = math.floor(.6*y1)
zr = z1-1
print("x0 : ",x0)
print("y0 : ",y0)
print("z0 : ",z0)
print("x1 : ",x1)
print("y1 : ",y1)
print("z1 : ",z1)
print("x2 : ",x2)
print("y2 : ",y2)
print("z2 : ",z2)
print("x3 : ",x3)
print("y3 : ",y3)
print("z3 : ",z3)
print("x4 : ",x4)
print("y4 : ",y4)
print("z4 : ",z4)
print("xr : ",xr)
print("yr : ",yr)
print("zr : ",zr)
# # # # IN WCS co-ordinate
p1 = [x1, y1, z1]
p2 = [x2, y2, z2]
p3 = [x3, y3, z3]
p4 = [x4, y4, z4]

# # # # IN VCS
p0 = [x0, y0, z0]
pr = [xr, yr, zr]
V = [1, 2, 0]  ### given VCS point
print("p0 : ",p0)
print("p1 : ",p1)
print("p2 : ",p2)
print("p3 : ",p3)
print("p4 : ",p4)

print("pr : ",pr)
print("V: ",V)
N = [x1 - x2 for (x1, x2) in zip(p0, pr)]
print("N : ",N)
# # # unit vector of n
n_hat = N / np.linalg.norm(N)
print("n_hat : ",n_hat)
# # # # calculate the value of U
U = np.cross(np.array(V), np.array(N))
print("U = VxN : ",U)
# # # unit vector of U
u_hat = U / np.linalg.norm(U)
print("u_hat : ",u_hat)

# # # Calcuate the value of small v name as v_hat
v_hat = np.cross(np.array(n_hat), np.array(u_hat))
print("v_hat= n x u : ",v_hat)
# # # Translation Matrix:
T = [[1, 0, 0, -x0], [0, 1, 0, -y0], [0, 0, 1, -z0], [0, 0, 0, 1]]
print("Translation Matrix T:\n",np.matrix(T))
# # # # Composite Rotation Matrix:
R = [[u_hat[0], u_hat[1], u_hat[2], 0], [v_hat[0], v_hat[1], v_hat[2], 0],
     [n_hat[0], n_hat[1], n_hat[2], 0], [0, 0, 0, 1]]
# Print R matrix
# # print('\n'.join([''.join(['{:4}'.format(item) for item in row])for row in R]))
print("Composite Rotation Matrix R :\n",np.matrix(R))
# # # World co-ordinate to view co-ordinate transformation
M_wc_vc = np.dot(np.array(R), np.array(T))
print("M_wc_to_vc :\n",M_wc_vc)

# # # point for view co-ordinate
print("Ans of question no 1. : \n")
p1.append(1)
p_1v = np.dot(M_wc_vc, p1)
print("p_1v :",p_1v)
p2.append(1)
p_2v = np.dot(M_wc_vc, p2)
print("p_2v :",p_2v)
p3.append(1)
p_3v = np.dot(M_wc_vc, p3)
print("p_3v :",p_3v)
p4.append(1)
p_4v = np.dot(M_wc_vc, p4)
print("p_4v :",p_4v)

# # # দুইনম্বর প্রশ্নের কাহিনী শুরু
# # # solution of question no 2.
# # # right
r = math.ceil(max(p_1v[0], p_2v[0], p_3v[0], p_4v[0])+1)
print("right r:", r)
# # # left
l = math.floor(min(p_1v[0], p_2v[0], p_3v[0], p_4v[0])-1)
print("left l:", l)
# # # top
t=math.ceil(max(p_1v[1],p_2v[1],p_3v[1],p_4v[1])+1)
print("top t:",t)

# ##bottom
b=math.floor(min(p_1v[1],p_2v[1],p_3v[1],p_4v[1])-1)
print("bottom b:",b)
###near
n=math.floor(max(p_1v[2],p_2v[2],p_3v[2],p_4v[2])/2)
print("near n:",n)

# ##far
f=math.floor(min(p_1v[2],p_2v[2],p_3v[2],p_4v[2])-2)
print("far f:",f)

###perspective projection matrix

M=[
    [
        (2*abs(n))/(r-l),0,(r+l)/(r-l),0
    ],[
        0,(2*abs(n))/(t-b),(t+b)/(t-b),0
    ],[
        0,0,(abs(n)+abs(f))/(abs(n)-abs(f)),(2*abs(n)*abs(f))/(abs(n)-abs(f))
    ],[
        0,0,-1,0
    ]
]
print("perspective projection matrix M :\n",np.matrix(M))
p_nv=[p_1v,p_2v,p_3v,p_4v]
# print("p_nv : ",np.matrix(p_nv))
p_hat=np.dot(M,np.array(p_nv).T)
print("p_hat :\n",p_hat)
###calculate the p_pers
pp=[[abs(n),0,0,0],[0,abs(n),0,0],[0,0,abs(n)+abs(f),abs(n)*abs(f)],[0,0,-1,0]]
# print(np.matrix(pp))
p_pers=np.dot(pp,np.array(p_nv).T)
# print("p_pers \n",p_pers)
print("p_pers1 : ",p_pers.T[0])
print("p_pers2 : ",p_pers.T[1])
print("p_pers3 : ",p_pers.T[2])
print("p_pers4 : ",p_pers.T[3])

p_1n=p_hat.T[0]/p_hat.T[0][-1]
p_1n=p_1n[:-1]
print("p_1n :",p_1n)

p_2n=p_hat.T[1]/p_hat.T[1][-1]
p_2n = p_2n[:-1]
print("p_2n :",p_2n)

p_3n=p_hat.T[2]/p_hat.T[2][-1]
p_3n=p_3n[:-1]
print("p_3n :",p_3n)

p_4n=p_hat.T[3]/p_hat.T[3][-1]
p_4n=p_4n[:-1]
print("p_4n :",p_4n)

