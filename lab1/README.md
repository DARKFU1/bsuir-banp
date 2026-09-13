<h1 style="text-align: center; width: 100%"> Лабораторная Работа №1 ОАиП</h1>

<table style="font-size: 150%; border: none; text-align: center; width: 90%; margin: auto">
    <tr style="text-align: left; border:none; border-bottom: 1px solid black">
        <th style="border: none">ФИО</th>
        <th style="border: none">Группа</th>
        <th style="border: none">Вариант</th>
        <th style="border: none">Целевая оценка</th>
    </tr>
    <tr style="border:none">
        <td style="border: none">Филиппов Андрей Сергеевич</td>
        <td style="border: none">651001</td>
        <td style="border: none">26</td>
        <td style="border: none">10</td>
    </tr>
</table>

---


## Этап 4. Постановка задачи

### 4.1 Входные данные

| Имя | Значение | ЕИ | Тип | Ограничение |
|---|---|---|---|---|
| `duration_min` | Длительность | ч | double |
| `distance_km `| Расстояние | км | double |
| `bat_level_start` | Заряд батареи в начале поездки | % | double | $ 0 \leq \text{bat\_level\_start} \leq 100$ |
| `bat_level_finish` | Заряд батареи в конце поездки | % | double | $ 0 \leq \text{bat\_level\_finish} \leq 100$ |
| `bat_capacity_kWh` | Полная емкость батереи |$\text{кВт} \cdot \text{ч} $ | double |
| `energy_tarrif_byn`| Цена электричества |$\text{BYN}/{100 \text{кВт} \cdot \text{ч}}$| double
| `passengers` | Количество пассажиров |чел.| double | $ \text{passengers} \geq 0 $ |

### 4.2 Выходные данные и формулы

| Результат | Формула |
|---|---|
| time_hours | $ \text{duration\_minutes} / 60.0 $ | 
| energy_used_kwh | $ \text{battery\_capacity\_kwh} \times (\text{start\_charge\_percent} - \text{finish\_charge\_percent}) / 100.0 $ |
| average_speed_kmh | $ \text{distance\_km} / \text{time\_hours} $ |
consumption_kwh_per_100| $ \text{km} $| energy_used_kWh / distance_km * 100.0 |
| trip_cost_byn | $ \text{energy\_used\_kwh} \times \text{tariff\_byn\_per\_kwh} $ |
| cost_per_passenger_byn | $ \text{trip\_cost\_byn} / \text{passengers} $ |


<table>
    <tr>
        <th style="background-color: #aaee7788" colspan="7" >Входные данные</th>
        <th colspan="6">Выходные данные</th>
    </tr>
    <tr>
        <th> Расстояние</th>
        <th> Длительность</th>
        <th> Полная емкость батереи</th>
        <th> Заряд батареи в начале поездки</th>
        <th> Заряд батареи в конце поездки</th>
        <th> Цена электричества </th>
        <th> Количество пассажиров </th>
        <th> Длительность, в часах</th>
        <th> Использованная энергия</th>
        <th> Средняя скорость </th>
        <th> Потребление энергии на 100км </th>
        <th> Цена</th>
        <th> Цена на человека</th>
    </tr>
    <tr>
		<td>120.5</td>
		<td>95</td>
		<td>64.0</td>
		<td>82.0</td>
		<td>54.5</td>
		<td>0.42</td>
		<td>3</td>
        <td>1.583333</td>
		<td>17.600000</td>
		<td>76.105263</td>
		<td>11.115789</td>
		<td>7.392000</td>
		<td>2.464000</td>
</table>

## 5. Этап 3. Реализация

### 5.1 Технические требования

