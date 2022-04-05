import numpy as np
import time
from sklearn import svm
from sklearn.neighbors import KNeighborsClassifier
from csv import reader

# загружаем CSV файл
def load_csv(filename):
	file = open(filename, "r")
	lines = reader(file)
	dataset = list(lines)
	return dataset

filename = 'Stress-Lysis.csv'
dataset = load_csv(filename)
DATA =np.matrix(dataset)
output = open('results.txt', 'a')

# задаём начальное количество данных для обучения
num_train = 6
# счётчик неправильно предсказанных значений 
counter = 1000
# начинаем отсчёт времени
t_beg = time.time()
while counter > 0:
    # первые num_train результатов используем для обучения 
    X_train = np.array(DATA[1:num_train, 0:3])
    Y_train = np.array(dataset)[1:num_train, 3]
    # остальные результаты используем для проверки
    X_test = np.array(DATA[num_train:, 0:3])
    Y_test = np.array(DATA[num_train:, 3])

    # создаём классификатор
    clf = svm.SVC()
    # обучаем его
    clf.fit(X_train, Y_train)

    # предсказываем значения уровня стресса для X_test
    predicted = clf.predict(X_test)
    # счётчик для неверно предсказанных результатов
    counter = 0
    for i in range(0, len(predicted)):
        #print("for humidity = ", X_test[i][0], ", temperature = ", X_test[i][1]," and step count = ", X_test[i][2], " - predicted stress level is ", predicted[i])
        if Y_test[i] != predicted[i]:
            counter += 1
    num_train += 1

output.write("Amount of training data is " + str(num_train) + "   Number of mispredicted results is " + str(counter)+ '\n')
# заканчиваем отсчёт времени 
t_end = time.time()
t = t_end - t_beg
output.write("With SVM it took " + str(t) + " seconds " + '\n')



# задаём начальное количество данных для обучения
num_train = 6
# счётчик неправильно предсказанных значений 
counter = 1000
# начинаем отсчёт времени
t_beg = time.time()
while counter > 0:
    # первые num_train результатов используем для обучения 
    X_train = np.array(DATA[1:num_train, 0:3], dtype=float)
    Y_train = np.array(DATA[1:num_train, 3], dtype=float)
    # остальные результаты используем для проверки
    X_test = np.array(DATA[num_train:, 0:3],dtype=float)
    Y_test = np.array(DATA[num_train:, 3], dtype=float)

    # создаём классификатор
    neigh = KNeighborsClassifier()
    # обучаем его
    neigh.fit(X_train, Y_train.ravel())

    # счётчик для неверно предсказанных результатов
    counter = 0
    # предсказываем значения уровня стресса для X_test
    for i in range(0, len(X_test)):
        predicted = neigh.predict([X_test[i]])
        if Y_test[i] != predicted:
            counter += 1
    num_train += 1

output.write("Amount of training data is " + str(num_train) + "   Number of mispredicted results is " + str(counter)+ '\n')
# заканчиваем отсчёт времени 
t_end = time.time()
t = t_end - t_beg
output.write("With kNN it took " + str(t) + " seconds " + '\n')

