'''
ord("") - #
chr() - char
secret_message.py

take user input message
'''

def encrypt():
  message = input("Enter a message to be encrypted: ")
  text = list(message)
  ascii = []
  for i in text:
    cnum = ord(i)
    ascii.append(cnum)
  print("Encrypted: ")
  for i in range(0, len(ascii)):
    print(ascii[i], end="")
  print("")

def decrypt():
  message = input("Enter a message to be decrypted: ")
  text = list(message)
  #print(text)
  ascii = []
  i = 0
  #print(len(text) - 1)
  while i < (len(text) - 1):
    if text[i] == "1":
      second = text[i + 1]
      third = text[i + 2]
      char = chr(int(text[i] + second + third))
      ascii.append(char)
      i += 3
    elif text[i] in ["2", "3", "4", "5", "6", "7", "8", "9", "10"]:
      second = text[i + 1]
      char = chr(int(text[i] + second))
      ascii.append(char)
      i += 2
    else:
      print("Invalid ascii value")
      i += 1
  print("Decrypted:")
  for i in range(0, len(ascii)):
    print(ascii[i], end="")
  print("")
  
done = False
print("Menu: ")
print("\t Encrypt[1]")
print("\t Decrypt[2]")
print("\t Exit[3]")
while not done:
  print("Enter your menu response: ")
  ans =input("")
  if ans == "1":
    encrypt()
  elif ans == "2":
    decrypt()
  elif ans == "3":
    done = True
  else:
    pass



