import os
import glob

def convert_maps():
    input_folder = "old_maps"   
    output_folder = "new_maps"  

    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 儲存每一層樓原本的 up 與 down 降落點
    landing_data = {} 
    raw_floors_data = {}
    
    file_list = glob.glob(os.path.join(input_folder, "*.txt"))
    if not file_list:
        print("Error: No .txt files found in old_maps!")
        return

    # === 第一階段：讀取所有舊地圖資訊 ===
    for filepath in file_list:
        with open(filepath, 'r', encoding='utf-8') as f:
            lines = [l.strip() for l in f.readlines() if l.strip()]

        if len(lines) < 14: continue

        floor_i = int(lines[0])
        # 原本 i 層的 upstairX, upstairY (第一行)
        up_x, up_y = map(int, lines[1].split())     
        # 原本 i 層的 downstairX, downstairY (第二行)
        dn_x, dn_y = map(int, lines[2].split())     
        
        landing_data[floor_i] = {
            'up': (up_x, up_y),
            'down': (dn_x, dn_y)
        }
        
        grid = [list(map(int, lines[3+y].split())) for y in range(11)]
        raw_floors_data[floor_i] = {
            'grid': grid,
            'filename': os.path.basename(filepath)
        }

    if not landing_data: return
    min_f, max_f = min(landing_data.keys()), max(landing_data.keys())

    # === 第二階段：依照你的最新邏輯產生新地圖 ===
    for i, data in raw_floors_data.items():
        if i == min_f or i == max_f:
            print(f"Skipping Floor {i} (Min/Max floor)...")
            continue
            
        # 🌟 flyX => 原本i層的upstairX, flyY =>原本i層的upstairY
        fly_x, fly_y = landing_data[i]['up']
        
        stair_entries = []
        grid = data['grid']

        for y in range(11):
            for x in range(11):
                # 🌟 x y =>掃描i層的30 (上樓)
                if grid[y][x] == 30:
                    target_f = i + 1
                    if target_f in landing_data:
                        # targetX =>原本 i+1層的upstairX, targetY =>原本 i+1層的upstairY
                        tx, ty = landing_data[target_f]['up']
                        stair_entries.append(f"{x} {y} {target_f} {tx} {ty}")
                
                # 🌟 x y =>掃描i層的31 (下樓)
                elif grid[y][x] == 31:
                    target_f = i - 1
                    if target_f in landing_data:
                        # targetX =>原本 i-1層的downstairX, targetY =>原本 i-1層的downstairY
                        tx, ty = landing_data[target_f]['down']
                        stair_entries.append(f"{x} {y} {target_f} {tx} {ty}")

        # 寫入新格式檔案
        new_path = os.path.join(output_folder, data['filename'])
        with open(new_path, 'w', encoding='utf-8') as f:
            f.write(f"{i}\n")
            f.write(f"{fly_x} {fly_y}\n")
            f.write(f"{len(stair_entries)}\n")
            for entry in stair_entries:
                f.write(entry + "\n")
            for row in grid:
                f.write(" ".join(map(str, row)) + "\n")
                
        print(f"Floor {i} converted successfully.")

if __name__ == "__main__":
    convert_maps()