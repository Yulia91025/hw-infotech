import numpy as np
import tensorflow as tf
from csv import reader
import matplotlib.pyplot as plt

# загружаем CSV файл
def load_csv(filename):
	file = open(filename, "r")
	lines = reader(file)
	dataset = list(lines)
	return dataset

filename = 'athlete_events.csv'
dataset = load_csv(filename)
DATA =np.matrix(dataset)
DATA = np.array(DATA[1:10000, [2,3,4,5,14]])

# обрабатываем датасет
i=0
while (i < len(DATA[:,0])):
    if DATA[i,0] == 'M':
        DATA[i,0] = 0
    elif DATA[i,0] == 'F':
        DATA[i,0] = 1
    flag = True
    j = 1
    while ((j < len(DATA[0])-1) and flag):
        if  DATA[i,j] == 'NA':
            DATA = np.delete(DATA,i,0)
            flag = False
        else:
            DATA[i,j] = float(DATA[i,j])
            j += 1
    if flag: 
        i+=1

for i in range(0,len(DATA[:,4])):
    if DATA[i,4] == 'Gold':
        DATA[i,4] = 1
    elif DATA[i,4] == 'Silver':
        DATA[i,4] = 2
    elif DATA[i,4] == 'Bronze':
        DATA[i,4] = 3
    elif DATA[i,4] == 'NA':
        DATA[i,4] = 4
    
DATA = np.array(DATA, float)
class_names = {1 : 'Gold', 2 : 'Silver', 3 : 'Bronze', 4 : 'NA'} 

num_train=1000
# первые num_train результатов используем для обучения
X_train=np.array(DATA[1:num_train, [0,1,2,3]])
Y_train = np.array(DATA[1:num_train, 4])

# цвета для графика тренировочного датасета 
class_color_train = {1 : 'gold', 2 : 'silver', 3 : 'darkorange', 4 : 'k'} 

colors_train = [i for i in range(0, len(Y_train))]
for i in range(0, len(Y_train)):
    colors_train[i] = class_color_train[Y_train[i]]

# остальные результаты используем для проверки
X_test=np.array(DATA[num_train:, [0,1,2,3]])
Y_test = np.array(DATA[num_train:, 4])

# создаём нейросеть 
model = tf.keras.Sequential([
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dense(4)
])

# компилируем нейросеть 
model.compile(optimizer='adam',
              loss=tf.keras.losses.MeanSquaredError(),
              metrics=['accuracy'])

# количество эпох 
ep_num = 500

# тренируем нейросеть 
model.fit(X_train, Y_train, epochs=ep_num)

# точность на тренировочных данных
test_loss, test_acc = model.evaluate(X_test,  Y_test, verbose=2)
print('\nTest accuracy:', test_acc)

# предсказываем вероятности попадания каждого элемента тестового датасета в классы 
predictions = model.predict(X_test)

# создаём массив со значениями, куда наиболее вероятно попадёт каждый элемент тестового датасета 
answer = [i for i in range(0, len(predictions[:,0]))]
for i in range(0, len(predictions[:,0])):
    answer[i] = np.argmax(predictions[i]) + 1

# цвета для графика тестового датасета 
class_color_test = {1 : 'r', 2 : 'g', 3 : 'm', 4 : 'c'}

colors_test = [i for i in range(0, len(answer))]
for i in range(0, len(answer)):
    colors_test[i] = class_color_test[answer[i]]

# создаём окно с двумя графиками 
fig, (ax1, ax2) = plt.subplots(1, 2)
fig.canvas.set_window_title('Работа с нейросетью')
ax1.set_title('Тренировочный датасет')
ax2.set_title('Тестовый датасет')

# параметры, для которых можно построить графики 
params = { 0 : 'Пол', 1 : 'Возраст', 2 : 'Рост', 3 : 'Вес'}

print('Графики какой зависимости необходимы?\n', params)
print('\nВведите первое число: ')
p1 = int(input())
print('\nВведите второе число: ')
p2 = int(input())

ax1.set_xlabel(params[p1])
ax1.set_ylabel(params[p2])
ax2.set_xlabel(params[p1])
ax2.set_ylabel(params[p2])

ax1.scatter(x=X_train[:,p1], y=X_train[:,p2], marker='o', c=colors_train)
ax2.scatter(x=X_test[:,p1], y=X_test[:,p2], marker='o', c=colors_test)

plt.show()

output = open('results.txt', 'a')
str_acc = '\nTest accuracy:' + str(test_acc)
output.write(str_acc)
for i in range(0, len(predictions[:,0])):
    out_str = '\n'+str(X_test[i]) + '    ' +str(answer[i])
    output.write(out_str)