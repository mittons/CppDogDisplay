import os
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import hashes
import base64
import sys

PEM_PRIV = 'PEM_KEY'

def check_env():
    """
    Check if required environment variables are set.
    Returns True if all required environment variables are set, False otherwise.
    """
    pkey = os.getenv(PEM_PRIV)
    return bool(pkey)


def sign_data_with_key(data):
    # Fetch key from env
    pem_private = os.getenv(PEM_PRIV)
    
    # Load the private key from PEM format
    private_key = serialization.load_pem_private_key(pem_private.encode(), password=None)

    # Create a signature
    signature = private_key.sign(
        data.encode(),
        padding.PKCS1v15(),
        hashes.SHA256()
    )
    return base64.b64encode(signature).decode('utf-8')
        
        
def load_data(path_to_file):
    file_content = ""
    with open(path_to_file, 'r', encoding='utf-8') as file:
        file_content = file.read()
    return file_content


if __name__ == "__main__":
    if not check_env():
        print("Required environment variables are not set")
        sys.exit(1)
    
    if len(sys.argv) != 2:
        #Troll (it's actually sign.py path/to/tmp_rndnum.html)
        #Context: This print statement might make it to the client as a html header
        print("Usage: sign.py data_to_sign")
        sys.exit(1)
        
    path_to_file = sys.argv[1]
        
    if (not os.path.exists(path_to_file)):
        print("Invalid argument")
        sys.exit(1)
    
    data = ""
    try:
        data = load_data(path_to_file)
    except Exception as e:
        print("Error loading data")
        sys.exit(1)

    try: 
        signature = sign_data_with_key(data)
        print(signature)
    except Exception as e:
        print("Error signing data")
        sys.exit(1)
    
