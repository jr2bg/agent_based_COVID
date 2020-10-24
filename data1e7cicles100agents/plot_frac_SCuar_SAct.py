import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("fraccion_sintomaticos_cuarentena_activos.csv")

#data = data[data["tiempo"]<3500000]
#fig, axs = plt.subplots()

data["tiempo (días)"] = data["tiempo"]/(60*60*24)
Axs = data.plot(x = "tiempo (días)", y = ["frac_sint_act","frac_cuar_act"])
Axs.set_ylabel("proporción de la población (%)")
plt.show()

