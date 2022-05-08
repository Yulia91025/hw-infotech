import numpy as np
import math
import time
import matplotlib.pyplot as plt
import ant_algorithm
import genetic_algorithm
import simulated_annealing

# n - количество городов
for n in range(50, 200, 25):
	# координаты городов
	X = np.random.randint(-100, 100, n)
	Y = np.random.randint(-100, 100, n)
	coords = list(map(list, zip(X, Y)))
	keys = [ i for i in range(0,len(X))]
	cities=dict(zip(keys, coords))


	############## Муравьиный алгоритм ##############
	
	# функция для нахождения расстояния между городами 
	def distance(start, end):
		x_distance = abs(start[0] - end[0])
		y_distance = abs(start[1] - end[1])
		return math.sqrt(pow(x_distance, 2) + pow(y_distance, 2))

	# количество итераций для муравьиного алгоритма 
	num_iter = n + 50
	# начинаем отсчёт времени
	t_beg = time.time()
	# создаём экземпляр класса Колонии муравьёв
	Colony = ant_algorithm.ant_colony(cities, distance, iterations=num_iter)
	# получаем последовательность, в которой надо посетить города и финальное расстояние 
	answer_AC = Colony.mainloop()
	dist1 = Colony.shortest_distance
	# заканчиваем отсчёт времени 
	t_end = time.time()
	t_AC = t_end - t_beg

	# координаты городов в нужной последовательности
	x1 = [i for i in range(0,n)]
	y1 = [i for i in range(0,n)]
	for i in range(0,n):
		x1[i] = cities[answer_AC[i]][0]
		y1[i] = cities[answer_AC[i]][1]


	############## Генетический алгоритм ##############

	# создаём список городов для генетического алгоритма
	cityList = []
	for i in range(0,n):
		cityList.append(genetic_algorithm.City(x=X[i], y=Y[i]))

	# количество поколений и размер популяции в генетическом алгоритме 
	num_of_generations = 150 + n
	popS = n
	# начинаем отсчёт времени
	t_beg = time.time()
	# получаем последовательность, в которой надо посетить города и финальное расстояние 
	answer_GA, dist2 = genetic_algorithm.geneticAlgorithm(population=cityList, popSize=popS, eliteSize=20, mutationRate=0.001, generations=num_of_generations)
	# заканчиваем отсчёт времени 
	t_end = time.time()
	t_GA = t_end - t_beg

	# координаты городов в нужной последовательности
	x2 = [i for i in range(0,n)]
	y2 = [i for i in range(0,n)]
	for i in range(0,n):
		x2[i] = answer_GA[i].x
		y2[i] = answer_GA[i].y


	############## Метод отжига ##############

	# значения предельной температуры и итерации 
	stop_T = 1e-8
	stop_iter = 5000
	# начинаем отсчёт времени
	t_beg = time.time()
	# создаём экземпляр класса Симуляции отжига
	SA = simulated_annealing.SimAnneal(coords,stopping_T = stop_T, stopping_iter=stop_iter)
	# получаем последовательность, в которой надо посетить города и финальное расстояние 
	answer_SA = SA.anneal()
	dist3 = SA.best_fitness
	# заканчиваем отсчёт времени 
	t_end = time.time()
	t_SA = t_end - t_beg

	x3 = []; y3 = []
	for i in answer_SA[0]:
		x3.append(coords[i][0])
		y3.append(coords[i][1])


	############## Графики ##############

	# создаём окно с графиком 
	fig, (ax1, ax2, ax3) = plt.subplots(nrows=1, ncols=3)
	fig.canvas.set_window_title('Задача коммивояжёра')
	fig.set_size_inches(18.5, 6)
	text = "Количество городов: "+ str(n)
	plt.suptitle(text, fontsize=16, y = 1.0001, c ='b')

	title1 = "Муравьиный алгоритм\n" + "Кол-во итераций: " + str(num_iter) 
	ax1.set_title(title1)
	str1 = "Длина пути: " + str(round(dist1, 2)) + "\nВремя работы: " + str(round(t_AC,2)) + " секунд"
	ax1.set_xlabel(str1)
	ax1.grid(True)
	ax1.set_xlim((-105,105))
	ax1.set_ylim((-105,105))
	# наносим на график города
	ax1.scatter(x=X, y=Y, marker='o', c='lime', edgecolors = 'b')
	# наносим на график линии, соединяющие города
	ax1.plot(x1, y1, c='r')
	ax1.annotate('start', (x1[0]-3, y1[0]+2))
	ax1.annotate('end', (x1[n-1]-2, y1[n-1]+2))
	
	title2 = "Генетический алгоритм\n" + "Кол-во поколений: " + str(num_of_generations) + " Размер популяции: " + str(popS)
	ax2.set_title(title2)
	str2 = "Длина пути: " + str(round(dist2,2)) + "\nВремя работы: " + str(round(t_GA,2))+ " секунд"
	ax2.set_xlabel(str2)
	ax2.grid(True)
	ax2.set_xlim((-105,105))
	ax2.set_ylim((-105,105))
	# наносим на график города
	ax2.scatter(x=X, y=Y, marker='o', c='lime', edgecolors = 'b')
	# наносим на график линии, соединяющие города
	ax2.plot(x2, y2, c='m')
	ax2.annotate('start', (x2[0]-3, y2[0]+2))
	ax2.annotate('end', (x2[n-1]-2, y2[n-1]+2))

	title3 = "Метод отжига\n" + "Min температура: " + str(stop_T) + " Max итерация: " + str(stop_iter)
	ax3.set_title(title3)
	str3 = "Длина пути: " + str(round(dist3,2)) + "\nВремя работы: " + str(round(t_SA,2))+ " секунд"
	ax3.set_xlabel(str3)
	ax3.grid(True)
	ax3.set_xlim((-105,105))
	ax3.set_ylim((-105,105))
	# наносим на график города
	ax3.scatter(x=X, y=Y, marker='o', c='lime', edgecolors = 'b')
	# наносим на график линии, соединяющие города
	ax3.plot(x3, y3, c='g')
	ax3.annotate('start', (x3[0]-3, y3[0]+2))
	ax3.annotate('end', (x3[n-1]-2, y3[n-1]+2))

	name = str(n) + '.png'
	plt.savefig(name)
	#plt.show()