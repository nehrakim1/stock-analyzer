import yfinance as yf
import sys

def fetch_data(symbol, start, end, file_path):
    stock = yf.Ticker(symbol)
    df = stock.history(start=start, end=end)
    df.reset_index(inplace=True)
    print(df.head())
    df.to_csv(file_path, index=False)
    print(f"Saved data to {file_path}")

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage: python fetch_data.py SYMBOL START_DATE END_DATE OUTPUT_PATH")
    else:
        symbol = sys.argv[1]
        start = sys.argv[2]
        end = sys.argv[3]
        output = sys.argv[4]
        fetch_data(symbol, start, end, output)
