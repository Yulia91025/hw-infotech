Программа проверяет, будет ли принят в университет абитуриент с номером, введённым пользователем. 
В фоновом режиме функция сan_go_to_university вычисляет, проходит ли человек в рейтинговых списках (на самом деле в моей функции это определяется просто рандомно). 
В это время пользователь вводит, прикреплено ли у абитуриента согласие, через функцию consent_to_enrollment. 
Если результат обеих функций оказывается true, то абитуриент зачислен и программа выведет это, 
если результат сan_go_to_university оказывается false, то программа выведет, что абитуриенту не хватило баллов, 
если же согласие абитуриента ещё не подано, то возможны 2 варианта: 
1) сan_go_to_university ещё не завершилась, тогда у студента ещё есть шанс подать согласие 
2) сan_go_to_university завершилась и программа выведет, что время закончилось 