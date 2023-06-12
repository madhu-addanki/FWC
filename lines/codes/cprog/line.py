import numpy as np
import matplotlib.pyplot as plt
import os


#Points
a = np.loadtxt('A.dat',dtype='float')
b = np.loadtxt('B.dat',dtype='float')
c = np.loadtxt('C.dat',dtype='float')
A=np.block([[a[0]],[a[1]],[a[2]]])
B=np.block([[b[0]],[b[1]],[b[2]]])
C=np.block([[c[0]],[c[1]],[c[2]]])

M=np.block([A,B,C])

# Plot
fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
ax.scatter(M[0], M[1], M[2])
ax.plot(M[0], M[1], M[2])
plt.grid()
plt.tight_layout()
plt.savefig('/sdcard/Download/vectors/figs/line_3d.png', dpi=600)
os.system('termux-open /sdcard/Download/vectors/figs/line_3d.png')
