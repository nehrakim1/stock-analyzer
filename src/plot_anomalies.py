import pandas as pd
import matplotlib.pyplot as plt
import argparse
import os

def detect_anomalies(df, k, threshold):
    anomalies = []

    for i in range(k, len(df)):
        window = df['Close'].iloc[i-k:i]
        current = df['Close'].iloc[i]
        avg = window.mean()
        deviation = abs(current - avg) / avg

        if deviation > threshold:
            anomalies.append({
                'Date': df['Date'].iloc[i],
                'Close': current,
                'Deviation (%)': round(deviation * 100, 2)
            })

    return pd.DataFrame(anomalies)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--k', type=int, default=5, help='Window size')
    parser.add_argument('--threshold', type=float, default=0.1, help='Deviation threshold')
    parser.add_argument('--show', action='store_true', help='Show plot on screen')
    args = parser.parse_args()

    # Load data
    df = pd.read_csv("data/stock.csv")
    df['Date'] = pd.to_datetime(df['Date'])

    # Calculate moving average
    df['MovingAvg'] = df['Close'].rolling(window=args.k).mean()

    # Detect anomalies
    anomalies_df = detect_anomalies(df, args.k, args.threshold)

    # Save anomalies to CSV
    os.makedirs("outputs", exist_ok=True)
    anomalies_df.to_csv("outputs/anomalies.csv", index=False)

    # Plot
    plt.figure(figsize=(12, 6))
    plt.plot(df['Date'], df['Close'], label='Close Price', color='blue')
    plt.plot(df['Date'], df['MovingAvg'], label=f'{args.k}-day Moving Avg', color='orange')
    if not anomalies_df.empty:
        plt.scatter(anomalies_df['Date'], anomalies_df['Close'], color='red', label='Anomalies', zorder=5)
    plt.title('Stock Price with Anomalies')
    plt.xlabel('Date')
    plt.ylabel('Close Price')
    plt.legend()
    plt.grid(True)

    # Save plot
    plt.tight_layout()
    plot_path = "outputs/anomalies_plot.png"
    plt.savefig(plot_path)

    # Print anomaly count
    print(f"\n✅ Total anomalies detected: {len(anomalies_df)}")
    print(f"📁 Plot saved at: {plot_path}")
    print(f"📁 Anomalies CSV saved at: outputs/anomalies.csv")

    # Show plot if requested
    if args.show:
        plt.show()

if __name__ == "__main__":
    main()