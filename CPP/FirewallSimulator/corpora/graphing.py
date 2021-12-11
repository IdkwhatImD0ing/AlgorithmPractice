import os
import time
# makes graphs.

MIN_SIZE = 1048576 - 1000000
MAX_SIZE = 1048576

os.system("make")
regenData = True
if regenData:
    os.system('rm -r data')
os.system('mkdir data; mkdir graphs')

copora = "/home/jzhan411/CSE13S-resources/corpora"
# I flattened my copora directory for simplicty, if you do not want to flatten then add the file's
# subdirectory: aaa.txt -> artificial/aaa.txt
files = ["bible.txt"]


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

        seeks = {}
        average_data = {}


        for i in range(MIN_SIZE, MAX_SIZE):
            if(i%10000 == 0):
                # Change this to the path to you
                file_name = f"{copora}/{arg}"
                file1 = open(f"data/{name}stats.txt", "a")  # append mode
                os.system(f"./banhammer -s -f {i} <{file_name} >> data/{name}stats.txt")
                # Not sure if I need to close the file here or not
                file1.close()
                file1 = open(f"data/{name}bloom.txt", "a")
                file1.write(f"Bloom: {i}\n")
                file1.close()

        data = open(f"data/{name}stats.txt", 'r')
        bloom = open(f"data/{name}bloom.txt", 'r')
        i = data.readline()
        j = bloom.readline()
        while i:
            j = j.split()[1]
            #Index of seeks and average
            seeks[j] = i.split()[1]
            average_data[j] = data.readline().split()[3]
            #Throw away next 2 lines
            data.readline().split()[3]
            data.readline().split()[3]
            i = data.readline()
            j = bloom.readline()

        seeks_file = open(f"data/{name}seeks.dat", 'a')
        average_file = open(f"data/{name}average.dat", 'a')
        for key, val in seeks.items():
            seeks_file.write(f"{key} {val}\n")
        for key, val in average_data.items():
            average_file.write(f"{key} {val}\n")
        seeks_file.close()
        average_file.close()
    
    MIN_SIZE = 10000 - 9000
    MAX_SIZE = 10000 + 9000
    print("Finished non mtf bloom")
    
    for arg in files:
        name = arg.split('.')[0]

        seeksH = {}
        average_dataH = {}


        for i in range(MIN_SIZE, MAX_SIZE):
            if(i%100 == 0):
                # Change this to the path to you
                file_name = f"{copora}/{arg}"
                file1 = open(f"data/{name}statsH.txt", "a")  # append mode
                os.system(f"./banhammer -s -t {i} <{file_name} >> data/{name}statsH.txt")
                # Not sure if I need to close the file here or not
                file1.close()
                file1 = open(f"data/{name}hashT.txt", "a")
                file1.write(f"HashTable: {i}\n")
                file1.close()

        dataH = open(f"data/{name}statsH.txt", 'r')
        hashT = open(f"data/{name}hashT.txt", 'r')
        i = dataH.readline()
        j = hashT.readline()
        while i:
            j = j.split()[1]
            #Index of seeks and average
            seeksH[j] = i.split()[1]
            average_dataH[j] = dataH.readline().split()[3]
            #Throw away next 2 lines
            dataH.readline().split()[3]
            dataH.readline().split()[3]
            i = dataH.readline()
            j = hashT.readline()

        seeks_file = open(f"data/{name}seeksH.dat", 'a')
        average_file = open(f"data/{name}averageH.dat", 'a')
        for key, val in seeksH.items():
            seeks_file.write(f"{key} {val}\n")
        for key, val in average_dataH.items():
            average_file.write(f"{key} {val}\n")
        seeks_file.close()
        average_file.close()

    print("Finished nonmtf hash")
    files = ["bibleMTF.txt"]
    MIN_SIZE = 1048576 - 1000000
    MAX_SIZE = 1048576
    for arg in files:
        name = arg.split('.')[0]

        seeksM = {}
        average_dataM = {}


        for i in range(MIN_SIZE, MAX_SIZE):
            if(i%10000 == 0):
                # Change this to the path to you
                file_name = f"{copora}/{arg}"
                file1 = open(f"data/{name}statsM.txt", "a")  # append mode
                os.system(f"./banhammer -m -s -f {i} <{file_name} >> data/{name}statsM.txt")
                # Not sure if I need to close the file here or not
                file1.close()
                file1 = open(f"data/{name}bloomM.txt", "a")
                file1.write(f"Bloom: {i}\n")
                file1.close()

        dataM = open(f"data/{name}statsM.txt", 'r')
        bloomM = open(f"data/{name}bloomM.txt", 'r')
        i = dataM.readline()
        j = bloomM.readline()
        while i:
            j = j.split()[1]
            #Index of seeks and average
            seeksM[j] = i.split()[1]
            average_dataM[j] = dataM.readline().split()[3]
            #Throw away next 2 lines
            dataM.readline().split()[3]
            dataM.readline().split()[3]
            i = dataM.readline()
            j = bloomM.readline()

        seeks_file = open(f"data/{name}seeksM.dat", 'a')
        average_file = open(f"data/{name}averageM.dat", 'a')
        for key, val in seeksM.items():
            seeks_file.write(f"{key} {val}\n")
        for key, val in average_dataM.items():
            average_file.write(f"{key} {val}\n")
        seeks_file.close()
        average_file.close()
    
    MIN_SIZE = 10000 - 9000
    MAX_SIZE = 10000 + 9000
    print("Finished mtf bloom")
    for arg in files:
        name = arg.split('.')[0]

        seeksHM = {}
        average_dataHM = {}


        for i in range(MIN_SIZE, MAX_SIZE):
            if(i%100 == 0):
                # Change this to the path to you
                file_name = f"{copora}/{arg}"
                file1 = open(f"data/{name}statsHM.txt", "a")  # append mode
                os.system(f"./banhammer -m -s -t {i} <{file_name} >> data/{name}statsHM.txt")
                # Not sure if I need to close the file here or not
                file1.close()
                file1 = open(f"data/{name}hashTM.txt", "a")
                file1.write(f"HashTable: {i}\n")
                file1.close()

        dataHM = open(f"data/{name}statsHM.txt", 'r')
        hashTM = open(f"data/{name}hashTM.txt", 'r')
        i = dataHM.readline()
        j = hashTM.readline()
        while i:
            j = j.split()[1]
            #Index of seeks and average
            seeksHM[j] = i.split()[1]
            average_dataHM[j] = dataHM.readline().split()[3]
            #Throw away next 2 lines
            dataHM.readline().split()[3]
            dataHM.readline().split()[3]
            i = dataHM.readline()
            j = hashTM.readline()

        seeks_file = open(f"data/{name}seeksHM.dat", 'a')
        average_file = open(f"data/{name}averageHM.dat", 'a')
        for key, val in seeksHM.items():
            seeks_file.write(f"{key} {val}\n")
        for key, val in average_dataHM.items():
            average_file.write(f"{key} {val}\n")
        seeks_file.close()
        average_file.close()
    print("Finished mtf hash")
    
files = ["bible.txt"]
os.system(plotinfo("Seeks vs BloomFilter Size", "seeks"))
os.system(plotinfo("Average Seek length vs BloomFilter size", "average"))
os.system(plotinfo("Seeks vs HashTable Size", "seeksH"))
os.system(plotinfo("Average Seek length vs HashTable size", "averageH"))
files = ["bibleMTF.txt"]
os.system(plotinfo("Seeks vs BloomFilter Size (MTF)", "seeksM"))
os.system(plotinfo("Average Seek length vs BloomFilter size (MTF)", "averageM"))
os.system(plotinfo("Seeks vs HashTable Size (MTF)", "seeksHM"))
os.system(plotinfo("Average Seek length vs HashTable size (MTF)", "averageHM"))
