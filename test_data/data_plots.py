import matplotlib.pyplot as plt
import sys

def calculate_text_statistics(filename):
    with open(filename, 'r') as file:
        text = file.read()

    words = text.split()
    word_lengths = [len(word) for word in words]

    return word_lengths

if __name__ == '__main__':
    # Read file name from command line
    filename = sys.argv[1]
    word_lengths = calculate_text_statistics(filename)

    plt.hist(word_lengths, bins=range(1, max(word_lengths) + 2), align='left', rwidth=0.8)
    plt.xlabel('Word Lengths')
    plt.ylabel('Count')
    plt.title('Histogram of Word Lengths')
    plt.show()
    