- [x] Стандарт C17; исходный файл `main.c` с точной входа `main`.
- [x] Для реализации основной логики программы использованы только стандартные функции `scanf()` и `printf()`.
- [x] Для вещественных величин используется `double`  [&#x1f517;IEEE 754 (2008) (pdf)](https://pub.sergev.org/doc/ieee754-2008.pdf)
- [x] Спецификаторы Мформатов `scanf()` и `printf()` корректны для соответствующих переменных
- [x] Имена переменных отражают их смысл
- [x] Сборка под Windows 11 с использованием **Gnu C Compiler** со следующими флагами: `gcc -Wall -Wextra -Wconversion -Wpedantic -Werror -g -std=c17 main.c -o a.exe` выполняется без вывода ошибок и предупреждений.
- [x] Не использованы функции из Windows API, значительно меняющие поведение консольных приложений (e.g. `system("pause")`, библиотека `conio.h` и др.)
  > Стоит отметить, что `exit()`  является стандартной функцией, определённой в стандарте C17, и не затрагивает системных API для управления консолью. Единственное, для чего используется данная функция - досрочное завершение программы при неправильном вводе данных.

## 6. Этап 4. Проверка программы

### 6.1 Минимальный набор тестов

| Тест | Что выявляет |
|---|---|
| T1. Демонстрация | Согласованность программы с эталоном |
| T2. Индивидуальны | й самостоятельное вычисление ожидаемых значений |
| T3. 45 минут | ошибку duration_minutes / 60 при целочисленном делении |
| T4. Дробные | проценты потерю дробной части и неверные скобки |
| T5. Один пассажир | cost_per_passenger должен совпасть с trip_cost |
| T6. Контрастный | малый расход при большой дистанции или короткая поездка; разумность единиц |
| T7. Типы данных | Точность программы при использовании различных точностей вещественного типа данных |

<table>
    <tr>
        <th>ID</th>
        <th>Ввод</th>
        <th>Ожидание</th>
        <th>Вывод</th>
        <th>Итог</th>
    <tr>
    <tr>
        <td>T1</td>
        <td><code>120.5 95 64.0 82.0 54.5 0.42 3</code></td>
        <td><code>17.60 76.11 14.61 7.39 2.40</code></td>
        <td><code>17.60 76.11 14.61 7.39 2.4</code></td>
        <td style="background-color: #66ee99">PASS</td>
    </tr>
    <tr>
        <td>T2</td>
        <td><code>250.5 239 98.0 69.1 58.2 0.685 3</code></td>
        <td><code>10.6820 3.9833 62.8870 426.</code></td>
        <td><code>10.6820 3.9833 62.8870 4.2643 7.3172 2.4391 </code></td>
        <td style="background-color: #66ee99">PASS</td>
    </tr>
    <tr>
        <td>T3</td>
        <td><code>120.5 55 64.0 82.0 54.5 0.42 3</code></td>
        <td><code>0.75 17.60 160.67 14.61 7.39 2.46</code></td>
        <td><code>0.75 17.60 160.67 14.61 7.39 2.46</code></td>
        <td style="background-color: #66ee99">PASS</td>
    </tr>
    <tr>
        <td>T5</td>
        <td><code>120.5 55 64.0 82.0 54.5 0.42 1</code></td>
        <td><code>10.6820 3.9833 62.8870 4.2643 7.3172 7.3172</code></td>
        <td><code>10.6820 3.9833 62.8870 4.2643 7.3172 7.3172</code></td>
        <td style="background-color: #66ee99">PASS</td>
    </tr>
    <tr>
        <td>T6</td>
        <td><code>12000.5 3 6400.0 82.0 0.5 0.42 123</code></td>
        <td><code>5216.0000 0.0500 240010.0000 43.4649 2190.7200 17.8107 
        <td><code>5216.0000 0.0500 240010.0000 43.4649 2190.7200 17.8107 
</code></td>
        <td style="background-color: #ffff3c; text-align: center;">?</td>
    </tr>
    <tr>
        <td>T7</td>
        <td><code>250.5 239 98.0 69.1 58.2 0.685 3</code></td>
        <td><code>1068200.0000 3.9833 62.8870 426427.1457 731717.0000 731717.0000</code></td>
        <td><code>1068199.7500 3.9833 62.8870 426427.0625 731716.8125 731717.8125</code></td>
        <td style="background-color: #ff5544">FAIL<a href="#footnote-explanation-1"><sup>[1]</sup></a></td>
    </tr>
</table>

[^1]: This is a footnote that corresponds to some kind of content above it

<ol>
    <li><p id="footnote-explanation-1">Так как точность 32-битного float соствляет около 7 значимых десятичных знаков, при использовании его в расчётах с большими числами видна погрешность.</p></li>
</ol>

### 7. Этап 5. Работа с AI


| Предложение AI | Решение | Как проверено | Вывод |
|---|---|---|---|


### 8. Аудит правдоподобного AI кода

Для проведения данного этапа написанный код был значительно изменён - добавлены как различные уязвимости, так и нелогичные и лишние операции, не позволяющие получить желаемый результат.

Полученный код был сохранён в файле `for-review.c`, созданный в соответствующей ветке `for-review`, для того, чтобы не повреждать написанную ранее программу.

Исходный код, находящийся в файле `for-review.c` перед передачей его ИИ модели:j

```c

#include <stdio.h>
...

```