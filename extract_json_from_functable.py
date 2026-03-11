import json
from collections import OrderedDict


def parse_func_tables(json_input):
    """
    Convert flat func_table entries into grouped tables.

    Behaviour:
    - All entries with the same group_key are merged into a single list
      regardless of ordering in the source. Order of first appearance is
      preserved via an OrderedDict.
    """
    data = json.loads(json_input)

    groups = OrderedDict()

    for item in data:
        func_code = item.get("funcCode", "")
        if not func_code:
            continue

        # Split the string by the last dot to separate the prefix and the suffix
        if "." in func_code:
            prefix, suffix = func_code.rsplit(".", 1)
        else:
            prefix, suffix = func_code, func_code

        # Determine the group name by stripping 'func_table.' if it exists
        if prefix.startswith("func_table."):
            group_key = prefix[len("func_table.") :]
        else:
            group_key = prefix

        # Skip alexa v3 function-table helper table entirely.
        # These entries are not useful for the bit layout we care about.
        if group_key == "v3_function_table->alexa_table1":
            continue

        # Special-case "key-less" func_table.* entries whose prefix is exactly
        # "func_table" (e.g. func_table.sport_show_num). These should become
        # their own tables, named after the field itself, with a single value.
        # Example:
        #   func_table.sport_show_num -> { "sport_show_num": ["sport_show_num"] }
        if group_key == "func_table":
            own_key = suffix
            if own_key not in groups:
                groups[own_key] = []
            groups[own_key].append(suffix)
            continue

        # Normal per-group collection
        if group_key not in groups:
            groups[group_key] = []
        groups[group_key].append(suffix)

    # Convert back to the original array-of-objects shape
    return [{key: values} for key, values in groups.items()]

if __name__ == "__main__":
    # You can read from a file by replacing this block with:
    with open("function_table.json", "r") as f:
        json_data = f.read()
    
    
    # Process the data
    formatted_data = parse_func_tables(json_data)
    
    # Output the result as a formatted JSON/Javascript array
    javascript_output = json.dumps(formatted_data, indent=2)
    print(javascript_output)
    
    # Optionally, write the result directly to a file:
    with open("function_table_output.json", "w") as f:
        f.write(javascript_output)