# script by chinmai srinivas (cssriniv)
# DO NOT REMOVE THIS COMMENT OR CHANGE THE NAME
# Please cite this somehwere

import os

times = []
os.system("make")
os.system('rm img -r; mkdir img')
plotinfo = lambda x: f'''
gnuplot <<XX
set terminal jpeg
set datafile separator " "
set output "img/{x} Swaps.jpg"
plot "img/{x}swaps.dat" with linespoints title "{x} Sort swaps"
set output "img/{x} Comps.jpg"
plot "img/{x}comps.dat" with linespoints title "{x} Sort"
XX
'''
for arg in ['b', 's', 'q', 'Q']:
    data = {}
    os.system("rm img/data.txt")
    for i in range(400):
        os.system(f"./sorting -{arg} -p0 -n{i} >> img/data.txt")



    longstuff = open("img/data.txt", 'r')
    for i in longstuff.readlines():
        if i == "\n" or "Sort" in i:
            continue
        i = i.split()
        nums = []
        for item in i:
            if item.isnumeric():
                nums.append(item)
        if len(nums) ==3:       
            data[nums[0]] = (nums[1], nums[2])
    swaps = open(f"img/{arg}swaps.dat", 'a')
    comps = open(f"img/{arg}comps.dat", 'a')
    for point in data:
        swaps.write(f"{point} {data[point][0]}\n")
        comps.write(f"{point} {data[point][1]}\n")
    swaps.close()
    comps.close()
    os.system(plotinfo(arg))