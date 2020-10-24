import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("fraccion_inmunesActivos_fallecidosAcumulados.csv")

data = data[data["tiempo"]<4000000]
#data["tiempo"]= data["tiempo"]/(60*60)
data.plot(x = "tiempo", y = ["frac_inmun_act","frac_dece_acum"])
plt.show()

