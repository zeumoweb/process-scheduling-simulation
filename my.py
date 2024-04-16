file = open("jobs_data22.txt", "w")

with open("jobs_data2.txt", "r") as f:
    for line in f.readlines():
        l = line.strip().split(":")
        file.write(f"{l[1].strip()}:{l[2].strip()}\n")


file.close()
        