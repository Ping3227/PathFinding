import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import argparse

# Function to plot contour
def plot_contour(df, x_col, y_col, z_col, title, xlabel, ylabel, zlabel):
    # Use pivot_table to handle missing values
    pivot_df = df.pivot_table(index=y_col, columns=x_col, values=z_col)

    # Create X, Y meshgrid
    X, Y = np.meshgrid(pivot_df.columns, pivot_df.index)

    # Get Z values and ensure no NaN values
    Z = pivot_df.values
    Z = np.nan_to_num(Z, nan=0)

    plt.figure(figsize=(8, 6))
    contour = plt.contourf(X, Y, Z, levels=20, cmap='viridis')
    plt.colorbar(contour, label=zlabel)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.show()

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description='Plot contour plots from CSV file.')
    parser.add_argument('filename', type=str, help='Path to the CSV file')

    args = parser.parse_args()

    # Load CSV data
    data = pd.read_csv(args.filename)

    # Plot DP valid paths
    plot_contour(
        data,
        x_col='n',
        y_col='p',
        z_col='DPAvgValidPaths',
        title='DP Valid Paths Contour Plot',
        xlabel='n',
        ylabel='p',
        zlabel='Avg DP Valid Paths'
    )

    # Plot Recursive valid paths
    plot_contour(
        data,
        x_col='n',
        y_col='p',
        z_col='RecAvgValidPaths',
        title='Recursive Valid Paths Contour Plot',
        xlabel='n',
        ylabel='p',
        zlabel='Avg Recursive Valid Paths'
    )

    # Plot DP optimal paths
    plot_contour(
        data,
        x_col='n',
        y_col='p',
        z_col='DPAvgOptimalPaths',
        title='DP Optimal Paths Contour Plot',
        xlabel='n',
        ylabel='p',
        zlabel='Avg DP Optimal Paths'
    )

    # Plot Recursive optimal paths
    plot_contour(
        data,
        x_col='n',
        y_col='p',
        z_col='RecAvgOptimalPaths',
        title='Recursive Optimal Paths Contour Plot',
        xlabel='n',
        ylabel='p',
        zlabel='Avg Recursive Optimal Paths'
    )

if __name__ == '__main__':
    main()
