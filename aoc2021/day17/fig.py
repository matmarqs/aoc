import sys
import numpy as np
import matplotlib.pyplot as plt

x, y = np.loadtxt(sys.stdin, delimiter=',', unpack = True)

plt.plot(x, y, 's', label=r'data')
plt.xlabel(r'$x$', fontsize=20)
plt.ylabel(r'$y$', fontsize=20)
plt.legend(fontsize=14)
plt.title(r'Data')
plt.savefig("./outdata.png", dpi=300, format='png', bbox_inches="tight")
