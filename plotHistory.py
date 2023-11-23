import matplotlib.pyplot as plt

values_1 = [351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 344.971, 344.971, 344.971, 344.971, 344.971, 343.282, 332.968, 332.968, 332.968, 314.437, 308.805, 303.172, 303.172, 303.172, 303.172, 303.172, 303.172, 303.172, 303.172, 300.402, 300.402, 300.402, 300.402, 297.631, 297.631, 294.86, 294.86, 294.86, 284.547, 266.015, 266.015, 266.015, 266.015, 266.015, 266.015, 266.015, 259.732, 259.732, 259.732, 259.732, 256.502, 256.502, 251.3, 251.3, 251.3, 251.3, 240.986, 240.986, 240.986, 240.986, 240.986, 240.986, 240.986, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 229.205, 227.515, 227.515, 227.515, 227.515, 227.515, 227.515, 227.515, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 221.974, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 221.974, 221.974, 221.974, 221.974, 221.974, 221.974, 221.974, 221.974, 221.974, 221.974, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 226.813, 224.042, 224.042, 224.042, 224.042, 224.042, 224.042, 224.042, 224.042, 222.353, 222.353, 220.663, 218.974, 218.974, 218.974, 218.974, 216.203, 216.203, 216.203, 216.203, 216.203, 216.203, 216.203, 213.433, 213.433, 210.662, 207.891, 207.891, 207.891, 207.891, 207.891, 206.233, 206.233, 206.233, 206.233, 205.855, 205.855, 199.571, 193.288, 193.288, 193.288, 193.288, 193.288, 193.288, 193.288, 193.288, 193.288, 193.288, 187.656, 182.023, 182.023, 182.023, 182.023, 182.023, 182.023, 182.023, 182.023, 182.023, 176.391, 170.759, 170.759, 170.759, 170.759, 170.759, 170.759, 170.759, 170.759, 164.475, 164.475, 164.475, 164.475, 164.475, 164.475, 164.475, 164.475, 164.475, 164.475, 164.016, 164.016, 164.016, 164.016, 164.016, 164.016, 164.016, 164.016, 164.016, 164.016, 166.787, 168.476, 168.476, 168.476, 168.476, 168.476, 168.476]
values_2 = [351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 344.971, 344.971, 344.971, 344.971, 344.971, 343.282, 332.968, 332.968, 332.968, 314.437, 308.805, 314.437, 314.437, 314.437, 314.437, 314.437, 314.437, 314.437, 314.437, 311.666, 311.666, 311.666, 311.666, 308.895, 308.895, 306.125, 306.125, 306.125, 295.812, 277.28, 281.251, 281.251, 281.251, 281.251, 281.251, 281.251, 281.251, 274.968, 274.968, 274.968, 274.968, 271.738, 271.738, 266.535, 266.535, 266.535, 266.535, 256.222, 256.222, 256.222, 256.222, 256.222, 256.222, 256.222, 256.222, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 250.589, 248.9, 248.9, 248.9, 248.9, 248.9, 248.9, 248.9, 248.9, 248.9, 248.9, 254.532, 264.846, 283.377, 285.039, 285.039, 285.039, 285.039, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 282.268, 280.579, 280.579, 280.579, 280.579, 280.579, 278.889, 278.889, 278.889, 278.889, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 276.119, 273.348, 273.348, 273.348, 273.348, 273.348, 270.577, 270.577, 270.577, 273.348, 279.631, 282.402, 288.034, 289.723, 291.413, 293.102, 299.385, 302.156, 308.439, 314.072, 320.355, 325.987, 336.301, 354.832, 360.464, 360.464, 360.464, 360.464, 360.464, 360.464, 360.464, 360.464, 360.464, 360.464, 360.464, 360.464, 363.698, 369.981, 369.982, 369.982, 369.981, 369.982, 372.752, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 374.442, 377.212, 378.902, 378.902, 378.902, 378.902, 378.902, 378.902, 378.902, 378.902, 373.269, 367.637, 367.637, 367.637, 367.637, 367.637, 367.637, 367.637, 367.637, 367.637, 367.637, 367.637, 367.637, 363.752, 357.469, 357.469, 357.469, 357.469, 357.469, 357.469, 357.469, 357.469, 351.836, 346.204, 340.572, 334.939, 334.939, 334.939, 334.939, 334.939, 334.939, 334.939, 334.939, 334.939, 328.656, 328.656, 328.656, 328.656, 328.656, 328.656, 328.656, 328.656, 323.024, 317.392, 311.759, 306.127, 306.127, 306.127, 306.127, 306.127, 306.127, 306.127, 306.127, 304.438]
values_3 = [351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 351.254, 344.971, 344.971, 344.971, 344.971, 344.971, 343.282, 332.968, 332.968, 332.968, 314.437, 308.805, 303.172, 303.172, 303.172, 303.172, 303.172, 303.172, 303.172, 303.172, 300.402, 300.402, 300.402, 300.402, 297.631, 297.631, 294.86, 294.86, 294.86, 284.547, 266.015, 266.015, 266.015, 266.015, 266.015, 266.015, 266.015, 259.732, 259.732, 259.732, 259.732, 256.502, 256.502, 251.3, 251.3, 251.3, 251.3, 240.986, 240.986, 240.986, 240.986, 240.986, 240.986, 240.986, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 235.354, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 233.665, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 230.894, 229.205, 227.515, 227.515, 227.515, 227.515, 227.515, 227.515, 227.515, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 224.745, 221.974, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 219.203, 216.433, 216.433, 216.433, 216.433, 216.433, 216.433, 216.433, 214.775, 214.775, 214.775, 214.775, 214.775, 214.775, 214.775, 214.775, 214.775, 214.775, 214.775, 209.142, 203.51, 203.51, 203.51, 203.51, 203.51, 203.51, 197.878, 192.245, 192.245, 192.245, 192.245, 192.245, 192.245, 192.245, 192.245, 192.245, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 185.962, 184.273, 184.273, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 182.583, 179.813, 179.813, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 177.042, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.501, 171.042]
plt.plot(values_3, marker='o')
plt.xlabel('Index')
plt.ylabel('Values')
plt.title('Line Plot of Values')
plt.show()