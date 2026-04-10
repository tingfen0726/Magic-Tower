import os

# 定義地圖的靜態內容部分
static_content = """5 7
5 3
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 30 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 31 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0"""

# 迴圈從 11 跑到 20 (包含 20)
for i in range(11, 21):
    # 設定檔名，例如 level11.txt
    filename = f"level{i}.txt"
    
    # 打開檔案寫入模式 (加上 utf-8 編碼確保跨平台相容)
    with open(filename, 'w', encoding='utf-8') as file:
        # 第一行先寫入目前的樓層數字 i，並加上換行符號
        file.write(f"{i}\n")
        # 接著寫入後面的靜態內容
        file.write(static_content)

print("成功產生 level11.txt 到 level20.txt！")