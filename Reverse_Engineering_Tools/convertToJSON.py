import pandas as pd

file_path1 = "./Resources/moves.csv"

try:
    df1 = pd.read_csv(file_path1)
except FileNotFoundError:
    print(f"File not found: {file_path1}")
except Exception as e:
    print(f"Error reading file: {e}")

output_file_path = r"./Resources/moves.json"

df1['accuracy'] = df1['accuracy'].astype('Int64')
df1['power'] = df1['power'].astype('Int64')
df1['pp'] = df1['pp'].astype('Int64')
df1['priority'] = df1['priority'].astype('Int64')
df1['damage_class_id'] = df1['damage_class_id'].astype('Int64')
df1['effect_id'] = df1['effect_id'].astype('Int64')
df1['effect_chance'] = df1['effect_chance'].astype('Int64')
df1['contest_type_id'] = df1['contest_type_id'].astype('Int64')
df1['contest_effect_id'] = df1['contest_effect_id'].astype('Int64')
df1['super_contest_effect_id'] = df1['super_contest_effect_id'].astype('Int64')
df1['target_id'] = df1['target_id'].astype('Int64')

try:
    df1.to_json(output_file_path,orient='records', indent=4)
    print(f"Saved merged data to {output_file_path}")
except Exception as e:
    print(f"Error saving file: {e}")