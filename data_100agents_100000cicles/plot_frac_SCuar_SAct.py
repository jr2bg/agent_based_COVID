import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("fraccion_sintomaticos_cuarentena_activos.csv")

data = data[data["tiempo"]<3500000]
data.plot(x = "tiempo", y = ["frac_sint_act","frac_cuar_act"])
plt.show()

