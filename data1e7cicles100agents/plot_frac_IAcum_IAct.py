import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("fraccion_infectados_acumuladosYactivos.csv")

#data = pd.DataFrame(data,)
data["tiempo (días)"] = data["tiempo"]/(60*60*24)
Axs = data.plot(x = "tiempo (días)", y = ["frac_inf_acum","frac_inf_act"])
Axs.set_ylabel("proporción de la población (%)")
plt.show()

