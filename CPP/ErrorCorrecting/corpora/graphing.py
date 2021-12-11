import os
import time
# makes graphs.

MIN_SIZE = 1
MAX_SIZE = 1000

os.system("make")
regenData = True
if regenData:
    os.system('rm -r data')
os.system('mkdir data; mkdir graphs')

copora = "/home/jzhan411/CSE13S-resources/corpora"
# I flattened my copora directory for simplicty, if you do not want to flatten then add the file's
# subdirectory: aaa.txt -> artificial/aaa.txt
files = ["aaa.txt", "alphabet.txt", "random.txt", "bible.txt", "alice29.txt", "pic"]


def plotinfo(type, file):
    output = f'''gnuplot <<XX
    set terminal jpeg
    set datafile separator " "
    set output "graphs/{type}.jpg"
    set title "{type}"
    plot '''
    plots = []
    for arg in files:
        name = arg.split('.')[0]
        plots.append(f'"data/{name}{file}.dat" with linespoints title "{arg}"')
    output += ", ".join(plots)
    print(output)
    return output


if regenData:
    for arg in files:
        name = arg.split('.')[0]

        error_data = {}
        time_data = {}
        entropy_data = {}

        for i in range(MIN_SIZE, MAX_SIZE):
            # Change this to the path to you
            file_name = f"{copora}/{arg}"
            file1 = open(f"data/data{name}.txt", "a")  # append mode
            file1.write(f"Error: {i / MAX_SIZE}\n")
            # Not sure if I need to close the file here or not
            file1.close()
            start = round(time.time() * 1000)
            os.system(f"./encode -i {file_name} -o data/encoded.txt")
            os.system(f"./error -e {i / MAX_SIZE} < data/encoded.txt > data/errored.txt")
            os.system(f"./entropy < data/errored.txt >> data/data{name}.txt")
            os.system(f"./decode -v -i data/errored.txt -o data/decoded.txt >> data/data{name}.txt 2>&1")
            file1 = open(f"data/data{name}.txt", "a")
            file1.write(f"Time: {round(time.time() * 1000) - start}\n")
            file1.close()

        data = open(f"data/data{name}.txt", 'r')
        i = data.readline()
        while i:
            i = i.split()
            error = i[1]
            entropy_data[error] = data.readline()
            bytes_read = data.readline()
            uncorrected_errors = data.readline()
            corrected_errors = data.readline()
            error_rate = data.readline().split()[2]
            error_data[error] = error_rate
            time_data[error] = data.readline().split()[1]
            i = data.readline()

        error_file = open(f"data/{name}Error.dat", 'a')
        time_file = open(f"data/{name}Time.dat", 'a')
        entropy_file = open(f"data/{name}Entropy.dat", 'a')
        for key, val in error_data.items():
            error_file.write(f"{key} {val}\n")
        for key, val in time_data.items():
            time_file.write(f"{key} {val}\n")
        for key, val in entropy_data.items():
            entropy_file.write(f"{key} {val}\n")
        error_file.close()
        time_file.close()
        entropy_file.close()

os.system(plotinfo("Corrected Error Rate vs Original", "Error"))
os.system(plotinfo("Run Time vs Error Rate (ms)", "Time"))
os.system(plotinfo("Entropy vs Error Rate (With Encode)", "Entropy"))
