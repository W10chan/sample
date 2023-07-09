import tkinter as tk
import csv
from gtts import gTTS
import os

def text_to_speech(text, lang='en'):
    tts = gTTS(text=text, lang=lang)
    tts.save('output.mp3')
    os.system('afplay output.mp3')

def load_dictionary_from_csv():
    try:
        with open("dictionary.csv", newline="", encoding="utf-8_sig") as file:
            reader = csv.reader(file)
            dictionary = {row[0]: row[1] for row in reader}
    except FileNotFoundError:
        dictionary = {}

    return dictionary


def save_dictionary_to_csv():
    with open("dictionary.csv", mode="w", newline="", encoding="utf-8_sig") as file:
        writer = csv.writer(file)
        for word, meaning in dictionary.items():
            writer.writerow([word, meaning])

def search_word():
    word = entry_search.get()
    if word in dictionary:
        meaning = dictionary[word]
        label_result.config(text=meaning)
    else:
        label_result.config(text="単語が見つかりません")

def add_word():
    word = entry_add_word.get()
    meaning = entry_add_meaning.get()
    if word and meaning:
        if word not in dictionary:
            dictionary[word] = meaning
            label_add_status.config(text="単語が追加されました")
            save_dictionary_to_csv(dictionary)
        else:
            label_add_status.config(text="単語が既に存在します")
    else:
        label_add_status.config(text="単語と意味を入力してください")

# Tkinterウィンドウの作成
window = tk.Tk()
window.title("辞書アプリ")

# 辞書データの読み込み
dictionary = load_dictionary_from_csv()

# 検索フレーム
frame_search = tk.Frame(window)
frame_search.pack(pady=10)

label_search = tk.Label(frame_search, text="検索する単語:")
label_search.pack(side="left")
entry_search = tk.Entry(frame_search)
entry_search.pack(side="left")

button_search = tk.Button(frame_search, text="検索", command=search_word)
button_search.pack(side="left")

label_result = tk.Label(window, text="")
label_result.pack(pady=10)

# 追加フレーム
frame_add = tk.Frame(window)
frame_add.pack(pady=10)

label_add_word = tk.Label(frame_add, text="追加する単語:")
label_add_word.pack(side="left")

entry_add_word = tk.Entry(frame_add)
entry_add_word.pack(side="left")

label_add_meaning = tk.Label(frame_add, text="意味:")
label_add_meaning.pack(side="left")

entry_add_meaning = tk.Entry(frame_add)
entry_add_meaning.pack(side="left")

button_add = tk.Button(window, text="追加", command=add_word)
button_add.pack(pady=10)

label_add_status = tk.Label(window, text="")
label_add_status.pack()

# 発音ボタン
button_speak = tk.Button(window, text="発音", command=text_to_speech, state="disabled")
button_speak.pack()

window.mainloop()

