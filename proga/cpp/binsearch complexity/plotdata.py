import numpy as np
import matplotlib.pyplot as plt
import math as mt


def read_data_from_file(input_filename):
    data = []

    with open(input_filename, 'r') as input_file:
        for line in input_file:
            if len(line.strip()) == 0 or line[0] == '#':
                continue  # пустые строки и строки-комментарии пропускаем
            if "END" in line:
                continue

            data.append(np.array(list(map(int, line.split(', ')[:-1]))))

    return data



# Настройка графиков
def axes_setup(ax, xlabel='', ylabel='', axislabelfonstsize=14, title='', titlefonstsize=15, xylimits=((0, 100), (0, 100)),
               ablegrid=True, change_tick_params=False, ticklabelcolor='', ticklabelsise='medium', tickwidth=1):
    global axesxylimits
    axesxylimits.append((ax, xylimits))
    ax.grid(ablegrid, linestyle='-.', alpha=0.33)
    if change_tick_params:
        ax.tick_params(labelcolor=ticklabelcolor, labelsize=ticklabelsise, width=tickwidth)
    ax.set_xlabel(xlabel, fontsize=axislabelfonstsize)
    ax.set_ylabel(ylabel, fontsize=axislabelfonstsize)
    ax.set_title(title, fontsize=titlefonstsize)

    if len(xylimits) == 2:
        ax.set_xlim(xylimits[0])
        ax.set_ylim(xylimits[1])


def axis_limits(x, y):
    return (min(x) - (max(x) - min(x)) * 0.075, max(x) + (max(x) - min(x)) * 0.09), (min(y) - (max(y) - min(y)) *
                                                                                       0.1, max(y) + (max(y) - min(y)) * 0.1)


# Построение гистограммы. На вход подается СЛОВАРЬ такого вида: {значение по оси x: значение по оси y}
def plot_bar(ax, data: dict, label='', yerr=0, color='g'):
    ax.bar(list(data.keys()), list(data.values()), label=label, alpha=0.75, color=color, edgecolor=color, width=1, align='center')
    ax.errorbar(list(data.keys()), list(data.values()), yerr=yerr, linestyle='none', ecolor='k', elinewidth=1.2, capsize=3.5)


# Построение прямой линии по заданным коэффициентам k и b
# Чтобы построить вертикальную прямую k = 'vert', в значение b передается абсцисса пересечения этой прямой с осью x
def plot_line(ax, k, b, start_point=0, end_point=100, label='', linestyle='solid', color='r'):
    if k == 'vert':
        ax.axvline(x=b, ymin=start_point, ymax=end_point, label=label, linestyle=linestyle, color=color, linewidth=1.35,
                   alpha=0.9)
    else:
        x = np.arange(start_point, end_point, 1)
        ax.plot(x, k * x + b, label=label, linestyle=linestyle, color=color, linewidth=1.35, alpha=0.9)


# Проводятся линии до координатных осей(xcoords, ycoords) от заданных точек (на вход подается СПИСОК) и отмечаются их координаты
def plot_stem(ax, x: list, y: list, xcoords=True, ycoords=False, linestyle='-.', color='k'):
    x = list(x)
    y = list(y)
    for axe in axesxylimits:
        if axe[0] == ax:
            xlimits = axe[1][0]
            ylimits = axe[1][1]
    if xcoords:
        secaxx = ax.secondary_xaxis('top')
        secaxx.tick_params(labelcolor='k', labelsize='medium', width=0.9, rotation=0)
        secaxx.set_xticks(x)
        for i in range(len(x)):
            ax.vlines(x=x[i], ymin=y[i], ymax=ylimits[1] + 10, linestyle=linestyle, color=color,
                        linewidth=0.9, alpha=0.6)
    if ycoords:
        secaxy = ax.secondary_yaxis('right')
        secaxy.tick_params(labelcolor='k', labelsize='medium', width=0.9, rotation=0)
        secaxy.set_yticks(y)
        for i in range(len(y)):
            ax.hlines(y=y[i], xmin=x[i], xmax=xlimits[1] + 10, linestyle=linestyle,
                      color=color, linewidth=0.9, alpha=0.6)


# Точки с заданной погрешностью. На вход подается массив значений по осям x и y
# Для отображения погрешностей требуется либо массив значений погрешностей для каждной точки xerr и yerr, либо фиксированное число
def plot_err(ax, x, y, label='', xerr=0, yerr=0, linestyle='none', dot_type='o', dot_color='b', dot_size=4.3):
    ax.errorbar(x, y, xerr=xerr, yerr=yerr, label=label, ecolor='k', elinewidth=0.8, capsize=3, linestyle=linestyle,
                 marker=dot_type, markeredgecolor=dot_color, markerfacecolor=dot_color, markersize=dot_size)


