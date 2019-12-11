'''
Collin Gros
11/29/2017

Problem:
Write a menu-based program to allow the dietician to input clients and their information. The menu should allow the dietician to enter client information, select a client, and exit the program.

Given:
English BMR (Basal Metabolic Rate) Formula
Women: BMR = 655 + ( 4.35 x weight in pounds ) + ( 4.7 x height in inches ) - ( 4.7 x age in years )
Men: BMR = 66 + ( 6.23 x weight in pounds ) + ( 12.7 x height in inches ) - ( 6.8 x age in year )

Harris Benedict Formula (Daily Calorie Need)
To determine your total daily calorie needs, multiply the BMR by the appropriate activity factor, as follows:
1. If sedentary (little or no exercise) : Calorie-Calculation = BMR x 1.2
2. If lightly active (light exercise/sports 1-3 days/week) : Calorie-Calculation = BMR x 1.375
3. If moderatetely active (moderate exercise/sports 3-5 days/week) : Calorie-Calculation = BMR x 1.55
4. If very active (hard exercise/sports 6-7 days a week) : Calorie-Calculation = BMR x 1.725
5. If extra active (very hard exercise/sports & physical job or 2x training) : Calorie-Calculation = BMR x 1.9

Foods (total calories, fat in grams)
French Fries, 570, 30
Onion Rings, 350, 16
Hamburger, 670, 39
Cheeseburger, 760, 47
Grilled Chicken Sandwich, 420, 10
Egg Biscuit, 300, 12
Mozzarella Sticks, 849, 56
Cheese Pizza, 300, 11
Macaroni and Cheese, 300, 7
Glazed Chicken and Veggies, 497, 7

Analysis:
I need to read in a file, splice it, use the info to run equations, and display the results to the user.

Method/Algorithm:
Write functions for the calculations, import a GUI system, read in file data, display information

Program:
'''
#import easygui
import csv #for file reading

def get_clients(filename="default.txt"):
	try:
		file = open(filename, 'r')
		file.close()
	except:
		print("The info file could not be found - creating \"default.txt\"") # incase file does not exist
		file = open(filename, 'w')
		file.write("")
		file.close()
	
	clients = {}
	


	while 1:
		file = open(filename, 'r')
		reader = csv.reader(file)
		print("The following clients are in the database: ")
		client_names = ""
		for row in reader:	#read in file and splice information into cilents dict  #client name, body type, weight, height, age, level of activity
			try:
				client_names += str(row[0]) + "-"
			except IndexError:
				client_names == ""
				break
		if client_names == "":
			print("The database is empty.")
		else:
			print(client_names)
		res = input("Would you like to:\n\t[C]ontinue\n\t[E]dit")
		if res == "C" or res == "c":
			file.close()
			return clients
		elif res == "E" or res == "e":
			res2 = input("Would you like to:\n\t[A]dd a client\n\t[R]emove a client")
			if res2 == "A" or res2 == "a":
				name = input("Enter the name of the client to add: ")
				sex = input("Enter the sex of the client: ")
				weight = input("Enter the weight of the client(in pounds): ")
				height = input("Enter the height of the client(in inches): ")
				age = input("Enter the age of the client: ")
				activity = input("Enter the client's activity level: \n\t[1] sedentary (little or no exercise)\n\t[2] lightly active (light exercise/sports 1-3 days/week)\n\t[3] moderately active (moderate exercise/sports 3-5 days/week)\n\t[4] very active (hard exercise/sports 6-7 days a week)\n\t[5] extra active (very hard exercise/sports & physical job or 2x training)")
				
				file.close()
				file = open(filename, 'a')
				file.write("{}, {}, {}, {}, {}, {},\n".format(name, sex, weight, height, age, activity))
				file.close()
				file = open(filename, 'r')
				reader = csv.reader(file)
				for row in reader:
					try:
						clients[row[0]] = [row[1].strip(), row[2].strip(), row[3].strip(), row[4].strip(), row[5].strip()]
					except IndexError:
						break
				#file.close()
			elif res2 == "R" or res2 == "r":
				name = input("Enter the name of the client to remove: ")
				
				file.close()
				file = open(filename, 'r')
				reader = csv.reader(file)
				row_ = None
				row_num = 0
				for row in reader:
					row_num += 1
					if row[0].strip() != name.strip():
						print("That name was not found in row {}.".format(row_num))
						continue
					else:
						print("That name was found in the database.")
						row_ = row
						print(row_)
						break
				lines = file.readlines()
				file.close()
				file = open(filename, 'w')
				for line in lines:
					if line != ','.join(row_):
						print(','.join(row_))
						print("writing line: {}".format(line))
						file.write(line + "\n")
					else:
						print("line skipped: {}".format(line))
				#file.close()

