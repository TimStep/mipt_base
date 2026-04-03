from nltk.stem.snowball import SnowballStemmer
from nltk.corpus import stopwords
import numpy as np
import matplotlib.pyplot as plt

stemmer = SnowballStemmer("russian")
russian_stopwords = stopwords.words("russian")

with open("titles.txt", "r") as file:

    lines = [line.strip().replace(",", "").lower() for line in file]
    titles = [' '.join([stemmer.stem(word) for word in line.split() if word not in russian_stopwords and len(word)>1]) for line in lines]

print(titles)

all_words = ' '.join(titles).split()
all_words = {word: np.zeros(len(titles)) for word in all_words}
#print(all_words)
for word in all_words:
    for i, title in enumerate(titles):
        if word in title: 
            #print(f"word {word} found in title {i}")
            all_words[word][i]+=1
            #print(all_words[word])
for word in list(all_words.keys()):
    if all_words[word].sum() == 1: del all_words[word]
print(all_words)

mat = np.array(list(all_words.values()))
print(mat)
print(mat.shape)

U, S, Vh = np.linalg.svd(mat)

word_coords = U[:, 0:2].T
title_coords = Vh[0:2]

plt.scatter(word_coords[0], word_coords[1], color='r')
plt.scatter(title_coords[0], title_coords[1], color='black')
plt.show()
