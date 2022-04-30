import numpy as np
from sklearn.linear_model import LinearRegression
from csv import reader
import matplotlib.pyplot as plt

# загружаем CSV файл
def load_csv(filename):
	file = open(filename, "r")
	lines = reader(file)
	dataset = list(lines)
	return dataset

filename = 'data.csv'
dataset = load_csv(filename)
DATA =np.matrix(dataset)

# напряжения между эмиттером и базой, коллектором и базой тразистора 
U_emitter=np.array(DATA[(0,2,4,6,8,10,12,14),0],float)
U_collector=np.array(DATA[(0,2,4,6,8,10,12,14),1],float)

# создаём массивы с тестовыми значениями 
U_em_test=np.array(DATA[(1,3,5,7,9,11,13,15),0],float)
U_coll_test=np.array(DATA[(1,3,5,7,9,11,13,15),1],float)

# создаём экземпляр класса LinearRegression, который будет представлять регрессионную модель
model = LinearRegression()
model.fit(U_emitter,U_collector)

# записываем коэффициенты, чтобы построить прямую y = kx + b
b = float(model.intercept_)
k = float(model.coef_)
x = np.arange(min(U_emitter), max(U_emitter), 0.01)
y = k*x+b

# создаём окно с графиком 
fig, ax1 = plt.subplots()
fig.canvas.set_window_title('Linear Regression')
ax1.set_xlabel('Voltage between emitter and base of transistor')
ax1.set_ylabel('Voltage between collector and base of transistor')

# наносим на график эксперементальные результаты и прямую, полученную с помощью линейной регрессии  
ax1.scatter(x=U_emitter, y=U_collector, marker='o', c='lime', edgecolors = 'b')
ax1.plot(x, y, c='r')

# наносим на график значения из тестовой выборки 
ax1.scatter(x=U_em_test, y=U_coll_test, marker='^', c='yellow', edgecolors = 'darkorange')

plt.show()