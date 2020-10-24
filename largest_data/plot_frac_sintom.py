import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("proporcion_sintomaticos.csv")
#data = pd.DataFrame(data,)
data = data[data["tiempo"]<1000000]
data.plot(x = "tiempo", y = "prop_sintomaticos")
plt.show()

