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
Write functions for the calculations, read in file data, write out file data, make a menu, display information

Program:
'''
FILENAME = "database.txt"

def edit_database():
	while True:
		choice = input("\nDATABASE EDITOR\n\t[1]. Add a client\n\t[2]. Delete a client\n\t[3]. View client data\n\t[4]. Save and go back\n") #database options
		if choice == "1":
			file = open(FILENAME, "a")
			
			user_name = input("Enter the client to add: ")
			sex = input("Enter the client's sex: ")
			age = input("Enter the client's age: ")
			weight = input("Enter the client's weight(pounds): ")
			height = input("Enter the client's height(inches): ")
			fitness_level = input("Enter the client's fitness level(1 for sedentary, 2 for lightly active, 3 for moderately, 4 for very active, 5 for extra active):")
			
			file.write("{},{},{},{},{},{},\n".format(user_name, sex, age, weight, height, fitness_level))
			file.close()
			
		elif choice == "2":
			file = open(FILENAME, "r") #writes all lines except the one with the client name to delete
			lines = file.readlines()
			file.close()
			
			req_name = input("Enter the client to delete: ")
			
			file = open(FILENAME, "w")
			for line in lines:
				if len(line.strip()) != 0:
					joined_line = line.split(",")
					if joined_line[0] != req_name:
						file.write(line)
					else:
						print(req_name + " found and deleted.")
			file.close()
			
		elif choice == "3":
			file = open(FILENAME, "r")#reads lines and neatly prints to screen
			lines = file.readlines()
			for line in lines:
				joined_line = line.split(",")
				print("Name: {}, Sex: {}, Age: {}, Weight: {}, Height: {}, Fitness Level: {}".format(joined_line[0], joined_line[1], joined_line[2], joined_line[3], joined_line[4], joined_line[5]))
			file.close()
		
		elif choice == "4":
			break

def pull_info(name):
	file = open(FILENAME, "r")
	lines = file.readlines()
	for line in lines:
		if len(line.strip()) != 0:
			joined_line = line.split(",") #searches the file and returns the list of info with client's name
			if joined_line[0] == name:
				return joined_line
	return None

def get_bmr(info): #bmr calculations
	name = info[0]
	sex = info[1]
	age = info[2]
	weight = info[3]
	height = info[4]
	
	if sex.lower().strip() == "male":
		bmr = 66 + (6.23 * float(weight)) + (12.7 * float(height)) - (6.8 * float(age)) #BMR male
	elif sex.lower().strip() == "female":
		bmr = 655 + (4.35 * float(weight)) + (12.7 * float(height)) - (4.7 * float(age)) # BMR FEmale
	else:
		print("The client's sex is invalid")
		bmr = None
	
	if bmr:
		bmr = round(bmr, 3)
	return bmr

def get_caloric_info(info): #caloric calculations
	activity = info[5]
	bmr = get_bmr(info)
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
		print("The client's activity level is invalid")
		calories = None
	
	if calories:
		calories = round(calories, 3)
	return calories

def get_menu():# prints the menu, adds up user's selected items in terms of calories and fat
	food = {"French Fries": [570, 30], "Onion Rings":[350, 16], "Hamburger":[670, 39], "Cheeseburger":[760, 47],  #dict, key = name of food value = list elm 0 = calories elm 1 = fat(g)
			"Grilled Chicken":[420, 10], "Egg Biscuit":[300, 12], "Mozzerella Sticks":[849, 56], 
			"Cheese Pizza":[300, 11], "Macaroni and Cheese":[300, 11], "Glazed Chicken and Veggies":[497, 7]}
	calories = 0
	fat = 0
	choices = []

	while 1:
		print("\n\nFOOD MENU\n")
		print("Food Item\tCalories\tFat(g)\n")
		for key, value in food.items():
			print(key + "\t" + str(value[0]) + "\t" + str(value[1]))
		choice = input("\nEnter the name of a food item you would like to add to your meal plan (enter \"1\" when finished): ")
		if choice == "1":
			break
		else:
			for key, value in food.items():
				if choice == key:
					calories += value[0]
					fat += value[1]
	print("Total calories: " + str(calories) + "\nTotal fat(g): " + str(fat))
	choices.append(calories)
	choices.append(fat)
	return choices

print("Welcome to the Dietition program!") #introduction
try: #check for file existance
	file = open(FILENAME, "r")
	print(FILENAME + " already exists, opening...")
	file.close()
except:
	print(FILENAME + " does not exist, creating...") #if the file does not exist, creats it with FILENAME
	file = open(FILENAME, "w")
	file.close()


while True:
	choice = input("\nMAIN MENU\n\nWould you like to: \n\t[1]. Edit / Browse the database\n\t[2]. Continue with the client name\n\t[3]. Exit\n")
	if choice == "1":
		edit_database()
	elif choice == "2":
		client_name = input("Enter the client name: ")
		client_info = pull_info(client_name)
		if not client_info:
			print("The client could not be found in the database")
			continue
		
		client_bmr = get_bmr(client_info)
		client_calories = get_caloric_info(client_info)
		print("\nCLIENT INFO\n")
		print("The client's BMR is: " + str(client_bmr))
		print("The client's daily caloric intake should be " + str(client_calories) + " calories.")
		print("The client's daily fat caloric intake should be " + str(round((client_calories * 0.2), 3)) + " to " + str(round((client_calories * 0.3), 3)) + " calories.") #doing percent calculations, rounding to 3rd place
		print("The client's daily fat caloric intake in grams should be " + str(round(((client_calories * 0.2) / 9), 3)) + " to " + str(round(((client_calories * 0.3) / 9), 3)) + " grams.")
		
		while True:
			c = input("\nWould the client like to lose weight?\n\t[1]. Yes\n\t[2]. No\n")
			if c == "1":
				reduced_calories = round((client_calories - client_calories * 0.1), 3)
				print("The client's daily caloric intake should be reduced to " + str(reduced_calories) + " calories.")
				print("The client's daily fat caloric intake should be reduced to " + str(round((reduced_calories * 0.2), 3)) + " to " + str(round((reduced_calories * 0.3), 3)) + " calories.")
				print("The client's daily fat caloric intake in grams should be " + str(round(((reduced_calories * 0.2) / 9), 3)) + " to " + str(round(((reduced_calories * 0.3) / 9), 3)) + " grams.")
				
				x = input("\n Would the client like to use the menu?\n\t[1]. Yes\n\t[2]. No\n")
				if x == "1":
					menu_choices = get_menu()#menu
				elif x == "2":
					break
				else:
					print("The choice you selected is not valid.")
				break
			elif c== "2":
				break
			else:
				print("The choice you selected is not valid.")
		
		
	elif choice == "3":
		break
	else:
		print("The choice you selected is not valid.")

