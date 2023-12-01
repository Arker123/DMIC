import sys

# open a binary file for reading
# with open('test.pcm', 'rb') as pcmfile:
#     pcmdata = pcmfile.read()

# print(pcmdata[:100])

def convert_hex_to_binary(hex_string):
    hex_values = [int(x, 16) for x in hex_string.split(',')]
    byte_values = bytes(hex_values)
    return byte_values

def main():
    input_file_path = sys.argv[1]
    output_file_path = 'output.pcm'

    with open(input_file_path, 'r') as input_file:
        hex_text = input_file.read()

    # remove the trailing comma and space from the hex text
    hex_string = hex_text.replace('\n', '')
    hex_string = hex_string.replace(' ', '')
    hex_string = hex_string.replace(',', '')
    hex_string = hex_string.replace('0x', '')
    # print(hex_string)

    hex_text = hex_string

    # print([hex_text.split(',')])

    # sys.exit(0)

    # print(hex_text[:100])
    # exit()

    hex_values = []

    for i in range(0, len(hex_text), 2):
        print(int(hex_text[i:i+2], 16))
        hex_values.append(int(hex_text[i:i+2], 16))

    byte_values = bytes(hex_values)


    # binary_data = convert_hex_to_binary(hex_text)

    with open(output_file_path, 'wb') as output_file:
        # output_file.write(binary_data)
        output_file.write(byte_values)

    print(f"Conversion complete. Binary data written to {output_file_path}")

main()