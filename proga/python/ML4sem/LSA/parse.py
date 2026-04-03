import requests
from lxml import html
from nltk.stem.snowball import SnowballStemmer
from nltk.corpus import stopwords
import numpy as np
import matplotlib.pyplot as plt

stemmer = SnowballStemmer("russian")
russian_stopwords = stopwords.words("russian")
spec_symb = str.maketrans(dict.fromkeys([",", ".", "-", "*", "+", "(", ")"], ""))

src = 'https://habr.com/ru/search/?q=lsa'
page = requests.get(src)
tree = html.fromstring(page.text)

content = tree.xpath('//a[@class="tm-title__link"]/@href')
content.append("/ru/articles/425177/")
print(content)

texts = []
titles = []
for link in content:

    url_post = "https://habr.com"+link
    page = requests.get(url_post)
    tree = html.fromstring(page.text)
    title = tree.xpath('//title')
    titles.append(title[0].text)
    print(title[0].text)

    content_lsa = tree.xpath('//div[@id="post-content-body"]')
    post_lsa = content_lsa[0].text_content()
    texts.append(post_lsa.lower().translate(spec_symb))


formatted = [' '.join([stemmer.stem(word) for word in post_lsa.split() if word not in russian_stopwords]) for post_lsa in texts]

all_words = ' '.join(formatted).split()
all_words = {word: np.zeros(len(formatted)) for word in all_words}
#print(all_words)
for word in all_words:
    for i, title in enumerate(formatted):
        if word in title: 
            #print(f"word {word} found in title {i}")
            all_words[word][i]+=1
            #print(all_words[word])
for word in list(all_words.keys()):
    if all_words[word].sum() == 1: del all_words[word]
print(all_words)

mat = np.array(list(all_words.values()))
#print(mat)
print(mat.shape)

U, S, Vh = np.linalg.svd(mat)

word_coords = U[:, 0:2].T
title_coords = Vh[0:2]

target_coords = title_coords[:, [-1]]
title_coords = title_coords[:, :-1]

dist = ((title_coords-target_coords)**2).mean(axis=0)
print(f"Best recommendation: {titles[np.argmin(dist)]}")

plt.scatter(word_coords[0], word_coords[1], color='r')
#plt.scatter(title_coords[0], title_coords[1], color='black')
plt.show()