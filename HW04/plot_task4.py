import re
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

for mode in ["static", "dynamic", "guided"]:
    text = open(f"task4_{mode}.out").read()
    threads = [int(t) for t in re.findall(r"t = (\d+)", text)]
    times = [float(x) for x in re.findall(r"time: ([\d.]+)ms", text)]

    plt.figure(figsize=(7, 5))
    plt.plot(threads, times, marker="o")
    plt.xlabel("Number of threads")
    plt.ylabel("Time (ms)")
    plt.title(f"N-body simulation time vs. threads (schedule({mode}))")
    plt.xticks(threads)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"task4_{mode}.png", dpi=150)
    plt.close()
    print(f"saved task4_{mode}.png")
