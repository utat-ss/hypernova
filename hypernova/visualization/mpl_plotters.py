import matplotlib.pyplot as plt
import numpy as np
from hypernova.solvers import SolverSolution

def plot_orbit(solution: SolverSolution, title: str = None, show: bool = True):
    """
    Plot the orbit.
    
    Parameters
    ----------
    solution : SolverSolution
        Solution structure.
    title : str
        Title of the plot.
    show : bool
        Show the plot.
    """
    
    fig = plt.figure(figsize=(12, 5), tight_layout=True)

    earth = [plt.Circle((0, 0), 6.378e6, color='lightblue') for i in range(3)]
    axes = []

    for i in range(3):
        axes.append(fig.add_subplot(231 + i))
        axes[i].add_patch(earth[i])
        axes[i].set_aspect("equal")
        axes[i].grid()

    x = solution.y[:, 0]
    y = solution.y[:, 1]
    z = solution.y[:, 2]
    axes[0].plot(x, y)
    axes[0].set_ylabel("y position (m)")
    axes[0].set_xlabel("x position (m)")
    axes[1].plot(y, z)
    axes[1].set_ylabel("z position (m)")
    axes[1].set_xlabel("y position (m)")
    axes[2].plot(x, z)
    axes[2].set_ylabel("z position (m)")
    axes[2].set_xlabel("x position (m)")
    axes[0].set_title("xy")
    axes[1].set_title("yz")
    axes[2].set_title("xz")

    axes.append(fig.add_subplot(212))
    # Plot altitude above each
    altitude = np.sqrt(x**2 + y**2 + z**2) - 6.378e6
    axes[3].plot(solution.jd, altitude)
    axes[3].set_ylabel("Altitude (m)")
    axes[3].set_xlabel("Mission Time (jd)")
    axes[3].grid()

    if title is not None:
        plt.suptitle(title)
    if show:
        plt.show()
    plt.close()