def save_clients(clients, filename="default.txt"):
	#does the opposite of get_clients and writes the data to the file
	pass

def is_valid_file(filename):
	#to check if the filename exists before writing / reading
	pass

def bmr_formula(sex, weight, height, age): #Women: BMR = 655 + ( 4.35 x weight in pounds ) + ( 4.7 x height in inches ) - ( 4.7 x age in years )
										   #Men: BMR = 66 + ( 6.23 x weight in pounds ) + ( 12.7 x height in inches ) - ( 6.8 x age in year )
	if sex == "male" or sex == "Male":
		bmr = 66 + (6.23 * float(weight)) + (12.7 * float(height)) - (6.8 * float(age))
	elif sex == "female" or sex == "Female":
		bmr = 655 + (4.35 * float(weight)) + (4.7 * float(height)) - (4.7 * float(age))
	else:
		print("error: sex \"{}\" is invalid.".format(sex))
		return
	#uses the english bmr formula and returns bmr
	
	return bmr

def calorie_need_formula(bmr, activity): #calculates daily calorie need and returns it
	bmr = int(bmr)
	if activity == "1":
		calories = bmr * 1.2
	elif activity == "2":
		calories = bmr * 1.375
	elif activity == "3":
		calories = bmr * 1.55
	elif activity == "4":
		calories = bmr * 1.725
	elif activity == "5":
		calories = bmr * 1.9
	else:
		print("error: activity \"{}\" is invalid.".format(activity))
		return
	
	return calories

def food_menu():
	food = {"French Fries": [570, 30], "Onion Rings":[350, 16], "Hamburger":[670, 39], "Cheeseburger":[760, 47], 
			"Grilled Chicken":[420, 10], "Egg Biscuit":[300, 12], "Mozzerella Sticks":[849, 56], 
			"Cheese Pizza":[300, 11], "Macaroni and Cheese":[300, 11], "Glazed Chicken and Veggies":[497, 7]} #the lists stand for calories, fat in grams
	calories = 0
	fat = 0
	print("FOOD MENU\nFood Name - Calories - Fat(g)")
	while 1:
		for key, value in food.items():
			print(key + "\t" + str(value[0]) + "\t" + str(value[1]))
		choice = input("Enter the name of a food item you would like to add to your meal plan (type \"1\" when finished): ")
		if choice == "1":
			break
		else:
			for key, value in food.items():
				if choice == key:
					calories += value[0]
					fat += value[1]

	print("Your total amount of calories in the meal plan: {}".format(str(calories)))
	print("Your total amount of fat in the meal plan: {}".format(str(fat)))
	return

print("Welcome to the Dietition Program!")

clients = get_clients()
#entering
client_name = input("Enter a client's name: ")
bmr = bmr_formula(clients[client_name][0], clients[client_name][1], clients[client_name][2], clients[client_name][3])
print("BMR is {:0.7}".format(bmr))
daily_calories = calorie_need_formula(bmr, clients[client_name][4]) #assigning bmr to clients[name][5] and calories needed to clients[name][6]
print("Daily calorie need is: {}".format(daily_calories))
dfat_calories = daily_calories / 9
print("Daily fat calorie need is from 20% ({:0.7}) to 30% ({:0.7}) of the daily calorie need\nIn fat grams from {:0.7} to {:0.7} grams daily (1 gram of fat is 9 calories)".format(0.2*daily_calories, 0.3*daily_calories, 0.2*dfat_calories, 0.3*dfat_calories))
daily_calories2 = daily_calories - daily_calories*0.1
dfat_calories2 = daily_calories2 / 9
print("To lose weight, reduce calories to 10% below daily ({})\nKeep daily fat calories from {:0.7} to {:0.7}\nIn fat grams from {:0.7} to {:0.7} grams daily".format(daily_calories2, 0.2*daily_calories2, 0.3*daily_calories2, dfat_calories2*0.2, dfat_calories2*0.3))
food_menu()
print("reminder: to lose weight, reduce calories to 10% below daily ({})\nKeep daily fat calories from {:0.7} to {:0.7}\nIn fat grams from {:0.7} to {:0.7} grams daily".format(daily_calories2, 0.2*daily_calories2, 0.3*daily_calories2, dfat_calories2*0.2, dfat_calories2*0.3))
#exiting
#input("Press RETURN to quit...")








