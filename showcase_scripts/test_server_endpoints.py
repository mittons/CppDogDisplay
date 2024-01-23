import requests

# Function to write a string to a file
def write_to_file(file_path, content, mode='a'):
    with open(file_path, mode) as file:
        file.write(content + '\n')

# URL endpoints
url1 = "http://localhost:7777/renderBreeds"
url2 = "http://localhost:7777"

# File to write output to
output_file = "server_response_data_out.txt"

# Make GET request to url1 and write response to file
response1 = requests.get(url1)
write_to_file(output_file, response1.text, mode='w')  # 'w' mode to overwrite if file exists

# Write separator
separator = "=" * 45
write_to_file(output_file, separator)
write_to_file(output_file, separator)
write_to_file(output_file, separator)

# Make GET request to url2 and append response to file
response2 = requests.get(url2)
write_to_file(output_file, response2.text)

# Append separator
write_to_file(output_file, separator)
write_to_file(output_file, separator)
write_to_file(output_file, separator)

# Make HEAD request to url1 and append headers to file
response3 = requests.head(url1)
write_to_file(output_file, str(response3.headers))

# Append separator
write_to_file(output_file, separator)
write_to_file(output_file, separator)
write_to_file(output_file, separator)

# Make HEAD request to url2 and append headers to file
response4 = requests.head(url2)
write_to_file(output_file, str(response4.headers))

# Current version of this file is powered by OpenAI, ChatGPT-4