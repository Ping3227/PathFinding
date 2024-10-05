import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import argparse
from scipy.interpolate import griddata

# Function to plot smooth contour with log-transform using log(1 + Z) to avoid log(0) issues
def plot_contour_log_smooth(df, x_col, y_col, z_col, title, xlabel, ylabel, zlabel):
    # Extract x, y, z values
    x_values = df[x_col].values
    y_values = df[y_col].values
    z_values = df[z_col].values

    # Generate grid for interpolation
    xi = np.linspace(min(x_values), max(x_values), 200)  # Smooth with 200 points
    yi = np.linspace(min(y_values), max(y_values), 200)

    # Interpolate Z values to create smooth contour
    zi = griddata((x_values, y_values), z_values, (xi[None, :], yi[:, None]), method='linear')

    # Apply log10(1 + Z) transform to avoid log(0) issue
    zi_log = np.log10(1 + zi)

    plt.figure(figsize=(8, 6))
    contour = plt.contourf(xi, yi, zi_log, levels=20, cmap='viridis', extend='both')
    plt.colorbar(contour, label=f'log10(1 + {zlabel})')
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.show()

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description='Plot log-transformed smooth contour plots from CSV file.')
    parser.add_argument('filename', type=str, help='Path to the CSV file')

    args = parser.parse_args()

    # Load CSV data
    data = pd.read_csv(args.filename)

    # Plot DP valid paths (log-smooth)
    plot_contour_log_smooth(
        data,
        x_col='n',
        y_col='p',
        z_col='DPAvgValidPaths',
        title='DP Valid Paths Contour Plot (Log-Smooth)',
        xlabel='n',
        ylabel='p',
        zlabel='Avg DP Valid Paths'
    )

    # Plot Recursive valid paths (log-smooth)
    plot_contour_log_smooth(
        data,
        x_col='n',
        y_col='p',
        z_col='RecAvgValidPaths',
        title='Recursive Valid Paths Contour Plot (Log-Smooth)',
        xlabel='n',
        ylabel='p',
        zlabel='Avg Recursive Valid Paths'
    )

    # Plot DP optimal paths (log-smooth)
    plot_contour_log_smooth(
        data,
        x_col='n',
        y_col='p',
        z_col='DPAvgOptimalPaths',
        title='DP Optimal Paths Contour Plot (Log-Smooth)',
        xlabel='n',
        ylabel='p',
        zlabel='Avg DP Optimal Paths'
    )

    # Plot Recursive optimal paths (log-smooth)
    plot_contour_log_smooth(
        data,
        x_col='n',
        y_col='p',
        z_col='RecAvgOptimalPaths',
        title='Recursive Optimal Paths Contour Plot (Log-Smooth)',
        xlabel='n',
        ylabel='p',
        zlabel='Avg Recursive Optimal Paths'
    )

if __name__ == '__main__':
    main()
