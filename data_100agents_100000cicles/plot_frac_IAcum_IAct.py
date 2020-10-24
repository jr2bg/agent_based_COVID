import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("fraccion_infectados_acumuladosYactivos.csv")

#data = pd.DataFrame(data,)
data = data[data["tiempo"]<1000000]
data.plot(x = "tiempo", y = ["frac_inf_acum","frac_inf_act"])
plt.show()

