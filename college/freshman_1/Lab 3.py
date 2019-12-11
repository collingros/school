# 2
for i in range(1,3):
    for j in range(1,4):
        for k in range(1,5):
            print("*", end="")
        print("!", end="")
    print("", end="")
print("End of For Loop Test")

print("\n")

# 4 Stars, and then 1 Exclamation Point. 
# Repeat 6 times.
count = 0
while count < 6:
    count += 1
    print("****!", end= "")
    
print("End of While Loop Test")

# 3
def mystery (x):
    y = 1
    z = 0
    while 2 * y <= x:
        y *= 2
        z += 1
    print (y, z)
print("Mystery 1")
mystery(1)
print("Mystery 19")
mystery(19)
print("Mystery 74")
mystery(74)

# 4
# Pre-allocating variables for use in the while loop
minimum_int = 0
maximum_int = 0 
first_time = True
while True:
    user_int = int(input("Enter an integer or enter -1 to quit: "))
    if user_int == -1:
        break
    else:
        if first_time:
            minimum_int = user_int
            maximum_int = user_int
        else:
            if user_int > maximum_int and user_int > minimum_int:
                maximum_int = user_int
            elif user_int < minimum_int and user_int < maximum_int:
                minimum_int = user_int
        first_time = False
print("Maximum integer that was entered: ", maximum_int)
print("Minimum integer that was entered: ", minimum_int)

# 5