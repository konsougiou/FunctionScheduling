import matplotlib.pyplot as plt

values = [351.254, 344.971, 314.437, 311.666, 282.332, 264.971, 251.888, 238.861, 233.389, 233.389, 233.389, 228.321, 228.321, 222.779, 220.498, 247.313, 288.037, 292.008, 289.94, 292.71, 305.089, 323.494, 325.183, 329.643, 329.643, 317.076, 311.444, 302.578, 296.945, 285.03, 264.162, 258.53, 255.151, 250.691, 250.782, 244.499, 238.867, 230.894, 232.583, 226.952, 218.549, 213.481, 213.332, 220.654, 207.91, 209.083, 202.799, 199.57, 193.287, 193.287, 193.287, 221.509, 221.509, 225.022, 256.543, 253.773, 250.195, 254.937, 249.869, 252.64, 262.365, 262.365, 247.775, 250.542, 291.917, 304.263, 317.723, 316.263, 320.723, 325.183, 302.654, 287.418, 264.889, 243.456, 237.173, 234.269, 245.534, 253.42, 250.649, 251.849, 248.47, 245.092, 236.78, 234.009, 222.064, 209.497, 220.7, 232.615, 235.386, 254.623, 254.623, 255.366, 228.866, 227.208, 222.14, 223.681, 219.803, 212.347, 219.444, 213.811]
plt.plot(values, marker='o')
plt.xlabel('Index')
plt.ylabel('Values')
plt.title('Line Plot of Values')
plt.show()