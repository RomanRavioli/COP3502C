import sys

# Function to read the key file
def read_key(file_name):
    with open(file_name, 'r') as key_file:
        n = int(key_file.readline().strip())  # Read the matrix size
        key_matrix = []
        for _ in range(n):
            row = list(map(int, key_file.readline().strip().split()))
            key_matrix.append(row)  # Read each row of the matrix
    return key_matrix, n

# Function to read and process the plaintext file
def process_plaintext(file_name, n):
    with open(file_name, 'r') as plain_file:
        text = plain_file.read().lower()  # Read all text and convert to lowercase
        filtered_text = ''.join(filter(str.isalpha, text))  # Keep only alphabetic characters
        # Pad with 'x' if the text length is not a multiple of n
        while len(filtered_text) % n != 0:
            filtered_text += 'x'
    return filtered_text

# Function to encrypt the plaintext using the key matrix (Hill cipher)
def hill_cipher_encrypt(plaintext, key_matrix, n):
    ciphertext = []
    for i in range(0, len(plaintext), n):
        block = [ord(char) - ord('a') for char in plaintext[i:i+n]]  # Convert block to numbers
        # Encrypt block by matrix multiplication
        encrypted_block = [(sum(key_matrix[j][k] * block[k] for k in range(n)) % 26) for j in range(n)]
        ciphertext.extend([chr(c + ord('a')) for c in encrypted_block])  # Convert back to characters
    return ''.join(ciphertext)

# Main function
def main():
    if len(sys.argv) != 3:
        print("Usage: python3 pa01.py <key_file> <plaintext_file>")
        sys.exit(1)

    # Read the key file and plaintext file
    key_matrix, n = read_key(sys.argv[1])
    plaintext = process_plaintext(sys.argv[2], n)
    
    # Encrypt the plaintext
    ciphertext = hill_cipher_encrypt(plaintext, key_matrix, n)

    # Output the key matrix
    print("Key matrix:")
    for row in key_matrix:
        print(' '.join(f'{num:4d}' for num in row))

    # Output the processed plaintext
    print("\nPlaintext:")
    for i in range(0, len(plaintext), 80):  # Print 80 characters per line
        print(plaintext[i:i+80])

    # Output the ciphertext
    print("\nCiphertext:")
    for i in range(0, len(ciphertext), 80):  # Print 80 characters per line
        print(ciphertext[i:i+80])

if __name__ == "__main__":
    main()