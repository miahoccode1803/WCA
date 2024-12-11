import matplotlib.pyplot as plt

# Dữ liệu minh họa từ kết quả chương trình
iterations = list(range(1, 51))
best_fitness = [10, 8, 6, 5, 3.5, 2.1, 1.8, 1.0, 0.6, 0.3, 0.2, 0.15, 0.1, 0.05, 0.01] + [0.0001] * 36

# Vẽ biểu đồ
plt.figure(figsize=(10, 6))
plt.plot(iterations, best_fitness, marker='o', label='Best Fitness (WCA)')
plt.title('WCA Optimization Progress')
plt.xlabel('Iterations')
plt.ylabel('Best Fitness (f(x))')
plt.yscale('log')  # Scale log để thấy rõ sự giảm
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.show()
