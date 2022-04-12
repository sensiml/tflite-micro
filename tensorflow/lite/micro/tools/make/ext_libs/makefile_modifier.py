

def fill_makefile(func):
    with open("Makefile","r") as fid:
        tmp_file = fid.read()

    new_file= tmp_file.replace("# FILL_HERE", func())    

    with open("Makefile","w") as out:
        out.write(new_file)



if __name__ == "__main__":
    import sys
    kernels = sys.argv[1]

    if kernels=="siliconlabs":
        from siliconlabs import get_fill_string
        fill_makefile(get_fill_string)

