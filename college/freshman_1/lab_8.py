'''#1
names = ['joe', 'tom', 'barb', 'sue', 'sally']
scores = [10, 23, 13, 18, 12]

def makeDictionary(list1, list2):
  mydict = {}
  for i in range (0, len(list1)):
    mydict[list1[i]] = list2[i]
  return mydict

scoreDict = makeDictionary(names, scores)
print(scoreDict)
#2
scoreDict['john'] = 19
sortedList = []
for name, score in scoreDict.items():
  sortedList.append(score)
print(sortedList)

avg = 0
for elm in sortedList:
  avg += float(elm)
avg = avg / len(sortedList)
print("avg: " + str(avg))
scoreDict['sally'] = 13
print("before: ")
print(scoreDict)
scoreDict.pop('john', None)
print("after: ")
print(scoreDict)

countryDict = {}
name = input("Enter the name of the country: ")
countryDict[name] = None
capital = input("Enter the name of the capital: ")
countryDict[name] = capital
name = input("Enter the name of the country: ")
countryDict[name] = None
capital = input("Enter the name of the capital: ")
countryDict[name] = capital
print(countryDict)
alpha = sorted(countryDict.values())
print(alpha)
'''









