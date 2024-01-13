import matplotlib.pyplot as plt
import sys

def calculate_text_statistics(filename):
    with open(filename, 'r') as file:
        text = file.read()

    words = text.split()
    word_length_categories = {'1-4': 0, '5-8': 0, '9+': 0}

    for word in words:
        length = len(word)
        if length <= 4:
            word_length_categories['1-4'] += 1
        elif 5 <= length <= 8:
            word_length_categories['5-8'] += 1
        else:
            word_length_categories['9+'] += 1

    return word_length_categories

if __name__ == '__main__':
    # Read file name from command line
    filename = sys.argv[1]
    word_length_categories = calculate_text_statistics(filename)

    labels = list(word_length_categories.keys())
    sizes = list(word_length_categories.values())

    plt.pie(sizes, labels=labels, autopct='%1.1f%%')
    plt.show()