# Стандартный график, на вход подается массив значений по осям x и y
def plot_graph(ax, x, y, label='', linestyle='--', color='r', dot_type='none', dot_color='r'):
    ax.plot(x, y, label=label, linestyle=linestyle, color=color, linewidth=1.35, marker=dot_type,
             markeredgecolor=dot_color, markerfacecolor=dot_color, markersize=4.3, alpha=0.9)


# Тут можно инициализировать данные для построения графиков

data_exaust_search_worst = read_data_from_file('/Users/daniil/Desktop/experiment2.txt')
exaust_search_worst = np.array(sum(data_exaust_search_worst) / len(data_exaust_search_worst)) / 10

data_exaust_search_average = read_data_from_file('/Users/daniil/Desktop/experiment1.txt')
exaust_search_average = np.array(sum(data_exaust_search_average) / len(data_exaust_search_average))

data_binary_search_worst = read_data_from_file('/Users/daniil/Desktop/experiment3.txt')
binary_search_worst = np.array(sum(data_binary_search_worst) / len(data_binary_search_worst)) / 10000

data_binary_search_average = read_data_from_file('/Users/daniil/Desktop/experiment4.txt')
binary_search_average = np.array(sum(data_binary_search_average) / len(data_binary_search_average)) / 100

exp_binary_search_average = np.exp(binary_search_average)
exp_binary_search_worst = 2.71 ** (binary_search_worst)

#N = np.array([100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 5000, 5100, 5200, 5300, 5400, 5500, 5600, 5700, 5800, 5900, 6000, 6100, 6200, 6300, 6400, 6500, 6600, 6700, 6800, 6900, 7000, 7100, 7200, 7300, 7400, 7500, 7600, 7700, 7800, 7900, 8000, 8100, 8200, 8300, 8400, 8500, 8600, 8700, 8800, 8900, 9000, 9100, 9200, 9300, 9400, 9500, 9600, 9700, 9800, 9900, 10000, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000, 26000, 27000, 28000, 29000, 30000, 31000, 32000, 33000, 34000, 35000, 36000, 37000, 38000, 39000, 40000, 41000, 42000, 43000, 44000, 45000, 46000, 47000, 48000, 49000, 50000, 51000, 52000, 53000, 54000, 55000, 56000, 57000, 58000, 59000, 60000, 61000, 62000, 63000, 64000, 65000, 66000, 67000, 68000, 69000, 70000, 71000, 72000, 73000, 74000, 75000, 76000, 77000, 78000, 79000, 80000, 81000, 82000, 83000, 84000, 85000, 86000, 87000, 88000, 89000, 90000, 91000, 92000, 93000, 94000, 95000, 96000, 97000, 98000, 99000, 100000])
N = np.array([1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000, 26000, 27000, 28000, 29000, 30000, 31000, 32000, 33000, 34000, 35000, 36000, 37000, 38000, 39000, 40000, 41000, 42000, 43000, 44000, 45000, 46000, 47000, 48000, 49000, 50000, 51000, 52000, 53000, 54000, 55000, 56000, 57000, 58000, 59000, 60000, 61000, 62000, 63000, 64000, 65000, 66000, 67000, 68000, 69000, 70000, 71000, 72000, 73000, 74000, 75000, 76000, 77000, 78000, 79000, 80000, 81000, 82000, 83000, 84000, 85000, 86000, 87000, 88000, 89000, 90000, 91000, 92000, 93000, 94000, 95000, 96000, 97000, 98000, 99000, 100000, 101000, 102000, 103000, 104000, 105000, 106000, 107000, 108000, 109000, 110000, 111000, 112000, 113000, 114000, 115000, 116000, 117000, 118000, 119000, 120000, 121000, 122000, 123000, 124000, 125000, 126000, 127000, 128000, 129000, 130000, 131000, 132000, 133000, 134000, 135000, 136000, 137000, 138000, 139000, 140000, 141000, 142000, 143000, 144000, 145000, 146000, 147000, 148000, 149000, 150000, 151000, 152000, 153000, 154000, 155000, 156000, 157000, 158000, 159000, 160000, 161000, 162000, 163000, 164000, 165000, 166000, 167000, 168000, 169000, 170000, 171000, 172000, 173000, 174000, 175000, 176000, 177000, 178000, 179000, 180000, 181000, 182000, 183000, 184000, 185000, 186000, 187000, 188000, 189000, 190000, 191000, 192000, 193000, 194000, 195000, 196000, 197000, 198000, 199000, 200000, 201000, 202000, 203000, 204000, 205000, 206000, 207000, 208000, 209000, 210000, 211000, 212000, 213000, 214000, 215000, 216000, 217000, 218000, 219000, 220000, 221000, 222000, 223000, 224000, 225000, 226000, 227000, 228000, 229000, 230000, 231000, 232000, 233000, 234000, 235000, 236000, 237000, 238000, 239000, 240000, 241000, 242000, 243000, 244000, 245000, 246000, 247000, 248000, 249000, 250000, 251000, 252000, 253000, 254000, 255000, 256000, 257000, 258000, 259000, 260000, 261000, 262000, 263000, 264000, 265000, 266000, 267000, 268000, 269000, 270000, 271000, 272000, 273000, 274000, 275000, 276000, 277000, 278000, 279000, 280000, 281000, 282000, 283000, 284000, 285000, 286000, 287000, 288000, 289000, 290000, 291000, 292000, 293000, 294000, 295000, 296000, 297000, 298000, 299000, 300000, 301000, 302000, 303000, 304000, 305000, 306000, 307000, 308000, 309000, 310000, 311000, 312000, 313000, 314000, 315000, 316000, 317000, 318000, 319000, 320000, 321000, 322000, 323000, 324000, 325000, 326000, 327000, 328000, 329000, 330000, 331000, 332000, 333000, 334000, 335000, 336000, 337000, 338000, 339000, 340000, 341000, 342000, 343000, 344000, 345000, 346000, 347000, 348000, 349000, 350000, 351000, 352000, 353000, 354000, 355000, 356000, 357000, 358000, 359000, 360000, 361000, 362000, 363000, 364000, 365000, 366000, 367000, 368000, 369000, 370000, 371000, 372000, 373000, 374000, 375000, 376000, 377000, 378000, 379000, 380000, 381000, 382000, 383000, 384000, 385000, 386000, 387000, 388000, 389000, 390000, 391000, 392000, 393000, 394000, 395000, 396000, 397000, 398000, 399000, 400000, 401000, 402000, 403000, 404000, 405000, 406000, 407000, 408000, 409000, 410000, 411000, 412000, 413000, 414000, 415000, 416000, 417000, 418000, 419000, 420000, 421000, 422000, 423000, 424000, 425000, 426000, 427000, 428000, 429000, 430000, 431000, 432000, 433000, 434000, 435000, 436000, 437000, 438000, 439000, 440000, 441000, 442000, 443000, 444000, 445000, 446000, 447000, 448000, 449000, 450000, 451000, 452000, 453000, 454000, 455000, 456000, 457000, 458000, 459000, 460000, 461000, 462000, 463000, 464000, 465000, 466000, 467000, 468000, 469000, 470000, 471000, 472000, 473000, 474000, 475000, 476000, 477000, 478000, 479000, 480000, 481000, 482000, 483000, 484000, 485000, 486000, 487000, 488000, 489000, 490000, 491000, 492000, 493000, 494000, 495000, 496000, 497000, 498000, 499000, 500000])


