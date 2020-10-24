import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("fraccion_inmunesActivos_fallecidosAcumulados.csv")

#data = data[data["tiempo"]<4000000]
data["tiempo (días)"]= data["tiempo"]/(60*60*24)
Axs = data.plot(x = "tiempo (días)", y = ["frac_inmun_act","frac_dece_acum"])
Axs.set_ylabel("proporción de la población (%)")
plt.show()

