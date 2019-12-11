'''
Name: Collin Gros
Course: CS 1411
Date: 10/31/2017
Problem: Generate a random lottery ticket and compare it to the past winnings of the Texas Lotto.
Given: 2 matching numbers, $2, 3 matching $10, 4, $100, 5, $10000, 6, $100000. lotto_dict['11/14/1992'] = {13,16,22,29,32,36}
Analysis: I need to randomly generate a number, iterate through the file, iterate through the new dictionary, compare common numbers in the sets, add numbers to the winnings, print out.
Method / Algorithm: Functions (random number generator), Imports, Iterations, File Opening, Comparisons, Printing, Menu

Program:
'''
'''
Set of 5 random numbers in the range from 1 to 10
aset = set()
for i in range(0, 5):
  aset.add(random.randint(1, 10))
afile = open('afile.csv','r')
reader = csv.reader(afile)
for row in reader:
print(row)
'''
#Imports
import random
import csv
def ticketGenerator(): #RAndom generator
  intset = set()
  while len(intset) != 6:
    intset.add(random.randint(1, 54))
  return intset

def compareTicket(ticket): #Iterates through dictionary from file , compares it's commonalities to the random ticket
  lottofile = open ('lottotexas.csv', 'r')
  reader = csv.reader(lottofile)
  lottodict = {}typ
  for row in reader:
    datestr = str(row[1]) + "/" + str(row[2]) + "/" + str(row[3])
    lottovalues = {int(row[4]), int(row[5]), int(row[6]), int(row[7]), int(row[8]), int(row[9])}
    lottodict[datestr] = lottovalues
    
  winnings = 0
  price = 0
  datedict = dict()
  for key, value in lottodict.items():
    price += 6
    tempset = set(value)
    if len(ticket & tempset) == 2: #comparing the common values, adding 
      winnings += 2
      datedict[key] = 2
    elif len(ticket & tempset) == 3:
      winnings += 10
      datedict[key] = 10
    elif len(ticket & tempset) == 4:
      winnings += 100
      datedict[key] = 100
    elif len(ticket & tempset) == 5:
      winnings += 10000
      datedict[key] = 10000
    elif len(ticket & tempset) == 6:
      winnings += 100000
      datedict[key] = 100000
  print("You would have spent $" + str(price) + " on tickets from 1992 to 2017.") #Telling user
  print("You would have won $" + str(winnings) + " from tickets from 1992 to 2017.")
  #print("Winning dates with winning amount: ")
  #for key, value in datedict.items():
  #  print("Date: " + str(key))
  #  print("Winnings: " + str(value))
  
  lottofile.close()
  return datedict

'''def howoften(numdict):
  oftenlist = []
  megaset = set()
  for valueset in numdict.values():
    megaset.add(valueset)
  print(megaset)
  return oftenlist
'''
done = False
while not done: # MAin function
  userticket = ticketGenerator()
  print("Your ticket: " +  str(userticket))
  dates = compareTicket(userticket)
  
  a = input("Do you want to see the dates and winnings dictionary? (y/n)")
  if a == "y":
    print(dates)
  ans = input("Do you want to roll again (y/n)")
  if ans == "y":
    done = False
  else:
    done = True