axesxylimits = []  # Переменная, отвечающая за пределы по осям у графиков. Заполняется сама в функции axes_setup()

# Создание фигуры(окна или виджета в jupiter notebook) fig. Создание нескольких подграфиков ax1, ax2
fig, ax1 = plt.subplots(1, 1, figsize=(12, 8), constrained_layout=True)

fig.suptitle(r'Зависимости $T(N)$ для бинарного поиска', fontsize=20)

# Начальная настройка осей. Ограничения по осям можно задать вручную так: ((xmin, xmax), (ymin, ymax))
# То же самое можно сделать с помощью вспомогательной функции axis_limits(x, y).
# Можно установить параметры xlabel, ylabel, title. Они отвечают за подписи к осям и за заголовок графика.
axes_setup(ax1, xlabel=r'$N$, количество элементов в массиве',
           ylabel=r'$T, мкс$ - среднее время выполнения программы', axislabelfonstsize=14,
           title=r'', titlefonstsize=17, xylimits=axis_limits(N, exp_binary_search_worst))

#plot_graph(ax1, N, exaust_search_worst, label='Худший случай полного перебора. Усреднение по 10000 запусков в 10 экспериментах', color='red', linestyle='solid')
#plot_graph(ax1, N, exaust_search_average, label='Средний случай полного перебора. Усреднение по 1000 запусков в 500 экспериментах', color='blue', linestyle='solid')

#plot_graph(ax1, N, binary_search_worst, label='Худший случай бинарного поиска. Усреднение по 10000000 запусков в 10 экспериментах', color='red', linestyle='solid')
#plot_graph(ax1, N, binary_search_average, label='Средний случай бинарного поиска. Усреднение по 100000 запусков в 1000 экспериментах', color='blue', linestyle='solid')

plot_graph(ax1, N, exp_binary_search_worst, label='Средний случай бинарного поиска. Усреднение по 100000 запусков в 1000 экспериментах', color='blue', linestyle='solid')


# Размещение легенд графиков
ax1.legend(loc='best', fontsize=14)


plt.savefig('/Users/daniil/Desktop/graph.png')

# Вывод графиков на экран
plt.show()
