import json
import random
from matplotlib.ticker import MaxNLocator
import matplotlib.colors as mcolors
import matplotlib.pyplot as plt
import numpy as np

# params_filename = '/home/csl/CppWorks/artwork/folder-digger/data/lic_calib.json'
params_filename = '/home/csl/CppWorks/artwork/folder-digger/data/folder_digger.json'
# img_filename = '/home/csl/CppWorks/artwork/folder-digger/img/lic_calib.png'
img_filename = '/home/csl/CppWorks/artwork/folder-digger/img/folder_digger.png'

# ['PiYG', 'PRGn', 'BrBG', 'PuOr', 'RdGy', 'RdBu', 'RdYlBu', 'RdYlGn', 'Spectral', 'coolwarm', 'bwr', 'seismic']
# color_name1 = 'Spectral'
color_name1 = 'PuOr'
# color_name2 = 'coolwarm'
color_name2 = 'RdGy'

# setting
config = {
    # "text.usetex": True,
    "font.family": 'serif',  # sans-serif/serif/cursive/fantasy/monospace
    "font.size": 12,  # medium/large/small
    'font.style': 'normal',  # normal/italic/oblique
    'font.weight': 'normal',  # bold
    "mathtext.fontset": 'cm',
    "font.serif": ['cmb10'],
    "axes.unicode_minus": False,
}

figure_color_alpha = 1.0
figure_marker_size = 3


def read_data(filename, field):
    file = open(filename, "r")
    lines = file.readlines()
    content = ''
    for line in lines:
        content += line
    array_buffer = json.loads(content).get(field)
    type_names = []
    values = []
    for i in range(len(array_buffer)):
        type_names.append(array_buffer[i]['key'])
        values.append(int(array_buffer[i]['value']))

    return [type_names, values]


def draw_bar(x_labels, y_values, ax, title):
    ax.bar(
        x_labels, y_values, alpha=figure_color_alpha, zorder=1, label=x_labels,
        color=plt.get_cmap(color_name1)(np.linspace(0.0, 1.0, len(x_labels))), edgecolor='black'
    )
    for i in range(len(x_labels)):
        ax.text(i, y_values[i], str(y_values[i]), ha='center', va='center',
                bbox=dict(boxstyle="Circle", fc="w", pad=0.5))

    ax.set_title(title)
    ax.set_xlabel("File Type")
    ax.set_ylabel("Number")
    ax.yaxis.set_major_locator(MaxNLocator(integer=True))


def func(pct, allvals):
    absolute = int(np.round(pct / 100. * np.sum(allvals)))
    return "{:.1f}%".format(pct, absolute)


def draw_pie(x_labels, y_values, ax, title):
    wedges, texts, autotexts = ax.pie(
        y_values, autopct=lambda pct: func(pct, y_values), textprops=dict(color="w"),
        wedgeprops={"linewidth": 1, "edgecolor": "black"},
        colors=plt.get_cmap(color_name2)(np.linspace(0.0, 1.0, len(x_labels)))
    )
    ax.set_title(title)
    ax.legend(
        wedges, x_labels, loc="center left", bbox_to_anchor=(1, 0, 0.5, 1)
    )


if __name__ == '__main__':
    plt.rcParams.update(config)
    plt.rcParams['figure.figsize'] = (15.0, 10.0)
    fig, axs = plt.subplots(2, 2)

    [type_names1, type_count] = read_data(params_filename, 'file_type_count')
    [type_names2, line_count] = read_data(params_filename, 'file_line_count')

    type_count, type_names1 = zip(*sorted(zip(type_count, type_names1)))
    line_count, type_names2 = zip(*sorted(zip(line_count, type_names2)))

    draw_bar(type_names1, type_count, axs[0, 0], "Number of Different Types of Files")
    draw_pie(type_names1, type_count, axs[0, 1], "Percentage of the Number of Different Types of Files")
    draw_bar(type_names2, line_count, axs[1, 0], "Lines of Different Types of Files")
    draw_pie(type_names2, line_count, axs[1, 1], "Percentage of Lines in Different Types of Files")

    plt.tight_layout()
    plt.savefig(img_filename)
    plt.show()
