'''
Generate gcc command for C compilation on Mac
CPE 310 Project

Author: Ian Jackson

run `python3 gen_gcc_cmd.py`
'''

#== Imports ==#
import os
import argparse

#== Main execution ==#
def main(args):
    # get all files in pwd
    files_pwd = os.listdir()
    
    # include only c files
    c_files = [c_file for c_file in files_pwd if c_file[-1] == 'c']
    print(len(c_files))
    
    # generate gcc command
    gcc_cmd = 'gcc '

    for file in c_files:
        gcc_cmd += file + ' '

    gcc_cmd += '-o MIPS_translatron'

    # auto run compiler if told to
    if args.run:
        os.system(gcc_cmd)
    else:
        print(f'Copy, Paste, and run into terminal:\n{gcc_cmd}')

if __name__ == "__main__":
    parser = argparse.ArgumentParser('CPE310 Project gcc auto-compiler')

    parser.add_argument('--run', action='store_true', help='Automatically run the gcc command')

    args = parser.parse_args()

    main(args)