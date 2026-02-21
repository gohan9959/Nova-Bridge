import pandas as pd

file_path1 = "./Resources/pokemon.csv"
file_path2 = "./Resources/pokemon_types.csv"

try:
    df1 = pd.read_csv(file_path1)
    df2 = pd.read_csv(file_path2)
    for i in range(1,898):
        filtered_df2 = df2[df2['pokemon_id'] == i]
        if not filtered_df2.empty:
            types = filtered_df2['type_id'].tolist()
            df1.loc[df1['id'] == i, 'type1'] = int(types[0]) if len(types) > 0 else None
            df1.loc[df1['id'] == i, 'type2'] = int(types[1]) if len(types) > 1 else None
except FileNotFoundError:
    print(f"File not found: {file_path1}")
except Exception as e:
    print(f"Error reading file: {e}")

df1['type1'] = df1['type1'].astype('Int64')
df1['type2'] = df1['type2'].astype('Int64')

output_file_path = r"./Resources/pokemon_with_types.json"

try:
    df1.to_json(output_file_path,orient='records', indent=4)
    print(f"Saved merged data to {output_file_path}")
except Exception as e:
    print(f"Error saving file: {e}")