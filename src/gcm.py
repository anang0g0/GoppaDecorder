from Crypto.Cipher import AES
from Crypto.Protocol.KDF import scrypt
from Crypto.Random import get_random_bytes
from Crypto.Util.number import long_to_bytes
import secrets
import binascii

flag= open("README.md", "rb").read()
key= get_random_bytes(32)
HexMyKey= key.hex()
cipher= AES.new(key, AES.MODE_GCM)

ciphertext, tag= cipher.encrypt_and_digest(flag)
enc= cipher.nonce + ciphertext + tag
HexEncryptedOriginalMessage= enc.hex()
print(HexEncryptedOriginalMessage)

key=bytes.fromhex(HexMyKey)
data = bytes.fromhex(HexEncryptedOriginalMessage)
cipher = AES.new(key, AES.MODE_GCM, data[:16]) # nonce
try:
    dec = cipher.decrypt_and_verify(data[16:-16], data[-16:]) # ciphertext, tag
    print(dec) # b'my secret data'
except ValueError:
    print("Decryption failed")