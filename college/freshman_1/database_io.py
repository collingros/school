FILENAME = "database.txt"

def edit_database():
	while True:
		choice = input("\nDATABASE EDITOR\n\t[1]. Add a client\n\t[2]. Delete a client\n\t[3]. View client data\n\t[4]. Save and go back\n")
		if choice == "1":
			file = open(FILENAME, "a")
			
			user_name = input("Enter the client to add: ")
			sex = input("Enter the client's sex: ")
			age = input("Enter the client's age: ")
			weight = input("Enter the client's weight(pounds): ")
			height = input("Enter the client's height(inches): ")
			fitness_level = input("Enter the client's fitness level(1 for ):")
			
			file.write("{},{},{},{},{},{},\n".format(user_name, sex, age, weight, height, fitness_level))
			file.close()
			
		elif choice == "2":
			file = open(FILENAME, "r")
			lines = file.readlines()
			file.close()
			
			req_name = input("Enter the client to delete: ")
			
			file = open(FILENAME, "a")
			for line in lines:
				print("foor")
				if len(line.strip()) != 0:
					joined_line = line.split(",")
					print(req_name)
					print(joined_line[0])
					if joined_line[0] != req_name:
						file.write(line)
					else:
						print(req_name + " found and deleted.")
			file.close()
			
		elif choice == "3":
			file = open(FILENAME, "r")
			lines = file.readlines()
			for line in lines:
				joined_line = line.split(",")
				print("Name: {}, Sex: {}, Age: {}, Weight: {}, Height: {}, Fitness Level: {}".format(joined_line[0], joined_line[1], joined_line[2], joined_line[3], joined_line[4], joined_line[5]))
			file.close()
		
		elif choice == "4":
			break

def pull_info(name):
	return

print("Welcome to the Dietition program!")
try:
	file = open(FILENAME, "r")
	print(FILENAME + " already exists, opening...")
	file.close()
except:
	print(FILENAME + " does not exist, creating...")
	file = open(FILENAME, "w")
	file.close()


while True:
	choice = input("Would you like to: \n\t[1]. Edit / Browse the database\n\t[2]. Continue with the client name\n")
	if choice == "1":
		edit_database()
	elif choice == "2":
		break
	else:
		print("The choice you selected is not valid.")

#Collin Gros, male, 18, 170, 67, 2

