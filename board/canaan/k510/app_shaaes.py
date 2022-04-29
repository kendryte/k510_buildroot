#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Description: u-boot.bin format update
Author: Wentao Wu (wuwentao@canaan-creative.com)
Date: 2022.02.11
"""

# pylint: disable=line-too-long

import sys
import hashlib
from Crypto.Cipher import AES


INITIAL_AES_IV = '\x0a\x01\x0b\x05\x04\x0f\x07\x09\x17\x03\x01\x06\x08\x0c\x0d\x5b'
INITIAL_AES_KEY = '123456K510BootromKey20200331hutu'


def write_head(output_file):
    """
    Description: write bin file head
    Author: Wentao Wu (wuwentao@canaan-creative.com)
    Date: 2022.02.11
    """
    output_file.write(b'\x00\x00\x00\x00')


def write_len(output_file, file_lenth):
    """
    Description: write bin file length
    Author: Wentao Wu (wuwentao@canaan-creative.com)
    Date: 2022.02.11
    """
    print(f"file length is : {file_lenth}")
    l_file = file_lenth.to_bytes(4, 'little')
    print(l_file.hex())
    output_file.write(l_file)


def write_bin(output_file, file_content):
    """
    Description: write bin file content
    Author: Wentao Wu (wuwentao@canaan-creative.com)
    Date: 2022.02.11
    """
    output_file.write(file_content)


def write_sign(output_file, sign_content):
    """
    Description: write bin file sha256 sign
    Author: Wentao Wu (wuwentao@canaan-creative.com)
    Date: 2022.02.11
    """
    output_file.write(sign_content)


def aes_cbc_encrypt(input_data):
    """
    Description: AES encrypt input data
    Author: Wentao Wu (wuwentao@canaan-creative.com)
    Date: 2022.02.11
    """
    obj = AES.new(INITIAL_AES_KEY.encode(), AES.MODE_CBC, INITIAL_AES_IV.encode())
    ciphertext = obj.encrypt(input_data)
    return ciphertext


if __name__ == "__main__":
    # check input args
    if len(sys.argv) != 3:
        print(f"{sys.argv[0]} input_file output_file")
        sys.exit(1)

    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    # soft hash key, without aes, app head 0x0,0x0
    print("\n--- Process soft hash key without aes")
    with open(input_file_name, 'rb') as in_file, open(output_file_name, 'wb') as out_file:
        write_head(out_file)
        file_data = in_file.read()
        file_len = len(file_data)

        # 16 bytes align
        # encode input file to hex for 16 bytes align
        ORDER_NO = ''
        file_data = file_data.hex()

        if file_len % 16:
            file_data = file_data + ORDER_NO.zfill((16 - file_len % 16) * 2)
            file_len += (16 - file_len % 16)

        # write file len after 16 bytes align
        write_len(out_file, file_len)

        # write bin str to file
        file_data = bytes.fromhex(file_data)
        write_bin(out_file, file_data)

        # calc sign str with SHA256
        print(f"SHA256 sign is : {hashlib.sha256(file_data).hexdigest()}")

       # write sign to file with bytes
        SIGN = hashlib.sha256(file_data).digest()
        write_sign(out_file, SIGN)

        out_file.flush()
        out_file.close()
        print("write to file finished")

    # hardware aes, software hash
    print("\n--- Process hardware aes, software hash")
    with open(input_file_name, 'rb') as in_file, open(output_file_name+'.aes', 'wb') as out_file:
        write_head(out_file)
        file_data = in_file.read()
        file_len = len(file_data)

        # 16 bytes align
        # encode input file to hex for 16 bytes align
        ORDER_NO = ''
        file_data = file_data.hex()

        if file_len % 16:
            file_data = file_data + ORDER_NO.zfill((16 - file_len % 16) * 2)
            file_len += (16 - file_len % 16)
        # write file len after 16 bytes align
        write_len(out_file, file_len)

        # recovery hex to str for AES
        file_data = bytes.fromhex(file_data)

        # do AES encrypt
        aes_output = aes_cbc_encrypt(file_data)
        # write bin with AES str to file
        write_bin(out_file, aes_output)

        # calc AES str sign with SHA256
        print(f"SHA256 sign is : {hashlib.sha256(aes_output).hexdigest()}")

        # write sign to file with bytes
        SIGN = hashlib.sha256(aes_output).digest()
        write_sign(out_file, SIGN)

        # write file end and flush
        out_file.seek(0x0)
        out_file.write(b'\x01')
        out_file.flush()
        out_file.close()
        print("write to file finished")

    print("\n--- Process AES file to aes_otp")
    with open(output_file_name+'.aes', 'rb') as in_file, open(output_file_name+'.aes_otp', 'wb') as output_otp:
        file_data = in_file.read()
        # read input file
        output_otp.write(file_data)
        output_otp.seek(0x1)
        output_otp.write(b'\x01')
        output_otp.flush()
        output_otp.close()
        print("write to file finished\n")
