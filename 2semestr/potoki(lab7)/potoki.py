import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("potoki.csv")

plt.figure(figsize=(10, 6))

colors = ['blue', 'red', 'green', 'orange', 'purple', 'brown', 'black']

for i, t in enumerate(sorted(df['threads'].unique())):
    subset = df[df['threads'] == t]
    plt.plot(
        subset['size'],
        subset['time'],
        label=f'{t} поток(а/ов)',
        marker='o',
        linestyle='-',
        color=colors[i % len(colors)],
        linewidth=2
    )

plt.title("Зависимость времени перемножения от размера матрицы и потоков")
plt.xlabel("Размер матрицы (N)")
plt.ylabel("Время (мс)")
plt.legend(title="Потоки")
plt.grid(True)
plt.tight_layout()
plt.savefig("plot.png")
plt.show()
