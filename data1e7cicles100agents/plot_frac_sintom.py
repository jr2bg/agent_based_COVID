import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("proporcion_sintomaticos.csv")
#data = pd.DataFrame(data,)
#data = data[data["tiempo"]<1000000]
data["tiempo (días)"] = data["tiempo"]/(60*60*24)
Axs = data.plot(x = "tiempo (días)", y = "prop_sintomaticos")
Axs.set_ylabel("proporción de la población (%)")
plt.show()

